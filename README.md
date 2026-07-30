# CPPChecker



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#legacy">Legacy</a></li>
    <li><a href="#license">License</a></li>
  </ol>
</details>



> [!TIP]
> ### QUICKSTART
> Copy-Paste the header [cxxchecker_reflection.hpp](https://github.com/nguyen-vh/CPPChecker/blob/main/include/cxxchecker_reflection.hpp) to your project and start to code.



<!-- ABOUT THE PROJECT -->
## About The Project
The goal is to create a header-only library for verifying non-functional code requirements. This means checking whether a specific class contains a member function with the exact name "foo". 

The project began with macros and many other workarounds to circumvent the limitations of the C++ era before the introduction of reflections. For more information, see the [Legacy](#legacy) section. 

However, with the introduction of GCC16.1 and support for reflections, the project has now been reworked, and the new header [cxxchecker_reflection.hpp](https://github.com/nguyen-vh/CPPChecker/blob/main/include/cxxchecker_reflection.hpp) represents the latest version of the project.
By leveraging reflections to accomplish the goal in a more elegant way, this project aims to provide a simple and efficient solution for verifying non-functional code requirements. The library is designed—like its predecessor—to be easy to use and integrate into existing projects. Including the header file is everything that is needed to begin the compile-time verification mania.

The project itself is a proof of concept designed to demonstrate that verifying non-functional C++ code is possible using only C++ and is easily extensible. For this demonstration, I also wrote a simple server that can accept C++ code and verify it against the requirements set beforehand. The server is written in C++ and is located in the [server](https://github.com/nguyen-vh/CPPChecker/tree/main/server) directory; further information can be found in the README there.



### Built With
* [![C++][cpp26-badge]][cpp-url]



<!-- GETTING STARTED -->
## Getting Started
This is a header-only project, so by downloading the header [cxxchecker_reflection.hpp](https://github.com/nguyen-vh/CPPChecker/blob/main/include/cxxchecker_reflection.hpp) you are good to go.
For more detail keep reading below or skip to the [next section](#usage).


### Prerequisites
The most obvious solution would be a compiler that supports C++26 and later versions. One option would be GCC 16.1, though it is not yet officially included in the Alpine image or in Homebrew for macOS users. To install GCC 16.1, you can use this [link](https://gcc.gnu.org/gcc-16/) for more information. The other option is to run a container with GCC 16.1 installed. This could be, for example, [Dev Containers](https://code.visualstudio.com/docs/devcontainers/containers) with GCC 16.1 installed. This project also includes devcontainer configuration in the root directory to help you get started.


> [!TIP]
> * [Better Comments](https://github.com/aaron-bond/better-comments) by Aaron Bond (VS Code) to improve your experience with comments. I use custom colors and symbols, acquire them in my [miscellaneous-cpp](https://github.com/nguyen-vh/miscellaneous-cpp/blob/main/IDE/extensions/better_comments.json) repository.
> * [Better C++ Syntax](https://github.com/jeff-hykin/better-cpp-syntax) by Jeff Hykin (VS Code) to make the code stand out more clearly with syntax highlighting.


### Installation
Get the header [cxxchecker_reflection.hpp](https://github.com/nguyen-vh/CPPChecker/blob/main/include/cxxchecker_reflection.hpp) and add it to your "include" folder inside your project.
You could also clone the repository and add a reference to the header file "include/cxxchecker_reflection.hpp", but that would just take up valuable storage space—which in todays economy will be huge burden.


> [!NOTE]
> If you want the server setup, refer to the [server](https://github.com/nguyen-vh/CPPChecker/tree/main/server) directory.


<!-- USAGE -->
## Usage
Here you will find instructions on how to use the header. For information on the old header, see the [Legacy](#legacy) section.

![List of Content][cxxchecker_reflections_list_of_content]

These are all the templates that have been implemented so far. Using them is as intuitive as you would expect, given their naming conventions.

> [!IMPORTANT]
> Names used inside the templates should be literal strings with suffix _ls, for example ` "foo"_ls `


Let us take a look at the `class_has_memberfunc<>` template. If we examine this example in detail, it will be easier to understand how to use the other templates, since they all work according to the same principle.

The general schema for the templates are as follows:
```cpp
class_has_memberfunc<"class"_ls, "function"_ls, returntype, inputtype1, inputtype2, ... >
```

Given we have a `class X` with a member function `foo(std::string, int)`:
```cpp
class X {
  double foo(std::string, int);
};
```
What shenanigans could I do while only using the `class_has_memberfunc<>` template?

1. Classic, I could check whether the `class X` has a member function `foo`:
    ```cpp
    std::cout << class_has_memberfunc<"X"_ls, "foo"_ls> << "\n";
    ```
    - What would happen if `class X` did not exist? It would return `false`.
    - What would happen if function `foo` did not exist? It would return `false`.

2. I could check whether the function has exactly the returntype `double`:
    ```cpp
    std::cout << class_has_memberfunc<"X"_ls, "foo"_ls, double> << "\n";
    ```
    - What would happen if it has a different returntype? It would return `false`.

3. I could check whether it has exactly two parameters `std::string` and `int`:
    ```cpp
    std::cout << class_has_memberfunc<"X"_ls, "foo"_ls, double, std::string, int> << "\n";
    ```
    - What would happen if I only check for one parameter? It would return `false`.
    - What would happen if I check for more than 2 parameters? It would return `false`.
    - What would happen if I change the order of parameters? It would return `false`.
    - Is there a limit on how many parameters I can check for? No.

Here are all the answers from above:
```cpp
#include <iostream>
#include <string>
#include "cxxchecker_reflections.hpp"

class X {
  double foo(std::string, int);
};

auto main(int /*argc*/, char* /*argv*/[]) -> int {
  // 1.
  std::cout << class_has_memberfunc<"X"_ls, "foo"_ls> << "\n"; // true
  std::cout << class_has_memberfunc<"Y"_ls, "foo"_ls> << "\n"; // false
  std::cout << class_has_memberfunc<"X"_ls, "goo"_ls> << "\n"; // false

  // 2.
  std::cout << class_has_memberfunc<"X"_ls, "foo"_ls, double> << "\n"; // true
  std::cout << class_has_memberfunc<"X"_ls, "foo"_ls, float> << "\n"; // false

  // 3.
  std::cout << class_has_memberfunc<"X"_ls, "foo"_ls, double, std::string, int> << "\n"; // true
  std::cout << class_has_memberfunc<"X"_ls, "foo"_ls, double, std::string> << "\n"; // false
  std::cout << class_has_memberfunc<"X"_ls, "foo"_ls, double, std::string, int, int> << "\n"; // false
  std::cout << class_has_memberfunc<"X"_ls, "foo"_ls, double, int, std::string> << "\n"; // false
  
  return 0;
}
```

What about classes, functions, etc. inside of a namespace or inside nested namespaces?
```cpp
namespace TASK {
class X {
  double foo(std::string, int);
};
}
```

Only the first parameter inside out template need to address the namespace structure to make it work.
```cpp
std::cout << class_has_memberfunc<"TASK::X"_ls, "foo"_ls> << "\n";
```

> [!IMPORTANT]
> This is how to write the requirement test for the task files as part of the server configuration.


<!-- LEGACY -->
## Legacy



<!-- LICENSE -->
## License
All source files include the license information at the beginning. Files that use other projects—such as "server/RestApi.cpp", which uses CrowCpp—also include the relevant license information.

For the general license, see [LICENSE][license].



<!-- MARKDOWN LINKS & IMAGES -->
[cpp26-badge]:https://img.shields.io/badge/C++26-00599C?style=for-the-badge&logo=cplusplus
[cpp-url]:https://isocpp.org/
[cxxchecker_reflections_list_of_content]:https://github.com/nguyen-vh/CPPChecker/blob/main/src/common/images/cxxchecker_reflections_list_of_content.png

[license]:https://github.com/nguyen-vh/CPPChecker/blob/main/LICENSE.md


<!-- LEGACY

TO-DO LIST

/* CPPChecker is an automated C++ program designed to thoroughly examine provided C++ code for the presence of classes, functions, variables, and their corresponding data types, along with verifying the output. The main objective of CPPChecker is to validate the given code after ensuring its independent functionality, guaranteeing that it runs smoothly without encountering errors during the checking process. To achieve this robustness, the program leverages SFINAE (Substitution Failure Is Not An Error) techniques and hides certain elements within namespaces, effectively circumventing compiler errors that might occur when classes, functions, or other components are absent. The provided code should be placed inside a namespace named "STUDENT" for the program not to fail. Overall, CPPChecker serves as a powerful tool for code verification.
Build

/* This program is designed to be dependency-free, meaning no third-party libraries are used. To use the code, include "iostream" and "sstream". If there's an error, include "type_traits". You can easily copy and paste the code since the program runs on its own.
Setup


Description

/* This tool is designed to facilitate the thorough evaluation of students' code, ensuring that they have successfully adhered to the specified task requirements. With the Tool, instructors can systematically assess the submitted code for accuracy, completeness, and alignment with the given assignment.


 -->