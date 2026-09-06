#import "/utils/todo.typ": TODO

= Summary<summary>

The final chapter is designed to offer a comprehensive resolution to this thesis, presenting a summary of the achieved goals, the conclusions derived, and the potential future directions for research.



== Status

=== Realized Goals <realized_goals>

The work presented in this thesis has been demonstrated to satisfy the requirements of @fr-header-only and @qa-portability. This is evident through the observation that all TDs are contained within a single header file. Additionally, the file in question can be included in any existing project without the necessity of external dependencies.  In the light of SFINAE, TD using reflections satisfied the criteria of @qa-idempotency and did not lead to an error. It can be stated with a high degree of confidence that @fr-basic-functionality was largely fulfilled, as evidenced by the implementation of TD listed in @fig:List_of_Templates.

With respect to the implementation of the server stack, it can be posited that a substantial proportion of the requirements enumerated in @system_requirements have been satisfied. The server stack is deployed within containers (@fr-containerization) with a web UI (@fr-web-ui), an archive (@fr-archive), and a backend application (@fr-basic-functionality2), which perform the fundamental operations to demonstrate the system's functionality. Following @fr-task-expansion, the task files are also expandable, thereby obviating the need for exhaustive familiarity with the entirety of the research. Additionally, comprehensive documentation of all elements is available on GitHub (@qa-documentation2). It is noteworthy that the security and performance concerns, designated as @qa-security and @qa-performance, have been implemented with minimal expense, aligning with the stipulated requirements without requiring primary attention.



=== Open Goals

Despite the assertion in Section 7.1.1 that FR1 is nearing completion, the requirement remains ambiguous, allowing for a considerable degree of flexibility in its implementation. The extent to which the TD expands can vary significantly, contingent upon the scope of one's own definition of "basic functionality." In that regard, it would remain one of the open goals of this thesis.

A review of the header file documentation for QA3 reveals significant shortcomings. It could be posited that the naming scheme should be easily discernible and clearly indicate its functionality. However, for a library, minimal documentation should still be a requirement. Although not explicitly required, the integration of UT and documentation is inherently linked, and the implementation of UT for the existing TD would have been advantageous.



== Conclusion

The utilization of TMP, in conjunction with the latest C++ standard feature, reflections, for the implementation of CPPChecker and the REST API server for the automation component, should provide a preliminary indication of the limitations encountered when attempting to automate the verification of non-functional source code with C++. Although the limit has not been reached, it is nevertheless possible to provide an initial response affirming the feasibility of this undertaking. Basic verification, as demonstrated by the evaluations, is indeed attainable. However, it is vital to recognize the necessity for further exploration to investigate unexplored areas.

Presently, the header file can be utilized to supplement UT, thereby preventing errors during the compilation process and ensuring the return of a practical boolean value.



== Future Work

If time were not a limiting factor, the implementation of a significantly greater number of TD would result in a greater degree of variability during the source code verification process. In addition, it would be unwise to depend exclusively on independent parties to test the library. Instead, I would initiate the UT process and proactively identify any anomalous behaviors early on. At a certain stage, the integration into the existing UT, such as GTest, would be implemented to ensure a seamless integration. With respect to automation, in the event that the server's capacity is overwhelmed due to a high volume of concurrent users transmitting their code to the API, a multitude of strategies exist for enhancing the system's swiftness and effectiveness.
