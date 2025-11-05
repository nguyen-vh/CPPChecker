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

#ifndef CXXCHECKER_HPP
#define CXXCHECKER_HPP

//----------------------------------------------------------------------------//
//*                             === INCLUDES ===                             *//
//----------------------------------------------------------------------------//

#include <concepts>
#include <iostream>
#include <sstream>
#include <type_traits>

//----------------------------------------------------------------------------//
//*                          === LIST OF MACROS ===                          *//
//----------------------------------------------------------------------------//

// HAS_CLASS(CLASS)
// CLASS_HAS_MEMBERVAR(CLASS, MEMBERVAR)
// CLASS_HAS_MEMBERFUNC(CLASS, MEMBERFUNC)
// CLASS_HAS_CONST_MEMBERFUNC(CLASS, MEMBERFUNC)
//
//
//! CLASS_HAS_STATIC_MEMBERVAR(CLASS, MEMBERVAR)
// CLASS_HAS_STATIC_MEMBERFUNC(CLASS, MEMBERFUNC)
// CLASS_HAS_MEMBERVAR_OF_TYPE(CLASS, MEMBERVAR, TYPE)
// CLASS_HAS_MEMBERFUNC_OF_RETURNTYPE(CLASS, MEMBERFUNC, RETURNTYPE)
//! CLASS_HAS_STATIC_MEMBERVAR_OF_TYPE(CLASS, MEMBERVAR, TYPE)
//! CLASS_HAS_STATIC_MEMBERFUNC_OF_RETURNTYPE(CLASS, MEMBERFUNC, RETURNTYPE)
//! HAS_FREE_FUNCTION(FUNCTION)
//! HAS_FREE_FUNCTION_OF_RETURNTYPE(FUNCTION, RETURNTYPE)
//! HAS_FREE_VARIABLE(VARIABLE)
//! HAS_FREE_VARIABLE_OF_TYPE(VARIABLE, TYPE)
// IS_OUTPUT_SAME(TEXT)

// overloaded functions
// templated member functions

//----------------------------------------------------------------------------//

//? Defines the namespace in which the code can be tested
#define NAMESPACE_TO_CHECK check_in_here

//----------------------------------------------------------------------------//
//*                             === FALLBACK ===                             *//
//----------------------------------------------------------------------------//
namespace condition::tester {
struct FallbackClass {};

struct FallbackReturntype {};

int main() {
  std::cout << "#" << std::endl;
  return 0;
}

int main(int argc, char** argv) {
  std::cout << "#" << std::endl;
  return 0;
}
}  // namespace condition::tester

//----------------------------------------------------------------------------//
//*                         === HAS_CLASS(CLASS) ===                         *//
//----------------------------------------------------------------------------//
// TODO: Refactor with c++26 Reflection because this is not failsafe right now

//? Creates a check to determine if a specific class exists in
//? the specified namespace
//-> bool check::has_class_'CLASS'_v
#define HAS_CLASS(CLASS)                                \
  namespace condition::tester {                         \
  using CLASS = FallbackClass;                          \
  }                                                     \
  namespace NAMESPACE_TO_CHECK::condition {             \
  using namespace ::condition::tester;                  \
  inline constexpr bool has_class_##CLASS =             \
      /*std::is_class_v<CLASS> &&*/ std::negation_v<    \
          std::is_same<CLASS, FallbackClass>>;          \
  }                                                     \
  namespace check {                                     \
  inline constexpr bool has_class_##CLASS##_v =         \
      NAMESPACE_TO_CHECK::condition::has_class_##CLASS; \
  }

//----------------------------------------------------------------------------//
//*              === CLASS_HAS_MEMBERVAR(CLASS, MEMBERVAR) ===               *//
//----------------------------------------------------------------------------//

//? Creates a check to determine if a specific class has a specific
//? membervariable in the specified namespace
//-> bool check::class_'CLASS'_has_membervar_'MEMBERVAR'_v
#define CLASS_HAS_MEMBERVAR(CLASS, MEMBERVAR)                           \
  namespace condition::tester {                                         \
  using CLASS = FallbackClass;                                          \
  }                                                                     \
  template <typename T>                                                 \
  concept Class##CLASS##HasMembervar##MEMBERVAR =                       \
      requires(T a) { a.MEMBERVAR; };                                   \
  namespace NAMESPACE_TO_CHECK::condition {                             \
  using namespace ::condition::tester;                                  \
  inline constexpr bool class_##CLASS##_has_membervar_##MEMBERVAR =     \
      Class##CLASS##HasMembervar##MEMBERVAR<CLASS>;                     \
  }                                                                     \
  namespace check {                                                     \
  inline constexpr bool class_##CLASS##_has_membervar_##MEMBERVAR##_v = \
      NAMESPACE_TO_CHECK::condition::                                   \
          class_##CLASS##_has_membervar_##MEMBERVAR;                    \
  }

//----------------------------------------------------------------------------//
//*             === CLASS_HAS_MEMBERFUNC(CLASS, MEMBERFUNC) ===              *//
//----------------------------------------------------------------------------//

//? Creates a check to determine if a specific class has a specific
//? memberfunction in the specified namespace
//-> bool check::class_'CLASS'_has_memberfunc_'MEMBERFUNC'_v
#define CLASS_HAS_MEMBERFUNC(CLASS, MEMBERFUNC)                           \
  namespace condition::tester {                                           \
  using CLASS = FallbackClass;                                            \
  }                                                                       \
  template <typename T>                                                   \
  concept Class##CLASS##HasMemberfunc##MEMBERFUNC =                       \
      requires(T a) { a.MEMBERFUNC(); };                                  \
  namespace NAMESPACE_TO_CHECK::condition {                               \
  using namespace ::condition::tester;                                    \
  inline constexpr bool class_##CLASS##_has_memberfunc_##MEMBERFUNC =     \
      Class##CLASS##HasMemberfunc##MEMBERFUNC<CLASS>;                     \
  }                                                                       \
  namespace check {                                                       \
  inline constexpr bool class_##CLASS##_has_memberfunc_##MEMBERFUNC##_v = \
      NAMESPACE_TO_CHECK::condition::                                     \
          class_##CLASS##_has_memberfunc_##MEMBERFUNC;                    \
  }

//----------------------------------------------------------------------------//
//*          === CLASS_HAS_CONST_MEMBERFUNC(CLASS, MEMBERFUNC) ===           *//
//----------------------------------------------------------------------------//

//? Creates a check to determine if a specific class has a specific
//? const memberfunction in the specified namespace
//-> bool check::class_'CLASS'_has_const_memberfunc_'MEMBERFUNC'_v
#define CLASS_HAS_CONST_MEMBERFUNC(CLASS, MEMBERFUNC)                       \
  namespace condition::tester {                                             \
  using CLASS = FallbackClass;                                              \
  }                                                                         \
  template <typename T>                                                     \
  concept Class##CLASS##HasConstMemberfunc##MEMBERFUNC =                    \
      requires(const T a) { a.MEMBERFUNC(); };                              \
  namespace NAMESPACE_TO_CHECK::condition {                                 \
  using namespace ::condition::tester;                                      \
  inline constexpr bool class_##CLASS##_has_const_memberfunc_##MEMBERFUNC = \
      Class##CLASS##HasConstMemberfunc##MEMBERFUNC<CLASS>;                  \
  }                                                                         \
  namespace check {                                                         \
  inline constexpr bool                                                     \
      class_##CLASS##_has_const_memberfunc_##MEMBERFUNC##_v =               \
          NAMESPACE_TO_CHECK::condition::                                   \
              class_##CLASS##_has_const_memberfunc_##MEMBERFUNC;            \
  }

//----------------------------------------------------------------------------//
//*!          === CLASS_HAS_STATIC_MEMBERVAR(CLASS, MEMBERVAR) ===           *//
//----------------------------------------------------------------------------//
// TODO: LIMIT TO STATIC
// (requires!std::is_member_pointer_v<decltype(T::MEMBERVAR)>;)

//? Creates a check to determine if a specific class has a specific
//? static membervariable in the specified namespace
//-> bool check::class_'CLASS'_has_static_membervar_'MEMBERVAR'_v
#define CLASS_HAS_STATIC_MEMBERVAR(CLASS, MEMBERVAR)                           \
  namespace condition::tester {                                                \
  using CLASS = FallbackClass;                                                 \
  }                                                                            \
  template <typename T>                                                        \
  concept Class##CLASS##HasStaticMembervar##MEMBERVAR =                        \
      requires { T::MEMBERVAR; };                                              \
  namespace NAMESPACE_TO_CHECK::condition {                                    \
  using namespace ::condition::tester;                                         \
  inline constexpr bool class_##CLASS##_has_static_membervar_##MEMBERVAR =     \
      Class##CLASS##HasStaticMembervar##MEMBERVAR<CLASS>;                      \
  }                                                                            \
  namespace check {                                                            \
  inline constexpr bool class_##CLASS##_has_static_membervar_##MEMBERVAR##_v = \
      NAMESPACE_TO_CHECK::condition::                                          \
          class_##CLASS##_has_static_membervar_##MEMBERVAR;                    \
  }

//----------------------------------------------------------------------------//
//*          === CLASS_HAS_STATIC_MEMBERFUNC(CLASS, MEMBERFUNC) ===          *//
//----------------------------------------------------------------------------//

//? Creates a check to determine if a specific class has a specific
//? static memberfunction in the specified namespace
//-> bool check::class_'CLASS'_has_static_memberfunc_'MEMBERFUNC'_v
#define CLASS_HAS_STATIC_MEMBERFUNC(CLASS, MEMBERFUNC)                       \
  namespace condition::tester {                                              \
  using CLASS = FallbackClass;                                               \
  }                                                                          \
  template <typename T>                                                      \
  concept Class##CLASS##HasStaticMemberfunc##MEMBERFUNC =                    \
      requires { T::MEMBERFUNC(); };                                         \
  namespace NAMESPACE_TO_CHECK::condition {                                  \
  using namespace ::condition::tester;                                       \
  inline constexpr bool class_##CLASS##_has_static_memberfunc_##MEMBERFUNC = \
      Class##CLASS##HasStaticMemberfunc##MEMBERFUNC<CLASS>;                  \
  }                                                                          \
  namespace check {                                                          \
  inline constexpr bool                                                      \
      class_##CLASS##_has_static_memberfunc_##MEMBERFUNC##_v =               \
          NAMESPACE_TO_CHECK::condition::                                    \
              class_##CLASS##_has_static_memberfunc_##MEMBERFUNC;            \
  }

//----------------------------------------------------------------------------//
//*       === CLASS_HAS_MEMBERVAR_OF_TYPE(CLASS, MEMBERVAR, TYPE) ===        *//
//----------------------------------------------------------------------------//

//? Creates a check to determine if a specific class has a specific
//? membervariable of a specific type in the specified namespace
//-> bool check::class_'CLASS'_has_membervar_'MEMBERVAR'_of_type_'TYPE'_v
#define CLASS_HAS_MEMBERVAR_OF_TYPE(CLASS, MEMBERVAR, TYPE)                \
  namespace condition::tester {                                            \
  using CLASS = FallbackClass;                                             \
  }                                                                        \
  template <typename T>                                                    \
  concept Class##CLASS##HasMembervar##MEMBERVAR##OfType##TYPE = requires { \
    requires std::is_same_v<decltype(std::declval<T>().MEMBERVAR), TYPE>;  \
  };                                                                       \
  namespace NAMESPACE_TO_CHECK::condition {                                \
  using namespace ::condition::tester;                                     \
  inline constexpr bool                                                    \
      class_##CLASS##_has_membervar_##MEMBERVAR##_of_type_##TYPE =         \
          Class##CLASS##HasMembervar##MEMBERVAR##OfType##TYPE<CLASS>;      \
  }                                                                        \
  namespace check {                                                        \
  inline constexpr bool                                                    \
      class_##CLASS##_has_membervar_##MEMBERVAR##_of_type_##TYPE##_v =     \
          NAMESPACE_TO_CHECK::condition::                                  \
              class_##CLASS##_has_membervar_##MEMBERVAR##_of_type_##TYPE;  \
  }

//----------------------------------------------------------------------------//
//*=== CLASS_HAS_MEMBERFUNC_OF_RETURNTYPE(CLASS, MEMBERFUNC, RETURNTYPE) === *//
//----------------------------------------------------------------------------//

//? Creates a check to determine if a specific class has a specific
//? memberfunction of a specific returntype in the specified namespace
//-> bool
// check::class_'CLASS'_has_memberfunc_'MEMBERFUNC'_of_returntype_'RETURNTYPE'_v

#define CLASS_HAS_MEMBERFUNC_OF_RETURNTYPE(CLASS, MEMBERFUNC, RETURNTYPE)               \
  namespace condition::tester {                                                         \
  using CLASS = FallbackClass;                                                          \
  }                                                                                     \
  template <typename T>                                                                 \
  concept Class##CLASS##HasMemberfunc##MEMBERFUNC##OfReturntype##RETURNTYPE =           \
      requires(T a) {                                                                   \
        { a.MEMBERFUNC() } -> std::same_as<RETURNTYPE>;                                 \
      };                                                                                \
  namespace NAMESPACE_TO_CHECK::condition {                                             \
  using namespace ::condition::tester;                                                  \
  inline constexpr bool                                                                 \
      class_##CLASS##_has_memberfunc_##MEMBERFUNC##_of_returntype_##RETURNTYPE =        \
          Class##CLASS##HasMemberfunc##MEMBERFUNC##OfReturntype##RETURNTYPE<            \
              CLASS>;                                                                   \
  }                                                                                     \
  namespace check {                                                                     \
  inline constexpr bool                                                                 \
      class_##CLASS##_has_memberfunc_##MEMBERFUNC##_of_returntype_##RETURNTYPE##_v =    \
          NAMESPACE_TO_CHECK::condition::                                               \
              class_##CLASS##_has_memberfunc_##MEMBERFUNC##_of_returntype_##RETURNTYPE; \
  }

//----------------------------------------------------------------------------//
//*!   === CLASS_HAS_STATIC_MEMBERVAR_OF_TYPE(CLASS, MEMBERVAR, TYPE) ===    *//
//----------------------------------------------------------------------------//

//? Creates a check to determine if a specific class has a specific
//? static membervariable of a specific type in the specified namespace
//-> bool
// check::class_'CLASS'_has_static_membervar_'MEMBERVAR'_of_returntype_'TYPE'_v
#define CLASS_HAS_STATIC_MEMBERVAR_OF_TYPE(CLASS, MEMBERVAR, TYPE)

//----------------------------------------------------------------------------//
//*   === CLASS_HAS_STATIC_MEMBERFUNC_OF_TYPE(CLASS, MEMBERFUNC, TYPE) ===   *//
//----------------------------------------------------------------------------//

//? Creates a check to determine if a specific class has a specific
//? static memberfunction of a specific type in the specified namespace
//-> bool
// check::class_'CLASS'_has_static_membervar_'MEMBERFUNC'_of_type_'TYPE'_v
#define CLASS_HAS_STATIC_MEMBERFUNC_OF_TYPE(CLASS, MEMBERFUNC, TYPE)               \
  namespace condition::tester {                                                    \
  using CLASS = FallbackClass;                                                     \
  }                                                                                \
  template <typename T>                                                            \
  concept Class##CLASS##HasStaticMemberfunc##MEMBERFUNC##OfType##TYPE =            \
      requires {                                                                   \
        { T::MEMBERFUNC() } -> std::same_as<TYPE>;                                 \
      };                                                                           \
  namespace NAMESPACE_TO_CHECK::condition {                                        \
  using namespace ::condition::tester;                                             \
  inline constexpr bool                                                            \
      class_##CLASS##_has_static_memberfunc_##MEMBERFUNC##_of_type_##TYPE =        \
          Class##CLASS##HasStaticMemberfunc##MEMBERFUNC##OfType##TYPE<CLASS>;      \
  }                                                                                \
  namespace check {                                                                \
  inline constexpr bool                                                            \
      class_##CLASS##_has_static_memberfunc_##MEMBERFUNC##_of_type_##TYPE##_v =    \
          NAMESPACE_TO_CHECK::condition::                                          \
              class_##CLASS##_has_static_memberfunc_##MEMBERFUNC##_of_type_##TYPE; \
  }

//----------------------------------------------------------------------------//
//*!                   === HAS_FREE_FUNCTION(FUNCTION) ===                   *//
//----------------------------------------------------------------------------//
// TODO: FIND A WAY WITH CONCEPTS

//? Creates a check to determine if the specified namespace has a specific
//? free function
//-> bool check::has_free_function_'FUNCTION'_v

#define HAS_FREE_FUNCTION(FUNCTION)                                           \
                                                                              \
  namespace condition::tester {                                               \
  FallbackReturntype FUNCTION();                                              \
  }                                                                           \
  namespace NAMESPACE_TO_CHECK::condition {                                   \
  using namespace ::condition::tester;                                        \
  template <typename T, typename = void>                                      \
  struct has_free_function_##FUNCTION##_sfinae : std::false_type {};          \
  template <typename T>                                                       \
  struct has_free_function_##FUNCTION##_sfinae<T, std::void_t<T>>             \
      : std::conjunction<                                                     \
            std::is_function<T>,                                              \
            std::negation<std::is_same<T, FallbackReturntype()>>> {};         \
  template <typename T>                                                       \
  struct has_free_function_##FUNCTION {                                       \
    static constexpr bool value = has_free_function_##FUNCTION##_sfinae<T>(); \
  };                                                                          \
  inline constexpr bool has_free_function_##FUNCTION##_v =                    \
      has_free_function_##FUNCTION<decltype(FUNCTION)>::value;                \
  }                                                                           \
                                                                              \
  namespace check {                                                           \
  inline constexpr bool has_free_function_##FUNCTION##_v =                    \
      NAMESPACE_TO_CHECK::condition::has_free_function_##FUNCTION##_v;        \
  }

//----------------------------------------------------------------------------//
//*!     === HAS_FREE_FUNCTION_OF_RETURNTYPE(FUNCTION, RETURNTYPE) ===       *//
//----------------------------------------------------------------------------//
// TODO: SAME AS ABOVE

//? Creates a check to determine if the specified namespace has a specific
//? free function of a specific returntype
//-> bool check::has_free_function_'FUNCTION'_of_returntype_'RETURNTYPE'_v
#define HAS_FREE_FUNCTION_OF_RETURNTYPE(FUNCTION, RETURNTYPE)                  \
  namespace condition::tester {                                                \
  FallbackReturntype FUNCTION();                                               \
  }                                                                            \
  namespace NAMESPACE_TO_CHECK::condition {                                    \
  using namespace ::condition::tester;                                         \
  template <typename T, typename = void>                                       \
  struct has_free_function_##FUNCTION##_of_returntype_##RETURNTYPE##_sfinae    \
      : std::false_type {};                                                    \
  template <typename T>                                                        \
  struct has_free_function_##FUNCTION##_of_returntype_##RETURNTYPE##           \
      _sfinae<T, std::void_t<T>>                                               \
      : std::conjunction<std::is_function<T>, std::is_same<T, RETURNTYPE()>> { \
  };                                                                           \
  template <typename T>                                                        \
  struct has_free_function_##FUNCTION##_of_returntype_##RETURNTYPE {           \
    static constexpr bool value =                                              \
        has_free_function_##FUNCTION##_of_returntype_##RETURNTYPE##_sfinae<    \
            T>();                                                              \
  };                                                                           \
  inline constexpr bool                                                        \
      has_free_function_##FUNCTION##_of_returntype_##RETURNTYPE##_v =          \
          has_free_function_##FUNCTION##_of_returntype_##RETURNTYPE<           \
              decltype(FUNCTION)>::value;                                      \
  }                                                                            \
  namespace check {                                                            \
  inline constexpr bool                                                        \
      has_free_function_##FUNCTION##_of_returntype_##RETURNTYPE##_v =          \
          NAMESPACE_TO_CHECK::condition::                                      \
              has_free_function_##FUNCTION##_of_returntype_##RETURNTYPE##_v;   \
  }

//----------------------------------------------------------------------------//
//*!                   === HAS_FREE_VARIABLE(VARIABLE) ===                   *//
//----------------------------------------------------------------------------//

//? Creates a check to determine if the specified namespace has a specific
//? free variable
//-> bool check::has_free_variable_'VARIABLE'_v
#define HAS_FREE_VARIABLE(VARIABLE)                                           \
                                                                              \
  namespace condition::tester {                                               \
  FallbackReturntype VARIABLE{};                                              \
  }                                                                           \
  namespace NAMESPACE_TO_CHECK::condition {                                   \
  using namespace ::condition::tester;                                        \
  template <typename T, typename = void>                                      \
  struct has_free_variable_##VARIABLE##_sfinae : std::false_type {};          \
  template <typename T>                                                       \
  struct has_free_variable_##VARIABLE##                                       \
      _sfinae<T, std::void_t<decltype(VARIABLE)>>                             \
      : std::conjunction<std::is_object<decltype(VARIABLE)>,                  \
                         std::negation<std::is_same<decltype(VARIABLE),       \
                                                    FallbackReturntype>>> {}; \
  template <typename T>                                                       \
  struct has_free_variable_##VARIABLE {                                       \
    static constexpr bool value =                                             \
        has_free_variable_##VARIABLE##_sfinae<T>::value;                      \
  };                                                                          \
  inline constexpr bool has_free_variable_##VARIABLE##_v =                    \
      has_free_variable_##VARIABLE<decltype(VARIABLE)>::value;                \
  }                                                                           \
                                                                              \
  namespace check {                                                           \
  inline constexpr bool has_free_variable_##VARIABLE##_v =                    \
      NAMESPACE_TO_CHECK::condition::has_free_variable_##VARIABLE##_v;        \
  }

//----------------------------------------------------------------------------//
//*!            === HAS_FREE_VARIABLE_OF_TYPE(VARIABLE, TYPE) ===            *//
//----------------------------------------------------------------------------//

//? Creates a check to determine if the specified namespace has a specific
//? free variable of a specific type
//-> bool check::has_free_variable_'VARIABLE'_of_type_'TYPE'_v
#define HAS_FREE_VARIABLE_OF_TYPE(VARIABLE, TYPE)                           \
                                                                            \
  namespace condition::tester {                                             \
  FallbackReturntype VARIABLE{};                                            \
  }                                                                         \
  namespace NAMESPACE_TO_CHECK::condition {                                 \
  using namespace ::condition::tester;                                      \
  template <typename T, typename = void>                                    \
  struct has_free_variable_##VARIABLE##_of_type_##TYPE##_sfinae             \
      : std::false_type {};                                                 \
  template <typename T>                                                     \
  struct has_free_variable_##VARIABLE##_of_type_##TYPE##                    \
      _sfinae<T, std::void_t<decltype(VARIABLE)>>                           \
      : std::conjunction<std::is_object<decltype(VARIABLE)>,                \
                         std::is_same<decltype(VARIABLE), TYPE>> {};        \
  template <typename T>                                                     \
  struct has_free_variable_##VARIABLE##_of_type_##TYPE {                    \
    static constexpr bool value =                                           \
        has_free_variable_##VARIABLE##_of_type_##TYPE##_sfinae<T>::value;   \
  };                                                                        \
  inline constexpr bool has_free_variable_##VARIABLE##_of_type_##TYPE##_v = \
      has_free_variable_##VARIABLE##_of_type_##TYPE<                        \
          decltype(VARIABLE)>::value;                                       \
  }                                                                         \
                                                                            \
  namespace check {                                                         \
  inline constexpr bool has_free_variable_##VARIABLE##_of_type_##TYPE##_v = \
      NAMESPACE_TO_CHECK::condition::                                       \
          has_free_variable_##VARIABLE##_of_type_##TYPE##_v;                \
  }

//----------------------------------------------------------------------------//
//*                      === IS_OUTPUT_SAME(TEXT)  ===                       *//
//----------------------------------------------------------------------------//

//? Creates a check to determine if the specified namespace outputs
//? the right string into std::cout
//-> bool check::is_output_same_v
#define IS_OUTPUT_SAME(TEXT)                                             \
  namespace NAMESPACE_TO_CHECK::condition {                              \
  using namespace ::condition::tester;                                   \
  bool check_namespace_output() {                                        \
    std::stringstream output_stream;                                     \
    std::streambuf* std_buffer = std::cout.rdbuf(output_stream.rdbuf()); \
    main(1, nullptr);                                                    \
    /*main(1, nullptr); For int main(int argc, char** argv)*/            \
    /*main(); For int main()*/                                           \
    std::cout.rdbuf(std_buffer);                                         \
    std::string namespace_output_arg = output_stream.str();              \
    return namespace_output_arg == TEXT;                                 \
  }                                                                      \
  }                                                                      \
  namespace check {                                                      \
  inline constexpr bool is_output_same_v =                               \
      NAMESPACE_TO_CHECK::condition::check_namespace_output();           \
  }

#endif  // CXXCHECKER_HPP
