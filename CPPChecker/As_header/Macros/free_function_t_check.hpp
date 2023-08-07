#ifndef FREE_FUNCTION_T_CHECK_HPP
#define FREE_FUNCTION_T_CHECK_HPP

//* Check for Free Function
#define M_FREE_FUNCTION(FUNCTION_NAME, TYPE)                                 \
  namespace TASK::TESTER {                                                   \
  char FUNCTION_NAME();                                                      \
  }                                                                          \
  namespace STUDENT::TASK {                                                  \
  using namespace ::TASK::TESTER;                                            \
                                                                             \
  template <typename T, typename = void>                                     \
  struct has_free_F_##FUNCTION_NAME : std::false_type {};                    \
                                                                             \
  template <typename T>                                                      \
  struct has_free_F_##FUNCTION_NAME<T, std::void_t<decltype(FUNCTION_NAME)>> \
      : std::conjunction<std::is_function<decltype(FUNCTION_NAME)>,          \
                         std::is_same<decltype(FUNCTION_NAME), TYPE()>> {};  \
                                                                             \
  template <typename T>                                                      \
  struct is_free_function##FUNCTION_NAME {                                   \
    static constexpr bool value = has_free_F_##FUNCTION_NAME<T>::value;      \
  };                                                                         \
                                                                             \
  template <typename = void>                                                 \
  bool check_free_function_##FUNCTION_NAME() {                               \
    bool has_free_function_##FUNCTION_NAME =                                 \
        is_free_function##FUNCTION_NAME<decltype(FUNCTION_NAME)>::value;     \
    if (has_free_function_##FUNCTION_NAME) {                                 \
      std::cout << "+ Free Function '" << #TYPE " " #FUNCTION_NAME           \
                << "' found" << std::endl;                                   \
    } else {                                                                 \
      std::cout << "- Free Function '" << #TYPE " " #FUNCTION_NAME           \
                << "' not found" << std::endl;                               \
    }                                                                        \
    return (has_free_function_##FUNCTION_NAME);                              \
  }                                                                          \
  }

#endif