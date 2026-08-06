// Copyright (c) 2026-present Hoang Nguyen
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
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

<script setup lang="ts">
import { ref, reactive, onMounted } from 'vue';

interface Task {
  id: number;
  title: string;
  description: string;
  task_token: string;
  solution: string;
}

const selected_task = ref<Task | null>(null);
const code = ref<string>('');
const is_submitting = ref<boolean>(false);
const response = ref<string>('');
const show_solution = ref<boolean>(false);

const tasks = reactive<Task[]>([
  {
    id: 1,
    title: 'Task 1: Rectangle',
    description: `
Define a struct named "Rectangle" with the elements "m_width" and "m_height" of type float.

Extend the struct with a member function "getArea" that returns a float value representing the area of the rectangle.

In the main function, create a rectangle with a width of 15.5 and a height of 20, and print "Area: " along with the area of the rectangle.
`,
    task_token: 'Rectangle1',
    solution: `
#include <iostream>

struct Rectangle {
  float m_width{};
  float m_height{};

  Rectangle(float w, float h) : m_width(w), m_height(h) {}

  auto getArea() -> float { return m_width * m_height; }
};

auto main(int /*argc*/, char* /*argv*/[]) -> int {
  std::cout << "Area: " << Rectangle(15.5f, 20.0f).getArea() << "\\n";

  std::cout << std::endl;
  return 0;
}
`
  },
  {
    id: 2,
    title: 'Task 2: Space',
    description: `
Define a global constant "LIGHT_SPEED" with value 299792458.0 (meters per second) of type double.

Write a free function "calculateDelay" that takes distance in kilometers (double) and returns signal travel time in seconds.

Create a class "SpaceProbe" with private members "m_name" (string), "m_distance" (double in km) and a constructor to initialize both.

Add private method "getSignalDelay()" that uses the free function above.
Add a method "sendMessage()" that prints:
"Sending to [name]..."
"Signal arrives in XX.XX seconds"

In main function create a probe "Pluto" at 7500000000 km. Send a message.
`,
    task_token: 'Space2',
    solution: `
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
    std::cout << "Sending to " << m_name << "..." << "\\n";
    std::cout << "Signal arrives in: " << getSignalDelay() << " seconds";
    std::cout << std::endl;
  }
};

auto main(int /*argc*/, char* /*argv*/[]) -> int {
  SpaceProbe("Pluto", 7500000000.0).sendMessage();

  return 0;
}
`
  },
  {
    id: 3,
    title: 'Task 3: Coffeeshop',
    description: `
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
`,
    task_token: 'Coffee3',
    solution: `
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

  std::cout << "=== Espresso ===" << "\\n";
  std::cout << "Description: " << espresso->getDescription() << "\\n";
  std::cout << "Special Instruction: " << espresso->getSpecialInstruction()
            << "\\n";
  std::cout << "Sold: " << espressoQuantity << " cups" << "\\n";
  std::cout << "Total Price: " << espressoTotal << "\\n";
  std::cout << std::endl;

  std::cout << "=== Cappuccino ===" << "\\n";
  std::cout << "Description: " << cappuccino->getDescription() << "\\n";
  std::cout << "Special Instruction: " << cappuccino->getSpecialInstruction()
            << "\\n";
  std::cout << "Sold: " << cappuccinoQuantity << " cups" << "\\n";
  std::cout << "Total Price: " << cappuccinoTotal << "\\n";

  return 0;
}
`
  }
]);

onMounted(() => {
  if (tasks.length > 0) {
    selected_task.value = tasks[0] as Task;
  }
});

const onTaskChange = () => {
  response.value = '';
  code.value = '';
  show_solution.value = false;
};

const toggleSolution = () => {
  if (selected_task.value) {
    show_solution.value = !show_solution.value;
  }
};

const submitCode = async () => {
  if (!selected_task.value || !code.value.trim()) {
    return;
  }

  is_submitting.value = true;
  response.value = '';

  try {
    const result = await submitToBackend(selected_task.value, code.value);
    response.value = result;
  } catch (error) {
    response.value = error instanceof Error ? error.message : 'Failed to submit code. Please try again.';
  } finally {
    is_submitting.value = false;
  }
};

const submitToBackend = async (task: Task, code: string): Promise<string> => {
  const url = `/api/${task.task_token}`;

  const response = await fetch(url, {
    method: 'POST',
    headers: {
      'Content-Type': 'text/plain',
    },
    body: code
  });

  console.log(url);

  return await response.text();
};
</script>

<template>
  <div id="app">
    <div class="container">
      <header>
        <h1>CPPChecker Webpage</h1>
      </header>

      <div class="task-section">
        <label for="task-select">Select Task:</label>
        <select id="task-select" v-model="selected_task" @change="onTaskChange">
          <option v-for="task in tasks" :key="task.id" :value="task">
            {{ task.title }}
          </option>
        </select>
      </div>

      <div class="description-section" v-if="selected_task">
        <h2>Task Description:</h2>
        <div class="description-content">
          <div v-for="(line, index) in selected_task.description.split('\n')" :key="index" class="description-line">
            {{ line || '\u00A0' }}
          </div>
        </div>
      </div>
    </div>

    <div class="solution-section" v-if="selected_task && show_solution">
      <div class="solution-header">
        <h2>Solution</h2>
      </div>
      <pre class="solution-code">{{ selected_task.solution }}</pre>
    </div>

    <div class="solution-toggle-section" v-if="selected_task">
      <button class="solution-toggle-btn" @click="toggleSolution">
        {{ show_solution ? 'Hide Solution' : 'Show Solution' }}
      </button>
    </div>

    <div class="code-section">
      <h2>Your C++ Solution</h2>
      <textarea v-model="code" class="code-editor" placeholder="  Write your C++ code here..." rows="12"
        spellcheck="false"></textarea>
    </div>

    <button class="submit-btn" @click="submitCode" :disabled="is_submitting || !code.trim()">
      {{ is_submitting ? 'Submitting...' : 'Submit Solution' }}
    </button>

    <div class="response-section" v-if="response">
      <h2>Response</h2>
      <pre class="output">{{ response }}</pre>
    </div>
  </div>
</template>

<style>
body,
#app {
  background: #0d0d0d;
  color: #e0e0e0;
}

#app {
  font-family: 'New Computer Modern', monospace;
}

.container,
.solution-section,
.code-section,
.response-section {
  background: #1a1a1a;
  border: 1px solid #2a2a2a;
  border-radius: 12px;
  padding: 24px;
  margin-bottom: 20px;
}

h1 {
  font-size: 2rem;
  font-weight: 500;
  letter-spacing: -0.5px;
  margin-bottom: 24px;
}

h2 {
  font-size: 1.2rem;
  font-weight: 500;
  margin-bottom: 12px;
  color: #e0e0e0;
}


.task-section {
  margin-bottom: 12px;
}

.task-section label {
  display: block;
  color: #e0e0e0;
  margin-bottom: 6px;
  font-weight: 500;
}

.task-section select {
  width: 100%;
  padding: 10px 12px;
  background: #0d0d0d;
  border: 1px solid #2a2a2a;
  border-radius: 8px;
  color: #e0e0e0;
  font-size: 0.95rem;
  transition: border-color 0.2s;
}

.task-section select:focus {
  outline: none;
  border-color: #4a4a4a;
}

.description-section {
  background: #0d0d0d;
  border: 1px solid #2a2a2a;
  border-radius: 8px;
  padding: 16px;
}

.description-content {
  color: #e0e0e0;
  line-height: 1.8;
}

.description-line {
  padding: 2px 0;
  white-space: pre-wrap;
}

.solution-toggle-section {
  text-align: center;
  margin: 20px 0;
}

.solution-toggle-btn {
  padding: 10px 24px;
  background: #2a2a2a;
  color: #e0e0e0;
  border: 1px solid #3a3a3a;
  border-radius: 8px;
  font-size: 1rem;
  font-weight: 500;
  cursor: pointer;
  transition: all 0.2s;
}

.solution-toggle-btn:hover {
  background: #333;
  border-color: #4a4a4a;
}

.solution-header {
  margin-bottom: 12px;
  color: #e0e0e0;
}

.close-solution-btn {
  background: none;
  border: none;
  color: #888;
  font-size: 1rem;
  cursor: pointer;
  padding: 0 8px;
  transition: color 0.2s;
  line-height: 1;
}

.close-solution-btn:hover {
  color: #e0e0e0;
}

.solution-code,
.output {
  background: #0d0d0d;
  color: #e0e0e0;
  padding: 12px;
  border-radius: 6px;
  overflow-x: auto;
  font-size: 13px;
  line-height: 1.6;
  border: 1px solid #2a2a2a;
  margin: 0;
  white-space: pre-wrap;
  word-wrap: break-word;
}


.code-editor {
  width: 100%;
  padding: 12px;
  background: #0d0d0d;
  border: 1px solid #2a2a2a;
  border-radius: 8px;
  color: #e0e0e0;
  font-size: 13px;
  line-height: 1.6;
  resize: vertical;
  transition: border-color 0.2s;
  box-sizing: border-box;
}

.code-editor:focus {
  outline: none;
  border-color: #4a4a4a;
}

.code-editor::placeholder {
  color: #666;
}

.submit-btn {
  width: 100%;
  padding: 12px;
  background: #2a2a2a;
  color: #e0e0e0;
  border: 1px solid #3a3a3a;
  border-radius: 8px;
  font-size: 0.95rem;
  font-weight: 500;
  cursor: pointer;
  transition: all 0.2s;
  margin-bottom: 20px;
}

.submit-btn:hover:not(:disabled) {
  background: #333;
  border-color: #4a4a4a;
}

.submit-btn:disabled {
  opacity: 0.5;
  cursor: not-allowed;
}
</style>