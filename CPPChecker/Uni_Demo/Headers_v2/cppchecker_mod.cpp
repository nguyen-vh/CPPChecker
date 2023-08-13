#include <iostream>
#include <sstream>
#include <type_traits>

//? Defines the namespace to be checked
#define NAMESPACE_TO_CHECK STUDENT

//! Call Macros in global namespace

/*
All Macros

HAS_CLASS(CLASS)
CLASS_HAS_MEMBERVAR(CLASS, MEMBER)
CLASS_HAS_MEMBERFUNC(CLASS, MEMBER)
?   CLASS_HAS_STATIC_MEMBERVAR(CLASS, MEMBER)
?   CLASS_HAS_STATIC_MEMBERFUNC(CLASS, MEMBER)
CLASS_HAS_MEMBERVAR_OF_TYPE(CLASS, MEMBER, TYPE)
CLASS_HAS_MEMBERFUNC_OF_TYPE(CLASS, MEMBER, TYPE)
?   CLASS_HAS_STATIC_MEMBERVAR_OF_TYPE(CLASS, MEMBER, TYPE)
?   CLASS_HAS_STATIC_MEMBERFUNC_OF_TYPE(CLASS, MEMBER, TYPE)
HAS_FREE_FUNCTION(FUNCTION)
HAS_FREE_FUNCTION_OF_TYPE(FUNCTION, TYPE)
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
//*V  bool Check::class_'CLASS'_has_membervar_'MEMBER'_v
#define CLASS_HAS_MEMBERVAR(CLASS, MEMBER)                                     \
                                                                               \
  namespace TASK::TESTER {                                                     \
  using CLASS = No;                                                            \
  }                                                                            \
  template <typename T, typename = void>                                       \
  struct class_##CLASS##_has_membervar_##MEMBER##_sfinae : std::false_type {}; \
  template <typename T>                                                        \
  struct class_##CLASS##_has_membervar_##MEMBER##_sfinae<                      \
      T, std::void_t<decltype(std::declval<T>().MEMBER)>> : std::true_type {}; \
  namespace NAMESPACE_TO_CHECK::TASK {                                         \
  using namespace ::TASK::TESTER;                                              \
  bool class_##CLASS##_has_membervar_##MEMBER =                                \
      class_##CLASS##_has_membervar_##MEMBER##_sfinae<CLASS>();                \
  }                                                                            \
                                                                               \
  namespace Check {                                                            \
  bool class_##CLASS##_has_membervar_##MEMBER##_v =                            \
      NAMESPACE_TO_CHECK::TASK::class_##CLASS##_has_membervar_##MEMBER;        \
  }

//  End of CLASS_HAS_MEMBERVAR

/*



*/

//? Creates a check to determine if a specific class has a specific
//? memberfunction in the specified namespace
//*F  bool Check::class_'CLASS'_has_memberfunc_'MEMBER'_v
#define CLASS_HAS_MEMBERFUNC(CLASS, MEMBER)                                    \
                                                                               \
  namespace TASK::TESTER {                                                     \
  using CLASS = No;                                                            \
  }                                                                            \
  template <typename T, typename = void>                                       \
  struct class_##CLASS##_has_memberfunc_##MEMBER##_sfinae : std::false_type {  \
  };                                                                           \
  template <typename T>                                                        \
  struct class_##CLASS##_has_memberfunc_##MEMBER##_sfinae<                     \
      T, std::void_t<decltype(std::declval<T>().MEMBER())>> : std::true_type { \
  };                                                                           \
  namespace NAMESPACE_TO_CHECK::TASK {                                         \
  using namespace ::TASK::TESTER;                                              \
  bool class_##CLASS##_has_memberfunc_##MEMBER =                               \
      class_##CLASS##_has_memberfunc_##MEMBER##_sfinae<CLASS>();               \
  }                                                                            \
                                                                               \
  namespace Check {                                                            \
  bool class_##CLASS##_has_memberfunc_##MEMBER##_v =                           \
      NAMESPACE_TO_CHECK::TASK::class_##CLASS##_has_memberfunc_##MEMBER;       \
  }

//  End of CLASS_HAS_MEMBERFUNC

/*

TODO Find a way to check static Member Variable

*/

//? Creates a check to determine if a specific class has a specific
//? static membervariable in the specified namespace
//*V  bool Check::class_'CLASS'_has_static_membervar_'MEMBER'_v
#define CLASS_HAS_STATIC_MEMBERVAR(CLASS, MEMBER)                              \
                                                                               \
  namespace TASK::TESTER {                                                     \
  using CLASS = No;                                                            \
  }                                                                            \
  template <typename T, typename = void>                                       \
  struct class_##CLASS##_has_static_membervar_##MEMBER##_sfinae                \
      : std::false_type {};                                                    \
  template <typename T>                                                        \
  struct class_##CLASS##_has_static_membervar_##MEMBER##_sfinae<               \
      T, std::void_t<decltype(std::declval<T>().MEMBER)>>                      \
      : std::is_member_pointer<T> {};                                          \
                                                                               \
  namespace NAMESPACE_TO_CHECK::TASK {                                         \
  using namespace ::TASK::TESTER;                                              \
  bool class_##CLASS##_has_static_membervar_##MEMBER =                         \
      class_##CLASS##_has_static_membervar_##MEMBER##_sfinae<CLASS>();         \
  }                                                                            \
                                                                               \
  namespace Check {                                                            \
  bool class_##CLASS##_has_static_membervar_##MEMBER##_v =                     \
      NAMESPACE_TO_CHECK::TASK::class_##CLASS##_has_static_membervar_##MEMBER; \
  }

//  End of CLASS_HAS_STATIC_MEMBERVAR

/*

TODO Find a way to check static Member Function

*/

//? Creates a check to determine if a specific class has a specific
//? static memberfunction in the specified namespace
//*F  bool Check::class_'CLASS'_has_static_memberfunc_'MEMBER'_v
#define CLASS_HAS_STATIC_MEMBERFUNC(CLASS, MEMBER)                      \
                                                                        \
  namespace TASK::TESTER {                                              \
  using CLASS = No;                                                     \
  }                                                                     \
  template <typename T, typename = void>                                \
  struct class_##CLASS##_has_static_memberfunc_##MEMBER##_sfinae        \
      : std::false_type {};                                             \
  template <typename T>                                                 \
  struct class_##CLASS##_has_static_memberfunc_##MEMBER##_sfinae<       \
      T, std::void_t<decltype(std::declval<T>().MEMBER)>>               \
      : std::is_member_pointer<T> {};                                   \
                                                                        \
  namespace NAMESPACE_TO_CHECK::TASK {                                  \
  using namespace ::TASK::TESTER;                                       \
  bool class_##CLASS##_has_static_memberfunc_##MEMBER =                 \
      class_##CLASS##_has_static_memberfunc_##MEMBER##_sfinae<CLASS>(); \
  }                                                                     \
                                                                        \
  namespace Check {                                                     \
  bool class_##CLASS##_has_static_memberfunc_##MEMBER##_v =             \
      NAMESPACE_TO_CHECK::TASK::                                        \
          class_##CLASS##_has_static_memberfunc_##MEMBER;               \
  }

//  End of CLASS_HAS_STATIC_MEMBERFUNC

/*



*/

//? Creates a check to determine if a specific class has a specific
//? membervariable of a specific type in the specified namespace
//*V  bool Check::class_'CLASS'_has_membervar_'MEMBER'_of_type_'TYPE'_v
#define CLASS_HAS_MEMBERVAR_OF_TYPE(CLASS, MEMBER, TYPE)                   \
                                                                           \
  namespace TASK::TESTER {                                                 \
  using CLASS = No;                                                        \
  }                                                                        \
  template <typename T, typename = void>                                   \
  struct class_##CLASS##_has_membervar_##MEMBER##_of_type_##TYPE##_sfinae  \
      : std::false_type {};                                                \
  template <typename T>                                                    \
  struct class_##CLASS##_has_membervar_##MEMBER##_of_type_##TYPE##_sfinae< \
      T, std::void_t<decltype(std::declval<T>().MEMBER)>>                  \
      : std::is_same<decltype(std::declval<T>().MEMBER), TYPE> {};         \
  namespace NAMESPACE_TO_CHECK::TASK {                                     \
  using namespace ::TASK::TESTER;                                          \
  bool class_##CLASS##_has_membervar_##MEMBER##_of_type_##TYPE =           \
      class_##CLASS##_has_membervar_##MEMBER##_of_type_##TYPE##_sfinae<    \
          CLASS>();                                                        \
  }                                                                        \
                                                                           \
  namespace Check {                                                        \
  bool class_##CLASS##_has_membervar_##MEMBER##_of_type_##TYPE##_v =       \
      NAMESPACE_TO_CHECK::TASK::                                           \
          class_##CLASS##_has_membervar_##MEMBER##_of_type_##TYPE;         \
  }

//  End of CLASS_HAS_MEMBERVAR_OF_TYPE

/*



*/

//? Creates a check to determine if a specific class has a specific
//? memberfunction of a specific type in the specified namespace
//*F  bool Check::class_'CLASS'_has_memberfunc_'MEMBER'_of_type_'TYPE'_v
#define CLASS_HAS_MEMBERFUNC_OF_TYPE(CLASS, MEMBER, TYPE)                   \
                                                                            \
  namespace TASK::TESTER {                                                  \
  using CLASS = No;                                                         \
  }                                                                         \
  template <typename T, typename = void>                                    \
  struct class_##CLASS##_has_memberfunc_##MEMBER##_of_type_##TYPE##_sfinae  \
      : std::false_type {};                                                 \
  template <typename T>                                                     \
  struct class_##CLASS##_has_memberfunc_##MEMBER##_of_type_##TYPE##_sfinae< \
      T, std::void_t<decltype(std::declval<T>().MEMBER())>>                 \
      : std::is_same<decltype(std::declval<T>().MEMBER()), TYPE> {};        \
  namespace NAMESPACE_TO_CHECK::TASK {                                      \
  using namespace ::TASK::TESTER;                                           \
  bool class_##CLASS##_has_memberfunc_##MEMBER##_of_type_##TYPE =           \
      class_##CLASS##_has_memberfunc_##MEMBER##_of_type_##TYPE##_sfinae<    \
          CLASS>();                                                         \
  }                                                                         \
                                                                            \
  namespace Check {                                                         \
  bool class_##CLASS##_has_memberfunc_##MEMBER##_of_type_##TYPE##_v =       \
      NAMESPACE_TO_CHECK::TASK::                                            \
          class_##CLASS##_has_memberfunc_##MEMBER##_of_type_##TYPE;         \
  }

//  End of CLASS_HAS_MEMBERFUNC_OF_TYPE

/*

TODO  Static test

*/

//? Creates a check to determine if a specific class has a specific
//? static membervariable of a specific type in the specified namespace
//*V  bool Check::class_'CLASS'_has_static_membervar_'MEMBER'_of_type_'TYPE'_v
#define CLASS_HAS_STATIC_MEMBERVAR_OF_TYPE(CLASS, MEMBER, TYPE)

//  End of CLASS_HAS_STATIC_MEMBERVAR_OF_TYPE

/*

TODO  Static test

*/

//? Creates a check to determine if a specific class has a specific
//? static memberfunction of a specific type in the specified namespace
//*V  bool Check::class_'CLASS'_has_static_membervar_'MEMBER'_of_type_'TYPE'_v
#define CLASS_HAS_STATIC_MEMBERFUNC_OF_TYPE(CLASS, MEMBER, TYPE)

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
  struct has_free_function_##FUNCTION##_sfinae<                                \
      T, std::void_t<decltype(FUNCTION)>>                                      \
      : std::conjunction<std::is_function<decltype(FUNCTION)>,                 \
                         std::negation<std::is_same<decltype(FUNCTION),        \
                                                    special_return_type()>>> { \
  };                                                                           \
  template <typename T>                                                        \
  struct has_free_function_##FUNCTIONNAME {                                    \
    static constexpr bool value =                                              \
        has_free_function_##FUNCTIONNAME##_sfinae<T>();                        \
  };                                                                           \
  bool has_free_function_##FUNCTIONNAME##_v =                                  \
      has_free_function_##FUNCTIONNAME<decltype(FUNCTIONNAME)>::value;         \
  }                                                                            \
                                                                               \
  namespace Check {                                                            \
  bool has_free_function_##FUNCTIONNAME##_v =                                  \
      NAMESPACE_TO_CHECK::TASK::has_free_function_##FUNCTIONNAME##_v;          \
  }

//* Fallback Free Function/ Variable
namespace TASK::TESTER {
struct special_return_type {};
}  // namespace TASK::TESTER

//  End of HAS_FREE_FUNCTION

/*



*/

//? Creates a check to determine if the specified namespace has a specific
//? free function of a specific type
//* bool Check::has_free_function_'FUNCTION'_of_type_'TYPE'_v
#define HAS_FREE_FUNCTION_OF_TYPE(FUNCTION, TYPE)                          \
                                                                           \
  namespace TASK::TESTER {                                                 \
  special_return_type FUNCTION();                                          \
  }                                                                        \
  namespace NAMESPACE_TO_CHECK::TASK {                                     \
  using namespace ::TASK::TESTER;                                          \
  template <typename T, typename = void>                                   \
  struct has_free_function_##FUNCTION##_of_type_##TYPE##_sfinae            \
      : std::false_type {};                                                \
  template <typename T>                                                    \
  struct has_free_function_##FUNCTION##_of_type_##TYPE##_sfinae<           \
      T, std::void_t<decltype(FUNCTION)>>                                  \
      : std::conjunction<std::is_function<decltype(FUNCTION)>,             \
                         std::is_same<decltype(FUNCTION), TYPE()>> {};     \
  template <typename T>                                                    \
  struct has_free_function_##FUNCTION##_of_type_##TYPE {                   \
    static constexpr bool value =                                          \
        has_free_function_##FUNCTION##_of_type_##TYPE##_sfinae<T>();       \
  };                                                                       \
  bool has_free_function_##FUNCTION##_of_type_##TYPE##_v =                 \
      has_free_function_##FUNCTION##_of_type_##TYPE<                       \
          decltype(FUNCTION)>::value;                                      \
  }                                                                        \
                                                                           \
  namespace Check {                                                        \
  bool has_free_function_##FUNCTION##_of_type_##TYPE##_v =                 \
      NAMESPACE_TO_CHECK::TASK::                                           \
          has_free_function_##FUNCTION##_of_type_##TYPE##_v;               \
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
  struct has_free_variable_##VARIABLE##_sfinae<                                \
      T, std::void_t<decltype(VARIABLE)>>                                      \
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
  struct has_free_variable_##VARIABLE##_of_type_##TYPE##_sfinae<          \
      T, std::void_t<decltype(VARIABLE)>>                                 \
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
    main(1, nullptr); /*For int main(int argc, char** argv)*/                 \
    /*main(); For int main()*/                                                \
    std::cout.rdbuf(std_buffer);                                              \
    std::string NamespaceOutput_arg = output_stream.str();                    \
    return NamespaceOutput_arg == TEXT;                                       \
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

/*

! Start of the Testing

*/

namespace STUDENT {

class ClassX {
 public:
  int Zaun{};
  void Baum(){};
  static int Blatt;  // const, if initialized
  static void Käfer(){};
};

void Wind(){};
int Sonne{};
int Stern{};

int main(int argc, char** argv) {
  std::cout << "Hello World" << std::endl;

  return 0;
}

}  // namespace STUDENT

/*



*/

HAS_CLASS(ClassX)  // existiert
HAS_CLASS(ClassY)  // existiert nicht

CLASS_HAS_MEMBERVAR(ClassX, Zaun)   // existiert
CLASS_HAS_MEMBERVAR(ClassX, Zäune)  // existiert nicht

CLASS_HAS_MEMBERFUNC(ClassX, Baum)   // existiert
CLASS_HAS_MEMBERFUNC(ClassX, Bäume)  // existiert nicht
/*
CLASS_HAS_STATIC_MEMBERVAR(ClassX, Blatt)  // ist static
CLASS_HAS_STATIC_MEMBERVAR(ClassX, Zaun)   // ist nicht static

CLASS_HAS_STATIC_MEMBERFUNC(ClassX, Käfer)  // ist static
CLASS_HAS_STATIC_MEMBERFUNC(ClassX, Baum)   // ist static
*/
CLASS_HAS_MEMBERVAR_OF_TYPE(ClassX, Zaun, int)     // ist int
CLASS_HAS_MEMBERVAR_OF_TYPE(ClassX, Zaun, double)  // ist nicht double

CLASS_HAS_MEMBERFUNC_OF_TYPE(ClassX, Baum, void)    // ist void
CLASS_HAS_MEMBERFUNC_OF_TYPE(ClassX, Baum, double)  // ist nicht double
/*
CLASS_HAS_STATIC_MEMBERVAR_OF_TYPE(ClassX, Blatt, int)     // ist static int
CLASS_HAS_STATIC_MEMBERVAR_OF_TYPE(ClassX, Blatt, double)  // ist static double

CLASS_HAS_STATIC_MEMBERFUNC_OF_TYPE(ClassX, Käfer, void)  // ist static void
CLASS_HAS_STATIC_MEMBERFUNC_OF_TYPE(ClassX, Käfer,
                                    double)  // ist nicht static double
*/
//! Dont create a free function/ variable check with the same name or the double
//! Fallback will cause an error
HAS_FREE_FUNCTION(Wind)    // existiert
HAS_FREE_FUNCTION(Wetter)  // existiert nicht

HAS_FREE_FUNCTION_OF_TYPE(Wind, void)    //  ist void
HAS_FREE_FUNCTION_OF_TYPE(Wind, double)  //  ist nicht double

HAS_FREE_VARIABLE(Sonne)  // existiert
HAS_FREE_VARIABLE(Mond)   //  existiert nicht

HAS_FREE_VARIABLE_OF_TYPE(Stern, int)      //  ist int
HAS_FREE_VARIABLE_OF_TYPE(Galaxy, double)  //  existiert nicht

IS_OUTPUT_SAME("Hello World\n")

/*



*/

int main() {
  std::cout << "HAS_CLASS" << std::endl;
  std::cout << Check::has_class_ClassX_v << std::endl;
  std::cout << Check::has_class_ClassY_v << std::endl;
  std::cout << "CLASS_HAS_MEMBERVAR" << std::endl;
  std::cout << Check::class_ClassX_has_membervar_Zaun_v << std::endl;
  std::cout << Check::class_ClassX_has_membervar_Zäune_v << std::endl;
  std::cout << "CLASS_HAS_MEMBERFUNC" << std::endl;
  std::cout << Check::class_ClassX_has_memberfunc_Baum_v << std::endl;
  std::cout << Check::class_ClassX_has_memberfunc_Bäume_v << std::endl;
  /*
  std::cout << "CLASS_HAS_STATIC_MEMBERVAR" << std::endl;
  std::cout << Check::class_ClassX_has_static_membervar_Blatt_v << std::endl;
  std::cout << Check::class_ClassX_has_static_membervar_Zaun_v << std::endl;
  std::cout << "CLASS_HAS_STATIC_MEMBERFUNC" << std::endl;
  std::cout << Check::class_ClassX_has_static_memberfunc_Käfer_v << std::endl;
  std::cout << Check::class_ClassX_has_static_memberfunc_Baum_v << std::endl;
  */
  std::cout << "CLASS_HAS_MEMBERVAR_OF_TYPE" << std::endl;
  std::cout << Check::class_ClassX_has_membervar_Zaun_of_type_int_v
            << std::endl;
  std::cout << Check::class_ClassX_has_membervar_Zaun_of_type_double_v
            << std::endl;
  std::cout << "CLASS_HAS_MEMBERFUNC_OF_TYPE" << std::endl;
  std::cout << Check::class_ClassX_has_memberfunc_Baum_of_type_void_v
            << std::endl;
  std::cout << Check::class_ClassX_has_memberfunc_Baum_of_type_double_v
            << std::endl;
  /*
  std::cout << "CLASS_HAS_STATIC_MEMBERVAR_OF_TYPE" << std::endl;
  std::cout << Check::class_ClassX_has_static_membervar_Blatt_of_type_int_v <<
  std::endl; std::cout <<
  Check::class_ClassX_has_static_membervar_Blatt_of_type_double_v << std::endl;
  std::cout << "CLASS_HAS_STATIC_MEMBERFUNC_OF_TYPE" << std::endl;
  std::cout << Check::class_ClassX_has_static_memberfunc_Käfer_of_type_void_v <<
  std::endl; std::cout <<
  Check::class_ClassX_has_static_memberfunc_Käfer_of_type_double_v << std::endl;
  */
  std::cout << "HAS_FREE_FUNCTION" << std::endl;
  std::cout << Check::has_free_function_Wind_v << std::endl;
  std::cout << Check::has_free_function_Wetter_v << std::endl;
  std::cout << "HAS_FREE_FUNCTION_OF_TYPE" << std::endl;
  std::cout << Check::has_free_function_Wind_of_type_void_v << std::endl;
  std::cout << Check::has_free_function_Wind_of_type_double_v << std::endl;
  std::cout << "HAS_FREE_VARIABLE" << std::endl;
  std::cout << Check::has_free_variable_Sonne_v << std::endl;
  std::cout << Check::has_free_variable_Mond_v << std::endl;
  std::cout << "HAS_FREE_VARIABLE_OF_TYPE" << std::endl;
  std::cout << Check::has_free_variable_Stern_of_type_int_v << std::endl;
  std::cout << Check::has_free_variable_Galaxy_of_type_double_v << std::endl;
  std::cout << "IS_OUTPUT_SAME" << std::endl;
  std::cout << Check::is_output_same_v << std::endl;

  return 0;
}
