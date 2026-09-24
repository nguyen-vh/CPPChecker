#import "/utils/todo.typ": TODO

= Evaluation<evaluation>

This section provides a detailed evaluation of the previously mentioned implementation of CPPChecker using the REST API server and the web UI.

== Design

The evaluation is based on a real case scenario, as outlined in @implementation_rest.
To that end, task files were created, see @fig:Taskfile_Rectangle, @fig:Taskfile_Space and @fig:Taskfile_Coffee, with requirements similar to those found in the programming course by #cite(<eisenecker2022basic>, form: "prose") @eisenecker2024advanced. In addition, the stack is deployed entirely on servers belonging to Leipzig University to estimate the RTT.
This task was not carried out by the author alone. Other parties were deliberately tasked with trying to break the header file library, and some of their results were unexpected.
This serves as the basis for the subsequent evaluation.



== Objectives

The three objectives delineated in the Introduction are consolidated into a single execution. This approach is employed for the evaluation, during which the implemented template definitions are subjected to testing. Subsequently, a comparison is made between the results of the testing and the expected outcomes. This analysis unveils the potential limitations and advantages of the current implementations. Due to time constraints, many template definitions remain unimplemented, which reduces the scope of the test. The succeeding paragraphs address the REST API server, the web UI, and the research question.



== Results

The aforementioned parties conducted a rigorous testing process, the results of which indicated that the majority of requirements enumerated in the header file were satisfied. The thesis identified a number of unanticipated outcomes.
First, when defining an alias type and subsequently employing that alias type as the return type for a function, the TD is unable to recognize it, as illustrated in @fig:Eval_Alias. The TD has identified the use of the alias for any other purpose.
The second issue pertains to the "_class_has_pure_virtual_memberfunc<>_" complication, which has already hindered the process of creating and testing the task. While it possesses the capability to discern pure virtual member functions, the TD's subsequent evaluation would be flawed should the quantity of template parameters subjected to inspection increase.
In Task 3, as indicated in @fig:Taskfile_Coffee, the development of an abstract class was a requirement. However, the TD has not yet been written for it. In the final analysis, certain functions necessitated an input type designated as "_double_." However, it should be noted that the use of "_const double&_" would also be considered valid. It is crucial to highlight that the system did not verify the output of the sent code. Consequently, the necessity to write code inside the main function becomes redundant.

The REST API server and web UI stack functioned without error or unexpected behavior, and the code sent for evaluation did not compromise the integrity of the system. The mean RTT for all three tasks is 8 seconds. The fastest recorded RTT was 5 seconds, while the longest recorded RTT was 12 seconds. The length of the sent code ranges from 10 to 75 lines. The testing was conducted over a university Virtual Private Network (VPN) to access the university server from outside.



== Findings <findings>

The last two findings stem from imprecise task file requirements rather than from the checker itself. The abstract class requirement could not be verified, and the input type requirement admitted multiple valid answers. It is evident that the abstract class could have been omitted as a requirement, given the inability to verify its presence and the potential for multiple responses as input type, refer to the expanded version in @fig:Taskfile_Space, specifically lines 78 and 79.

With regard to the initial two observations, it is conceivable that the _\<meta>_ standard library (reflections library) is not functioning as intended. This phenomenon could be attributed to the library being an early release that lacks some reflections features, or the TD for those findings being implemented incorrectly. It is important to note that both of these options are possible. In general, the issue is more likely to occur in the reflections library, as evidenced by the failure of the "_class_has_memberfunc<>_" to function properly when declaring an alias of type float for the evaluation and returning on a simple type check (refer to @fig:Eval_Alias_Check).

When considered as a whole, the observations can be classified into two categories: limitations inherent to the metaprogramming approach, and limitations arising from the requirement specification itself.

\

1. Limitations of the approach
  - Alias-type detection failure (@fig:Eval_Alias): TD cannot see through "_using_" when the alias is used as a return type for a function, although it detects the alias elsewhere.

  - "_class_has_pure_virtual_memberfunc<>_" scaling issue: Correctness degrades as the number of inspected template parameters grows.

  Both of these findings point to the early-release reflections library as the likely cause, indicating an expressive limit of the technique rather than a bug in the tooling.

\

2. Limitations of the requirement specification
  - Abstract-class requirement in Task 3 (@fig:Taskfile_Coffee) is unverifiable because no TD was written for it.

  - "_double_" vs. "_const double&_" ambiguity in @fig:Taskfile_Space, which should allow multiple valid answers.

  These are not failures of the underlying approach. Rather, they demonstrate that the precision of compile-time verification is constrained by the specificity of the requirements it encodes.

\
These findings address the RQ to a limited extent. They identify the points of failure of the approach, but not its full reach.



== Limitations

The limitations of this evaluation can be categorized into two distinct classes. The initial category comprises limitations pertaining to the evaluation method. The second category comprises limitations pertaining to the system under evaluation. The former are addressed first, as they constitute the foundation of the confidence in the findings. Subsequently, these elements are restated as the expressive boundaries of the approach itself.


The evaluation approach that has been employed was to replicate the actual case scenario. However, in the absence of temporal constraints, a comprehensive UT would have identified the bugs irrespective of the initial conditions. Consequently, the probability of a bias in testing specific edge cases is high, and it is improbable that all anomalous behaviors have been identified.

A design decision is the omission of an output check, as this practice places all checks at compile time, making the verification process faster, as well as not allow malicious code execution. The compromise entails the exclusion of functional correctness from the scope of the project, thereby rendering the "_main_" function superfluous.

The boundaries of the approach itself follow from these observations. Firstly, the expressiveness of the technique is currently constrained by the maturity of the reflections library. As reflected entities are represented as "_std::meta::info_" values, any inaccuracy in the manner in which the library projects a source entity into said representation is propagated to each TD that inspects it. This phenomenon impacts the resolution of aliases and the management of an increasing number of inspected template parameters. Whether a fully matured reflections implementation will resolve these cases remains unresolved. Secondly, given that verification operates on the type system, it can establish the presence, naming form, and type of a declaration. However, it is important to note that it is not capable of determining the semantic appropriateness of an identifier. This limit is conceptual in nature and would persist even in the event of a mature reflections implementation. Thirdly, and most fundamentally, the precision of verification is constrained by the precision of the requirement. A requirement that permits multiple valid answers, or that is not encoded as a TD, cannot be enforced. It is important to note that these three boundaries do not constitute defects of the implementation. They delineate the expressive envelope within which compile-time verification of non-functional requirements is feasible in C++.

Collectively, these limitations do not invalidate the approach and instead delineate its expressive envelope. Consequently, the evaluation delineates the limits of the technique's expressive capacity, which is the question the RQ poses.
