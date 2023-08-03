#ifndef CLASS_HANDLING_HPP
#define CLASS_HANDLING_HPP

#include <iostream>
#include <type_traits>

//* Checks for the Existence of a Class
#define M_CLASS_HANDLING( ) \
template <typename T> \
bool check_class( ) { \
std::string strClassN = typeid( T ).name( ) , strClassNreadable {}; \
        strClassN = strClassN.erase( 0 , 9 ); \
        for ( int i = 0; i < strClassN.length( ); ++i ) { \
            if ( std::isdigit( strClassN [ i ] ) ) { \
                if ( !std::isdigit( strClassN [ i + 1 ] ) ) { \
                    strClassNreadable = strClassN.substr( i + 1 ); } } } \
                    strClassNreadable.pop_back( ); \
    if ( !std::is_same<T , TASK::TESTER::No>::value ) { \
        std::cout << "+ Class '" << strClassNreadable << "' found" << std::endl; \
        return true; } else { \
        std::cout << "- Class in Assignment not found. " << std::endl; \
        return false; }} \
\
struct Filler {}; \
    template <typename T , typename = void> \
    struct check_Filler : std::true_type {}; \
 template <typename = void> \
 bool check_free_function_Filler( ){ return true; } \
template <typename = void> \
 bool check_free_variable_Filler( ){ return true; }

#endif