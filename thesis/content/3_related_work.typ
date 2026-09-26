#import "/utils/todo.typ": TODO

= Related Work<related_work>

This thesis sits at the intersection of three research strands. The first strand is the automated assessment of programming assignments. The second strand is the assessment of non-functional code requirements. The third strand is compile-time verification through C++ metaprogramming. The subsequent sections undertake a thorough examination of each strand, with the objective of identifying the gap that serves as the foundation for the work.



== Automated Assessment of Programming Assignments<related_work_aa>

Automated assessment has a long history in programming education. Historically, early systems focused on functional correctness, executing student submissions against test suites and generating pass/fail results. Surveys by #cite(<paiva2022automated>, form: "author"), #cite(<ullah2018effect>, form: "author") and #cite(<ala2005survey>, form: "author") catalogue a broad range of tools and techniques, distinguishing dynamic approaches, static approaches, and hybrid approaches that combine both @paiva2022automated @ullah2018effect @ala2005survey. #cite(<messer2024automated>, form: "author") conducted a survey of the current state of the art regarding automated tools for programming education. The majority of the reviewed papers focused on assignment correctness, thereby confirming that the predominant use of automated assessment remains the provision of feedback on functional correctness @messer2024automated.



== Non-Functional Code Requirements<related_work_nfr>

#cite(<eckhardt2016are>, form: "author") document that NFRs are notoriously challenging to evaluate, because they resist the binary pass/fail treatment that suits functional requirements @eckhardt2016are. In the context of programming education, this challenge is further exacerbated. Naming requirements are not merely technical constraints, but pedagogical instruments intended to cultivate professional practice @werf2024naming, and their evaluation serves a learning objective independent of runtime behavior.

Existing work on NFR assessment in education remains sparse and largely manual. Where automation exists, it is typically confined to syntactic convention checking using linters and static analysis tools.



== Compile-Time Verification in C++<related_work_metaprogramming>

C++ metaprogramming provides a distinct approach to structural verification. It involves the expression of requirements as compile-time constraints, thereby enabling the compiler to function as the verifier. Template metaprogramming, "_static_assert_", Substitution Failure Is Not An Error (SFINAE), C++20 _Concepts_ and C++26 _Reflections_ enable the examination of a broad spectrum of properties during compilation @vandevoorde2018template @eisenecker2024advanced.

A number of studies have previously utilized these techniques in domains such as library design @rahaman2022lib and error messages @rude2009cpp. However, the application of these techniques as a systematic pedagogical verification mechanism for non-functional code requirements appear to not been subject of extensive research thus far.



== Gap and Positioning<related_work_gap>

The literatures reviewed above reveal a consistent gap. Automated assessment research concentrates on functional correctness. NFR research establishes the difficulty of evaluating NFRs but offers few automated solutions for education. Compile-time verification is well understood as a language mechanism but has not been evaluated as a pedagogical verification mechanism.

This thesis aims to address this gap by designing, implementing, and evaluating a header-based C++ framework that leverages metaprogramming to verify non-functional structural requirements. It operates entirely within the standard C++ toolchain. The contribution provides a structured overview of the range of expressions offered by this technique, thereby answering the research question posed in the #link(<objectives>)[Objectives section].
