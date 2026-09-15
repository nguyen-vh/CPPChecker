#import "/utils/custom.typ": secth

Programming assignments teach students to code and develop sophisticated software @hofbauer2022teaching. These assignments often impose constraints on the non-functional aspects of the code, giving students the opportunity to solve them in a creative manner. A comprehensive evaluation of the assignment is essential for constructive feedback. However, C++ offers multiple valid problem-solving methods, and a single template does not provide a pragmatic approach for automated assessment. Manual review of each piece of code is time-consuming, particularly for large courses.

This thesis thoroughly examines the available methods for automated assessment and explores the limits of non-functional source code verification and its automation. The program utilizes the C++ programming language as a verification mechanism, leveraging template metaprogramming to express structural requirements as compile-time constraints. The objective of this research is to develop a "header-only" C++ library for verifying non-functional requirements for C++ code, with a pragmatic implementation of a server stack. The stack comprises a REST API and a Web UI to automate the verification workflow.

The header library's C++ implementation offers a valid approach to the latest metaprogramming additions. The real-world evaluation indicates the feasibility of fundamental verification. However, the reflection library exhibits anomalous behavior during type alias processing and efficiency problems arise during verification of abstract classes. While the proposed framework provides a solid foundation for automated non-functional code verification, further exploration is necessary to address identified limits and expand library expressiveness through additional definitions and unit testing.



#secth[KEYWORDS]
Non-Functional Requirements, Computer Science Education, Automatic Assessment, Metaprogramming, Reflections
