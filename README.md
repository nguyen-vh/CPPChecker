# **CPPChecker**

A C++-Program developed to automatically check provided c++-code for the existence of classes, functions, variables and their types, as well as the ooutput. The goal is to check the provided code after its known that it can run by itself and not cause an error in the checking process. To achieve this, the program uses SFINAE-techniques as well as hiding in namespaces to prevent a compiler error when the class/function/etc. is missing.
This repository has the program "CPPChecker.cpp" with examples, "cppchecker.hpp" as header for own usage with all the functionalities and in the Macros-folder the split-up code for even more freedom.

## **Download**

This program has the intention of running dependancy free, so no third-party-libriary are being used. To use the code, include <iostream> and <sstream>. If it gives an error, include <type_traits>. Copy and paste works here because the program runs on its own.

### **Setup**

+ Tested program with **C++20** and **C++23** (August 2023)
+ For better comments experience download **"Better Comments"** by Aaron Bond (VS Code)
+ For more color in code download **Better C++ Syntax** by Jeff Hykin (VS Code)

### **Important**

There is a Github-Action which tests "CPPChecker.cpp", if it fails, **DO NOT DOWNLOAD IT!**




