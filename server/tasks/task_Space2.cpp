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
  Define a global constant "LIGHT_SPEED" with value 299792458.0 (meters per
  second) of type double.

  Write a free function "calculateDelay" that takes distance in kilometers
  (double) and returns signal travel time in seconds.

  Create a class "SpaceProbe" with private members "m_name" (string),
  "m_distance" (double in km) and a constructor to initialize both.

  Add private method "getSignalDelay()" that uses the free function above.
  Add a method "sendMessage()" that prints:
  "Sending to [name]..."
  "Signal arrives in XX.XX seconds"

  In main function create a probe "Pluto" at 7500000000 km. Send a message.
*/

//----------------------------------------------------------------------------//
// °                              === MAIN ===                              ° //
//----------------------------------------------------------------------------//

auto main(int /*argc*/, char* /*argv*/[]) -> int {
  std::cout << (has_free_variable<"TASK::LIGHT_SPEED"_ls, const double>
                    ? "Has global double LIGHT_SPEED\n"
                    : "Missing global double LIGHT_SPEED\n");

  std::cout << (has_free_function<"TASK::calculateDelay"_ls, double, double>
                    ? "Has global double calculateDelay()\n"
                    : "Missing global double calculateDelay()\n");

  std::cout << (has_class<"TASK::SpaceProbe"_ls> ? "Has SpaceProbe\n"
                                                 : "Missing SpaceProbe\n");
  std::cout << (class_has_membervar<"TASK::SpaceProbe"_ls, "m_distance">
                    ? "Has SpaceProbe member double m_distance\n"
                    : "Missing SpaceProbe member double m_distance\n");
  std::cout
      << (class_has_membervar<"TASK::SpaceProbe"_ls, "m_name"_ls, std::string>
              ? "Has SpaceProbe member string m_name\n"
              : "Missing SpaceProbe member string m_name\n");

  std::cout << (class_has_private_memberfunc<"TASK::SpaceProbe"_ls,
                                             "getSignalDelay"_ls>
                    ? "Has SpaceProbe private member getSignalDelay()\n"
                    : "Missing SpaceProbe private member getSignalDelay()\n");
  std::cout << (class_has_memberfunc<"TASK::SpaceProbe"_ls, "sendMessage"_ls>
                    ? "Has SpaceProbe member sendMessage()\n"
                    : "Missing SpaceProbe member sendMessage()\n");

  return 0;
}

//----------------------------------------------------------------------------//
// °                          === ONE SOLUTION ===                          ° //
//----------------------------------------------------------------------------//

namespace __solution__ {
#include <iostream>
#include <string>

constexpr double LIGHT_SPEED{299792458.0};

auto calculateDelay(double distance) -> double {
  return (distance * 1000) / LIGHT_SPEED;
}

class SpaceProbe {
 private:
  std::string m_name{};
  double m_distance{};

  auto getSignalDelay() const -> double { return calculateDelay(m_distance); }

 public:
  SpaceProbe(std::string name, double distance)
      : m_name(name), m_distance(distance) {}

  auto sendMessage() const -> void {
    std::cout << "Sending to " << m_name << "..." << "\n";
    std::cout << "Signal arrives in: " << getSignalDelay() << " seconds";
    std::cout << std::endl;
  }
};

auto main(int /*argc*/, char* /*argv*/[]) -> int {
  SpaceProbe("Pluto", 7500000000.0).sendMessage();

  return 0;
}
}  // namespace __solution__