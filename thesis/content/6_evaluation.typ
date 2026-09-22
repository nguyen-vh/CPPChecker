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

The aforementioned parties conducted a rigorous testing process, the results of which indicated that the majority of requirements enumerated in the header file were satisfied. The study identified a number of unanticipated outcomes.
First, when defining an alias type and subsequently employing that alias type as the return type for a function, the TD is unable to recognize it, as illustrated in @fig:Eval_Alias. The TD has identified the use of the alias for any other purpose.
The second issue pertains to the "_class_has_pure_virtual_memberfunc<>_" complication, which has already hindered the process of creating and testing the task. While it possesses the capability to discern pure virtual member functions, the TD's subsequent evaluation would be flawed should the quantity of template parameters subjected to inspection increase.
In Task 3, as indicated in @fig:Taskfile_Coffee, the development of an abstract class was a requirement. However, the TD has not yet been written for it. In the final analysis, certain functions necessitated an input type designated as "_double_". However, it should be noted that the use of "_const double&_" would also be considered valid. It is crucial to highlight that the system did not verify the output of the sent code. Consequently, the necessity to write code inside the main function becomes redundant.

The REST API server and web UI stack functioned without error or unexpected behavior, and the code sent for evaluation did not compromise the integrity of the system. The mean RTT for all three tasks is 8 seconds. The fastest recorded RTT was 5 seconds, while the longest recorded RTT was 12 seconds. The length of the sent code ranges from 10 to 75 lines. The testing was conducted over a university Virtual Private Network (VPN) to access the university server from outside.



== Findings <findings>

The last two findings stem from imprecise task file requirements rather than from the checker itself. The abstract class requirement could not be verified, and the input type requirement admitted multiple valid answers. It is evident that the abstract class could have been omitted as a requirement, given the inability to verify its presence and the potential for multiple responses as input type, refer to the expanded version in @fig:Taskfile_Space, specifically lines 78 and 79.
With regard to the initial two observations, it is conceivable that the _\<meta>_ standard library (reflections library) is not functioning as intended. This phenomenon could be attributed to the library being an early release that lacks some reflections features, or the TD for those findings being implemented incorrectly. It is important to note that both of these options are possible. In general, the issue is more likely to occur in the reflections library, as evidenced by the failure of the "_class_has_memberfunc<>_" to function properly when declaring an alias of type float for the evaluation and returning on a simple type check (refer to @fig:Eval_Alias_Check).



== Limitations

The evaluation approach that has been employed is to replicate the actual case scenario. However, in the absence of temporal constraints, a comprehensive UT would have identified the bugs irrespective of the initial conditions. Consequently, the probability of a bias in testing specific edge cases is high, and it is improbable that all anomalous behaviors have been identified.

A significant constraint is the omission of an output check. Because all checks run at compile time, output verification was deprioritized. A basic verification of the output would have been the call of the sent code's primary function, while redirecting "_std::cout_", "the standard output stream object in C++" @geeksforge2026cout, to a "_std::string_" and making a comparison of the string with the expected output string.
The absence of output validation does offer certain advantages. Primarily, the code is checked at compile time rather than runtime, resulting in significantly expedited execution. Moreover, this approach eliminates the potential for malicious code execution, a crucial benefit.
To broaden the scope, as previously stated in @subsystem_decomposition, the utilization of a namespace is advantageous in circumventing the duplicate main functions. This approach offers significant benefits, primarily the prevention of malicious code execution. To illustrate this point, consider the example of having a function situated in the global scope. The utilization of namespaces enables the global space to be accessed exclusively through the process of exiting the specified namespace. However, this action impedes the ability to compile the code and prevents the initiation of the evaluation process.
