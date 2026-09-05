#import "/utils/todo.typ": TODO
#import "/utils/fr_qa_c.typ": C, FR, QA

= Requirements<requirements>

In order to establish the requirements for this project, this chapter will build upon the foundations laid in @background and the current approaches reviewed in @related_work. The identification of functional and qualitative requirements, in addition to constraints imposed by the limited time available, will serve as the underlying foundation for the design of this project. These elements will be further elaborated in the subsequent chapters.


== Header File Requirements


=== Functional Requirements<h_fr>

#FR(
  "Basic functionality",
)[ The header file contains the functionality of verification for specified requirements. ]
A comprehensive inspection of NFRs of classes, functions, variables, and the most prevalent implementations within classes is imperative.

\
#FR("Header-only")[ The verification logic and templates should be consolidated into a single C++ header file. ]
The utilization of a single header file approach is of paramount importance, as header-only files exhibit a more simplified distribution process in comparison to that of compiled libraries. This approach is particularly well-suited for code that is predominantly template-heavy @codefinity2026header. The incorporation of simplified distribution and inclusion into existing projects ensures the practical application of the concept beyond the confines of the problem space.

=== Quality Attributes<h_qa>

#QA(
  "Idempotency",
)[ It is imperative that the element in question be idempotent, thereby ensuring that the inclusion of the element, regardless of the number of repetitions, does not result in errors.  ]

#QA(
  "Portability",
)[ The utilization of standard C++ is imperative, while the employment of compiler-specific syntax is to be avoided. ]


#QA(
  "Documentation",
)[ The code should be written in a manner that is readily comprehensible without the need for extensive documentation. In the event that documentation is deemed necessary, it must be clear and concise. ]

=== Constraints<h_c>

#C(
  "Pure C++",
)[ The sole constraint imposed pertains to the utilization of pure C++ language. The employment of any alternative programming language must be avoided. ]


== System Requirements

Despite the fact that the system plays a secondary role in this thesis, it is still necessary to demonstrate the viability of the header file implementation and to evaluate the research in a straightforward and realistic manner.


=== Functional Requirements<s_fr>

#FR(
  "Basic functionality",
)[ The system possesses the functionality to execute the intended verification process for the specified requirement. ]

\
#FR(
  "Web UI",
)[ In order to provide a practical illustration of the system's functionality in a real-world context, it is necessary to deploy a web page through which the user can submit their code and receive an evaluation. ]

\
#FR(
  "Task expansion",
)[ The incorporation of new tasks into the verification process should not pose a significant challenge, provided that the existing codebase remains unaltered. This feature is imperative for preserving the flexibility and scalability of the future system over time. ]

\
#FR(
  "Containerization",
)[ The system in its entirety should be containerized for the purpose of facilitating deployment. This approach ensures the system's functionality across various environments without necessitating modifications, thereby simplifying the deployment of complex, multi-component applications. ]

\
#FR(
  "Archive",
)[ The system must possess the capacity to archive verification results, thereby enabling straightforward retrieval and analysis of past verification processes for the purpose of future development and problem identification. This feature is also crucial for the evaluation in @evaluation. ]

=== Quality Attributes<s_qa>

#QA(
  "Performance",
)[ It is imperative that the system responds within a reasonable timeframe, estimated to be approximately 10 seconds. In the event that the response time exceeds 30 seconds, it is reasonable to conclude that the system's viability is diminishing. ]

\
#QA("Security")[ The sent code should not pose a threat to the server or modify already archived files. ]

\
#QA("Documentation", ckey: "qa-documentation2")[
  The development of an informative user manual concerning the task creation process would be a crucial step in enhancing the functionality and usability of the system. ]


=== Constraints<s_c>

#C("Compilable code")[ The system shall exclusively process code that is eligible for compilation without errors. ]

\
#C("Technology")[ The system's construction will be predominantly utilizing the C++ programming language. ]


== Proposed System Design<proposed_design>

The system will be demonstrated through a webpage that displays C++ coding tasks and a field in which the solution to the given task can be entered and transmitted to the server. The server will be divided into two parts. The initial component will be a REST API server that will be tasked with the reception of the code solution and the subsequent transmission of an evaluation of the code. The subsequent step involves the utilization of the header file, the received code, and the task file to assess the code. The evaluation of the sent code will be archived.
