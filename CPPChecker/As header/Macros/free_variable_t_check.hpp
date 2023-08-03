#ifndef FREE_VARIABLE_T_CHECK_HPP
#define FREE_VARIABLE_T_CHECK_HPP

//* Check for Free Variable
#define M_FREE_VARIABLE( VARIABLE_NAME, TYPE ) \
namespace TASK::TESTER{ char VARIABLE_NAME{}; } \
namespace STUDENT::TASK { \
    using namespace ::TASK::TESTER; \
\
    template <typename T , typename = void> \
    struct has_free_V_##VARIABLE_NAME : std::false_type {}; \
\
    template <typename T> \
    struct has_free_V_##VARIABLE_NAME<T , std::void_t<decltype( VARIABLE_NAME )>> : \
        std::conjunction< \
        std::is_object<decltype( VARIABLE_NAME )> , \
        std::is_same<decltype( VARIABLE_NAME ) , TYPE>> {}; \
\
    template <typename T> \
    struct is_free_variable##VARIABLE_NAME { \
        static constexpr bool value = has_free_V_##VARIABLE_NAME<T>::value; \
        }; \
\
template <typename = void> \
bool check_free_variable_##VARIABLE_NAME( ) { \
bool has_free_variable_##VARIABLE_NAME = is_free_variable##VARIABLE_NAME<decltype( VARIABLE_NAME )>::value; \
if (has_free_variable_##VARIABLE_NAME){ \
std::cout << "+ Free Variable '" << #VARIABLE_NAME << "' found" << std::endl; \
    } \
else { \
    std::cout << "- Free Variable '" << #VARIABLE_NAME << "' not found" << std::endl; \
    } \
    return ( has_free_variable_##VARIABLE_NAME ); } }

#endif