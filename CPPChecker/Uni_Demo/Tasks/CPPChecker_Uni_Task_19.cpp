#include "pch_uni.hpp"

//! STUDENT Code
namespace STUDENT {

#include "../students_code.cpp"

}  // namespace STUDENT
M_START

M_CLASS_HAS_MEMBER(checks_IDE, IDE)
M_CLASS_HAS_MEMBER(checks_printed_f, printed())
M_CLASS_HAS_MEMBER_T(checks_AMP_T, AMP, int)
M_CLASS_HAS_MEMBER_T(checks_OHM_f_T, OHM(), void)
M_FREE_VARIABLE(Schokolade, int)
M_FREE_FUNCTION(SomeFunctionX, void)
M_CLASS_AND_MEMBER_2(MyClassX, checks_IDE, "IDE", checks_printed_f, "printed()")
M_CLASS_AND_MEMBER_2(MyClassY, checks_IDE, "IDE", checks_printed_f, "printed()")
M_CLASS_AND_MEMBER_1(MyClassZ, checks_OHM_f_T, "void OHM()")

M_MAIN("Printed...\n", MyClassX, MyClassY, MyClassZ, SomeFunctionX, Filler,
       Filler, Schokolade, Filler, Filler)
