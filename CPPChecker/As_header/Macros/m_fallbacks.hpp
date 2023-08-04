#ifndef M_FALLBACKS_HPP
#define M_FALLBACKS_HPP

#define M_FALLBACKS \
struct Filler {}; \
template <typename T , typename = void> \
struct check_Filler : std::true_type {}; \
template <typename = void> \
    bool check_free_function_Filler( ){ return true; } \
template <typename = void> \
    bool check_free_variable_Filler( ){ return true; } \
namespace TASK::TESTER { struct No {}; }

#endif