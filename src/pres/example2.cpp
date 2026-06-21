#include "cppchecker.hpp"

namespace STUDENT {
#include <iostream>

struct Rectangle {
  float m_width{};
  float m_height{};

  Rectangle(float w, float h) : m_width(w), m_height(h) {}

  auto getArea() -> float { return m_width * m_height; }
};

auto main(int /*argc*/, char* /*argv*/[]) -> int {
  std::cout << "Area: " << Rectangle(15.5f, 20.0f).getArea() << "\n";

  std::cout << std::endl;
  return 0;
}
}  // namespace STUDENT

IS_OUTPUT_SAME("Area: 310\n")
HAS_CLASS(Rectangle)
CLASS_HAS_MEMBERVAR_OF_TYPE(Rectangle, m_width, float)
CLASS_HAS_MEMBERVAR_OF_TYPE(Rectangle, m_height, float)
CLASS_HAS_MEMBERFUNC(Rectangle, getArea)

auto main(int /*argc*/, char* /*argv*/[]) -> int {
  std::cout << check::has_class_Rectangle_v ? "Has Rectangle"
                                            : "Missing Rectangle" << "\n";

  std::cout << check::has_class_Rectangle_has_membervar_m_width_of_type_float_v
      ? "Has float m_width"
      : "Missing float m_width" << "\n";

  std::cout << check::has_class_Rectangle_has_membervar_m_height_of_type_float_v
      ? "Has float m_height"
      : "Missing float m_height" << "\n";

  std::cout << check::class_Rectangle_has_memberfunc_getArea_v
      ? "Has getArea()"
      : "Missing getArea()" << "\n";

  std::cout << check::is_output_same_v ? "Output is correct"
                                       : "Output not correct" << "\n";

  std::cout << std::endl;
  return 0;
}
