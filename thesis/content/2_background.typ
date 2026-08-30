#import "/utils/todo.typ": TODO


= Background<background>
#TODO[
  Describe each proven technology / concept shortly that is important to understand your thesis. Point out why it is interesting for your thesis. Make sure to incorporate references to important literature here.
]


This chapter introduces the fundamental concepts that will be elaborated upon in subsequent chapters. The succeeding paragraphs help understand the problem space and the design of the solution. First, it will provide an overview of the fundamentals of unit testing. Subsequently, the concept of metaprogramming will be delineated. Following this, a concise exposure on header-only libraries will be presented.



== Unit Testing

A plethora of evaluation methods exists to ascertain the functionality of the program in accordance with its intended purpose. One such category is unit tests, which are considered to be relatively straightforward to automate in comparison to other types of tests @pittet2026. According to Microsoft, the term "unit test" is derived from the concept of "breaking down the functionality of a program into discrete, testable behaviors that can be evaluated as individual units" @microsoft2026unittest.
Unit testing involves the evaluation of a unit's functionality in isolation. In many cases, a minimal environment must be prepared for the evaluation of a unit. Such an environment may include variables or more complex data structures. Subsequently, the unit is executed with a specific set of parameters @eisenecker2022basic.
The employment of unit testing frameworks facilitates the development of unit tests, which possess the capacity to execute and generate results. The implementation and execution of these tests with each iteration of the code will provide feedback regarding the efficacy of the implemented changes. The objective of the tests is to assess whether the alterations have resulted in any alterations or compromises to the behavior of the existing code. As Microsoft asserts, "Unit testing exerts the most significant influence on the quality of code when it constitutes an integral component of the software development workflow" @microsoft2026unittest.



== Metaprogramming

This is a technique through which computer programs have the ability to treat other programs as their data @wiki2026metaprogramming. This finding suggests the potential for a program to manipulate other programs, including itself. A notable example of such a program is the GCC Compiler, which takes the program and generates an executable @stackoverflow2017metaprogramming. Metaprogramming can also be used to move computations from runtime to compile time and to generate code using compile time computations @wiki2026metaprogramming.

=== Templates

One such example is template metaprogramming (TMP), which is defined as "templates are used by a compiler to generate temporary source code, which is merged by the compiler with the rest of the source code and then compiled" @wiki2026templatemeta. The utilization of these templates can yield a range of outcomes, including compile-time constants, data structures, and entire functions @wiki2026templatemeta. Erwin Unruh's findings revealed that the C++ TMP system was Turing-complete, thereby enabling the execution of arbitrary programs at compile time @unruh2002, @eisenecker2024advanced. TMP facilitates the prioritization of architecture by the programmer, thereby enabling the compiler to generate any implementation necessitated by client code. Consequently, template metaprogramming has emerged as a pivotal element in contemporary programming languages, particularly due to its capacity to enhance the safety and reliability of software code @wiki2026templatemeta @eisenecker2024advanced.



=== Reflection

The capacity of a programming language to serve as its own metalanguage enables the practice of reflective programming, a concept referred to as "reflection" @wiki2026metaprogramming. Onyekwere's assertion posits that "reflection is a mechanism that enables a process to perform introspective operations, examine, and modify its own structure and behavior" @onyekwere2023medium @wiki2026reflection. Two forms of reflection are distinguished. The first of these is known as runtime reflection, and it is present in languages such as Golang and Java. The second type of compile-time reflection is supported by the C++ and Rust programming languages. As asserted by  #cite(<stackoverflow2014reflection>, form: "prose"), runtime reflection is eschewed due to the drawbacks of performance overhead, security restrictions, and exposure of internals. Conversely, compile time reflection offers a more streamlined approach, accompanied by a reduced set of disadvantages. Reflection is a process that enables programmers to develop generic software libraries. It facilitates the "display of data, the processing of various data formats, the serialization and deserialization of data for communication purposes, and the bundling and unbundling of data for containers or bursts of communication" @wiki2026reflection.



== Header-only library

