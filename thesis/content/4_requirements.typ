#import "/utils/todo.typ": TODO
#import "/utils/fr_qa_c.typ": C, FR, QA

= Requirements

In order to establish the requirements for this project, this chapter will build upon the foundations laid in Chapter 2 and the current approaches reviewed in Chapter 3. The identification of functional and qualitative requirements, in addition to constraints imposed by the limited time available, will serve as the underlying foundation for the design of this project. These elements will be further elaborated in the subsequent chapters.



== Proposed Design

The system will be demonstrated through a webpage that displays C++ coding tasks and a field in which the solution to the given task can be entered and transmitted to the server. The server will be divided into two parts. The initial component will be a Representational State Transfer (REST) application programming interface (API) server that will be tasked with the reception of the code solution and the subsequent transmission of an evaluation of the code. The subsequent step involves the utilization of the header file, the received code, and the task file to assess the code. The evaluation of the sent code will be archived.



=== Functional Requirements

#FR(
  "Web application",
)[ In order to provide a practical illustration of the system's functionality in a real-world context, it is necessary to deploy a web page through which the user can submit their code and receive an evaluation. ]
\
#FR(
  "Basic functionality",
)[ The system possesses the functionality to execute the intended verification process for the specified requirement. ]
\
#FR("Header-only")[ The verification logic and templates should be consolidated into a single C++ header file. ]
The utilization of a single header file approach is of paramount importance, as header-only files exhibit a more simplified distribution process in comparison to that of compiled libraries. This approach is particularly well-suited for code that is predominantly template-heavy @codefinity2026header. The incorporation of simplified distribution and inclusion into existing projects ensures the practical application of the concept beyond the confines of the problem space.
\
#FR(
  "Task expansion",
)[ The incorporation of new tasks into the verification process should not pose a significant challenge, provided that the existing codebase remains unaltered. This feature is imperative for preserving the flexibility and scalability of the future system over time. ]
\
#FR(
  "Archive",
)[ The system must possess the capacity to archive verification results, thereby enabling straightforward retrieval and analysis of past verification processes for the purpose of future development and problem identification. This feature is also crucial for the evaluation in Chapter 6. ]
\
#FR(
  "Containerization",
)[ The system in its entirety should be containerized for the purpose of facilitating deployment. This approach ensures the system's functionality across various environments without necessitating modifications, thereby simplifying the deployment of complex, multi-component applications. ]
\


=== Quality Attributes

#QA("Security")[ The sent code should not pose a threat to the server or modify already archived files. ]
\
#QA(
  "Performance",
)[ It is imperative that the system respond within a reasonable timeframe, estimated to be approximately 10 seconds. In the event that the response time exceeds 30 seconds, it is reasonable to conclude that the system's viability is diminishing. ]
\
#QA("Documentation")[
  The development of an informative user manual concerning the task creation process would be a crucial step in enhancing the functionality and usability of the system. ]
\

=== Constraints

#C("Compilable code")[ The system shall exclusively process code that is eligible for compilation without errors. ]
\
#C("Technology")[ The system's construction will be predominantly utilizing the C++ programming language. ]
\



== System Models
#TODO[
  This section includes important system models for the requirements.
]

=== Use Case Model
#TODO[
  This subsection should contain a UML Use Case Diagram including roles and their use cases. You can use colors to indicate priorities. Think about splitting the diagram into multiple ones if you have more than 10 use cases. *Important:* Make sure to describe the most important use cases using the use case table template (./tex/use-case-table.tex). Also describe the rationale of the use case model, i.e. why you modeled it like you show it in the diagram.

]

=== Analysis Object Model
#TODO[
  This subsection should contain a UML Class Diagram showing the most important objects, attributes, methods and relations of your application domain including taxonomies using specification inheritance (see @bruegge2004object). Do not insert objects, attributes or methods of the solution domain. *Important:* Make sure to describe the analysis object model thoroughly in the text so that readers are able to understand the diagram. Also write about the rationale how and why you modeled the concepts like this.

]

=== Dynamic Model
#TODO[
  This subsection should contain dynamic UML diagrams. These can be a UML state diagrams, UML communication diagrams or UML activity diagrams.*Important:* Make sure to describe the diagram and its rationale in the text. *Do not use UML sequence diagrams.*
]

=== User Interface
#TODO[
  Show mockups of the user interface of the software you develop and their connections / transitions. You can also create a storyboard. *Important:* Describe the mockups and their rationale in the text.
]
