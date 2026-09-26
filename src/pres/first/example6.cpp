#include <iostream>

#include "cxxchecker_reflection.hpp"


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

auto main(int /*argc*/, char* /*argv*/[]) -> int {
  std::cout << (has_class<"STUDENT::Rectangle"_ls> ? "Has Rectangle\n"
                                                   : "Missing Rectangle\n");
  std::cout
      << (class_has_membervar<"STUDENT::Rectangle"_ls, "m_width"_ls, float>
              ? "Has float m_width\n"
              : "Missing float m_width\n");
  std::cout
      << (class_has_membervar<"STUDENT::Rectangle"_ls, "m_height"_ls, float>
              ? "Has float m_height\n"
              : "Missing float m_height\n");
  std::cout
      << (class_has_memberfunc<"STUDENT::Rectangle"_ls, "getArea"_ls, float>
              ? "Has getArea()\n"
              : "Missing getArea()\n");
  std::cout << std::endl;
  return 0;
}
