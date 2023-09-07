#include "../Headers/pch_uni.hpp"

//! STUDENT Code
namespace STUDENT {

#include "../studentCodeOverwrite.cpp"

}  // namespace STUDENT

HAS_CLASS(MyClassX)
CLASS_HAS_MEMBERFUNC(MyClassY, printed)
HAS_FREE_FUNCTION_OF_RETURNTYPE(SomeFunctionX, int)
int main() {
  std::cout << std::endl;
  if (Check::has_class_MyClassX_v) {
    std::cout << "Has MyClassX" << std::endl;
  } else {
    std::cout << "Missing MyClassX" << std::endl;
  }
  if (Check::class_MyClassY_has_memberfunc_printed_v) {
    std::cout << "Has printed() in MyClassY" << std::endl;
  } else {
    std::cout << "Missing printed() in MyClassY" << std::endl;
  }
  if (Check::has_free_function_SomeFunctionX_of_returntype_int_v) {
    std::cout << "Has int SomeFunctionX()" << std::endl;
  } else {
    std::cout << "Missing int SomeFunctionX()" << std::endl;
  }

  return 0;
}