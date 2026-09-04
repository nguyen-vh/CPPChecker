#import "/utils/todo.typ": TODO

= Implementation <implementation>

This chapter delineates the design and implementation of the header file and the proposed system, which is derived from the requirements identified in @requirements. The implementation has been meticulously tailored to a real case usage in programming courses by #cite(<eisenecker2024advanced>, form: "prose"), ensuring its relevance and applicability to real-world scenarios.


== Implementation of CPPChecker

The header file that incorporates the templates utilized for the purpose of verifying the task requirements is designated as _"CPPChecker"_. This section will provide a more thorough examination of the header's functionalities, the process, and the rationale behind its implementation.

=== Prior Reflections Introduction

Before the commencement of this thesis, another effort was made to address the challenge. At that time, the C++ language did not yet support reflection, so an alternative approach had to be adopted. The approach employed utilized SFINAE (Substitution Failure Is Not An Error) with conventional C++17 syntax, subsequently adapting to the more recent C++20 _Concepts_. The underlying rationale for this approach is to employ an overload of the template, thereby facilitating the deduced type. In the event of a failure, the specialization is discarded, a process that circumvents the occurrence of a compile error @cpprefernce2026sfinae.

To complement that approach, it was necessary to have a set of fallback classes to which the compiler could refer in the event that a particular class was not found. Furthermore, an approach delineated in a blog post series by #cite(<chen2019namespaces>, form: "prose") was implemented. In this series, Chen placed namespaces in a way that necessitated a specific sequence for checking within those namespaces. Consequently, these namespaces offer an optimal location for the placement of fallback classes.

The objective was to implement standard template calls for the type and name verification of the requirements. However, it was observed that the template alone was incapable of generating nested namespaces and fallback classes, which resulted in issues when the template was used twice. In light of this deficiency, the utilization of C++ _Macros_ was employed to automate the generation of the majority of boiler code during the compile phase.

Precisely one month after the commencement of this thesis, GCC (GNU Compiler Collection) unveiled its latest iteration, GCC 16.1#footnote[ https://gcc.gnu.org/gcc-16/ ], which introduced C++ _Reflections_ support for the first time. The opportunity to revise the solution once more arose, with the objective of aligning it with the most recent C++26 standard. The entire thesis will be devoted to the reflection rewritten version. However, should further interest arise, the Appendix C will address the macro approach.

*[NOTE: Dont forget the appendix C]*



=== Template Declarations

==== String Literal TD

The file utilizes the latest feature of C++26 _Reflections_, to search for the task requirements.
The foundation of the implementation is rooted in the code contributed by Stack Overflow#footnote[ https://stackoverflow.com/questions ] users Oersted#footnote[ https://stackoverflow.com/users/21691539/oersted ] and 康桓瑋(Hewill Kang)#footnote[ https://stackoverflow.com/users/11638718/%e5%ba%b7%e6%a1%93%e7%91%8b ], a distinguished figure who has been recognized as one of only three individuals to attain the prestigious C++20 gold badge on the platform, as documented in @fig:appendix:oersted. The program utilizes _String Literal_ templates to pass the function name that has been searched for during compile time to the reflections. According to #cite(<gabe2011stackoverflow>, form: "prose"), "A string is a sequence of characters. A literal is data that's typed in as part of the program." In the header file, their _String Literal_ templates were utilized without modification.



==== Class TD

The initial approach was adopted and subsequently modified to align with the specified solution space. In their code, they sought a particular named function within a class. In the context of my own application, I am unaware of the existence of the class in question. Consequently, the class name has been modified to be passed as a _String Literal_. In addition, it was logical to disassociate the class lookup from their consolidated lookup solution. This approach was taken to avoid redundancy when new templates that require the class are introduced in the future. In contrast to the automatic detection of nested namespaces in Oersted's code, the present code did not exhibit such an ability. The solution that was implemented involved the incorporation of a loop that traversed all namespaces within the literal string to identify the class is displayed in @fig:Template_get_class_by_name and @fig:Template_has_class.

The final class templates can be utilized to verify the name of a class during compile time through the use of reflection. It is evident that the code can be utilized independently in scenarios where the verification of a class is undertaken. Moreover, its integration is imperative for the amalgamation of class functions and the execution of class-wide lookups.



==== Class Member Function TD<class_member_function>

Oersted's solution in @fig:appendix:oersted incorporates verifications for the input and return types of the function. This approach represents a missed opportunity to leverage the potential of templates and enhance their generic appeal. To illustrate, it would be advantageous for the template to function in scenarios where the primary objective is to ascertain the existence of a specific function, irrespective of its input type or verifying with its input type without the return type.

The implementation of this functionality was enabled by the application of _template default arguments_. By default, when the template is instantiated without explicitly specifying trailing parameters, the default argument is used, as established by #cite(<eisenecker2024advanced>, form: "prose").

\
#figure(
  image("../figures/Template_class_has_memberfunc.png"),
  caption: [Template to verify the existence and type of a function within a given class],
) <fig:Template_class_has_memberfunc>
\

In the @fig:Template_class_has_memberfunc line two, the default argument is designated as _unspecified_return_t_, which is defined as an empty _struct_. The final argument constitutes a template parameter _pack_, defined as "a template parameter that accepts zero or more template arguments" @cppreference2026pack.

In the 16th line of the template, a comparison is made between the instantiated template parameter, designated here as _"Returntype"_, and the custom _unspecified_return_t_. In the event that the two parameters are found to be congruent, it can be deduced that no return type has been specified, and the template will solely examine the presence of the function. In the event that the return type is found to be incompatible, a designated type has been allocated. As indicated on line 18, the templates have been programmed to verify if the _pack_ contains more than zero arguments. In the absence of zero arguments in the _"Inputtype"_, it can be deduced that no input arguments were provided. These cases involve a simple verification process that includes the function's existence and the appropriateness of the return type. In the event that input arguments are provided, the entirety of the function is subject to review.



==== Class Member Variable TD

Before addressing the main subject, it is imperative to clarify the terminology. The most precise designation in this context would be _"data member"_ instead of _"member variable"_, as substantiated by #cite(<cppreference2026classes>, form: "prose"), which asserts that "A class can have the following kinds of members:

1) data members

1a) non-static data members, including bit-fields

1b) static data members

2) member functions

3) nested types

4) enumerators

5) member templates".

\

An examination of  @fig:Template_class_has_membervar reveals that the utilization of _std::meta::is_variable()_ on lines 10 and 11 is insufficient. This is due to the fact that _std::meta::is_variable()_ exclusively applies to _static data members_, while _std::meta::is_nonstatic_data_member()_ is necessary for _non-static data members_.
In fact, the _std::meta::is_static_data_member()_ function is not a viable option, documented in the papers by #cite(<isocpp2025reflections>, form: "prose"), as _std::meta::is_variable()_ performs the same task.

\
#figure(
  image("../figures/Template_class_has_membervar.png"),
  caption: [Template to verify the existence and type of a variable within a given class],
) <fig:Template_class_has_membervar>
\

The remainder of the template definition is essentially analogous to that of the Class Member Function TD in @class_member_function, with the exception of the _pack_ element at the end of the template _parameter-list_.



==== Specialized Class Member TD

It should be noted that _CPPChecker_ also contains more specialized iterations of the aforementioned templates. This process involves verifying, for instance, a member function that falls within the scope of public, protected, or private _access specifiers_, or its static version.

\
#figure(
  image("../figures/Template_class_has_public_memberfunc.png"),
  caption: [Template to verify the existence and type of a static function within a given class in its public access specifier],
) <fig:Template_class_has_public_memberfunc>
\

As illustrated in @fig:Template_class_has_public_memberfunc, the template declaration exhibits a high degree of similarity with the template depicted in @fig:Template_class_has_memberfunc. The sole discrepancy manifests within the _for loop_, specifically in lines 10 and 11. In this instance, the members inside the class are matched for being _public_ and after for being _static_. As demonstrated in the foregoing example, the specialization of these templates is a relatively uncomplicated process. It is imperative to acknowledge the significance of the order in this context. For instance, the utilization of _std::meta::type_of()_ in the absence of _std::meta::has_identifier()_ can, under certain circumstances, result in the compiler emitting an error. This assertion has been previously documented by #cite(<oersted2026stackoverflow>, form: "prose"). Therefore, it is recommended to prioritize the validation of more general checks before addressing those that are more specialized. A comprehensive list of all available templates can be found in @fig:List_of_Templates.



==== ? Free Function ?



==== ? Free Variable ?



== Implementation of REST API Server <implementation_rest>

=== Design Goals <design_goals>

For the proposed system, the implementation and execution of all the quality attributes mentioned in @requirements is desired. For _QA5_, the utilization of Bubblewrap#footnote[ https://github.com/containers/bubblewrap ] will be employed to establish isolated environments for each task compile case, in the event that the code contains malicious intent. In regard to _QA6_, a GitHub page will be generated, and the procedures for utilizing and expanding the system will be thoroughly documented. However, due to temporal limitations, the _C2_ option is subject to constraints. The _C3_ option involves the utilization of Vue.js#footnote[ https://vuejs.org/ ] as the frontend application framework. This conclusion is substantiated by the observation that Vue.js exhibits a substantial advantage in terms of speed in implementing fundamental functionalities when compared to a pure C++ solution. Consequently, this decision enables the primary focus to be maintained on other aspects of the project. The backend API server will be written in C++, leveraging the CrowCpp framework#footnote[ https://github.com/crowcpp/crow ]. The deployment of the system will be facilitated through the utilization of Docker Compose#footnote[ https://docs.docker.com/compose/ ], accompanied by Dockerfiles for the frontend and backend services, respectively to meet _FR6_.
The RTT (Round-Trip Time) will be measured for _QA4_. In the event that the requirement is not met, modifications will be made.



=== Subsystem Decomposition <subsystem_decomposition>
#TODO[
  Describe the architecture of your system by decomposing it into subsystems and the services provided by each subsystem. Use UML class diagrams including packages / components for each subsystem.
]
\
*[NOTE: UML class diagrams including packages / components for each subsystem]*
\

The system under review is composed of three parts, in addition to the header file, for the purpose of checking the code. The frontend part, which was developed using Vue.js, facilitates user interaction with the application. This process entails the transmission of user input, which is subsequently processed and displayed alongside the task and evaluation of the code that has been submitted by the user. The second component is the REST API server, which is written in C++ with CrowCpp. The server's primary functions include receiving code, sending the evaluation back, archiving the evaluation, and executing the third component. The third component, which is written in C++ with Bubblewrap, compiles the task file. This file employs the header file to verify the code and generate the evaluation for the transmitted code.

The task file in @fig:Template_Taskfile exemplifies a template for creating the task files. As illustrated in lines 40 to 42, a macro definition is identified within a specified namespace. The macro's objective is to streamline the process of compiling the task file with code files that have been assigned distinct names. These code files are transmitted to the backend by the user. During the compilation process, it is possible to incorporate the compiler flag "-DINCLUDE_FILE=" alongside the name of the ".cpp" file corresponding to the code that has been sent. This approach eliminates the necessity to parse the code within the task file and subsequently replace it with the subsequent code, thereby enabling the execution of these processes in parallel. The complete code solution, inclusive of its main function, is incorporated herein. The presence of two main functions in the global space can result in a state of disarray for the compiler. Consequently, it is located within a designated namespace. A thorough evaluation of the advantages and disadvantages will be conducted in the subsequent section. The frontend and backend components will be deployed within containers managed by Docker Compose.

\
#figure(
  image("../figures/Template_Taskfile.png"),
  caption: [Template to create the task files.],
) <fig:Template_Taskfile>
\




#pagebreak()
=== Boundary Conditions
#TODO[
  Optional section describing the use cases how to start up the separate components of the system, how to shut them down, and what to do if a component or the system fails.
]

The utilization and expansion of the system have been thoroughly documented in the READMEs located within the GitHub repository#footnote[ https://github.com/nguyen-vh/CPPChecker/tree/main/server ]. A preliminary evaluation indicates that the "Make"#footnote[ https://en.wikipedia.org/wiki/Make_(software) ] program has been installed on the system. Subsequently, the utilization of the "make" function will initiate the process of spinning up the Docker containers. In contrast, the "make backend" function does not result in the deployment of the frontend container. The implementation of the "make down" function will result in the cessation of all container operations.

