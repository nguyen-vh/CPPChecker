#import "/utils/todo.typ": TODO

= Summary<summary>

The final chapter is designed to offer a comprehensive resolution to this thesis, presenting a summary of the achieved goals, the conclusions derived, and the potential future directions for research.



== Status

=== Realized Goals <realized_goals>

The work presented in this thesis has been demonstrated to satisfy the requirements of @fr-header-only and @qa-portability. This is evident because all TDs are contained in a single header file. Additionally, the file in question can be included in any existing project without the necessity of external dependencies.  In the light of SFINAE, TD using reflections satisfied the criteria of @qa-idempotency and did not lead to an error. It can be stated with a high degree of confidence that @fr-basic-functionality is fulfilled for the subset of TDs listed in @fig:List_of_Templates.

With respect to the implementation of the server stack, it can be posited that a substantial proportion of the requirements enumerated in @system_requirements have been satisfied. The server stack is deployed within containers (@fr-containerization) with a web UI (@fr-web-ui), an archive (@fr-archive), and a backend application (@fr-basic-functionality2), which perform the fundamental operations to demonstrate the system's functionality. Following @fr-task-expansion, the task files are also expandable, thereby obviating the need for exhaustive familiarity with the entirety of the research. Additionally, comprehensive documentation of all elements is available on GitHub (@qa-documentation2). It is noteworthy that the security and performance concerns, designated as @qa-security and @qa-performance, have been implemented with minimal expense, aligning with the stipulated requirements without requiring primary attention.



=== Open Goals

Despite the assertion in Section 7.1.1 that @fr-basic-functionality is nearing completion, the requirement remains ambiguous, allowing for a considerable degree of flexibility in its implementation. The extent to which the TD expands can vary significantly, contingent upon the scope of one's own definition of "basic functionality." In that regard, it would remain one of the open goals of this thesis.

A review of the header file documentation for @qa-documentation reveals significant shortcomings. The naming scheme should be easily discernible and clearly indicate its functionality. However, for a library, minimal documentation remains a prerequisite. Although not explicitly required, the integration of UT and documentation is inherently linked, and the implementation of UT for the existing TD would have been advantageous.



== Conclusion

This thesis set out to determine the strengths and limitations of automated non-functional source code verification within C++. The evaluation indicates that the approach's strengths lie in two layers. At the verification layer, presence, naming form, signature, and return types can be enforced entirely within the standard toolchain. This is achieved without the use of external parsers, runtime execution of the sent code, or compromising idempotence under SFINAE. At the automation layer, the REST API and Web UI deliver these checks end-to-end with a mean RTT of 8 seconds and no runtime execution risk.

The limitations follow the same two-layer division. At the verification layer, three boundaries emerge. Firstly, the expressiveness of the technique is currently constrained by the maturity of the reflections library, whose projection of source entities into "_std::meta::info_" is not yet reliable for aliased return types. Secondly, the approach can verify that a declaration has a given shape, but not that its name is semantically appropriate. This is a conceptual boundary of type-level verification, not an implementation defect. Thirdly, the precision of verification is bounded by the precision of the requirement, so requirements that admit multiple valid answers cannot be enforced as a single compile-time constraint. At the automation layer, the pipeline inherits every gap in the TD catalogue. Consequently, an unimplemented check is silently absent rather than reported, and its scalability under concurrent load was not evaluated.

These findings address the RQ within the scope of the evaluated subset of template definitions. The work thus demonstrates that non-functional requirements are partially expressible as compile-time constraints in C++, and it identifies the limits of that expressiveness. The header file is presently usable as a supplement to unit testing, where it prevents errors at compilation and yields a compile-time boolean value. The extension of this technique beyond the evaluated subset, and confirming whether a matured reflections implementation removes the first boundary, remains a task for further research.



== Future Work

If time were not a limiting factor, the implementation of a significantly greater number of TD would result in a greater degree of variability during the source code verification process. In addition, it would be unwise to depend exclusively on independent parties to test the library. Instead, the implementation of a UT process is necessary to proactively identify any anomalous behaviors early on.  In the context of automation, the RTT and load balancing benchmarking for the REST API server is pending, with the objective of demonstrating the impact of the implemented changes and additions through concrete results.
At a certain stage, the integration into the existing UT frameworks, such as GTest, would be implemented to ensure a seamless integration. With respect to automation, in the event that the server's capacity is overwhelmed due to a high volume of concurrent users transmitting their code to the API, a multitude of strategies exist for enhancing the system's swiftness and effectiveness.
