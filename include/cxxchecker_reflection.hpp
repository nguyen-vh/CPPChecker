// Copyright (c) 2026-present Hoang Nguyen
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its
//    contributors may be used to endorse or promote products derived from
//    this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

//----------------------------------------------------------------------------//

#ifndef CXXCHECKER_REFLECTION_HPP
#define CXXCHECKER_REFLECTION_HPP

//----------------------------------------------------------------------------//
//*                             === INCLUDES ===                             *//
//----------------------------------------------------------------------------//

#include <iostream>
#include <meta>
#include <string_view>
#include <type_traits>

//----------------------------------------------------------------------------//
//*                         === LIST OF CONTENT ===                          *//
//----------------------------------------------------------------------------//

//
//* bool has_class<>
//  |
//* |>   bool class_has_membervar<>
//  |     - bool class_has_public_membervar<>
//  |     - bool class_has_protected_membervar<>
//  |     - bool class_has_private_membervar<>
//  |
//  |
//* |>  bool class_has_static_membervar<>
//  |     - bool class_has_public_static_membervar<>
//  |     - bool class_has_protected_static_membervar<>
//  |     - bool class_has_private_static_membervar<>
//  |
//  |
//* |>  bool class_has_memberfunc<>
//  |     - bool class_has_public_memberfunc<>
//  |     - bool class_has_protected_memberfunc<>
//  |     - bool class_has_private_memberfunc<>
//  |
//  |
//* |>  bool class_has_static_memberfunc<>
//  |     - bool class_has_public_static_memberfunc<>
//  |     - bool class_has_protected_static_memberfunc<>
//  |     - bool class_has_private_static_memberfunc<>
//

//----------------------------------------------------------------------------//

//
//* bool has_free_variable<>
//
//* bool has_free_static_variable<>
//
//* bool has_free_function<>
//
//* bool has_free_static_function<>
//
//  TODO: FINAL CLASS, TEMPLATE CLASS
//

//----------------------------------------------------------------------------//

// TODO: VIRTUAL; OVERRIDE; FINAL

//----------------------------------------------------------------------------//

// TODO: Use has_template_arguments and template_arguments_of

//! MEMBER FUNCTION TEMPLATES

//! FUNCTION TEMPLATES

//! CLASS TEMPLATES

//! CONVERSION FUNCTION TEMPLATES

//! OPERATOR FUNCTION TEMPLATES

//! LITERAL OPERATOR TEMPLATES

//! CONSTRUCTION FUNCTION TEMPLATES

//! CONCEPTS

//----------------------------------------------------------------------------//

//

//----------------------------------------------------------------------------//
//*                       === HELPER TEMPLATES ===                           *//
//----------------------------------------------------------------------------//

template <std::size_t N>
struct LiteralString {
  consteval LiteralString(const char (&s)[N]) { std::copy(s, s + N, &data[0]); }
  consteval operator std::string_view() const { return {data, data + N - 1}; }

  static constexpr std::size_t size = N;
  char data[N]{};
};

template <LiteralString LS>
constexpr auto operator""_ls() {
  return LS;
}

template <LiteralString Class>
consteval auto get_class_by_name() -> std::meta::info {
  std::string_view full_name{Class};
  auto scope = ^^::;

  while (!full_name.empty()) {
    auto pos = full_name.find("::");
    bool b_last_pos = (pos == std::string_view::npos);
    std::string_view part_of_name =
        b_last_pos ? full_name : full_name.substr(0, pos);
    if (part_of_name.empty()) break;

    bool b_found = false;
    auto members =
        std::meta::members_of(scope, std::meta::access_context::unchecked());

    for (const auto& member : members) {
      if (std::meta::has_identifier(member) &&
          std::meta::identifier_of(member) == part_of_name) {
        if (b_last_pos) {
          if (!std::meta::is_type(member)) continue;
          if (!std::meta::is_class_type(member)) continue;

          return member;
        }

        if (std::meta::is_namespace(member)) {
          scope = member;
          b_found = true;

          break;
        }

        return {};
      }
    }

    if (!b_found) return {};

    full_name.remove_prefix(b_last_pos ? full_name.size() : pos + 2);
  }
  return {};
}

struct unspecified_return_t {};

//----------------------------------------------------------------------------//
//*                          === has_class<> ===                             *//
//----------------------------------------------------------------------------//

template <LiteralString ClassName>
concept has_class = (get_class_by_name<ClassName>() != std::meta::info{});

//----------------------------------------------------------------------------//
//*                      === class_has_membervar<> ===                       *//
//----------------------------------------------------------------------------//

template <LiteralString Class, LiteralString Membervar,
          typename Type = unspecified_return_t>
concept class_has_membervar = []() {
  if (!has_class<Class>) return false;

  auto members = std::meta::members_of(get_class_by_name<Class>(),
                                       std::meta::access_context::unchecked());

  for (const auto& member : members) {
    if (!std::meta::is_nonstatic_data_member(member)) continue;

    if (std::meta::has_identifier(member) &&
        std::meta::identifier_of(member) != std::string_view(Membervar))
      continue;

    if (std::meta::has_identifier(member)) {
      if constexpr (std::is_same_v<Type, unspecified_return_t>)
        return true;
      else if (std::meta::type_of(member) == ^^Type)
        return true;
    }
  }
  return false;
}();

//----------------------------------------------------------------------------//
//*                     === class_has_memberfunc<> ===                       *//
//----------------------------------------------------------------------------//

//? Also works for const

template <LiteralString Class, LiteralString Memberfunc,
          typename Returntype = unspecified_return_t, typename... Inputtype>
concept class_has_memberfunc = []() {
  if (!has_class<Class>) return false;

  auto members = std::meta::members_of(get_class_by_name<Class>(),
                                       std::meta::access_context::unchecked());

  for (const auto& member : members) {
    if (!std::meta::is_function(member)) continue;

    if (std::meta::has_identifier(member) &&
        (std::meta::identifier_of(member) != std::string_view(Memberfunc)))
      continue;

    if (std::meta::has_identifier(member)) {
      if constexpr (std::is_same_v<Returntype, unspecified_return_t>) {
        return true;
      } else if constexpr (sizeof...(Inputtype) != 0) {
        if (std::meta::type_of(member) == ^^Returntype(Inputtype...))
          return true;
      } else if (std::meta::return_type_of(member) == ^^Returntype)
        return true;
    }
  }
  return false;
}();

//----------------------------------------------------------------------------//
//*                   === class_has_static_memberfunc ===                    *//
//----------------------------------------------------------------------------//

template <LiteralString Class, LiteralString Memberfunc,
          typename Returntype = unspecified_return_t, typename... Inputtype>
concept class_has_static_memberfunc = []() {
  if (!has_class<Class>) return false;

  auto members = std::meta::members_of(get_class_by_name<Class>(),
                                       std::meta::access_context::unchecked());

  for (const auto& member : members) {
    if (!std::meta::is_static_member(member)) continue;
    if (!std::meta::is_function(member)) continue;

    if (std::meta::has_identifier(member) &&
        (std::meta::identifier_of(member) != std::string_view(Memberfunc)))
      continue;

    if (std::meta::has_identifier(member)) {
      if constexpr (std::is_same_v<Returntype, unspecified_return_t>)
        return true;
      if constexpr (sizeof...(Inputtype) != 0) {
        if (std::meta::type_of(member) == ^^Returntype(Inputtype...))
          return true;

        if (std::meta::return_type_of(member) == ^^Returntype) return true;
      }
    }
  }
  return false;
}();

//----------------------------------------------------------------------------//
//*                   === class_has_static_membervar<> ===                   *//
//----------------------------------------------------------------------------//

template <LiteralString Class, LiteralString Membervar,
          typename Type = unspecified_return_t>
concept class_has_static_membervar = []() {
  if (!has_class<Class>) return false;

  auto members = std::meta::members_of(get_class_by_name<Class>(),
                                       std::meta::access_context::unchecked());

  for (const auto& member : members) {
    if (!std::meta::is_static_member(member)) continue;
    if (!std::meta::is_variable(member)) continue;

    if (std::meta::has_identifier(member) &&
        std::meta::identifier_of(member) != std::string_view(Membervar))
      continue;

    if (std::meta::has_identifier(member)) {
      if constexpr (std::is_same_v<Type, unspecified_return_t>) return true;
      if (std::meta::type_of(member) == ^^Type) return true;
    }
  }
  return false;
}();

//----------------------------------------------------------------------------//
//*                        === has_free_function<> ===                       *//
//----------------------------------------------------------------------------/
// TODO: in namespace scope too

template <LiteralString Memberfunc, typename Returntype = unspecified_return_t,
          typename... Inputtype>
concept has_free_function = []() {
  auto global_namespace = ^^::;
  auto members = std::meta::members_of(global_namespace,
                                       std::meta::access_context::current());

  for (const auto& member : members) {
    if (!std::meta::is_function(member)) continue;

    if (std::meta::has_identifier(member) &&
        (std::meta::identifier_of(member) != std::string_view(Memberfunc)))
      continue;

    if (std::meta::has_identifier(member)) {
      if constexpr (std::is_same_v<Returntype, unspecified_return_t>)
        return true;
      else if constexpr (sizeof...(Inputtype) != 0) {
        if (std::meta::type_of(member) == ^^Returntype(Inputtype...))
          return true;
      } else {
        if (std::meta::return_type_of(member) == ^^Returntype) return true;
      }
    }
  }
  return false;
}();

//----------------------------------------------------------------------------//
//*                        === has_free_variable<> ===                       *//
//----------------------------------------------------------------------------//

// TODO: in namespace scope too

template <LiteralString Membervar, typename Type = unspecified_return_t>
concept has_free_variable = []() {
  auto global_namespace = ^^::;
  auto members = std::meta::members_of(global_namespace,
                                       std::meta::access_context::current());

  for (const auto& member : members) {
    if (!std::meta::is_variable(member)) continue;

    if (std::meta::has_identifier(member) &&
        std::meta::identifier_of(member) != std::string_view(Membervar))
      continue;

    if (std::meta::has_identifier(member)) {
      if constexpr (std::is_same_v<Type, unspecified_return_t>) {
        return true;
      } else if (std::meta::type_of(member) == ^^Type)
        return true;
    }
  }
  return false;
}();

//----------------------------------------------------------------------------//
//*                     === has_free_static_function<> ===                   *//
//----------------------------------------------------------------------------//

// TODO: in namespace scope too

template <LiteralString Memberfunc, typename Returntype = unspecified_return_t,
          typename... Inputtype>
concept has_free_static_function = []() {
  auto global_namespace = ^^::;
  auto members = std::meta::members_of(global_namespace,
                                       std::meta::access_context::current());

  for (const auto& member : members) {
    if (!std::meta::has_internal_linkage(member)) continue;

    if (!std::meta::is_function(member)) continue;

    if (std::meta::has_identifier(member) &&
        (std::meta::identifier_of(member) != std::string_view(Memberfunc)))
      continue;

    if (std::meta::has_identifier(member)) {
      if constexpr (std::is_same_v<Returntype, unspecified_return_t>) {
        return true;
      } else if constexpr (sizeof...(Inputtype) != 0) {
        if (std::meta::type_of(member) == ^^Returntype(Inputtype...))
          return true;
      } else {
        if (std::meta::return_type_of(member) == ^^Returntype) return true;
      }
    }
  }
  return false;
}();

//----------------------------------------------------------------------------//
//*                      === has_free_static_variable<> ===                  *//
//----------------------------------------------------------------------------//

// TODO: in namespace scope too

template <LiteralString Membervar, typename Type = unspecified_return_t>
concept has_free_static_variable = []() {
  auto global_namespace = ^^::;
  auto members = std::meta::members_of(global_namespace,
                                       std::meta::access_context::current());

  for (const auto& member : members) {
    if (!std::meta::has_internal_linkage(member)) continue;
    if (!std::meta::is_variable(member)) continue;

    if (std::meta::has_identifier(member) &&
        std::meta::identifier_of(member) != std::string_view(Membervar))
      continue;

    if (std::meta::has_identifier(member)) {
      if constexpr (std::is_same_v<Type, unspecified_return_t>) {
        return true;
      } else if (std::meta::type_of(member) == ^^Type)
        return true;
    }
  }
  return false;
}();

//----------------------------------------------------------------------------//
//*                     === class_has_public_memberfunc<> =                  *//
//----------------------------------------------------------------------------//

template <LiteralString Class, LiteralString Memberfunc,
          typename Returntype = unspecified_return_t, typename... Inputtype>
concept class_has_public_memberfunc = []() {
  if (!has_class<Class>) return false;

  auto members = std::meta::members_of(get_class_by_name<Class>(),
                                       std::meta::access_context::unchecked());

  for (const auto& member : members) {
    if (!std::meta::is_public(member)) continue;
    if (!std::meta::is_function(member)) continue;

    if (std::meta::has_identifier(member) &&
        (std::meta::identifier_of(member) != std::string_view(Memberfunc)))
      continue;

    if (std::meta::has_identifier(member)) {
      if constexpr (std::is_same_v<Returntype, unspecified_return_t>) {
        return true;
      } else if constexpr (sizeof...(Inputtype) != 0) {
        if (std::meta::type_of(member) == ^^Returntype(Inputtype...))
          return true;
      } else {
        if (std::meta::return_type_of(member) == ^^Returntype) return true;
      }
    }
  }
  return false;
}();

//----------------------------------------------------------------------------//
//*                    === class_has_protected_memberfunc<> ===              *//
//----------------------------------------------------------------------------//

template <LiteralString Class, LiteralString Memberfunc,
          typename Returntype = unspecified_return_t, typename... Inputtype>
concept class_has_protected_memberfunc = []() {
  if (!has_class<Class>) return false;

  auto members = std::meta::members_of(get_class_by_name<Class>(),
                                       std::meta::access_context::unchecked());

  for (const auto& member : members) {
    if (!std::meta::is_protected(member)) continue;
    if (!std::meta::is_function(member)) continue;

    if (std::meta::has_identifier(member) &&
        (std::meta::identifier_of(member) != std::string_view(Memberfunc)))
      continue;

    if (std::meta::has_identifier(member)) {
      if constexpr (std::is_same_v<Returntype, unspecified_return_t>) {
        return true;
      } else if constexpr (sizeof...(Inputtype) != 0) {
        if (std::meta::type_of(member) == ^^Returntype(Inputtype...))
          return true;
      } else {
        if (std::meta::return_type_of(member) == ^^Returntype) return true;
      }
    }
  }
  return false;
}();

//----------------------------------------------------------------------------//
//*                    === class_has_private_memberfunc<> ===                *//
//----------------------------------------------------------------------------//

template <LiteralString Class, LiteralString Memberfunc,
          typename Returntype = unspecified_return_t, typename... Inputtype>
concept class_has_private_memberfunc = []() {
  if (!has_class<Class>) return false;

  auto members = std::meta::members_of(get_class_by_name<Class>(),
                                       std::meta::access_context::unchecked());

  for (const auto& member : members) {
    if (!std::meta::is_private(member)) continue;
    if (!std::meta::is_function(member)) continue;

    if (std::meta::has_identifier(member) &&
        (std::meta::identifier_of(member) != std::string_view(Memberfunc)))
      continue;

    if (std::meta::has_identifier(member)) {
      if constexpr (std::is_same_v<Returntype, unspecified_return_t>) {
        return true;
      } else if constexpr (sizeof...(Inputtype) != 0) {
        if (std::meta::type_of(member) == ^^Returntype(Inputtype...))
          return true;
      } else {
        if (std::meta::return_type_of(member) == ^^Returntype) return true;
      }
    }
  }
  return false;
}();

//----------------------------------------------------------------------------//
//*                === class_has_public_static_memberfunc<> ===              *//
//----------------------------------------------------------------------------//

template <LiteralString Class, LiteralString Memberfunc,
          typename Returntype = unspecified_return_t, typename... Inputtype>
concept class_has_public_static_memberfunc = []() {
  if (!has_class<Class>) return false;

  auto members = std::meta::members_of(get_class_by_name<Class>(),
                                       std::meta::access_context::unchecked());

  for (const auto& member : members) {
    if (!std::meta::is_public(member)) continue;
    if (!std::meta::is_static_member(member)) continue;
    if (!std::meta::is_function(member)) continue;

    if (std::meta::has_identifier(member) &&
        (std::meta::identifier_of(member) != std::string_view(Memberfunc)))
      continue;

    if (std::meta::has_identifier(member)) {
      if constexpr (std::is_same_v<Returntype, unspecified_return_t>)
        return true;
      if constexpr (sizeof...(Inputtype) != 0) {
        if (std::meta::type_of(member) == ^^Returntype(Inputtype...))
          return true;

        if (std::meta::return_type_of(member) == ^^Returntype) return true;
      }
    }
  }
  return false;
}();

//----------------------------------------------------------------------------//
//*               === class_has_protected_static_memberfunc<> ===            *//
//----------------------------------------------------------------------------//

template <LiteralString Class, LiteralString Memberfunc,
          typename Returntype = unspecified_return_t, typename... Inputtype>
concept class_has_protected_static_memberfunc = []() {
  if (!has_class<Class>) return false;

  auto members = std::meta::members_of(get_class_by_name<Class>(),
                                       std::meta::access_context::unchecked());

  for (const auto& member : members) {
    if (!std::meta::is_protected(member)) continue;
    if (!std::meta::is_static_member(member)) continue;
    if (!std::meta::is_function(member)) continue;

    if (std::meta::has_identifier(member) &&
        (std::meta::identifier_of(member) != std::string_view(Memberfunc)))
      continue;

    if (std::meta::has_identifier(member)) {
      if constexpr (std::is_same_v<Returntype, unspecified_return_t>)
        return true;
      if constexpr (sizeof...(Inputtype) != 0) {
        if (std::meta::type_of(member) == ^^Returntype(Inputtype...))
          return true;

        if (std::meta::return_type_of(member) == ^^Returntype) return true;
      }
    }
  }
  return false;
}();

//----------------------------------------------------------------------------//
//*               === class_has_private_static_memberfunc<> ===              *//
//----------------------------------------------------------------------------//

template <LiteralString Class, LiteralString Memberfunc,
          typename Returntype = unspecified_return_t, typename... Inputtype>
concept class_has_private_static_memberfunc = []() {
  if (!has_class<Class>) return false;

  auto members = std::meta::members_of(get_class_by_name<Class>(),
                                       std::meta::access_context::unchecked());

  for (const auto& member : members) {
    if (!std::meta::is_private(member)) continue;
    if (!std::meta::is_static_member(member)) continue;
    if (!std::meta::is_function(member)) continue;

    if (std::meta::has_identifier(member) &&
        (std::meta::identifier_of(member) != std::string_view(Memberfunc)))
      continue;

    if (std::meta::has_identifier(member)) {
      if constexpr (std::is_same_v<Returntype, unspecified_return_t>)
        return true;
      if constexpr (sizeof...(Inputtype) != 0) {
        if (std::meta::type_of(member) == ^^Returntype(Inputtype...))
          return true;

        if (std::meta::return_type_of(member) == ^^Returntype) return true;
      }
    }
  }
  return false;
}();

//----------------------------------------------------------------------------//
//*                    === class_has_public_membervar<> ===                  *//
//----------------------------------------------------------------------------//

template <LiteralString Class, LiteralString Membervar,
          typename Type = unspecified_return_t>
concept class_has_public_membervar = []() {
  if (!has_class<Class>) return false;

  auto members = std::meta::members_of(get_class_by_name<Class>(),
                                       std::meta::access_context::unchecked());

  for (const auto& member : members) {
    if (!std::meta::is_public(member)) continue;
    if (!std::meta::is_nonstatic_data_member(member)) continue;

    if (std::meta::has_identifier(member) &&
        std::meta::identifier_of(member) != std::string_view(Membervar))
      continue;

    if (std::meta::has_identifier(member)) {
      if constexpr (std::is_same_v<Type, unspecified_return_t>)
        return true;
      else if (std::meta::type_of(member) == ^^Type)
        return true;
    }
  }
  return false;
}();

//----------------------------------------------------------------------------//
//*                   === class_has_protected_membervar<> ===                *//
//----------------------------------------------------------------------------//

template <LiteralString Class, LiteralString Membervar,
          typename Type = unspecified_return_t>
concept class_has_protected_membervar = []() {
  if (!has_class<Class>) return false;

  auto members = std::meta::members_of(get_class_by_name<Class>(),
                                       std::meta::access_context::unchecked());

  for (const auto& member : members) {
    if (!std::meta::is_protected(member)) continue;
    if (!std::meta::is_nonstatic_data_member(member)) continue;

    if (std::meta::has_identifier(member) &&
        std::meta::identifier_of(member) != std::string_view(Membervar))
      continue;

    if (std::meta::has_identifier(member)) {
      if constexpr (std::is_same_v<Type, unspecified_return_t>)
        return true;
      else if (std::meta::type_of(member) == ^^Type)
        return true;
    }
  }
  return false;
}();

//----------------------------------------------------------------------------//
//*                    === class_has_private_membervar<> ===                 *//
//----------------------------------------------------------------------------//

template <LiteralString Class, LiteralString Membervar,
          typename Type = unspecified_return_t>
concept class_has_private_membervar = []() {
  if (!has_class<Class>) return false;

  auto members = std::meta::members_of(get_class_by_name<Class>(),
                                       std::meta::access_context::unchecked());

  for (const auto& member : members) {
    if (!std::meta::is_private(member)) continue;
    if (!std::meta::is_nonstatic_data_member(member)) continue;

    if (std::meta::has_identifier(member) &&
        std::meta::identifier_of(member) != std::string_view(Membervar))
      continue;

    if (std::meta::has_identifier(member)) {
      if constexpr (std::is_same_v<Type, unspecified_return_t>)
        return true;
      else if (std::meta::type_of(member) == ^^Type)
        return true;
    }
  }
  return false;
}();

//----------------------------------------------------------------------------//
//*                 === class_has_public_static_membervar<> ===              *//
//----------------------------------------------------------------------------//

template <LiteralString Class, LiteralString Membervar,
          typename Type = unspecified_return_t>
concept class_has_public_static_membervar = []() {
  if (!has_class<Class>) return false;

  auto members = std::meta::members_of(get_class_by_name<Class>(),
                                       std::meta::access_context::unchecked());

  for (const auto& member : members) {
    if (!std::meta::is_public(member)) continue;
    if (!std::meta::is_static_member(member)) continue;
    if (!std::meta::is_variable(member)) continue;

    if (std::meta::has_identifier(member) &&
        std::meta::identifier_of(member) != std::string_view(Membervar))
      continue;

    if (std::meta::has_identifier(member)) {
      if constexpr (std::is_same_v<Type, unspecified_return_t>) return true;
      if (std::meta::type_of(member) == ^^Type) return true;
    }
  }
  return false;
}();

//----------------------------------------------------------------------------//
//*                === class_has_protected_static_membervar<> ===            *//
//----------------------------------------------------------------------------//

template <LiteralString Class, LiteralString Membervar,
          typename Type = unspecified_return_t>
concept class_has_protected_static_membervar = []() {
  if (!has_class<Class>) return false;

  auto members = std::meta::members_of(get_class_by_name<Class>(),
                                       std::meta::access_context::unchecked());

  for (const auto& member : members) {
    if (!std::meta::is_protected(member)) continue;
    if (!std::meta::is_static_member(member)) continue;
    if (!std::meta::is_variable(member)) continue;

    if (std::meta::has_identifier(member) &&
        std::meta::identifier_of(member) != std::string_view(Membervar))
      continue;

    if (std::meta::has_identifier(member)) {
      if constexpr (std::is_same_v<Type, unspecified_return_t>) return true;
      if (std::meta::type_of(member) == ^^Type) return true;
    }
  }
  return false;
}();

//----------------------------------------------------------------------------//
//*                === class_has_private_static_membervar<> ===              *//
//----------------------------------------------------------------------------//

template <LiteralString Class, LiteralString Membervar,
          typename Type = unspecified_return_t>
concept class_has_private_static_membervar = []() {
  if (!has_class<Class>) return false;

  auto members = std::meta::members_of(get_class_by_name<Class>(),
                                       std::meta::access_context::unchecked());

  for (const auto& member : members) {
    if (!std::meta::is_private(member)) continue;
    if (!std::meta::is_static_member(member)) continue;
    if (!std::meta::is_variable(member)) continue;

    if (std::meta::has_identifier(member) &&
        std::meta::identifier_of(member) != std::string_view(Membervar))
      continue;

    if (std::meta::has_identifier(member)) {
      if constexpr (std::is_same_v<Type, unspecified_return_t>) return true;
      if (std::meta::type_of(member) == ^^Type) return true;
    }
  }
  return false;
}();

#endif  // CXXCHECKER_REFLECTION_HPP