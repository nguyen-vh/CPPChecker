*Macro Approach* <appendix_c>

\

This section is dedicated to the Macro Approach mentioned in @prior_reflections and provides a more detailed exposition of the approach for interested readers.

\

In @fig:macro_class_has_memberfunc, a macro template to verify the presence of a member function within a class is shown, similar to @fig:Template_class_has_memberfunc. The utilization of macros is necessitated by the requirement to place a function within the confines of the nested namespace construct. This is done to ensure the enforcement of an order of visibility and to guarantee uniqueness in the naming scheme. For a more comprehensive overview of this subject, readers are directed to consult the articles by #cite(<chen2019namespaces>, form: "prose").

\
#figure(
  image("../figures/macro_class_has_memberfunc.png"),
  caption: [Macro to check a member function inside a class],
) <fig:macro_class_has_memberfunc>
\

A thorough examination of the namespaces reveals the presence of four distinct ones. Notably, the "_check_" namespace in @fig:macro_class_has_memberfunc, commencing on line 159, is employed to avoid the pollution of the global namespace. The namespaces "_condition_" and "_tester_" within the "_condition_" namespace on line 148 establish the foundation for the class lookup to proceed without failure in the event that it is not provided by the checked code. As illustrated in @fig:macro_fallback, the definition for the fallback class is located on line 77.
The final namespace is concealed and is designated by a macro named "_NAMESPACE_TO_CHECK_" because it is subject to alteration based on the specific use case. During the process of compilation, it can be modified to a different namespace. By examining the @fig:macro_class_has_memberfunc line 151, it becomes evident that the template employs the C++ _Concepts_ to ascertain the presence of a member function, instead of using the older SFINAE approach with multiple templates and "_std::void_t_". The function requires a "_typename T_" argument, which is supplied with the desired class for searching. The problem is that if the provided class does not exist, this will lead to a compile error. Consequently, a function within the specified namespace, designated as "_NAMESPACE_TO_CHECK::condition_", is invoked. The "_NAMESPACE_TO_CHECK::condition_" namespace utilizes the "_condition::tester_" namespace internally and invokes the template. Accordingly, the template call with the type T will first utilize the class contained within "_NAMESPACE_TO_CHECK_". In the event that the class is unavailable, the struct "_FallbackClass_" will be employed as it is also "globally" available within that same namespace.

\
#figure(
  image("../figures/macro_fallback.png"),
  caption: [Fallback definitions inside nested namespaces],
) <fig:macro_fallback>
\

The utilization of the aforementioned code can be achieved through the implementation of a specific configuration. This configuration involves the placement of the code inside a namespace, in @fig:macro_usecase "_check_in_here_". Additionally, the execution of the macro requires the invocation of the class name and the function name. This will result in the generation of a function within the "_check_" namespace, with the provided names, in this case "_check::class_X_has_memberfunc_foo_v_". This function will return a boolean value, shown in @fig:macro_usecase.

\
#figure(
  image("../figures/macro_usecase.png"),
  caption: [Macro CLASS_HAS_MEMBERFUNC showcase],
) <fig:macro_usecase>
\

A potential drawback of the code is that it will generate an error if multiple macros with identical inputs are utilized. Furthermore, it should be noted that the macros, which are designed to verify the return and input types, are incapable of testing a C++ type that utilizes multiple words, such as "_long long int_". This is due to a conflict with the name generation for the function. One possible solution to this issue is to define aliases in order to circumvent the conflict.
