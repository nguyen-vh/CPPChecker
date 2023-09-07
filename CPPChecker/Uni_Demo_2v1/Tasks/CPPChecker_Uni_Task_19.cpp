#include "../Headers/pch_uni.hpp"

//! STUDENT Code
namespace STUDENT {

#include "../studentCodeOverwrite.cpp"

}  // namespace STUDENT

//! Task
/*

Write a Program with 3 Classes named "MyClassX", "MyClassY" and "MyClassZ".
"MyClassZ" should have a Function called "OHM" with return type "void".
Also create a global Variable named "Snake".

*/

HAS_CLASS(MyClassX)
HAS_CLASS(MyClassY)
HAS_FREE_VARIABLE(Snake)
CLASS_HAS_MEMBERFUNC_OF_RETURNTYPE(MyClassZ, OHM, void)

int main() {
  std::cout << std::endl;
  if (Check::has_class_MyClassX_v) {
    std::cout << "Has MyClassX" << std::endl;
  } else {
    std::cout << "Missing MyClassX" << std::endl;
  }
  if (Check::has_class_MyClassY_v) {
    std::cout << "Has MyClassY" << std::endl;
  } else {
    std::cout << "Missing MyClassY" << std::endl;
  }
  if (Check::has_free_variable_Snake_v) {
    std::cout << "Has Snake" << std::endl;
  } else {
    std::cout << "Missing Snake" << std::endl;
  }
  if (Check::class_MyClassZ_has_memberfunc_OHM_of_returntype_void_v) {
    std::cout << "Has void OHM(){}" << std::endl;
  } else {
    std::cout << "Missing void OHM(){}" << std::endl;
  }
  return 0;
}