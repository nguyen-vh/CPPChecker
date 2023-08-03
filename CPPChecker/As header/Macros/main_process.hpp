#ifndef MAIN_PROCESS_HPP
#define MAIN_PROCESS_HPP

#include <iostream>
#include <type_traits>

//* Main Input Processing
#define C_MAIN( ExpectedOutput, Class1, Class2, Class3, FreeFunction1, FreeFunction2, FreeFunction3, FreeVariable1, FreeVariable2, FreeVariable3 ) \
void evaluation( const std::string& expectedOutput, const bool& Bt1, const bool& Bt2, \
    const bool& Bt3, const bool& Bt4, const bool& Bt5, const bool& Bt6, const bool& Bt7, const bool& Bt8, const bool& Bt9 ) { \
    if ( Bt1 && Bt2 && Bt3 && Bt4 && Bt5 && Bt6 && Bt7 && Bt8 && Bt9 ) { \
        if ( check_output( *( STUDENT::main ), expectedOutput ) ) { \
            std::cout << "______________________________________" << std::endl; \
            std::cout << "\n+ + + Student did a great Job! + + +\n" << std::endl; }} \
    else { \
        std::cout << "______________________________________" << std::endl; \
        std::cout << "\n- Student forgot something!\n" << std::endl; }} \
\
namespace STUDENT::TASK { using namespace ::TASK::TESTER; \
void testing( ) { \
        bool Bt1 = check_##Class1<Class1>(); bool Bt2 = check_##Class2<Class2>(); bool Bt3 = check_##Class3<Class3>(); \
        bool Bt4 = check_free_function_##FreeFunction1<>(); bool Bt5 = check_free_function_##FreeFunction2<>(); bool Bt6 = check_free_function_##FreeFunction3<>(); \
        bool Bt7 = check_free_variable_##FreeVariable1<>(); bool Bt8 = check_free_variable_##FreeVariable2<>(); bool Bt9 = check_free_variable_##FreeVariable3<>(); \
        std::string expectedOutput = ExpectedOutput; \
        ::evaluation( expectedOutput, Bt1, Bt2, Bt3, Bt4, Bt5, Bt6, Bt7, Bt8, Bt9 ); } } \
\
int main( ) { std::cout << std::endl; STUDENT::TASK::testing( ); return 0; }

#endif