#import "/utils/todo.typ": TODO
#import "/utils/custom.typ": box, secth


= Introduction<intro>

Programming is widely regarded as an essential skill in the fields of computer science and engineering, as asserted by #cite(<hofbauer2022teaching>, form: "prose"). The acquisition of proficiency in programming can be accomplished within a relatively brief period. However, attaining excellence in this field necessitates a more extensive and sustained investment of time and effort. Consequently, it becomes imperative to initiate the instruction of these critical traits at an early stage.
One method for enhancing students' competencies involves the implementation of challenging and engaging coding assignments. The overarching objective of these assignments can be distilled into two key aspects. Assignments have been meticulously designed to enhance students' comprehension of course concepts, with a focus on conceptual understanding. Furthermore, these assignments are instrumental in promoting adherence to established programming practices @eisenecker2022basic @eisenecker2024advanced. This adherence is imperative for cultivating a robust foundation in the field and preparing students for potential professional work environments.



== Problem<problem>
The present thesis focuses on a particular type of non-functional requirement, termed "code nomenclature." The nomenclature of classes, functions, and variables is structurally imperative yet functionally inconsequential. It has been demonstrated that a class designated "Rectangle" exhibits equivalent functionality to one designated "ClassA," unless the program employs either reflection or serialization. It has been determined that nomenclature does not affect a program's computations, outputs, or interactions. Consequently, it cannot be regarded as a functional property. Instead, it is a structural and qualitative attribute, thus classifying it as an NFR. The latter pertains to the manner in which a system executes its functions, rather than the nature of its actions @eckhardt2016are.

In this thesis, the term "non-functional code requirements" is employed to denote constraints on the structural and organizational aspects of source code, including naming conventions, class/function signatures, type declarations, and visibility modifiers.
This distinction is practically relevant in programming assignments. The requirement for specific naming conventions extends beyond the scope of functional correctness. Instead, it functions as an educational instrument, cultivating the development of professional software engineering practices. The aforementioned conventions are designed to promote the creation of readable, maintainable, and structurally sound code. It is evident that these objectives are independent of runtime behavior and, as such, are valuable learning objectives in their own right @microsoft2025decorated.

The evaluation of such requirements poses a significant challenge, a well-documented difficulty experienced by NFRs @eckhardt2016are. The verification of functional correctness can be efficiently accomplished through the implementation of unit tests. The employment of static analysis tools, including linters and convention checkers, has been demonstrated to promote adherence to syntactic naming patterns. However, these tools rarely verify the semantic appropriateness of a name in relation to the element's role. This discrepancy is of consequence for automated pedagogical assessment. The objective of this thesis is to design, implement, and evaluate an automated system that verifies non-functional code requirements. In greater detail, the system will verify the presence, naming, signature, and return types of the classes and functions in question.

The approach undertaken in this thesis utilizes the C++ language itself as the verification mechanism. Metaprogramming has the capacity to express structural requirements in the form of compile-time constraints. When a student's code is compiled against a header containing these constraints, the compiler becomes the verifier, emitting errors or warnings for violations. This process functions exclusively within the standard C++ toolchain, thereby eliminating the necessity for external parsers or analysis tools. However, the efficacy of this technique in articulating intricate or nuanced requirements remains a subject of debate. This question is the fundamental premise of this thesis.



== Motivation<motivation>

The prevailing methodologies employed for the evaluation of non-functional code requirements have proven to be inadequate. The manual review process conducted by instructors is both time-consuming and subjective, thereby hindering the provision of timely feedback to students, particularly in large-scale courses. While static analysis tools (linters) can enforce basic syntactic rules, they fundamentally lack the capability to assess the semantic appropriateness of an identifier. To illustrate, a linter can enforce the "camelCase" convention but lacks the capacity to discern if a function is named "processData."

The impetus for this thesis stems from the necessity for an automated, scalable, and consistent method for evaluating the structural and semantic aspects of code. The objective of this study is to establish a connection between rudimentary syntactic verification and the substantial expense associated with manual review. The proposed system is designed to be readily accessible, capable of straightforward augmentation, and compatible with prevailing educational workflows.



== Objectives<objectives>

The central research objective of this thesis is to design, implement, and evaluate a header-based framework written in C++ that leverages metaprogramming to verify non-functional structural requirements in source code. The specific aims of this research are as follows:

1. Develop a reusable C++ header containing template definitions capable of enforcing requirements at compile time.

2. Evaluate the expressiveness of this approach by determining which requirements can and cannot be effectively verified.

3. Demonstrate the practical viability of the framework by integrating it into a larger system, which should comprise a Representational State Transfer (REST) Application Programming Interface (API) and a Web User Interface (UI). This integration will automate the verification workflow.

#box[*RQ:* What are the limitations of automated non-functional source code verification within the C++ programming language?]



== Methodology<methodology>

The methodology will entail the utilization of header files as the fundamental framework for this research study. In addition, the proposed approach will entail the incorporation of a server that is equipped with a REST API and a Web UI. This integration will serve to substantiate the practicability of automating the validation process of code and usability in a tangible setting. To provide a comprehensive answer to the research question, a thorough examination of the entire process will be conducted.

