#ifndef M_OUTPUT_HPP
#define M_OUTPUT_HPP

//* Evaluates the output from Student
#define M_OUTPUT                                                           \
  template <typename T>                                                    \
  bool check_output(T&& main_call, const std::string& expectedOutput) {    \
    std::stringstream output_stream;                                       \
    std::streambuf* std_buffer = std::cout.rdbuf(output_stream.rdbuf());   \
    (main_call)();                                                         \
    std::cout.rdbuf(std_buffer);                                           \
    std::string STUDENTOutput = output_stream.str();                       \
    if (STUDENTOutput == expectedOutput) {                                 \
      std::cout << "\n+ Student Output correct" << std::endl;              \
      return true;                                                         \
    } else {                                                               \
      std::cout << "\n- Student Output incorrect" << std::endl;            \
      std::cout << "   > Expected Output: " << expectedOutput              \
                << "   >  Student Output: " << STUDENTOutput << std::endl; \
      return false;                                                        \
    }                                                                      \
  }

#endif