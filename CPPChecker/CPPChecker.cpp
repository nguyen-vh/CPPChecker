#include <iostream>
#include <sstream>
#include <type_traits>

//! Macros

//* SFINAE Check for a Member (Member can be for example Function with () and Variable)
#define M_CLASS_HAS_MEMBER( NAME, MEMBER ) \
template <typename T, typename = void> \
struct NAME : std::false_type {}; \
\
template <typename T> \
struct NAME<T , std::void_t<decltype( std::declval<T>( ).MEMBER )>> : std::true_type {};


//* Combines a Class with the Check of 1 Member
#define M_CLASS_AND_MEMBER_1( CLASSNAME, NAME_FROM_HAS_MEMBER, MEMBER_STRING ) \
namespace TASK::TESTER{ using CLASSNAME = No; } \
template <typename T> \
bool CLASSNAME##_class_has_Member_##NAME_FROM_HAS_MEMBER( ) { \
    bool result = NAME_FROM_HAS_MEMBER<T>::value; \
    if (result) { \
        std::cout << "+  > Member '" << MEMBER_STRING << "' found\n" << std::endl; \
    } else { \
        std::cout << "-  > Member '" << MEMBER_STRING << "' not found\n" << std::endl; \
    } \
    return result; } \
\
template <typename T> \
bool check_##CLASSNAME( ) { \
    bool classResult = check_class<T>( ); \
    bool resultMember = CLASSNAME##_class_has_Member_##NAME_FROM_HAS_MEMBER<T>( ); \
    return ( classResult && resultMember ); \
    } 


//* Combines a Class with the Check of 2 Members
#define M_CLASS_AND_MEMBER_2( CLASSNAME, NAME_FROM_HAS_MEMBER, MEMBER_STRING, NAME_FROM_HAS_MEMBER_2, MEMBER_STRING_2 ) \
namespace TASK::TESTER { using CLASSNAME = No; } \
\
template <typename T> \
bool CLASSNAME##_class_has_Member_##NAME_FROM_HAS_MEMBER( ) { \
    bool result = NAME_FROM_HAS_MEMBER<T>::value; \
    if (result) { \
        std::cout << "+  > Member '" << MEMBER_STRING << "' found" << std::endl; \
    } else { \
        std::cout << "-  > Member '" << MEMBER_STRING << "' not found" << std::endl; \
    } \
    return result; \
} \
\
template <typename T> \
bool CLASSNAME##_class_has_Member_##NAME_FROM_HAS_MEMBER_2( ) { \
    bool result = NAME_FROM_HAS_MEMBER_2<T>::value; \
    if (result) { \
        std::cout << "+  > Member '" << MEMBER_STRING_2 << "' found\n" << std::endl; \
    } else { \
        std::cout << "-  > Member '" << MEMBER_STRING_2 << "' not found\n" << std::endl; \
    } \
    return result; \
} \
\
template <typename T> \
bool check_##CLASSNAME() { \
    bool classResult = check_class<T>( ); \
    bool resultMember = CLASSNAME##_class_has_Member_##NAME_FROM_HAS_MEMBER<T>( ); \
    bool resultMember_2 = CLASSNAME##_class_has_Member_##NAME_FROM_HAS_MEMBER_2<T>( ); \
    return ( classResult && resultMember && resultMember_2 ); \
}


//* Combines a Class with the Check of 3 Members
#define M_CLASS_AND_MEMBER_3( CLASSNAME, NAME_FROM_HAS_MEMBER, MEMBER_STRING, NAME_FROM_HAS_MEMBER_2, MEMBER_STRING_2, NAME_FROM_HAS_MEMBER_3, MEMBER_STRING_3 ) \
namespace TASK::TESTER { using CLASSNAME = No; } \
\
template <typename T> \
bool CLASSNAME##_class_has_Member_##NAME_FROM_HAS_MEMBER( ) { \
    bool result = NAME_FROM_HAS_MEMBER<T>::value; \
    if (result) { \
        std::cout << "+  > Member '" << MEMBER_STRING << "' found" << std::endl; \
    } else { \
        std::cout << "-  > Member '" << MEMBER_STRING << "' not found" << std::endl; \
    } \
    return result; \
} \
\
template <typename T> \
bool CLASSNAME##_class_has_Member_##NAME_FROM_HAS_MEMBER_2( ) { \
    bool result = NAME_FROM_HAS_MEMBER_2<T>::value; \
    if (result) { \
        std::cout << "+  > Member '" << MEMBER_STRING_2 << "' found" << std::endl; \
    } else { \
        std::cout << "-  > Member '" << MEMBER_STRING_2 << "' not found" << std::endl; \
    } \
    return result; \
} \
template <typename T> \
bool CLASSNAME##_class_has_Member_##NAME_FROM_HAS_MEMBER_3( ) { \
    bool result = NAME_FROM_HAS_MEMBER_3<T>::value; \
    if (result) { \
        std::cout << "+  > Member '" << MEMBER_STRING_3 << "' found\n" << std::endl; \
    } else { \
        std::cout << "-  > Member '" << MEMBER_STRING_3 << "' not found\n" << std::endl; \
    } \
    return result; \
} \
\
template <typename T> \
bool check_##CLASSNAME( ) { \
    bool classResult = check_class<T>(); \
    bool resultMember = CLASSNAME##_class_has_Member_##NAME_FROM_HAS_MEMBER<T>( ); \
    bool resultMember_2 = CLASSNAME##_class_has_Member_##NAME_FROM_HAS_MEMBER_2<T>( ); \
    bool resultMember_3 = CLASSNAME##_class_has_Member_##NAME_FROM_HAS_MEMBER_3<T>( ); \
    return ( classResult && resultMember && resultMember_2 && resultMember_3 ); \
}


//* SFINAE Check for a Member with specific type
#define M_CLASS_HAS_MEMBER_T( NAME, MEMBER, TYPE ) \
template <typename T, typename = void> \
struct NAME : std::false_type {}; \
\
template <typename T> \
struct NAME<T , std::void_t<decltype( std::declval<T>( ).MEMBER )>> : std::is_same<decltype(std::declval<T>( ).MEMBER), TYPE>{};


//* Fallback for M_MAIN
#define M_FALLBACKS \
struct Filler {}; \
template <typename T , typename = void> \
struct check_Filler : std::true_type {}; \
template <typename = void> \
    bool check_free_function_Filler( ){ return true; } \
template <typename = void> \
    bool check_free_variable_Filler( ){ return true; } \
namespace TASK::TESTER { struct No {}; } 


//* Checks for the Existence of a Class
#define M_CLASS_HANDLING \
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
                        return false; } }



  //* Evaluates the output from Student
#define M_OUTPUT \
template <typename T> \
bool check_output( T&& main_call , const std::string& expectedOutput ) { \
    std::stringstream output_stream; \
    std::streambuf* std_buffer = std::cout.rdbuf( output_stream.rdbuf( ) ); \
    ( main_call )( ); \
    std::cout.rdbuf( std_buffer ); \
    std::string STUDENTOutput = output_stream.str( ); \
    if ( STUDENTOutput == expectedOutput ) { \
        std::cout << "\n+ Student Output correct" << std::endl; \
        return true; } else { \
        std::cout << "\n- Student Output incorrect" << std::endl; \
        std::cout << "   > Expected Output: " << expectedOutput   \
         << "   >  Student Output: " << STUDENTOutput << std::endl; \
        return false; }}


//* Check for Free Function
#define M_FREE_FUNCTION( FUNCTION_NAME, TYPE ) \
namespace TASK::TESTER{ char FUNCTION_NAME( ); } \
namespace STUDENT::TASK { \
    using namespace ::TASK::TESTER; \
\
    template <typename T , typename = void> \
    struct has_free_F_##FUNCTION_NAME : std::false_type {}; \
\
    template <typename T> \
    struct has_free_F_##FUNCTION_NAME<T , std::void_t<decltype( FUNCTION_NAME )>> : \
        std::conjunction< \
        std::is_function<decltype( FUNCTION_NAME )> , \
        std::is_same<decltype( FUNCTION_NAME ) , TYPE( )>> {}; \
\
    template <typename T> \
    struct is_free_function##FUNCTION_NAME { \
        static constexpr bool value = has_free_F_##FUNCTION_NAME<T>::value; \
        }; \
\
template <typename = void> \
bool check_free_function_##FUNCTION_NAME( ) { \
bool has_free_function_##FUNCTION_NAME = is_free_function##FUNCTION_NAME<decltype( FUNCTION_NAME )>::value; \
if (has_free_function_##FUNCTION_NAME){ \
std::cout << "+ Free Function '" << #FUNCTION_NAME << "' found" << std::endl; \
    } \
else { \
    std::cout << "- Free Function '" << #FUNCTION_NAME << "' not found" << std::endl; \
    } \
    return ( has_free_function_##FUNCTION_NAME ); } } 


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


//* Main Input Processing
#define M_MAIN( ExpectedOutput, Class1, Class2, Class3, FreeFunction1, FreeFunction2, FreeFunction3, FreeVariable1, FreeVariable2, FreeVariable3 ) \
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



//! STUDENT Code
namespace STUDENT {
//* Students code starts here . . .

    //#include <iostream>   // Commented out because formatter doing weird formatting 

    using namespace std;

    class MyClassX {
        public:
        int IDE;
        void printed( ) { cout << "Printed..." << endl; }
        };

    class MyClassY {
        public:
        int printed( );
        int IDE;
        };

    class MyClassZ {
        public:
        void OHM( ) {};
        double AMP;
        float VOLT;
        };

    int Schokolade { 12 };

    void SomeFunctionX( ) {}

    std::string Snake;

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

M_CLASS_HAS_MEMBER_T( checks_AMP_T , AMP , int )
M_CLASS_HAS_MEMBER_T( checks_OHM_f_T , OHM( ) , void )
M_FREE_VARIABLE( Schokolade , int )
//? M_FREE_VARIABLE( Variablename, type )
M_FREE_VARIABLE( Snake , std::string )
M_FREE_FUNCTION( SomeFunctionX , void )
//? M_FREE_FUNCTION( Variablename, type )
M_CLASS_HAS_MEMBER( checks_IDE , IDE )
//? M_CLASS_HAS_MEMBER( Name for SFINAE-Template, Membername )
M_CLASS_HAS_MEMBER( checks_printed_f , printed( ) )
M_CLASS_HAS_MEMBER( checks_AMP , AMP )
M_CLASS_AND_MEMBER_3( MyClassX , checks_IDE , "IDE" , checks_printed_f , "printed()" , checks_AMP , "AMP" )
M_CLASS_AND_MEMBER_2( MyClassY , checks_IDE , "IDE" , checks_printed_f , "printed()" )
//? M_CLASS_AND_MEMBER_2( Classname, 1st Name of the SFINAE-Template, string of 1st Membername, 2nd Name of the SFINAE-Template, string of 2nd Membername )
M_CLASS_AND_MEMBER_2( MyClassZ , checks_AMP_T , "int AMP" , checks_OHM_f_T , "void OHM()" )
//! Mains
M_MAIN( "Printed...\n" , MyClassX , MyClassY , MyClassZ , SomeFunctionX , Filler , Filler , Schokolade , Snake , Filler )
//? C_MAIN( string Output, Class1, Class2, Class3, FreeFunction1, FreeFunction2, FreeFunction3, Variable1, Variable2, Variable3 )