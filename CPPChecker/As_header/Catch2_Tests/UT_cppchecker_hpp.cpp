#define CATCH_CONFIG_MAIN

#include "../cppchecker.hpp"
#include "./catch.hpp"

namespace STUDENT {
class DeclaredOnly;
class DefinedButEmpty {};

class ClassWithVars {
 public:
  void *vp{nullptr};
  bool b;
  long double ld;
};

class ClassWithFuncs {
 public:
  ClassWithFuncs() = delete;
  void m1();  // incomplete
  void m2(){};
  int m3() { return 42; };
  int m3() const { return 42; };
};

void f1();
void f2(){};

}  // namespace STUDENT

HAS_CLASS(NotExistant)
HAS_CLASS(DeclaredOnly)
HAS_CLASS(DefinedButEmpty)
// HAS_CLASS(f1)                                    // geht nicht
// HAS_CLASS(f2)                                    // geht nicht

CLASS_HAS_MEMBERVAR(NotExistant, none)
CLASS_HAS_MEMBERVAR(DeclaredOnly, none)
CLASS_HAS_MEMBERVAR(DefinedButEmpty, none)
CLASS_HAS_MEMBERVAR(ClassWithVars, none)
CLASS_HAS_MEMBERVAR(ClassWithVars, vp)
CLASS_HAS_MEMBERVAR(ClassWithVars, b)
CLASS_HAS_MEMBERVAR(ClassWithVars, ld)
CLASS_HAS_MEMBERVAR(ClassWithFuncs, none)
CLASS_HAS_MEMBERVAR(ClassWithFuncs, m1)
CLASS_HAS_MEMBERVAR(ClassWithFuncs, m2)
CLASS_HAS_MEMBERVAR(ClassWithFuncs, m3);

CLASS_HAS_MEMBERFUNC(NotExistant, none)
CLASS_HAS_MEMBERFUNC(DeclaredOnly, none)
CLASS_HAS_MEMBERFUNC(DefinedButEmpty, none)
CLASS_HAS_MEMBERFUNC(ClassWithVars, none)
CLASS_HAS_MEMBERFUNC(ClassWithVars, vp)
CLASS_HAS_MEMBERFUNC(ClassWithVars, b)
CLASS_HAS_MEMBERFUNC(ClassWithVars, ld)
CLASS_HAS_MEMBERFUNC(ClassWithFuncs, none)
CLASS_HAS_MEMBERFUNC(ClassWithFuncs, m1)
CLASS_HAS_MEMBERFUNC(ClassWithFuncs, m2)
CLASS_HAS_MEMBERFUNC(ClassWithFuncs,
                     m3);  // Cannot distinguish between const and non-const

CLASS_HAS_MEMBERVAR_OF_TYPE(NotExistant, none, void)
CLASS_HAS_MEMBERVAR_OF_TYPE(DeclaredOnly, none, void)
CLASS_HAS_MEMBERVAR_OF_TYPE(DefinedButEmpty, none, int)
CLASS_HAS_MEMBERVAR_OF_TYPE(ClassWithVars, none, int)
CLASS_HAS_MEMBERVAR_OF_TYPE(ClassWithVars, vp, void)
// Die folgende Zeile kann nicht kompilieren
// CLASS_HAS_MEMBERVAR_OF_TYPE(ClassWithVars,vp,void *)
using pvoid = void *;  // Umweg
// Jetzt sollte es gehen
CLASS_HAS_MEMBERVAR_OF_TYPE(ClassWithVars, vp, pvoid)
CLASS_HAS_MEMBERVAR_OF_TYPE(ClassWithVars, b, int)
CLASS_HAS_MEMBERVAR_OF_TYPE(ClassWithVars, b, bool)
CLASS_HAS_MEMBERVAR_OF_TYPE(ClassWithVars, ld, void)
// Ähnliches Problem wie oben
// CLASS_HAS_MEMBERVAR_OF_TYPE(ClassWithVars, ld, long double)
using longdouble = long double;  // Umweg
CLASS_HAS_MEMBERVAR_OF_TYPE(ClassWithVars, ld, longdouble)
CLASS_HAS_MEMBERVAR_OF_TYPE(ClassWithFuncs, none, bool)
CLASS_HAS_MEMBERVAR_OF_TYPE(ClassWithFuncs, m1, char)
CLASS_HAS_MEMBERVAR_OF_TYPE(ClassWithFuncs, m2, int)
CLASS_HAS_MEMBERVAR_OF_TYPE(ClassWithFuncs, m3, int);

TEST_CASE("HAS_CLASS") {
  REQUIRE(Check::has_class_NotExistant_v == false);
  // Interessant: Die folgende Assertion verlangt nicht,
  //  dass DeclaredOnly ein complete type ist.
  REQUIRE(Check::has_class_DeclaredOnly_v == true);
  REQUIRE(Check::has_class_DefinedButEmpty_v == true);
  // REQUIRE(Check::has_class_f1_v == false);
  // REQUIRE(Check::has_class_f2_v == false);
}

TEST_CASE("CLASS_HAS_MEMBERVAR") {
  using namespace Check;
  REQUIRE(class_NotExistant_has_membervar_none_v == false);
  REQUIRE(class_DeclaredOnly_has_membervar_none_v == false);
  REQUIRE(class_DefinedButEmpty_has_membervar_none_v == false);
  REQUIRE(class_ClassWithVars_has_membervar_none_v == false);
  REQUIRE(class_ClassWithVars_has_membervar_vp_v == true);
  REQUIRE(class_ClassWithVars_has_membervar_b_v == true);
  REQUIRE(class_ClassWithVars_has_membervar_ld_v == true);
  REQUIRE(class_ClassWithFuncs_has_membervar_none_v == false);
  REQUIRE(class_ClassWithFuncs_has_membervar_m1_v == false);
  REQUIRE(class_ClassWithFuncs_has_membervar_m2_v == false);
  REQUIRE(class_ClassWithFuncs_has_membervar_m3_v == false);
}

TEST_CASE("CLASS_HAS_MEMBERFUNC") {
  using namespace Check;
  REQUIRE(class_NotExistant_has_memberfunc_none_v == false);
  REQUIRE(class_DeclaredOnly_has_memberfunc_none_v == false);
  REQUIRE(class_DefinedButEmpty_has_memberfunc_none_v == false);
  REQUIRE(class_ClassWithVars_has_memberfunc_none_v == false);
  REQUIRE(class_ClassWithVars_has_memberfunc_vp_v == false);
  REQUIRE(class_ClassWithVars_has_memberfunc_b_v == false);
  REQUIRE(class_ClassWithVars_has_memberfunc_ld_v == false);
  REQUIRE(class_ClassWithFuncs_has_memberfunc_none_v == false);
  REQUIRE(class_ClassWithFuncs_has_memberfunc_m1_v == true);
  REQUIRE(class_ClassWithFuncs_has_memberfunc_m2_v == true);
  REQUIRE(class_ClassWithFuncs_has_memberfunc_m3_v == true);
}

TEST_CASE("CLASS_HAS_MEMBERVAR_OF_TYPE") {
  using namespace Check;
  REQUIRE(class_NotExistant_has_membervar_none_of_type_void_v == false);
  REQUIRE(class_DeclaredOnly_has_membervar_none_of_type_void_v == false);
  REQUIRE(class_DefinedButEmpty_has_membervar_none_of_type_int_v == false);
  REQUIRE(class_ClassWithVars_has_membervar_none_of_type_int_v == false);
  REQUIRE(class_ClassWithVars_has_membervar_vp_of_type_void_v == false);
  REQUIRE(class_ClassWithVars_has_membervar_vp_of_type_pvoid_v == true);
  using pvoid = void *;

  REQUIRE(class_ClassWithVars_has_membervar_b_of_type_int_v == false);
  REQUIRE(class_ClassWithVars_has_membervar_b_of_type_bool_v == true);
  REQUIRE(class_ClassWithVars_has_membervar_ld_of_type_void_v == false);
  REQUIRE(class_ClassWithVars_has_membervar_ld_of_type_longdouble_v == true);
  REQUIRE(class_ClassWithFuncs_has_membervar_none_of_type_bool_v == false);
  REQUIRE(class_ClassWithFuncs_has_membervar_m1_of_type_char_v == false);
  REQUIRE(class_ClassWithFuncs_has_membervar_m2_of_type_int_v == false);
  REQUIRE(class_ClassWithFuncs_has_membervar_m3_of_type_int_v == false);
}
