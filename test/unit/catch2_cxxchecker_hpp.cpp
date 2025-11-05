// Copyright (c) 2023-present Hoang Nguyen
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

#define CATCH_CONFIG_MAIN

//----------------------------------------------------------------------------//
//*                            === INCLUDES ===                              *//
//----------------------------------------------------------------------------//

#include <array>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../../include/catch.hpp"
#include "../../include/cxxchecker.hpp"

//----------------------------------------------------------------------------//
//*                          === EXAMPLE CODE ===                            *//
//----------------------------------------------------------------------------//

namespace check_in_here {

#include "example_code.cpp"

}  // namespace check_in_here

//----------------------------------------------------------------------------//
//*                         === HELPER TYPENAMES ===                         *//
//----------------------------------------------------------------------------//

using bool_p = bool *;

using char_p = char *;

using char8_t_p = char8_t *;

using char16_t_p = char16_t *;

using char32_t_p = char32_t *;

using double_p = double *;

using float_p = float *;

using int_p = int *;

using longdouble = long double;
using longdouble_p = long double *;

using longint = long int;
using longint_p = long int *;
using long_p = long *;

using longlongint = long long int;
using longlongint_p = long long int *;
using longlong_p = long long *;

using shortint = short int;
using shortint_p = short int *;
using short_p = short *;

using string = std::string;

using string_view = std::string_view;

using unsignedchar = unsigned char;
using unsignedchar_p = unsigned char *;

using unsignedint = unsigned int;
using unsignedint_p = unsigned int *;

using unsignedlongint = unsigned long int;
using unsignedlongint_p = unsigned long int *;
using unsignedlong = unsigned long;
using unsignedlong_p = unsigned long *;

using unsignedlonglongint = unsigned long long int;
using unsignedlonglongint_p = unsigned long long int *;
using unsignedlonglong = unsigned long long;
using unsignedlonglong_p = unsigned long long *;

using unsignedshortint = unsigned short int;
using unsignedshortint_p = unsigned short int *;
using unsignedshort = unsigned short;
using unsignedshort_p = unsigned short *;

using wchar_t_p = wchar_t *;
//----------------------------------------------------------------------------//
//*                             === CLASSES ===                              *//
//----------------------------------------------------------------------------//

HAS_CLASS(ClassDeclaredOnly)
HAS_CLASS(ClassDefinedButEmpty)
HAS_CLASS(StructDeclaredOnly)
HAS_CLASS(StructDefinedButEmpty)

HAS_CLASS(ClassNotExistent)
HAS_CLASS(StructNotExistent)

TEST_CASE("HAS_CLASS", "[class]") {
  using namespace check;

  CHECK(has_class_ClassDeclaredOnly_v);
  CHECK(has_class_ClassDefinedButEmpty_v);
  CHECK(has_class_StructDeclaredOnly_v);
  CHECK(has_class_StructDefinedButEmpty_v);

  CHECK_FALSE(has_class_ClassNotExistent_v);
  CHECK_FALSE(has_class_StructNotExistent_v);
}

//----------------------------------------------------------------------------//
//*                         === CLASS VARIABLES ===                          *//
//----------------------------------------------------------------------------//

CLASS_HAS_MEMBERVAR(ClassWithVariables, bool_declared_only)
CLASS_HAS_MEMBERVAR(ClassWithVariables, bool_list_init)
CLASS_HAS_MEMBERVAR(ClassWithVariables, bool_copy_init)

CLASS_HAS_MEMBERVAR(ClassWithVariables, char_declared_only)
CLASS_HAS_MEMBERVAR(ClassWithVariables, char_list_init)
CLASS_HAS_MEMBERVAR(ClassWithVariables, char_copy_init)

CLASS_HAS_MEMBERVAR(ClassWithVariables, char8_t_declared_only)
CLASS_HAS_MEMBERVAR(ClassWithVariables, char8_t_list_init)
CLASS_HAS_MEMBERVAR(ClassWithVariables, char8_t_copy_init)

CLASS_HAS_MEMBERVAR(ClassWithVariables, char16_t_declared_only)
CLASS_HAS_MEMBERVAR(ClassWithVariables, char16_t_list_init)
CLASS_HAS_MEMBERVAR(ClassWithVariables, char16_t_copy_init)

CLASS_HAS_MEMBERVAR(ClassWithVariables, char32_t_declared_only)
CLASS_HAS_MEMBERVAR(ClassWithVariables, char32_t_list_init)
CLASS_HAS_MEMBERVAR(ClassWithVariables, char32_t_copy_init)

CLASS_HAS_MEMBERVAR(ClassWithVariables, double_declared_only)
CLASS_HAS_MEMBERVAR(ClassWithVariables, double_list_init)
CLASS_HAS_MEMBERVAR(ClassWithVariables, double_copy_init)

CLASS_HAS_MEMBERVAR(ClassWithVariables, float_declared_only)
CLASS_HAS_MEMBERVAR(ClassWithVariables, float_list_init)
CLASS_HAS_MEMBERVAR(ClassWithVariables, float_copy_init)

CLASS_HAS_MEMBERVAR(ClassWithVariables, int_declared_only)
CLASS_HAS_MEMBERVAR(ClassWithVariables, int_list_init)
CLASS_HAS_MEMBERVAR(ClassWithVariables, int_copy_init)

CLASS_HAS_MEMBERVAR(ClassWithVariables, longdouble_declared_only)
CLASS_HAS_MEMBERVAR(ClassWithVariables, longdouble_list_init)
CLASS_HAS_MEMBERVAR(ClassWithVariables, longdouble_copy_init)

CLASS_HAS_MEMBERVAR(ClassWithVariables, longint_declared_only)
CLASS_HAS_MEMBERVAR(ClassWithVariables, longint_list_init)
CLASS_HAS_MEMBERVAR(ClassWithVariables, longint_copy_init)

CLASS_HAS_MEMBERVAR(ClassWithVariables, longlongint_declared_only)
CLASS_HAS_MEMBERVAR(ClassWithVariables, longlongint_list_init)
CLASS_HAS_MEMBERVAR(ClassWithVariables, longlongint_copy_init)

CLASS_HAS_MEMBERVAR(ClassWithVariables, shortint_declared_only)
CLASS_HAS_MEMBERVAR(ClassWithVariables, shortint_list_init)
CLASS_HAS_MEMBERVAR(ClassWithVariables, shortint_copy_init)

CLASS_HAS_MEMBERVAR(ClassWithVariables, string_declared_only)
CLASS_HAS_MEMBERVAR(ClassWithVariables, string_list_init)
CLASS_HAS_MEMBERVAR(ClassWithVariables, string_copy_init)

CLASS_HAS_MEMBERVAR(ClassWithVariables, string_view_declared_only)
CLASS_HAS_MEMBERVAR(ClassWithVariables, string_view_list_init)
CLASS_HAS_MEMBERVAR(ClassWithVariables, string_view_copy_init)

CLASS_HAS_MEMBERVAR(ClassWithVariables, unsignedchar_declared_only)
CLASS_HAS_MEMBERVAR(ClassWithVariables, unsignedchar_list_init)
CLASS_HAS_MEMBERVAR(ClassWithVariables, unsignedchar_copy_init)

CLASS_HAS_MEMBERVAR(ClassWithVariables, unsignedint_declared_only)
CLASS_HAS_MEMBERVAR(ClassWithVariables, unsignedint_list_init)
CLASS_HAS_MEMBERVAR(ClassWithVariables, unsignedint_copy_init)

CLASS_HAS_MEMBERVAR(ClassWithVariables, unsignedlongint_declared_only)
CLASS_HAS_MEMBERVAR(ClassWithVariables, unsignedlongint_list_init)
CLASS_HAS_MEMBERVAR(ClassWithVariables, unsignedlongint_copy_init)

CLASS_HAS_MEMBERVAR(ClassWithVariables, unsignedlonglongint_declared_only)
CLASS_HAS_MEMBERVAR(ClassWithVariables, unsignedlonglongint_list_init)
CLASS_HAS_MEMBERVAR(ClassWithVariables, unsignedlonglongint_copy_init)

CLASS_HAS_MEMBERVAR(ClassWithVariables, unsignedshortint_declared_only)
CLASS_HAS_MEMBERVAR(ClassWithVariables, unsignedshortint_list_init)
CLASS_HAS_MEMBERVAR(ClassWithVariables, unsignedshortint_copy_init)

CLASS_HAS_MEMBERVAR(ClassWithVariables, wchar_t_declared_only)
CLASS_HAS_MEMBERVAR(ClassWithVariables, wchar_t_list_init)
CLASS_HAS_MEMBERVAR(ClassWithVariables, wchar_t_copy_init)

//----------------------------------------------------------------------------//

CLASS_HAS_MEMBERVAR(ClassWithVariables, not_existent)

TEST_CASE("CLASS_HAS_MEMBERVAR") {
  using namespace check;

  SECTION("bool") {
    CHECK(class_ClassWithVariables_has_membervar_bool_declared_only_v);
    CHECK(class_ClassWithVariables_has_membervar_bool_list_init_v);
    CHECK(class_ClassWithVariables_has_membervar_bool_copy_init_v);
  }

  SECTION("char") {
    CHECK(class_ClassWithVariables_has_membervar_char_declared_only_v);
    CHECK(class_ClassWithVariables_has_membervar_char_list_init_v);
    CHECK(class_ClassWithVariables_has_membervar_char_copy_init_v);
  }

  SECTION("char8_t") {
    CHECK(class_ClassWithVariables_has_membervar_char8_t_declared_only_v);
    CHECK(class_ClassWithVariables_has_membervar_char8_t_list_init_v);
    CHECK(class_ClassWithVariables_has_membervar_char8_t_copy_init_v);
  }

  SECTION("char16_t") {
    CHECK(class_ClassWithVariables_has_membervar_char16_t_declared_only_v);
    CHECK(class_ClassWithVariables_has_membervar_char16_t_list_init_v);
    CHECK(class_ClassWithVariables_has_membervar_char16_t_copy_init_v);
  }

  SECTION("char32_t") {
    CHECK(class_ClassWithVariables_has_membervar_char32_t_declared_only_v);
    CHECK(class_ClassWithVariables_has_membervar_char32_t_list_init_v);
    CHECK(class_ClassWithVariables_has_membervar_char32_t_copy_init_v);
  }

  SECTION("double") {
    CHECK(class_ClassWithVariables_has_membervar_double_declared_only_v);
    CHECK(class_ClassWithVariables_has_membervar_double_list_init_v);
    CHECK(class_ClassWithVariables_has_membervar_double_copy_init_v);
  }

  SECTION("float") {
    CHECK(class_ClassWithVariables_has_membervar_float_declared_only_v);
    CHECK(class_ClassWithVariables_has_membervar_float_list_init_v);
    CHECK(class_ClassWithVariables_has_membervar_float_copy_init_v);
  }

  SECTION("int") {
    CHECK(class_ClassWithVariables_has_membervar_int_declared_only_v);
    CHECK(class_ClassWithVariables_has_membervar_int_list_init_v);
    CHECK(class_ClassWithVariables_has_membervar_int_copy_init_v);
  }

  SECTION("long double") {
    CHECK(class_ClassWithVariables_has_membervar_longdouble_declared_only_v);
    CHECK(class_ClassWithVariables_has_membervar_longdouble_list_init_v);
    CHECK(class_ClassWithVariables_has_membervar_longdouble_copy_init_v);
  }

  SECTION("long int") {
    CHECK(class_ClassWithVariables_has_membervar_longint_declared_only_v);
    CHECK(class_ClassWithVariables_has_membervar_longint_list_init_v);
    CHECK(class_ClassWithVariables_has_membervar_longint_copy_init_v);
  }

  SECTION("long long int") {
    CHECK(class_ClassWithVariables_has_membervar_longlongint_declared_only_v);
    CHECK(class_ClassWithVariables_has_membervar_longlongint_list_init_v);
    CHECK(class_ClassWithVariables_has_membervar_longlongint_copy_init_v);
  }

  SECTION("short int") {
    CHECK(class_ClassWithVariables_has_membervar_shortint_declared_only_v);
    CHECK(class_ClassWithVariables_has_membervar_shortint_list_init_v);
    CHECK(class_ClassWithVariables_has_membervar_shortint_copy_init_v);
  }

  SECTION("std::string") {
    CHECK(class_ClassWithVariables_has_membervar_string_declared_only_v);
    CHECK(class_ClassWithVariables_has_membervar_string_list_init_v);
    CHECK(class_ClassWithVariables_has_membervar_string_copy_init_v);
  }

  SECTION("std::string_view") {
    CHECK(class_ClassWithVariables_has_membervar_string_view_declared_only_v);
    CHECK(class_ClassWithVariables_has_membervar_string_view_list_init_v);
    CHECK(class_ClassWithVariables_has_membervar_string_view_copy_init_v);
  }

  SECTION("unsigned char") {
    CHECK(class_ClassWithVariables_has_membervar_unsignedchar_declared_only_v);
    CHECK(class_ClassWithVariables_has_membervar_unsignedchar_list_init_v);
    CHECK(class_ClassWithVariables_has_membervar_unsignedchar_copy_init_v);
  }

  SECTION("unsigned long int") {
    CHECK(
        class_ClassWithVariables_has_membervar_unsignedlongint_declared_only_v);
    CHECK(class_ClassWithVariables_has_membervar_unsignedlongint_list_init_v);
    CHECK(class_ClassWithVariables_has_membervar_unsignedlongint_copy_init_v);
  }

  SECTION("unsigned long long int") {
    CHECK(
        class_ClassWithVariables_has_membervar_unsignedlonglongint_declared_only_v);
    CHECK(
        class_ClassWithVariables_has_membervar_unsignedlonglongint_list_init_v);
    CHECK(
        class_ClassWithVariables_has_membervar_unsignedlonglongint_copy_init_v);
  }

  SECTION("unsigned short int") {
    CHECK(
        class_ClassWithVariables_has_membervar_unsignedshortint_declared_only_v);
    CHECK(class_ClassWithVariables_has_membervar_unsignedshortint_list_init_v);
    CHECK(class_ClassWithVariables_has_membervar_unsignedshortint_copy_init_v);
  }

  SECTION("wchar_t") {
    CHECK(class_ClassWithVariables_has_membervar_wchar_t_declared_only_v);
    CHECK(class_ClassWithVariables_has_membervar_wchar_t_list_init_v);
    CHECK(class_ClassWithVariables_has_membervar_wchar_t_copy_init_v);
  }

  SECTION("not existent") {
    CHECK_FALSE(class_ClassWithVariables_has_membervar_not_existent_v);
  }
}

//----------------------------------------------------------------------------//

TEST_CASE("CLASS_HAS_STATIC_MEMBERVAR") { using namespace check; }

//----------------------------------------------------------------------------//

TEST_CASE("CLASS_HAS_CONST_MEMBERVAR") { using namespace check; }

//----------------------------------------------------------------------------//

TEST_CASE("CLASS_HAS_VOLATILE_MEMBERVAR") { using namespace check; }

//----------------------------------------------------------------------------//

TEST_CASE("CLASS_HAS_STATIC_CONST_MEMBERVAR") { using namespace check; }

//----------------------------------------------------------------------------//

TEST_CASE("CLASS_HAS_MEMBERVAR_OF_TYPE") { using namespace check; }

//----------------------------------------------------------------------------//

TEST_CASE("CLASS_HAS_STATIC_MEMBERVAR_OF_TYPE") { using namespace check; }

//----------------------------------------------------------------------------//

TEST_CASE("CLASS_HAS_CONST_MEMBERVAR_OF_TYPE") { using namespace check; }

//----------------------------------------------------------------------------//

TEST_CASE("CLASS_HAS_STATIC_CONST_MEMBERVAR_OF_TYPE") { using namespace check; }

//----------------------------------------------------------------------------//

TEST_CASE("CLASS_HAS_VOLATILE_MEMBERVAR_OF_TYPE") { using namespace check; }

// TODO TRY static, const, volatile as a combined type like the helper types in
// CLASS_HAS_MEMBERVAR_OF_TYPE

//----------------------------------------------------------------------------//
//*                         === CLASS FUNCTIONS ===                          *//
//----------------------------------------------------------------------------//

TEST_CASE("CLASS_HAS_MEMBERFUNC") { using namespace check; }

//----------------------------------------------------------------------------//

TEST_CASE("CLASS_HAS_CONST_MEMBERFUNC") { using namespace check; }

//----------------------------------------------------------------------------//

TEST_CASE("CLASS_HAS_STATIC_MEMBERFUNC") { using namespace check; }

//----------------------------------------------------------------------------//

TEST_CASE("CLASS_HAS_MEMBERFUNC_OF_RETURNTYPE") { using namespace check; }

//----------------------------------------------------------------------------//

TEST_CASE("CLASS_HAS_STATIC_MEMBERFUNC_OF_TYPE") { using namespace check; }

//----------------------------------------------------------------------------//

TEST_CASE("HAS_FREE_FUNCTION") { using namespace check; }

//----------------------------------------------------------------------------//

TEST_CASE("HAS_FREE_FUNCTION_OF_RETURNTYPE") { using namespace check; }

//----------------------------------------------------------------------------//