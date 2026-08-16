#import "/utils/todo.typ": TODO
#import "/utils/custom.typ": box, secth


= Introduction <intro>

Programming is widely regarded as an essential skill in the fields of computer science and engineering, as asserted by #cite(<hofbauer2022teaching>, form: "prose"). The acquisition of proficiency in programming can be accomplished within a relatively brief period. However, attaining excellence in this field necessitates a more extensive and sustained investment of time and effort. Consequently, it becomes imperative to initiate the instruction of these critical traits at an early stage.
One method for enhancing students' competencies involves the implementation of challenging and engaging coding assignments. The overarching objective of these assignments can be distilled into two key aspects. Assignments have been meticulously designed to enhance students' comprehension of course concepts, with a focus on conceptual understanding. Furthermore, these assignments are instrumental in promoting adherence to established programming practices *[NOTE: find in bpp/app book]*. This adherence is imperative for cultivating a robust foundation in the field and preparing students for potential professional work environments.



== Problem <problem>

In the process of creating task assignments, two aspects must be evaluated: the functional aspect, which refers to the intended functionality of the code, and the non-functional requirements of the code, which encompass the non-functional attributes of the code that are not directly related to its functionality. Non-functional requirements (NFRs) are distinguished from functional requirements by the manner in which the system is expected to execute its functions @eckhardt2016are.
When evaluating the task for functionality, unit testing and testing of the output are commonly used. Non-functional requirements, however, present a distinct set of challenges. The ambiguity inherent in their description, coupled with the interpretive discretion afforded to the evaluator, renders them more challenging to evaluate.


*[NOTE: Is this not functional rather than non-functional?]*



The issue at hand manifests when the task entails meticulous adherence to instructions, entailing the predetermination of names for classes, functions, variables, and other such components. This pedagogical strategy is designed to encourage adherence to proper naming conventions and to provide students with a robust foundation for their functional code part. In the context of C++, it is challenging to test for non-functional requirements, such as the name of a class.



== Motivation <motivation>

A variety of approaches exist for verifying these requirements. These include the manual verification of answers and the use of other programming languages for the parsing of source code. However, from an objective perspective, these solutions appear to lack the elegance and simplicity that could be achieved. Despite the fact that the present study will concentrate on a limited segment of non-functional requirements, specifically the verification of code, efforts will be made to ensure maximum ease of use and fast expandability. This approach is intended to minimize the time required for manual code checking and the development of numerous edge cases for the parser approach.



== Objectives <objective>
#TODO[
  Describe the research goals and/or research questions and how you address them by summarizing what you want to achieve in your thesis, e.g. developing a system and then evaluating it.
]

The main research objective of this thesis is to answer the central question below:

#box[*RQ 1:* What are the limitations of automated non-functional source code verification within the C++ programming language?]

The question is addressed through a meticulous examination of existing approaches and the most recent language standards, implementing both to compare them.

*[NOTE: Do I have space to compare both?]*

The methodology will include the header file implementation, but additionally also involve a server to prove the viability of automating the process of validating code. To provide a comprehensive answer to the research question, a thorough examination of the entire process will be conducted.

\
*[NOTE: Move to requirements]*
\

In consideration of the aforementioned research question, it is imperative that several goals be established for the implemented system. The research goals are as follows:


#secth[Research Goal 1: Header File]

#box[*RG 1.1:* The implementation of the verification component should be a "header-only" library to ensure maximum portability and reusability.]

The primary concern should be the solution to the aforementioned problem state. However, the "header-only" nature of the code is of secondary importance. The creation of a reusable header is of significant value, as it allows for its application in various projects and its integration into existing ones. Additionally, it is imperative that the functionality of the system under consideration be independent of external frameworks.


#box[*RG 1.2:* The implementation must refrain from parsing the code during source code checking, such as using tokens or other forms.]

Upon observing the prevalence of methodologies that employ parsing or tokenizing the entirety of the source code, it becomes evident that such approaches are not optimal. Consequently, an alternative approach will be pursued.


#secth[Research Goal 2: API Server]

#box[*RG 2.1:* The server is required to utilize the aforementioned header exclusively for the purpose of verifying the code that has been transmitted.]


#box[*RG 2.2:* A containerized approach should be deployed for the server.]

In order to facilitate the demonstration of the project and to accommodate other users who may wish to experiment with it at a later time, it is imperative that the configuration for running the server be designed to be as user-friendly as possible.


#box[*RG 2.3:* The development of a rudimentary web application is imperative for the purposes of evaluation and demonstration.]


This finalizes the enumeration of objectives to be executed in the designated project and provides a response to the research question.


#TODO[
  == Outline

  Describe the outline of your thesis

  * maybe *
]


