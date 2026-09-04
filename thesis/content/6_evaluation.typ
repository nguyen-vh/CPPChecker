#import "/utils/todo.typ": TODO

= Evaluation<evaluation>

== Design

The subsequent section will provide a detailed evaluation of the previously mentioned implementation of CPPChecker using the REST API Server and the web UI. The evaluation will be based on a real case scenario, as outlined in @implementation_rest. To that end, task files were created, see @fig:Taskfile_Rectangle, @fig:Taskfile_Space and @fig:Taskfile_Coffee, with requirements similar to those found in the programming course by #cite(<eisenecker2022basic>, form: "prose") @eisenecker2024advanced. It is imperative to acknowledge that the execution of this task will not fall solely upon the author. The execution of this responsibility will be delegated to other parties, who will endeavor to disrupt the header file library. It is important to consider the possibility that this process may yield outcomes that were not foreseen.
This will serve as the basis for the subsequent evaluation.



== Objectives

The three objectives delineated in the Introduction will be consolidated into a single execution. The aforementioned approach will be employed for the evaluation, during which the implemented template definitions will be subjected to testing. Subsequently, a comparison will be made between the results of the testing and the expected outcomes. This will reveal the possibilities and shortcomings of the current implementations. Due to temporal limitations, the implementation of numerous template definitions has not yet been completed. This will result in a reduction in the scope of the test. The succeeding paragraphs will address the REST API Server, the web UI, and the research question.



== Results

The aforementioned parties conducted a rigorous testing process, the results of which indicated that the majority of requirements enumerated in the header file were satisfied. The study identified a number of unanticipated outcomes.
First, when defining an alias type and subsequently employing that alias type as the return type for a function, the TD is unable to recognize it, as illustrated in @fig:Eval_Alias. The TD has identified the use of the alias for any other purpose.
The second issue pertains to the _class_has_pure_virtual_memberfunc<>_ complication, which has already hindered the process of creating and testing the task. While it possesses the capability to discern pure virtual member functions, the TD's subsequent evaluation would be flawed should the quantity of template parameters subjected to inspection increase.
In Task 3, as indicated in @fig:Taskfile_Coffee, the development of an abstract class was a requirement. However, the TD has not yet been written for it. In the final analysis, certain functions necessitated an input type designated as _double_. However, it should be noted that the use of _const double&_ would also be considered valid.



== Findings
#TODO[
  Interpret the results and conclude interesting findings
]

The final two findings should be considered part of a group that do not demonstrate proficiency in the creation of task files. It is evident that the abstract class could have been omitted as a requirement, given the inability to verify its presence and the potential for multiple responses as input type, refer to the expanded version in @fig:Taskfile_Space, specifically lines 78 and 79.
With respect to the initial two observations, it is conceivable that ...


\
*_TO CONTINUE HERE ... _*
\
\

== Discussion
#TODO[
  Discuss the findings in more detail and also review possible disadvantages that you found
]

== Limitations
#TODO[
  Describe limitations and threats to validity of your evaluation, e.g. reliability, generalizability, selection bias, researcher bias
]

