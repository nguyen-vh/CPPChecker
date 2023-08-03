#ifndef CLASS_MEMEBER_CHECK_HPP
#define CLASS_MEMEBER_CHECK_HPP

#include <iostream>
#include <type_traits>

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

#endif