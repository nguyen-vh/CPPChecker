#import "/utils/todo.typ": TODO


= Background<background>

This chapter introduces the fundamental concepts that are further explored in the following chapters. The following paragraphs help to clarify the problem space and the design of the solution. First, an overview of the fundamentals of unit testing is provided. Next, the concept of metaprogramming is explained.



== Unit Testing

A plethora of evaluation methods exists to ascertain the functionality of the program in accordance with its intended purpose. One such category is unit tests, which are considered to be relatively straightforward to automate in comparison to other types of tests @pittet2026. According to #cite(<microsoft2026unittest>, form: "author"), the term "unit test" is derived from the concept of "breaking down the functionality of a program into discrete, testable behaviors that can be evaluated as individual units" @microsoft2026unittest.
Unit Testing (UT) involves the evaluation of a unit's functionality in isolation. In many cases, a minimal environment must be prepared for the evaluation of a unit. Such an environment may include variables or more complex data structures. Subsequently, the unit is executed with a specific set of parameters @eisenecker2022basic.
The employment of UT frameworks facilitates the development of unit tests, which possess the capacity to execute and generate results. The implementation and execution of these tests with each iteration of the code will provide feedback regarding the efficacy of the implemented changes. The objective of the tests is to assess whether the alterations have resulted in any functional alterations or compromises to the behavior of the existing code. As Microsoft asserts, "Unit testing exerts the most significant influence on the quality of code when it constitutes an integral component of the software development workflow" @microsoft2026unittest.

#pagebreak()


=== Frameworks <ut_frameworks>

In the domain of software development, the two most prevalent testing frameworks in the C++ programming language are Google Test#footnote[ https://github.com/google/googletest ] (GTest) and Catch2#footnote[ https://github.com/catchorg/Catch2 ]. GTest necessitates discrete compilation, a process that can influence the time required for setup. Conversely, Catch2 v2 is a lightweight, header-only testing framework that prioritizes simplicity @catch2 @pamela2025ut. Catch2 has also released version 3, which functions as a conventional library, incorporating multiple headers and a distinct implementation. For the purposes of this example, Catch2 v2 will be utilized due to its status as a single-header library and its close alignment with the solution space. However, it is imperative to acknowledge the applicability of the presented example across related frameworks. Frameworks such as Catch2 and GTest offer advanced unit testing capabilities, which is why Catch2 can serve as a representative example for the broader set of existing frameworks. Yet, when confronted with the problem delineated in @problem, it becomes apparent that a workaround is necessary.

In @fig:catch2_hasClass, a code example is presented that utilizes the Catch2 v2 single-header file to illustrate a UT example. The code functions properly without errors. However, it is imperative to consider the implications of alternative class designations or the absence of the class. As demonstrated by the @fig:catch2_noClass example, the UT does not indicate a failure. Instead, the compiler refuses to compile. In the GTest framework, the macro _GTEST_SKIP()_ has been implemented to bypass assertions. In a similar vein, the macro _SKIP()_ has been incorporated into Catch2 v3. It should be noted that these skips are only applicable to runtime assertions, which, in turn, will not resolve the compile-time issue @googletest2026.

#pagebreak()


== Metaprogramming

This is a technique through which computer programs have the ability to treat other programs as their data @wiki2026metaprogramming. This finding suggests the potential for a program to manipulate other programs, including itself. A notable example of such a program is the GNU Compiler Collection (GCC) Compiler, which takes the program and generates an executable @stackoverflow2017metaprogramming. Metaprogramming can also be used to move computations from runtime to compile time and to generate code using compile time computations @wiki2026metaprogramming.

=== Templates

One such example is template metaprogramming (TMP), a form of static metaprogramming, in which C++ templates are used to perform computations during compilation. A template metaprogram is defined as a program whose execution is carried out by the compiler through template instantiation, and whose result is a set of template instantiations @krzysztof2000generative @vandevoorde2018template.

The utilization of these templates can yield a range of outcomes, including compile-time constants, data structures, and entire functions @wiki2026templatemeta. #box[#cite(<unruh2002>, form: "author")'s] findings revealed that the C++ TMP system is Turing-complete, thereby enabling the execution of arbitrary programs at compile time @unruh2002, @eisenecker2024advanced. TMP facilitates the prioritization of architecture by the programmer, thereby enabling the compiler to generate any implementation necessitated by client code. Consequently, template metaprogramming has emerged as a pivotal element in contemporary programming languages, particularly due to its capacity to enhance the safety and reliability of software code @wiki2026templatemeta @eisenecker2024advanced.



=== Reflection

The capacity of a programming language to serve as its own metalanguage enables the practice of reflective programming, a concept referred to as "reflection" @wiki2026metaprogramming. #box[#cite(<onyekwere2023medium>, form: "author")'s] assertion posits that "reflection is a mechanism that enables a process to perform introspective operations, examine, and modify its own structure and behavior" @onyekwere2023medium @wiki2026reflection. Two forms of reflection are distinguished. The first of these is known as runtime reflection, and it is present in languages such as Golang and Java. The second type of compile-time reflection is supported by the #box[C++] programming language as well as Rust, among other programming languages.
Runtime reflection is eschewed due to the drawbacks of performance overhead, security restrictions, and exposure of internals. Conversely, compile-time reflection offers a more streamlined approach, accompanied by a reduced set of disadvantages, as asserted by #cite(<stackoverflow2014reflection>, form: "prose"). Reflection is a process that enables programmers to develop generic software libraries. It facilitates the "display of data, the processing of various data formats, the serialization and deserialization of data for communication purposes, and the bundling and unbundling of data for containers or bursts of communication" @wiki2026reflection.
