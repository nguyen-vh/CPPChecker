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

#ifndef CPPCHECKER_HPP
#define CPPCHECKER_HPP

#include <iostream>
#include <sstream>
#include <type_traits>

//? Defines the namespace to be checked
#define NAMESPACE_TO_CHECK STUDENT

//! Call Macros in global namespace

/*
All Macros

HAS_CLASS(CLASS)
CLASS_HAS_MEMBERVAR(CLASS, MEMBERVAR)
CLASS_HAS_MEMBERFUNC(CLASS, MEMBERFUNC)
CLASS_HAS_CONST_MEMBERFUNC(CLASS, MEMBERFUNC)


?   CLASS_HAS_STATIC_MEMBERVAR(CLASS, MEMBERVAR)
?   CLASS_HAS_STATIC_MEMBERFUNC(CLASS, MEMBERFUNC)
CLASS_HAS_MEMBERVAR_OF_TYPE(CLASS, MEMBERVAR, TYPE)
CLASS_HAS_MEMBERFUNC_OF_RETURNTYPE(CLASS, MEMBERFUNC, RETURNTYPE)
?   CLASS_HAS_STATIC_MEMBERVAR_OF_TYPE(CLASS, MEMBERVAR, TYPE)
?   CLASS_HAS_STATIC_MEMBERFUNC_OF_RETURNTYPE(CLASS, MEMBERFUNC, RETURNTYPE)
HAS_FREE_FUNCTION(FUNCTION)
HAS_FREE_FUNCTION_OF_RETURNTYPE(FUNCTION, RETURNTYPE)
HAS_FREE_VARIABLE(VARIABLE)
HAS_FREE_VARIABLE_OF_TYPE(VARIABLE, TYPE)
IS_OUTPUT_SAME(TEXT)
*/

/*



*/

//? Creates a check to determine if a specific class exists in
//? the specified namespace
//* bool Check::has_class_'CLASS'_v
#define HAS_CLASS(CLASS)                                                    \
                                                                            \
  namespace TASK::TESTER {                                                  \
  using CLASS = No;                                                         \
  }                                                                         \
  namespace NAMESPACE_TO_CHECK::TASK {                                      \
  using namespace ::TASK::TESTER;                                           \
  bool has_class_##CLASS = check_class<CLASS>();                            \
  }                                                                         \
                                                                            \
  namespace Check {                                                         \
  bool has_class_##CLASS##_v = NAMESPACE_TO_CHECK::TASK::has_class_##CLASS; \
  }

//*  Fallback Class
namespace TASK::TESTER {
struct No {};
}  // namespace TASK::TESTER

template <typename T>
bool check_class() {
  return !std::is_same_v<T, TASK::TESTER::No>;
}

//  End of HAS_CLASS

/*



*/

//? Creates a check to determine if a specific class has a specific
//? membervariable in the specified namespace
//*V  bool Check::class_'CLASS'_has_membervar_'MEMBERVAR'_v
#define CLASS_HAS_MEMBERVAR(CLASS, MEMBERVAR)                              \
                                                                           \
  namespace TASK::TESTER {                                                 \
  using CLASS = No;                                                        \
  }                                                                        \
  template <typename T, typename = void>                                   \
  struct class_##CLASS##_has_membervar_##MEMBERVAR##_sfinae                \
      : std::false_type {};                                                \
  template <typename T>                                                    \
  struct class_##CLASS##_has_membervar_##MEMBERVAR##                       \
      _sfinae<T, std::void_t<decltype(std::declval<T>().MEMBERVAR)>>       \
      : std::true_type {};                                                 \
  namespace NAMESPACE_TO_CHECK::TASK {                                     \
  using namespace ::TASK::TESTER;                                          \
  bool class_##CLASS##_has_membervar_##MEMBERVAR =                         \
      class_##CLASS##_has_membervar_##MEMBERVAR##_sfinae<CLASS>();         \
  }                                                                        \
                                                                           \
  namespace Check {                                                        \
  bool class_##CLASS##_has_membervar_##MEMBERVAR##_v =                     \
      NAMESPACE_TO_CHECK::TASK::class_##CLASS##_has_membervar_##MEMBERVAR; \
  }

//  End of CLASS_HAS_MEMBERVAR

/*



*/

//? Creates a check to determine if a specific class has a specific
//? memberfunction in the specified namespace
//*F  bool Check::class_'CLASS'_has_memberfunc_'MEMBERFUNC'_v
#define CLASS_HAS_MEMBERFUNC(CLASS, MEMBERFUNC)                              \
                                                                             \
  namespace TASK::TESTER {                                                   \
  using CLASS = No;                                                          \
  }                                                                          \
  template <typename T, typename = void>                                     \
  struct class_##CLASS##_has_memberfunc_##MEMBERFUNC##_sfinae                \
      : std::false_type {};                                                  \
  template <typename T>                                                      \
  struct class_##CLASS##_has_memberfunc_##MEMBERFUNC##                       \
      _sfinae<T, std::void_t<decltype(std::declval<T>().MEMBERFUNC())>>      \
      : std::true_type {};                                                   \
  namespace NAMESPACE_TO_CHECK::TASK {                                       \
  using namespace ::TASK::TESTER;                                            \
  bool class_##CLASS##_has_memberfunc_##MEMBERFUNC =                         \
      class_##CLASS##_has_memberfunc_##MEMBERFUNC##_sfinae<CLASS>();         \
  }                                                                          \
                                                                             \
  namespace Check {                                                          \
  bool class_##CLASS##_has_memberfunc_##MEMBERFUNC##_v =                     \
      NAMESPACE_TO_CHECK::TASK::class_##CLASS##_has_memberfunc_##MEMBERFUNC; \
  }

//  End of CLASS_HAS_MEMBERFUNC

/*



*/

//? Creates a check to determine if a specific class has a specific
//? const memberfunction in the specified namespace
//*F  bool Check::class_'CLASS'_has_const_memberfunc_'MEMBERFUNC'_v
#define CLASS_HAS_CONST_MEMBERFUNC(CLASS, MEMBERFUNC)                         \
                                                                              \
  namespace TASK::TESTER {                                                    \
  using CLASS = No;                                                           \
  }                                                                           \
  template <typename T, typename = void>                                      \
  struct class_##CLASS##_has_const_memberfunc_##MEMBERFUNC##_sfinae           \
      : std::false_type {};                                                   \
  template <typename T>                                                       \
  struct class_##CLASS##_has_const_memberfunc_##MEMBERFUNC##                  \
      _sfinae<T, std::void_t<decltype(std::declval<const T>().MEMBERFUNC())>> \
      : std::true_type {};                                                    \
  namespace NAMESPACE_TO_CHECK::TASK {                                        \
  using namespace ::TASK::TESTER;                                             \
  bool class_##CLASS##_has_const_memberfunc_##MEMBERFUNC =                    \
      class_##CLASS##_has_const_memberfunc_##MEMBERFUNC##_sfinae<CLASS>();    \
  }                                                                           \
                                                                              \
  namespace Check {                                                           \
  bool class_##CLASS##_has_const_memberfunc_##MEMBERFUNC##_v =                \
      NAMESPACE_TO_CHECK::TASK::                                              \
          class_##CLASS##_has_const_memberfunc_##MEMBERFUNC;                  \
  }

//  End of CLASS_HAS_CONST_MEMBERFUNC

/*

TODO Find a way to check static Member Variable

*/

//? Creates a check to determine if a specific class has a specific
//? static membervariable in the specified namespace
//*V  bool Check::class_'CLASS'_has_static_membervar_'MEMBERVAR'_v
#define CLASS_HAS_STATIC_MEMBERVAR(CLASS, MEMBERVAR)                      \
                                                                          \
  namespace TASK::TESTER {                                                \
  using CLASS = No;                                                       \
  }                                                                       \
  template <typename T, typename = void>                                  \
  struct class_##CLASS##_has_static_membervar_##MEMBERVAR##_sfinae        \
      : std::false_type {};                                               \
  template <typename T>                                                   \
  struct class_##CLASS##_has_static_membervar_##MEMBERVAR##               \
      _sfinae<T, std::void_t<decltype(std::declval<T>().MEMBERVAR)>>      \
      : std::is_member_pointer<T> {};                                     \
                                                                          \
  namespace NAMESPACE_TO_CHECK::TASK {                                    \
  using namespace ::TASK::TESTER;                                         \
  bool class_##CLASS##_has_static_membervar_##MEMBERVAR =                 \
      class_##CLASS##_has_static_membervar_##MEMBERVAR##_sfinae<CLASS>(); \
  }                                                                       \
                                                                          \
  namespace Check {                                                       \
  bool class_##CLASS##_has_static_membervar_##MEMBERVAR##_v =             \
      NAMESPACE_TO_CHECK::TASK::                                          \
          class_##CLASS##_has_static_membervar_##MEMBERVAR;               \
  }

//  End of CLASS_HAS_STATIC_MEMBERVAR

/*

TODO Find a way to check static Member Function

*/

//? Creates a check to determine if a specific class has a specific
//? static memberfunction in the specified namespace
//*F  bool Check::class_'CLASS'_has_static_memberfunc_'MEMBERFUNC'_v
#define CLASS_HAS_STATIC_MEMBERFUNC(CLASS, MEMBERFUNC)                      \
                                                                            \
  namespace TASK::TESTER {                                                  \
  using CLASS = No;                                                         \
  }                                                                         \
  template <typename T, typename = void>                                    \
  struct class_##CLASS##_has_static_memberfunc_##MEMBERFUNC##_sfinae        \
      : std::false_type {};                                                 \
  template <typename T>                                                     \
  struct class_##CLASS##_has_static_memberfunc_##MEMBERFUNC##               \
      _sfinae<T, std::void_t<decltype(std::declval<T>().MEMBERFUNC)>>       \
      : std::is_member_pointer<T> {};                                       \
                                                                            \
  namespace NAMESPACE_TO_CHECK::TASK {                                      \
  using namespace ::TASK::TESTER;                                           \
  bool class_##CLASS##_has_static_memberfunc_##MEMBERFUNC =                 \
      class_##CLASS##_has_static_memberfunc_##MEMBERFUNC##_sfinae<CLASS>(); \
  }                                                                         \
                                                                            \
  namespace Check {                                                         \
  bool class_##CLASS##_has_static_memberfunc_##MEMBERFUNC##_v =             \
      NAMESPACE_TO_CHECK::TASK::                                            \
          class_##CLASS##_has_static_memberfunc_##MEMBERFUNC;               \
  }

//  End of CLASS_HAS_STATIC_MEMBERFUNC

/*



*/

//? Creates a check to determine if a specific class has a specific
//? membervariable of a specific type in the specified namespace
//*V  bool Check::class_'CLASS'_has_membervar_'MEMBERVAR'_of
//*     _type_'TYPE'_v
#define CLASS_HAS_MEMBERVAR_OF_TYPE(CLASS, MEMBERVAR, TYPE)                  \
                                                                             \
  namespace TASK::TESTER {                                                   \
  using CLASS = No;                                                          \
  }                                                                          \
  template <typename T, typename = void>                                     \
  struct class_##CLASS##_has_membervar_##MEMBERVAR##_of_type_##TYPE##_sfinae \
      : std::false_type {};                                                  \
  template <typename T>                                                      \
  struct class_##CLASS##_has_membervar_##MEMBERVAR##_of_type_##TYPE##        \
      _sfinae<T, std::void_t<decltype(std::declval<T>().MEMBERVAR)>>         \
      : std::is_same<decltype(std::declval<T>().MEMBERVAR), TYPE> {};        \
  namespace NAMESPACE_TO_CHECK::TASK {                                       \
  using namespace ::TASK::TESTER;                                            \
  bool class_##CLASS##_has_membervar_##MEMBERVAR##_of_type_##TYPE =          \
      class_##CLASS##_has_membervar_##MEMBERVAR##_of_type_##TYPE##_sfinae<   \
          CLASS>();                                                          \
  }                                                                          \
                                                                             \
  namespace Check {                                                          \
  bool class_##CLASS##_has_membervar_##MEMBERVAR##_of_type_##TYPE##_v =      \
      NAMESPACE_TO_CHECK::TASK::                                             \
          class_##CLASS##_has_membervar_##MEMBERVAR##_of_type_##TYPE;        \
  }

//  End of CLASS_HAS_MEMBERVAR_OF_TYPE

/*



*/

//? Creates a check to determine if a specific class has a specific
//? memberfunction of a specific returntype in the specified namespace
//*F  bool Check::class_'CLASS'_has_memberfunc_'MEMBERFUNC'_of
//*     _returntype_'RETURNTYPE'_v
#define CLASS_HAS_MEMBERFUNC_OF_RETURNTYPE(CLASS, MEMBERFUNC, RETURNTYPE)                \
                                                                                         \
  namespace TASK::TESTER {                                                               \
  using CLASS = No;                                                                      \
  }                                                                                      \
  template <typename T, typename = void>                                                 \
  struct                                                                                 \
      class_##CLASS##_has_memberfunc_##MEMBERFUNC##_of_returntype_##RETURNTYPE##         \
      _sfinae : std::false_type {};                                                      \
  template <typename T>                                                                  \
  struct                                                                                 \
      class_##CLASS##_has_memberfunc_##MEMBERFUNC##_of_returntype_##RETURNTYPE##         \
      _sfinae<T, std::void_t<decltype(std::declval<T>().MEMBERFUNC())>>                  \
      : std::is_same<decltype(std::declval<T>().MEMBERFUNC()), RETURNTYPE> {};           \
  namespace NAMESPACE_TO_CHECK::TASK {                                                   \
  using namespace ::TASK::TESTER;                                                        \
  bool class_##CLASS##_has_memberfunc_##MEMBERFUNC##_of_returntype_##RETURNTYPE =        \
      class_##CLASS##_has_memberfunc_##MEMBERFUNC##_of_returntype_##RETURNTYPE##_sfinae< \
          CLASS>();                                                                      \
  }                                                                                      \
                                                                                         \
  namespace Check {                                                                      \
  bool class_##CLASS##_has_memberfunc_##MEMBERFUNC##_of_returntype_##RETURNTYPE##_v =    \
      NAMESPACE_TO_CHECK::TASK::                                                         \
          class_##CLASS##_has_memberfunc_##MEMBERFUNC##_of_returntype_##RETURNTYPE;      \
  }

//  End of CLASS_HAS_MEMBERFUNC_OF_RETURNTYPE

/*

TODO  Static test

*/

//? Creates a check to determine if a specific class has a specific
//? static membervariable of a specific type in the specified namespace
//*V  bool Check::class_'CLASS'_has_static_membervar_'MEMBERVAR'_of_
//*V    returntype_'TYPE'_v
#define CLASS_HAS_STATIC_MEMBERVAR_OF_TYPE(CLASS, MEMBERVAR, TYPE)

//  End of CLASS_HAS_STATIC_MEMBERVAR_OF_RETURNTYPE

/*

TODO  Static test

*/

//? Creates a check to determine if a specific class has a specific
//? static memberfunction of a specific type in the specified namespace
//*F  bool Check::class_'CLASS'_has_static_membervar_'MEMBERFUNC'_of
//*     _type_'TYPE'_v
#define CLASS_HAS_STATIC_MEMBERFUNC_OF_TYPE(CLASS, MEMBERFUNC, TYPE)

//  End of CLASS_HAS_STATIC_MEMBERFUNC_OF_TYPE

/*



*/

//? Creates a check to determine if the specified namespace has a specific
//? free function
//* bool Check::has_free_function_'FUNCTIONNAME'_v
#define HAS_FREE_FUNCTION(FUNCTION)                                            \
                                                                               \
  namespace TASK::TESTER {                                                     \
  special_return_type FUNCTION();                                              \
  }                                                                            \
  namespace NAMESPACE_TO_CHECK::TASK {                                         \
  using namespace ::TASK::TESTER;                                              \
  template <typename T, typename = void>                                       \
  struct has_free_function_##FUNCTION##_sfinae : std::false_type {};           \
  template <typename T>                                                        \
  struct has_free_function_##FUNCTION##                                        \
      _sfinae<T, std::void_t<decltype(FUNCTION)>>                              \
      : std::conjunction<std::is_function<decltype(FUNCTION)>,                 \
                         std::negation<std::is_same<decltype(FUNCTION),        \
                                                    special_return_type()>>> { \
  };                                                                           \
  template <typename T>                                                        \
  struct has_free_function_##FUNCTION {                                        \
    static constexpr bool value = has_free_function_##FUNCTION##_sfinae<T>();  \
  };                                                                           \
  bool has_free_function_##FUNCTION##_v =                                      \
      has_free_function_##FUNCTION<decltype(FUNCTION)>::value;                 \
  }                                                                            \
                                                                               \
  namespace Check {                                                            \
  bool has_free_function_##FUNCTION##_v =                                      \
      NAMESPACE_TO_CHECK::TASK::has_free_function_##FUNCTION##_v;              \
  }

//* Fallback Free Function/ Variable
namespace TASK::TESTER {
struct special_return_type {};
}  // namespace TASK::TESTER

//  End of HAS_FREE_FUNCTION

/*



*/

//? Creates a check to determine if the specified namespace has a specific
//? free function of a specific returntype
//* bool Check::has_free_function_'FUNCTION'_of_returntype_'RETURNTYPE'_v
#define HAS_FREE_FUNCTION_OF_RETURNTYPE(FUNCTION, RETURNTYPE)                \
                                                                             \
  namespace TASK::TESTER {                                                   \
  special_return_type FUNCTION();                                            \
  }                                                                          \
  namespace NAMESPACE_TO_CHECK::TASK {                                       \
  using namespace ::TASK::TESTER;                                            \
  template <typename T, typename = void>                                     \
  struct has_free_function_##FUNCTION##_of_returntype_##RETURNTYPE##_sfinae  \
      : std::false_type {};                                                  \
  template <typename T>                                                      \
  struct has_free_function_##FUNCTION##_of_returntype_##RETURNTYPE##         \
      _sfinae<T, std::void_t<decltype(FUNCTION)>>                            \
      : std::conjunction<std::is_function<decltype(FUNCTION)>,               \
                         std::is_same<decltype(FUNCTION), RETURNTYPE()>> {}; \
  template <typename T>                                                      \
  struct has_free_function_##FUNCTION##_of_returntype_##RETURNTYPE {         \
    static constexpr bool value =                                            \
        has_free_function_##FUNCTION##_of_returntype_##RETURNTYPE##_sfinae<  \
            T>();                                                            \
  };                                                                         \
  bool has_free_function_##FUNCTION##_of_returntype_##RETURNTYPE##_v =       \
      has_free_function_##FUNCTION##_of_returntype_##RETURNTYPE<             \
          decltype(FUNCTION)>::value;                                        \
  }                                                                          \
                                                                             \
  namespace Check {                                                          \
  bool has_free_function_##FUNCTION##_of_returntype_##RETURNTYPE##_v =       \
      NAMESPACE_TO_CHECK::TASK::                                             \
          has_free_function_##FUNCTION##_of_returntype_##RETURNTYPE##_v;     \
  }

//  End of HAS_FREE_FUNCTION_OF_TYPE

/*



*/

//? Creates a check to determine if the specified namespace has a specific
//? free variable
//* bool Check::has_free_variable_'VARIABLE'_v
#define HAS_FREE_VARIABLE(VARIABLE)                                            \
                                                                               \
  namespace TASK::TESTER {                                                     \
  special_return_type VARIABLE{};                                              \
  }                                                                            \
  namespace NAMESPACE_TO_CHECK::TASK {                                         \
  using namespace ::TASK::TESTER;                                              \
  template <typename T, typename = void>                                       \
  struct has_free_variable_##VARIABLE##_sfinae : std::false_type {};           \
  template <typename T>                                                        \
  struct has_free_variable_##VARIABLE##                                        \
      _sfinae<T, std::void_t<decltype(VARIABLE)>>                              \
      : std::conjunction<std::is_object<decltype(VARIABLE)>,                   \
                         std::negation<std::is_same<decltype(VARIABLE),        \
                                                    special_return_type>>> {}; \
  template <typename T>                                                        \
  struct has_free_variable_##VARIABLE {                                        \
    static constexpr bool value =                                              \
        has_free_variable_##VARIABLE##_sfinae<T>::value;                       \
  };                                                                           \
  bool has_free_variable_##VARIABLE##_v =                                      \
      has_free_variable_##VARIABLE<decltype(VARIABLE)>::value;                 \
  }                                                                            \
                                                                               \
  namespace Check {                                                            \
  bool has_free_variable_##VARIABLE##_v =                                      \
      NAMESPACE_TO_CHECK::TASK::has_free_variable_##VARIABLE##_v;              \
  }

//  End of HAS_FREE_VARIABLE

/*



*/

//? Creates a check to determine if the specified namespace has a specific
//? free variable of a specific type
//* bool Check::has_free_variable_'VARIABLE'_of_type_'TYPE'_v
#define HAS_FREE_VARIABLE_OF_TYPE(VARIABLE, TYPE)                         \
                                                                          \
  namespace TASK::TESTER {                                                \
  special_return_type VARIABLE{};                                         \
  }                                                                       \
  namespace NAMESPACE_TO_CHECK::TASK {                                    \
  using namespace ::TASK::TESTER;                                         \
  template <typename T, typename = void>                                  \
  struct has_free_variable_##VARIABLE##_of_type_##TYPE##_sfinae           \
      : std::false_type {};                                               \
  template <typename T>                                                   \
  struct has_free_variable_##VARIABLE##_of_type_##TYPE##                  \
      _sfinae<T, std::void_t<decltype(VARIABLE)>>                         \
      : std::conjunction<std::is_object<decltype(VARIABLE)>,              \
                         std::is_same<decltype(VARIABLE), TYPE>> {};      \
  template <typename T>                                                   \
  struct has_free_variable_##VARIABLE##_of_type_##TYPE {                  \
    static constexpr bool value =                                         \
        has_free_variable_##VARIABLE##_of_type_##TYPE##_sfinae<T>::value; \
  };                                                                      \
  bool has_free_variable_##VARIABLE##_of_type_##TYPE##_v =                \
      has_free_variable_##VARIABLE##_of_type_##TYPE<                      \
          decltype(VARIABLE)>::value;                                     \
  }                                                                       \
                                                                          \
  namespace Check {                                                       \
  bool has_free_variable_##VARIABLE##_of_type_##TYPE##_v =                \
      NAMESPACE_TO_CHECK::TASK::                                          \
          has_free_variable_##VARIABLE##_of_type_##TYPE##_v;              \
  }

//  End of HAS_FREE_VARIABLE_OF_TYPE

/*
!   Find a way to either switch between calling main() and
!   main(int argc, char**argv) or make 2 CCPChecker and which one fails has
!   the wrong main
*/

//? Creates a check to determine if the specified namespace outputs
//? the right string into std::cout
//* bool Check::is_output_same_v
#define IS_OUTPUT_SAME(TEXT)                                                  \
                                                                              \
  namespace NAMESPACE_TO_CHECK::TASK {                                        \
  using namespace ::TASK::TESTER;                                             \
  bool check_namespace_output() {                                             \
    std::stringstream output_stream;                                          \
    std::streambuf* std_buffer = std::cout.rdbuf(output_stream.rdbuf());      \
    main(); /*main(1, nullptr) for int main(int argc, char** argv)*/          \
    /*main(); For int main()*/                                                \
    std::cout.rdbuf(std_buffer);                                              \
    std::string NamespaceOutput_arg = output_stream.str();                    \
    return TEXT == NamespaceOutput_arg;                                       \
  }                                                                           \
  }                                                                           \
                                                                              \
  namespace Check {                                                           \
  bool is_output_same_v = NAMESPACE_TO_CHECK::TASK::check_namespace_output(); \
  }

//* Fallback for main
namespace TASK::TESTER {
int main() {
  std::cout << "#" << std::endl;
  return 0;
}

int main(int argc, char** argv) {
  std::cout << "#" << std::endl;
  return 0;
}

}  // namespace TASK::TESTER

//  End of IS_OUTPUT_SAME

#endif