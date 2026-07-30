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

The project began with macros and many other workarounds to circumvent the limitations of the C++ era before the introduction of reflections. For more information, see the <a href="#legacy">Legacy</a> section. 

However, with the introduction of GCC16.1 and support for reflections, the project has now been reworked, and the new header [cxxchecker_reflection.hpp](https://github.com/nguyen-vh/CPPChecker/blob/main/include/cxxchecker_reflection.hpp) represents the latest version of the project.
By leveraging reflections to accomplish the goal in a more elegant way, this project aims to provide a simple and efficient solution for verifying non-functional code requirements. The library is designed—like its predecessor—to be easy to use and integrate into existing projects. Including the header file is everything that is needed to begin the compile-time verification mania.

The project itself is a proof of concept designed to demonstrate that verifying non-functional C++ code is possible using only C++ and is easily extensible. For this demonstration, I also wrote a simple server that can accept C++ code and verify it against the requirements set beforehand. The server is written in C++ and is located in the [server](https://github.com/nguyen-vh/CPPChecker/tree/main/server) directory; further information can be found in the README there.



### Built With
* [![C++][cpp26-badge]][cpp-url]



<!-- GETTING STARTED -->
## Getting Started
This is a header-only project, so by downloading the header [cxxchecker_reflection.hpp](https://github.com/nguyen-vh/CPPChecker/blob/main/include/cxxchecker_reflection.hpp) you are good to go.
For more detail keep reading below or skip to the <a href="#usage">next section</a>.


### Prerequisites
The most obvious solution would be a compiler that supports C++26 and later versions. One option would be GCC 16.1, though it is not yet officially included in the Alpine image or in Homebrew for macOS users. To install GCC 16.1, you can use this [link](https://gcc.gnu.org/gcc-16/) for more information. The other option is to run a container with GCC 16.1 installed. This could be, for example, [Dev Containers](https://code.visualstudio.com/docs/devcontainers/containers) with GCC 16.1 installed. This project also includes devcontainer configuration in the root directory to help you get started.


> [!TIP]
> * [Better Comments](https://github.com/aaron-bond/better-comments) by Aaron Bond (VS Code) to improve your experience with comments. I use custom colors and symbols, acquire them in my [miscellaneous-cpp](https://github.com/nguyen-vh/miscellaneous-cpp/blob/main/IDE/extensions/better_comments.json) repository.
> * [Better C++ Syntax](https://github.com/jeff-hykin/better-cpp-syntax) by Jeff Hykin (VS Code) to make the code stand out more clearly with syntax highlighting.


### Installation
Get the header [cxxchecker_reflection.hpp](https://github.com/nguyen-vh/CPPChecker/blob/main/include/cxxchecker_reflection.hpp) and add it to your "include" folder inside your project.


> [!NOTE]
> If you want the server setup, refer to the [server](https://github.com/nguyen-vh/CPPChecker/tree/main/server) directory.


<!-- USAGE -->
## Usage



<!-- LEGACY -->
## Legacy



<!-- LICENSE -->
## License
All source files include the license information at the beginning. Files that use other projects—such as "server/RestApi.cpp", which uses CrowCpp—also include the relevant license information.

For the general license, see [LICENSE][license].



<!-- MARKDOWN LINKS & IMAGES -->
[cpp26-badge]:https://img.shields.io/badge/C++26-00599C?style=for-the-badge&logo=cplusplus
[cpp-url]:https://isocpp.org/
[license]:https://github.com/nguyen-vh/CPPChecker/blob/main/LICENSE.md


<!-- LEAGCY

TO-DO LIST

/* CPPChecker is an automated C++ program designed to thoroughly examine provided C++ code for the presence of classes, functions, variables, and their corresponding data types, along with verifying the output. The main objective of CPPChecker is to validate the given code after ensuring its independent functionality, guaranteeing that it runs smoothly without encountering errors during the checking process. To achieve this robustness, the program leverages SFINAE (Substitution Failure Is Not An Error) techniques and hides certain elements within namespaces, effectively circumventing compiler errors that might occur when classes, functions, or other components are absent. The provided code should be placed inside a namespace named "STUDENT" for the program not to fail. Overall, CPPChecker serves as a powerful tool for code verification.
Build

/* This program is designed to be dependency-free, meaning no third-party libraries are used. To use the code, include "iostream" and "sstream". If there's an error, include "type_traits". You can easily copy and paste the code since the program runs on its own.
Setup


Description

/* This tool is designed to facilitate the thorough evaluation of students' code, ensuring that they have successfully adhered to the specified task requirements. With the Tool, instructors can systematically assess the submitted code for accuracy, completeness, and alignment with the given assignment.


 -->