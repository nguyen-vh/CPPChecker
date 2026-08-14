#import "/utils/todo.typ": TODO

= Implementation

This chapter delineates the design and implementation of the proposed system, which is derived from the requirements identified in Chapter 4. The implementation has been meticulously tailored to a real case usage in programming courses by Prof. Eisenecker, ensuring its relevance and applicability to real-world scenarios.



== Design Goals

For the proposed system, the implementation and execution of all the quality attributes mentioned in Chapter 4 is desired. For QA1, the utilization of Bubblewrap#footnote[ https://github.com/containers/bubblewrap ] will be employed to establish isolated environments for each task compile case, in the event that the code contains malicious intent. In regard to QA3, a GitHub page will be generated, and the procedures for utilizing and expanding the system will be thoroughly documented. However, due to temporal limitations, the C1 option is subject to constraints. The C2 option involves the utilization of Vue.js#footnote[ https://vuejs.org/ ] as the frontend application framework. This conclusion is substantiated by the observation that Vue.js exhibits a substantial advantage in terms of speed in implementing fundamental functionalities when compared to a pure C++ solution. Consequently, this decision enables the primary focus to be maintained on other aspects of the project. The backend API server will be written in C++, leveraging the CrowCpp framework#footnote[ https://github.com/crowcpp/crow ].



== Subsystem Decomposition
#TODO[
  Describe the architecture of your system by decomposing it into subsystems and the services provided by each subsystem. Use UML class diagrams including packages / components for each subsystem.
]




== Hardware Software Mapping
#TODO[
  This section describes how the subsystems are mapped onto existing hardware and software components. The description is accompanied by a UML deployment diagram. The existing components are often off-the-shelf components. If the components are distributed on different nodes, the network infrastructure and the protocols are also described.
]

== Persistent Data Management
#TODO[
  Optional section that describes how data is saved over the lifetime of the system and which data. Usually this is either done by saving data in structured files or in databases. If this is applicable for the thesis, describe the approach for persisting data here and show a UML class diagram how the entity objects are mapped to persistent storage. It contains a rationale of the selected storage scheme, file system or database, a description of the selected database and database administration issues.
]

== Access Control
#TODO[
  Optional section describing the access control and security issues based on the quality attributes and constraints. It also de- scribes the implementation of the access matrix based on capabilities or access control lists, the selection of authentication mechanisms and the use of en- cryption algorithms.
]

== Global Software Control
#TODO[
  Optional section describing the control flow of the system, in particular, whether a monolithic, event-driven control flow or concurrent processes have been selected, how requests are initiated and specific synchronization issues
]

== Boundry Conditions
#TODO[
  Optional section describing the use cases how to start up the separate components of the system, how to shut them down, and what to do if a component or the system fails.
]

