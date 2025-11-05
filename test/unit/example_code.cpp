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

//----------------------------------------------------------------------------//
//*                             === INCLUDES ===                             *//
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

//----------------------------------------------------------------------------//
//*                          === EMPTY CLASSES ===                           *//
//----------------------------------------------------------------------------//

class ClassDeclaredOnly;
class ClassDefinedButEmpty {};
struct StructDeclaredOnly;
struct StructDefinedButEmpty {};
// class ClassNotExistent {};
// struct StructNotExistent {};

//----------------------------------------------------------------------------//
//*                       === CLASS WITH VARIABLES ===                       *//
//----------------------------------------------------------------------------//

class ClassWithVariables {
 public:
  bool bool_declared_only;
  bool bool_list_init{true};
  bool bool_copy_init = true;

  char char_declared_only;
  char char_list_init{'a'};
  char char_copy_init = 'a';

  char8_t char8_t_declared_only;
  char8_t char8_t_list_init{'a'};
  char8_t char8_t_copy_init = 'a';

  char16_t char16_t_declared_only;
  char16_t char16_t_list_init{'a'};
  char16_t char16_t_copy_init = 'a';

  char32_t char32_t_declared_only;
  char32_t char32_t_list_init{'a'};
  char32_t char32_t_copy_init = 'a';

  double double_declared_only;
  double double_list_init{1.0};
  double double_copy_init = 1.0;

  float float_declared_only;
  float float_list_init{1.0};
  float float_copy_init = 1.0;

  int int_declared_only;
  int int_list_init{1};
  int int_copy_init = 1;

  long double longdouble_declared_only;
  long double longdouble_list_init{1.0};
  long double longdouble_copy_init = 1.0;

  long int longint_declared_only;
  long int longint_list_init{1};
  long int longint_copy_init = 1;

  long long int longlongint_declared_only;
  long long int longlongint_list_init{1};
  long long int longlongint_copy_init = 1;

  short int shortint_declared_only;
  short int shortint_list_init{1};
  short int shortint_copy_init = 1;

  std::string string_declared_only;
  std::string string_list_init{"abc"};
  std::string string_copy_init = "abc";

  std::string_view string_view_declared_only;
  std::string_view string_view_list_init{"abc"};
  std::string_view string_view_copy_init = "abc";

  unsigned char unsignedchar_declared_only;
  unsigned char unsignedchar_list_init{'a'};
  unsigned char unsignedchar_copy_init = 'a';

  unsigned int unsignedint_declared_only;
  unsigned int unsignedint_list_init{1};
  unsigned int unsignedint_copy_init = 1;

  unsigned long int unsignedlongint_declared_only;
  unsigned long int unsignedlongint_list_init{1};
  unsigned long int unsignedlongint_copy_init = (1);

  unsigned long long int unsignedlonglongint_declared_only;
  unsigned long long int unsignedlonglongint_list_init{1};
  unsigned long long int unsignedlonglongint_copy_init = 1;

  unsigned short int unsignedshortint_declared_only;
  unsigned short int unsignedshortint_list_init{1};
  unsigned short int unsignedshortint_copy_init = 1;

  wchar_t wchar_t_declared_only;
  wchar_t wchar_t_list_init{'a'};
  wchar_t wchar_t_copy_init = 'a';

 protected:
 private:
};

//----------------------------------------------------------------------------//
//*                       === CLASS WITH FUNCTIONS ===                       *//
//----------------------------------------------------------------------------//

class ClassWithFunctions {
 public:
 protected:
 private:
};

//----------------------------------------------------------------------------//
//*                       === CLASS WITH POINTERS ===                        *//
//----------------------------------------------------------------------------//

class ClassWithPointers {
 public:
 protected:
 private:
};

//----------------------------------------------------------------------------//
//*                      === CLASS WITH REFERENCES ===                       *//
//----------------------------------------------------------------------------//

class ClassWithReferences {
 public:
 protected:
 private:
};

//----------------------------------------------------------------------------//
//*                       === CLASS WITH TEMPLATES ===                       *//
//----------------------------------------------------------------------------//

class ClassWithTemplates {
 public:
 protected:
 private:
};

//----------------------------------------------------------------------------//
//*                        === CLASS WITH ARRAYS ===                         *//
//----------------------------------------------------------------------------//

class ClassWithArrays {
 public:
 protected:
 private:
};

//----------------------------------------------------------------------------//
//*                         === CLASS WITH MAPS ===                          *//
//----------------------------------------------------------------------------//

class ClassWithMaps {
 public:
 protected:
 private:
};

//----------------------------------------------------------------------------//
//*                          === FREE VARIABLES ===                          *//
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
//*                          === FREE FUNCTIONS ===                          *//
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
//*                            === NAMESPACE ===                             *//
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
//*                          === MAIN FUNCTION ===                           *//
//----------------------------------------------------------------------------//

auto main(int /*argc*/, char** /*argv*/) -> int {
  std::cout << "example_code.cpp" << std::endl;
  return 0;
}