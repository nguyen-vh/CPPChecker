# **CPPChecker**

CPPChecker is a C++ program developed to automatically check provided C++ code for the existence of classes, functions, variables, and their types, as well as the output. The primary goal is to verify the provided code after it's known that it can run by itself without causing errors during the checking process. To achieve this, the program utilizes SFINAE techniques and hiding in namespaces to prevent compiler errors when the class, function, etc., is missing.

## **Download**

This program is designed to be dependency-free, meaning no third-party libraries are used. To use the code, include '<iostream>' and '<sstream>'. If there's an error, include '<type_traits>'. You can easily copy and paste the code since the program runs on its own.

### **Setup**

+ The program has been tested with **C++20** and **C++23** (August 2023)
+ For a better comments experience, consider downloading **"Better Comments"** by Aaron Bond (VS Code)
+ To add more color to the code, you can download **"Better C++ Syntax"** by Jeff Hykin (VS Code)

### **Important**

There's a Github Action in place that tests "CPPChecker.cpp". If it fails, **DO NOT DOWNLOAD IT!**









