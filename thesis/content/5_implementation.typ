#import "/utils/todo.typ": TODO

= Implementation <implementation>

This chapter delineates the design and implementation of the proposed system, which is derived from the requirements identified in @requirements. The implementation has been meticulously tailored to a real case usage in programming courses by Prof. Eisenecker, ensuring its relevance and applicability to real-world scenarios.



== Design Goals <design_goals>

For the proposed system, the implementation and execution of all the quality attributes mentioned in @requirements is desired. For _QA1_, the utilization of Bubblewrap#footnote[ https://github.com/containers/bubblewrap ] will be employed to establish isolated environments for each task compile case, in the event that the code contains malicious intent. In regard to _QA3_, a GitHub page will be generated, and the procedures for utilizing and expanding the system will be thoroughly documented. However, due to temporal limitations, the _C1_ option is subject to constraints. The _C2_ option involves the utilization of Vue.js#footnote[ https://vuejs.org/ ] as the frontend application framework. This conclusion is substantiated by the observation that Vue.js exhibits a substantial advantage in terms of speed in implementing fundamental functionalities when compared to a pure C++ solution. Consequently, this decision enables the primary focus to be maintained on other aspects of the project. The backend API server will be written in C++, leveraging the CrowCpp framework#footnote[ https://github.com/crowcpp/crow ]. The deployment of the system will be facilitated through the utilization of Docker Compose#footnote[ https://docs.docker.com/compose/ ], accompanied by Dockerfiles for the frontend and backend services, respectively to meet _FR6_.

*[NOTE: Should FR6 be a QA?]*


== Subsystem Decomposition <subsystem_decomposition>
#TODO[
  Describe the architecture of your system by decomposing it into subsystems and the services provided by each subsystem. Use UML class diagrams including packages / components for each subsystem.
]
\
*[NOTE: UML class diagrams including packages / components for each subsystem]*
\

The system under review is composed of three parts, in addition to the header file, for the purpose of checking the code. The frontend part, which was developed using Vue.js, facilitates user interaction with the application. This process entails the transmission of user input, which is subsequently processed and displayed alongside the task and evaluation of the code that has been submitted by the user. The second component is the REST API server, which is written in C++ with CrowCpp. The server's primary functions include receiving code, sending the evaluation back, archiving the evaluation, and executing the third component. The third component, which is written in C++ with Bubblewrap, compiles the task file. This file utilizes the header file to verify the code and generate the evaluation for the transmitted code. The frontend and backend components will be deployed within containers managed by Docker Compose.

*[NOTE: Show/point clear parts using future UML]*


== Persistent Data Management
#TODO[
  Optional section that describes how data is saved over the lifetime of the system and which data. Usually this is either done by saving data in structured files or in databases. If this is applicable for the thesis, describe the approach for persisting data here and show a UML class diagram how the entity objects are mapped to persistent storage. It contains a rationale of the selected storage scheme, file system or database, a description of the selected database and database administration issues.
]
\
*[NOTE: UML class diagram how the entity objects are mapped to persistent storage]*
\







== Global Software Control
#TODO[
  Optional section describing the control flow of the system, in particular, whether a monolithic, event-driven control flow or concurrent processes have been selected, how requests are initiated and specific synchronization issues
]

== Boundry Conditions
#TODO[
  Optional section describing the use cases how to start up the separate components of the system, how to shut them down, and what to do if a component or the system fails.
]

