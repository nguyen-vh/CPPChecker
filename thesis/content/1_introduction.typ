#import "/utils/todo.typ": TODO
#import "/utils/custom.typ": box, secth


= Introduction<intro>

Programming is widely regarded as an essential skill in the fields of computer science and engineering, as asserted by #cite(<hofbauer2022teaching>, form: "prose"). The acquisition of proficiency in programming can be accomplished within a relatively brief period. However, attaining excellence in this field necessitates a more extensive and sustained investment of time and effort. Consequently, it becomes imperative to initiate the instruction of these critical traits at an early stage.
One method for enhancing students' competencies involves the implementation of challenging and engaging coding assignments. The overarching objective of these assignments can be distilled into two key aspects. Assignments have been meticulously designed to enhance students' comprehension of course concepts, with a focus on conceptual understanding. Furthermore, these assignments are instrumental in promoting adherence to established programming practices @eisenecker2022basic @eisenecker2024advanced. This adherence is imperative for cultivating a robust foundation in the field and preparing students for potential professional work environments.



== Problem<problem>
The non-functional problem in this thesis is the nomenclature of classes, functions, variables, and other elements. It is imperative to note that the necessity of an exact name for a class does not constitute a prerequisite for the program to function. During the process of compilation, the compiler will generate encoded strings referred to as "decorated names" for linking @microsoft2025decorated. The class name assigned to the class is not relevant to the compiler.
Consequently, it can be deduced that the problem space falls within the non-functional category.

In the process of creating task assignments, two aspects must be evaluated. The first aspect is the functional aspect, which refers to the intended functionality of the code. The second aspect is the non-functional requirements of the code, which encompass the non-functional attributes of the code that are not directly related to its functionality. Non-functional requirements (NFRs) are distinguished from functional requirements by the manner in which the system is expected to execute its functions @eckhardt2016are.
When evaluating the task for functionality, unit testing and testing of the output are commonly used. NFRs, however, present a distinct set of challenges. The ambiguity inherent in their description, coupled with the interpretive discretion afforded to the evaluator, renders them more challenging to evaluate.

The issue at hand manifests when the task entails meticulous adherence to instructions, entailing the predetermination of names for classes, functions, variables, and other such components. This pedagogical strategy is designed to encourage adherence to proper naming conventions and to provide students with a robust foundation for their functional code part. In the context of C++, it is challenging to test for NFRs, such as the name of a class.



== Motivation<motivation>

A variety of approaches exist for verifying these requirements. These include the manual verification of answers and the use of other programming languages for the parsing of source code. However, from an objective perspective, these solutions appear to lack the elegance and simplicity that could be achieved. Despite the fact that the present study will concentrate on a limited segment of NFRs, specifically the verification of code, efforts will be made to ensure maximum ease of use and fast expandability. This approach is intended to minimize the time required for manual code checking and the development of numerous edge cases for the parser approach.



== Objectives<objectives>
#TODO[
  Describe the research goals and/or research questions and how you address them by summarizing what you want to achieve in your thesis, e.g. developing a system and then evaluating it.
]

The central research objective of this thesis is to address the following question:

#box[*RQ:* What are the limitations of automated non-functional source code verification within the C++ programming language?]

The inquiry is addressed through the formulation of code capable of verifying the aforementioned NFRs.


== Methodology<methodology>

The methodology will entail the utilization of header files as the fundamental framework for this research study. Furthermore, the proposed approach will incorporate the integration of a server that is equipped with a Representational State Transfer (REST) Application Programming Interface (API) and a Web User Interface (UI). This integration will serve to substantiate the practicability of automating the validation process of code and usability in a tangible setting. To provide a comprehensive answer to the research question, a thorough examination of the entire process will be conducted.

