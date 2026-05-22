// https://www.open-std.org/JTC1/SC22/WG21/docs/papers/2026/p3856r5.pdf
//  15.05.2026

#include <iostream>
#include <meta>

// Forward-declare so we can recurse.
namespace proposed {
consteval bool is_structural_type(std::meta::info);
}

namespace detail {

// Strip top-level cv, but not references (rvalue refs are *not* structural).
consteval std::meta::info canonicalize(std::meta::info t) {
  return remove_cv(dealias(t));
}

// Peel one array extent; P2996 has array transforms in
// [meta.reflection.trans.arr].
consteval std::meta::info remove_one_extent(std::meta::info t) {
  return remove_extent(t);
}

consteval bool is_array_of_structural_types(std::meta::info t) {
  t = canonicalize(t);

  if (!is_array_type(t)) return false;

  // Recursively strip all extents, then check the element type
  std::meta::info elem = t;
  while (is_array_type(elem)) {
    elem = remove_one_extent(elem);
  }
  return proposed::is_structural_type(canonicalize(elem));
}

// Return false if any direct base is not public *or* its type isn’t structural.
consteval bool bases_ok(std::meta::info t) {
  constexpr auto unchecked = std::meta::access_context::unchecked();
  for (std::meta::info rel : bases_of(t, unchecked)) {
    if (!is_public(rel)) return false;  // declared access
    std::meta::info rel_type = type_of(rel);

    // recursive check
    if (!proposed::is_structural_type(canonicalize(rel_type))) return false;
  }
  return true;
}

// Return false if any nsdm is not public or is mutable, or its type isn’t
// structural/array-of-structural.
consteval bool data_members_ok(std::meta::info t) {
  constexpr auto unchecked = std::meta::access_context::unchecked();
  for (std::meta::info m : nonstatic_data_members_of(t, unchecked)) {
    if (!is_accessible(m, unchecked)) return false;

    if (!is_public(m)) return false;

    if (is_mutable_member(m)) return false;

    std::meta::info MT = type_of(m);

    if (is_array_type(MT)) {
      if (!is_array_of_structural_types(MT)) return false;
    } else {
      if (!proposed::is_structural_type(canonicalize(MT))) return false;
    }
  }
  return true;
}

// Forward declaration for mutual recursion.
consteval bool is_literal_type(std::meta::info type,
                               std::meta::access_context ctx);

// Helper: at least one variant member of a union is a non-volatile literal
// type. (Empty unions are allowed by DR 2598.)
consteval bool union_has_literal_variant(std::meta::info union_type,
                                         std::meta::access_context ctx) {
  auto ms = nonstatic_data_members_of(union_type, ctx);

  if (ms.empty()) return true;  // union with 0 variant members

  for (auto m : ms) {
    if (!is_accessible(m, ctx)) return false;

    std::meta::info mt = dealias(type_of(m));
    if (!is_volatile_type(mt) && is_literal_type(mt, ctx)) {
      return true;
    }
  }
  return false;
}

// Helper: check “all bases and non-static data members are non-volatile literal
// types”, and enforce the “anonymous union has a literal variant” rule for
// classes with anon unions.
consteval bool class_members_are_literal(
    std::meta::info class_type,
    std::meta::access_context ctx = std::meta::access_context::unchecked()) {
  // Bases
  for (auto b : bases_of(class_type, ctx)) {
    std::meta::info bt = dealias(type_of(b));
    if (is_volatile_type(bt) || !is_literal_type(bt, ctx)) {
      return false;
    }
  }
  // Non-static data members
  for (auto m : nonstatic_data_members_of(class_type, ctx)) {
    if (!is_accessible(m, ctx)) return false;

    std::meta::info mt = dealias(type_of(m));

    // Anonymous union members need a special check (P2996 exposes
    // has_identifier + union test).
    if (is_union_type(mt) && !has_identifier(m)) {
      if (!union_has_literal_variant(mt, ctx)) {
        return false;
      }
      continue;
    }

    if (is_volatile_type(mt) || !is_literal_type(mt, ctx)) {
      return false;
    }
  }
  return true;
}

// Probe for “constexpr destructor when default constructible” using
// substitution.
template <class T, class = void>
constexpr bool __has_constexpr_dtor_if_default = false;

template<class T>
constexpr bool __has_constexpr_dtor_if_default<
  T,
  // This requires both a constexpr default construction *and* that the destructor
  // is permitted in constant evaluation, which implies a constexpr destructor.
  decltype( []{
    constexpr T t{}; // ok only if T is literal *and* its dtor is constexpr
    (void)t;
  }(), void() )
> = true;

consteval bool is_literal_type(
    std::meta::info type, std::meta::access_context ctx /* = unchecked */) {
  type = dealias(type);

  // Primary cases
  if (is_void_type(type)) return true;
  if (is_reference_type(type)) return true;
  if (is_scalar_type(type)) return true;

  // Arrays: literal iff the element type is literal.
  if (is_array_type(type)) {
    return is_literal_type(remove_all_extents(type), ctx);
  }

  // Unions: aggregate union with a literal variant (or empty union) and
  // non-volatile members.
  if (is_union_type(type)) {
    if (!is_aggregate_type(type))
      return false;  // matches the “aggregate union” bullet
    return union_has_literal_variant(type, ctx);
  }

  // Class types: check members/bases first.
  if (is_class_type(type)) {
    if (!class_members_are_literal(type, ctx)) {
      return false;
    }

    // Destructor condition: C++20+ requires a constexpr destructor (trivial
    // counts). P2996R13 doesn't expose “is this function constexpr?” for
    // destructors, so we implement a conservative check:
    //  - accept trivially-destructible (always OK);
    //  - otherwise, *attempt* to verify a constexpr destructor in the
    //  default-constructible case
    //    via a substitution probe (__has_constexpr_dtor_if_default).
    if (!is_trivially_destructible_type(type)) {
      bool ok = false;
      // Try the default-constructible constexpr-dtor probe.
      // (If T isn't default-constructible but still has a constexpr dtor, we
      // can't detect it.)
      ok = extract<bool>(
          substitute(^^__has_constexpr_dtor_if_default, {
                                                            type}));
      if (!ok)
        return false;  // conservative: fail if we cannot prove constexpr dtor
    }

    // Final disjunct for class types:
    //   * aggregates are fine (no need to find a constexpr ctor explicitly),
    //   * otherwise the standard allows “has at least one constexpr
    //   non-copy/move ctor”
    //     or “lambda type”. P2996R13 doesn’t yet expose “is this constructor
    //     constexpr?” nor “is this a lambda closure type?”, so be conservative
    //     and only accept aggregates.
    if (is_aggregate_type(type)) {
      return true;
    }

    // Without constructor-constexpr/lambda queries, we can't soundly accept
    // non-aggregate classes here. Be conservative.
    return false;
  }

  // Everything else (functions, etc.) — not literal.
  return false;
}

consteval bool is_literal_class_type(std::meta::info t,
                                     std::meta::access_context ctx) {
  if (!(is_class_type(t) || is_union_type(t))) return false;

  return is_literal_type(t, ctx);
}
}  // namespace detail

consteval bool proposed::is_structural_type(std::meta::info t0) {
  // Ok to use unchecked access context, per LEWG Jan '26 telecon.
  constexpr auto ctx = std::meta::access_context::unchecked();

  // 1) lvalue reference types are structural (top-level cv is ignored)
  if (is_lvalue_reference_type(t0)) {
    return true;
  }

  // Work with cv‑stripped, de-aliased type for the rest
  std::meta::info t = detail::canonicalize(t0);

  // 2) scalar types are structural
  if (is_scalar_type(t)) {
    return true;
  }

  // 3) literal class/union with the “public & non‑mutable &
  // structural-or-array-of-structural” condition
  if (is_class_type(t) || is_union_type(t)) {
    if (!detail::is_literal_class_type(t, ctx)) {
      return false;
    }

    return detail::bases_ok(t) && detail::data_members_ok(t);
  }

  // Other kinds (function types, arrays as such, rvalue refs, etc.) are not
  // structural
  return false;
}

struct S {
 public:
  int x;
};
struct Bad1 {
 private:
  int x;
};
struct Bad2 {
 public:
  mutable int x;
};
struct A {
 public:
  int a[2][3];
};
struct B : public S {};   // OK: public base of structural type
struct C : private S {};  // not structural: private base

static_assert(proposed::is_structural_type(^^int));
static_assert(proposed::is_structural_type(^^int&));
static_assert(
    !proposed::is_structural_type(^^int&&));  // rvalue ref is not structural
static_assert(proposed::is_structural_type(^^S));
static_assert(!proposed::is_structural_type(^^Bad1));
static_assert(!proposed::is_structural_type(^^Bad2));
static_assert(proposed::is_structural_type(^^A));
static_assert(proposed::is_structural_type(^^B));
static_assert(!proposed::is_structural_type(^^C));

int main() {
  std::cout << std::endl;
  return 0;
}
