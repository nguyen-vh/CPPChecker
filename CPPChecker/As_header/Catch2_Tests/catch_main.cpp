#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../cppchecker.hpp"

namespace STUDENT {
//* Students code starts here . . .

    //#include <iostream>   // Commented out because formatter doing weird formatting 

    using namespace std;

    class MyClassX {
        public:
        int IDE;
        void printed( ) { cout << "Printed..." << endl; }

        double Clock;
        double TV( ) { return 0; }
        };

    class MyClassXA {};

    class MyClassY {
        public:
        int printed( );
        int IDE;
        };

    class MyClassYA {};

    class MyClassZ {
        public:
        void OHM( ) {};
        double AMP;
        float VOLT;
        };


    void Tcout( ) { std::cout << "TEST CORRECT" << std::endl; }
    void Fcout( ) { std::cout << "TEST FALSE" << std::endl; }



    int Chips { 12 };
    int Fries { 9 };

    void Marker( ) {}
    void Pencil( ) {}

    int main( ) {
        MyClassX x;
        x.printed( );
        return 0;
        }

//* Student code ends here.
    }

M_FALLBACKS
M_OUTPUT
M_CLASS_HANDLING

//! Custom Settings

M_CLASS_HAS_MEMBER( check_IDE , IDE )
M_CLASS_HAS_MEMBER( check_printed_f , printed( ) )
M_CLASS_HAS_MEMBER_T( check_int_Clock_t , Clock , int )
M_CLASS_HAS_MEMBER_T( check_int_TV_f_t , TV( ) , int )


M_CLASS_HAS_MEMBER_T( check_int_printed_f_t , printed( ) , int )
M_CLASS_HAS_MEMBER_T( check_int_IDE_t , IDE , int )


M_CLASS_HAS_MEMBER( check_OHM_f , OHM( ) )
M_CLASS_HAS_MEMBER_T( check_double_AMP_t , AMP , double )
M_CLASS_HAS_MEMBER_T( check_float_VOLT_t , VOLT , float )


M_FREE_VARIABLE( Chips , int )
M_FREE_VARIABLE( ChipsA , float )
M_FREE_VARIABLE( Fries , float )


M_FREE_FUNCTION( Marker , void )
M_FREE_FUNCTION( MarkerA , void )
M_FREE_FUNCTION( Pencil , float )


M_CLASS_AND_MEMBER_1( MyClassX , check_IDE , "IDE" )
M_CLASS_AND_MEMBER_1( MyClassXA , check_IDE , "IDE" )


M_CLASS_AND_MEMBER_2( MyClassY , check_int_printed_f_t , "int printed()" , check_int_IDE_t , "int IDE" )
M_CLASS_AND_MEMBER_2( MyClassYA , check_int_printed_f_t , "int printed()" , check_int_IDE_t , "int IDE" )


M_CLASS_AND_MEMBER_3( MyClassZ , check_OHM_f , "OHM()" , check_double_AMP_t , "double AMP" , check_float_VOLT_t , "float VOLT" )
M_CLASS_AND_MEMBER_3( MyClassZA , check_OHM_f , "OHM()" , check_double_AMP_t , "double AMP" , check_float_VOLT_t , "float VOLT" )



//For TEST_CASE( "Check M_CLASS_HANDLING" )
namespace TASK::TESTER { using ClassNE = No; }


namespace STUDENT::TASK {
    using namespace ::TASK::TESTER;


    TEST_CASE( "Check M_CLASS_HAS_MEMBER" ) {
        //has member
        CHECK( check_IDE<MyClassX>( ) == true );
        CHECK_FALSE( check_IDE<MyClassXA>( ) == true );
        //has not member
        CHECK( check_printed_f<MyClassX>( ) == true );
        CHECK_FALSE( check_printed_f<MyClassXA>( ) == true );
        }


    TEST_CASE( "Check M_CLASS_HAS_MEMBER_T" ) {
        //has member
        CHECK( check_int_IDE_t<MyClassY>( ) == true );
        CHECK_FALSE( check_int_IDE_t<MyClassYA>( ) == true );
        //has not member
        CHECK( check_int_printed_f_t<MyClassY>( ) == true );
        CHECK_FALSE( check_int_printed_f_t<MyClassYA>( ) == true );
        //has member but wrong type
        CHECK_FALSE( check_int_Clock_t<MyClassX>( ) == true );
        CHECK_FALSE( check_int_TV_f_t<MyClassX>( ) == true );
        }


    TEST_CASE( "Check Free Function" ) {
        //has function
        CHECK( check_free_function_Marker<>( ) == true );
        //has not function
        CHECK_FALSE( check_free_function_MarkerA<>( ) == true );
        //has function but wrong type
        CHECK_FALSE( check_free_function_Pencil<>( ) == true );
        }


    TEST_CASE( "Check Free Variable" ) {
        //has variable
        CHECK( check_free_variable_Chips<>( ) == true );
        //has not variable
        CHECK_FALSE( check_free_variable_ChipsA<>( ) == true );
        //has variable but wrong type
        CHECK_FALSE( check_free_variable_Fries<>( ) == true );
        }


    TEST_CASE( "Check M_CLASS_AND_MEMBER_1" ) {
        //has member
        CHECK( check_MyClassX<MyClassX>( ) == true );
        //has not member
        CHECK_FALSE( check_MyClassXA<MyClassXA>( ) == true );
        }


    TEST_CASE( "Check M_CLASS_AND_MEMBER_2" ) {
        //has 2 members
        CHECK( check_MyClassY<MyClassY>( ) == true );
        //has not 2 members
        CHECK_FALSE( check_MyClassYA<MyClassYA>( ) == true );
        }


    TEST_CASE( "Check M_CLASS_AND_MEMBER_3" ) {
        //has 3 members
        CHECK( check_MyClassZ<MyClassZ>( ) == true );
        //has not not 3 members
        CHECK_FALSE( check_MyClassZA<MyClassZA>( ) == true );
        }


    TEST_CASE( "Check M_CLASS_HANDLING" ) {
        //has class
        CHECK( check_class<MyClassX>( ) == true );
        //has not class
        CHECK_FALSE( check_class<ClassNE>( ) == true );
        }


    TEST_CASE( "Check M_OUTPUT" ) {
        //correct output
        CHECK( check_output( *( STUDENT::Tcout ) , "TEST CORRECT\n" ) == true );
        //false output
        CHECK_FALSE( check_output( *( STUDENT::Fcout ) , "TEST CORRECT\n" ) == true );
        }


    TEST_CASE( "Check Filler" ) {
        CHECK( check_Filler<Filler>( ) == true );
        CHECK( check_free_function_Filler<>( ) == true );
        CHECK_FALSE( check_free_variable_Filler<>( ) == true );
        }


    }