// Copyright (c) 2026-present Hoang Nguyen
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its
//    contributors may be used to endorse or promote products derived from
//    this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

//?  Task creator: Hoang Nguyen

//----------------------------------------------------------------------------//
// °                            === INCLUDES ===                            ° //
//----------------------------------------------------------------------------//

#include "../include/cxxchecker_reflection.hpp"
#include "../include/standard_libs.hpp"

namespace TASK {

#ifdef INCLUDE_FILE
#include INCLUDE_FILE
#endif

}  // namespace TASK

//----------------------------------------------------------------------------//
// °                              === TASK ===                              ° //
//----------------------------------------------------------------------------//

/*
  Define a struct named "Rectangle" with the elements "m_width" and "m_height"
  of type float.

  Extend the struct with a member function "getArea" that returns a float value
  representing the area of the rectangle.

  In the main function, create a rectangle with a width of
  15.5 and a height of 20, and
  print "Area: " along with the area of the rectangle.
*/

//----------------------------------------------------------------------------//
// °                              === MAIN ===                              ° //
//----------------------------------------------------------------------------//

auto main(int /*argc*/, char* /*argv*/[]) -> int {
  std::cout << (has_class<"TASK::Rectangle"_ls> ? "Has Rectangle\n"
                                                : "Missing Rectangle\n");
  std::cout << (class_has_membervar<"TASK::Rectangle"_ls, "m_width"_ls, float>
                    ? "Has Rectangle member float m_width\n"
                    : "Missing Rectangle member float m_width\n");
  std::cout << (class_has_membervar<"TASK::Rectangle"_ls, "m_height"_ls, float>
                    ? "Has Rectangle member float m_height\n"
                    : "Missing Rectangle member float m_height\n");

  std::cout << (class_has_memberfunc<"TASK::Rectangle"_ls, "getArea"_ls, float>
                    ? "Has Rectangle member float getArea()\n"
                    : "Missing Rectangle member float getArea()\n");

  return 0;
}

//----------------------------------------------------------------------------//
// °                          === ONE SOLUTION ===                          ° //
//----------------------------------------------------------------------------//

namespace __solution__ {

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

}  // namespace __solution__
