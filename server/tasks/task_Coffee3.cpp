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
  Define an abstract base class "Coffee" with:
  - Private variables: m_name (string), m_price (double), m_stock (int)
  - Constructor to initialize all values
  - Member function "sell(int quantity)" that:
    - Reduces stock by quantity
    - Returns the total price (price * quantity) in double
  - Virtual function "getDescription()" that returns a string
  - Virtual function "getSpecialInstruction()" that returns a string (default:
  "Standard brew")

  Create a derived class "Espresso" that inherits from Coffee:
  - Constructor that sets name to "Espresso", price to 3.5, stock to 20
  - Override getDescription() to return "Strong and bold Italian classic"
  - Override getSpecialInstruction() to return "Serve in pre-heated cup"

  Create a derived class "Cappuccino" that inherits from Coffee:
  - Constructor that sets name to "Cappuccino", price to 4.7, stock to 16
  - Override getDescription() to return "Smooth with perfect foam ratio"
  - Override getSpecialInstruction() to return "Sprinkle with cocoa powder"

  In main function:
  - Create an Espresso object and a Cappuccino object as Coffee pointers
  - Sell 6 cups of espresso
  - Sell 3 cups of cappuccino
  - Display for each:
    - Description
    - Special instruction
    - Sold quantity and total price
*/

//----------------------------------------------------------------------------//
// °                              === MAIN ===                              ° //
//----------------------------------------------------------------------------//

auto main(int /*argc*/, char* /*argv*/[]) -> int {
  std::cout << (has_class<"TASK::Coffee"_ls> ? "Has Coffee\n"
                                             : "Missing Coffee\n");
  std::cout << (class_has_private_membervar<"TASK::Coffee"_ls, "m_name"_ls,
                                            std::string>
                    ? "Has Coffee private member string m_name\n"
                    : "Missing Coffee private member string m_name\n");
  std::cout
      << (class_has_private_membervar<"TASK::Coffee"_ls, "m_price"_ls, double>
              ? "Has Coffee private member double m_price\n"
              : "Missing Coffee private member double m_price\n");
  std::cout
      << (class_has_private_membervar<"TASK::Coffee"_ls, "m_stock"_ls, int>
              ? "Has Coffee private member int m_stock\n"
              : "Missing Coffee private member int m_stock\n");
  std::cout << (class_has_memberfunc<"TASK::Coffee"_ls, "sell"_ls, double, int>
                    ? "Has Coffee member double sell()\n"
                    : "Missing Coffee member double sell()\n");
  std::cout
      << (class_has_virtual_memberfunc<"TASK::Coffee"_ls, "getDescription"_ls>
              ? "Has Coffee virtual member getDescription()\n"
              : "Missing Coffee virtual member getDescription()\n");
  std::cout
      << (class_has_virtual_memberfunc<"TASK::Coffee"_ls,
                                       "getSpecialInstruction"_ls>
              ? "Has Coffee virtual member getSpecialInstruction()\n"
              : "Missing Coffee virtual member getSpecialInstruction()\n");

  std::cout << (class_is_base_of<"TASK::Coffee"_ls, "TASK::Espresso"_ls>
                    ? "Has Espresso derive from Coffee\n"
                    : "Missing Espresso derive from Coffee\n");
  std::cout << (class_has_override_memberfunc<"TASK::Espresso"_ls,
                                              "getDescription"_ls>
                    ? "Has Espresso override getDescription()\n"
                    : "Missing Espresso override getDescription()\n");
  std::cout << (class_has_override_memberfunc<"TASK::Espresso"_ls,
                                              "getSpecialInstruction"_ls>
                    ? "Has Espresso override getSpecialInstruction()\n"
                    : "Missing Espresso override getSpecialInstruction()\n");

  std::cout << (class_is_base_of<"TASK::Coffee"_ls, "TASK::Cappuccino"_ls>
                    ? "Has Cappuccino derive from Coffee\n"
                    : "Missing Cappuccino derive from Coffee\n");
  std::cout << (class_has_override_memberfunc<"TASK::Cappuccino"_ls,
                                              "getDescription"_ls>
                    ? "Has Cappuccino override getDescription()\n"
                    : "Missing Cappuccino override getDescription()\n");
  std::cout << (class_has_override_memberfunc<"TASK::Cappuccino"_ls,
                                              "getSpecialInstruction"_ls>
                    ? "Has Cappuccino override getSpecialInstruction()\n"
                    : "Missing Cappuccino override getSpecialInstruction()\n");

  return 0;
}

//----------------------------------------------------------------------------//
// °                          === ONE SOLUTION ===                          ° //
//----------------------------------------------------------------------------//

namespace __solution__ {
#include <iostream>
#include <memory>
#include <string>

class Coffee {
 private:
  std::string m_name{};
  double m_price{};
  int m_stock{};

 public:
  Coffee(std::string name, double price, int stock)
      : m_name(name), m_price(price), m_stock(stock) {}

  auto sell(int quantity) -> double {
    m_stock -= quantity;
    return m_price * quantity;
  }
  virtual ~Coffee() = default;

  virtual auto getDescription() -> std::string = 0;
  virtual auto getSpecialInstruction() -> std::string {
    return "Standard brew";
  }
};

class Espresso : public Coffee {
 public:
  Espresso() : Coffee("Espresso", 3.5, 23) {}

  auto getDescription() -> std::string override {
    return "Strong and bold Italian classic";
  }
  auto getSpecialInstruction() -> std::string override {
    return "Serve in pre-heated cup";
  }
};

class Cappuccino : public Coffee {
 public:
  Cappuccino() : Coffee("Cappuccino", 4.7, 16) {}

  auto getDescription() -> std::string override {
    return "Smooth with perfect foam ratio";
  }
  auto getSpecialInstruction() -> std::string override {
    return "Sprinkle with cocoa powder";
  }
};

auto main(int /*argc*/, char* /*argv*/[]) -> int {
  std::unique_ptr<Coffee> espresso = std::make_unique<Espresso>();
  std::unique_ptr<Coffee> cappuccino = std::make_unique<Cappuccino>();

  int espressoQuantity{6};
  double espressoTotal{espresso->sell(espressoQuantity)};

  int cappuccinoQuantity{3};
  double cappuccinoTotal{cappuccino->sell(cappuccinoQuantity)};

  std::cout << "=== Espresso ===" << "\n";
  std::cout << "Description: " << espresso->getDescription() << "\n";
  std::cout << "Special Instruction: " << espresso->getSpecialInstruction()
            << "\n";
  std::cout << "Sold: " << espressoQuantity << " cups" << "\n";
  std::cout << "Total Price: " << espressoTotal << "\n";
  std::cout << std::endl;

  std::cout << "=== Cappuccino ===" << "\n";
  std::cout << "Description: " << cappuccino->getDescription() << "\n";
  std::cout << "Special Instruction: " << cappuccino->getSpecialInstruction()
            << "\n";
  std::cout << "Sold: " << cappuccinoQuantity << " cups" << "\n";
  std::cout << "Total Price: " << cappuccinoTotal << "\n";

  return 0;
}
}  // namespace __solution__