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
