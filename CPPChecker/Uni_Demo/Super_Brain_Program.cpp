#include "Headers/pch_uni.hpp"
//? Precompile all headers
// g++ -x c++-header pch_uni.hpp -o pch_uni.hpp.gch
//? include precompiled header
// g++ -include pch_uni.hpp Super_Brain_Program.cpp

#define M_Task_Number "19"

#ifdef _WIN32
#define M_Students_Code_compiled "students_code.exe"
#define M_task_file_compiled "CPPChecker_Uni_Task_" M_Task_Number ".exe"

#else
#define M_Students_Code_compiled "./students_code"
#define M_task_file_compiled "./CPPChecker_Uni_Task_" M_Task_Number
#endif

/* Incase pch_uni.hpp is not included
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
*/

int main() {
  const std::string Students_Code_File = "students_code.cpp";
  const std::string Students_Code_compiled = M_Students_Code_compiled;
  std::string compileCommand_Students = "g++ -std=c++20 -o " +
                                        Students_Code_compiled + " " +
                                        Students_Code_File + " 2>&1";

  std::ofstream output("Students_Results.txt");
  std::streambuf* std_buffer = std::cout.rdbuf();
  std::cout.rdbuf(output.rdbuf());
  // std::cout.rdbuf(std_buffer);  //! <- Remove line after debugging

  std::stringstream errorStream;
  FILE* pipe = popen(compileCommand_Students.data(), "r");

  char buffer[8];
  while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
    errorStream << buffer;
  }
  int compileResult = pclose(pipe);

  if (compileResult != 0) {
    //! Students Code didnt compile

    std::string errorMessage = errorStream.str();
    std::string marker = "      |";
    size_t markerPos = errorMessage.find(marker);
    errorMessage.erase(markerPos);

    bool conditionMet = false;

    //* Error Messages by GCC
    //* Syntax Errors
    if (((errorMessage.find("error: expected ';'") != std::string::npos) ||
         (errorMessage.find("error: expected ',' or ';'") !=
          std::string::npos)) &&
        !conditionMet) {
      std::cout << "Missing Semicolon";
      conditionMet = true;
    }
    if (errorMessage.find("error: expected identifier") != std::string::npos &&
        !conditionMet) {
      std::cout << "Missing Variable or Function Name";
      conditionMet = true;
    }
    if (errorMessage.find("error: missing terminating") != std::string::npos &&
        !conditionMet) {
      std::cout << "Unclosed Strings or Character Literals";
      conditionMet = true;
    }
    if (errorMessage.find("error: unmatched") != std::string::npos &&
        !conditionMet) {
      std::cout << "Mismatched Parentheses, Braces, or Brackets";
      conditionMet = true;
    }
    if (errorMessage.find("error: invalid suffix") != std::string::npos &&
        !conditionMet) {
      std::cout << "Points to an incorrect numeric Constant";
      conditionMet = true;
    }
    if (errorMessage.find("error: stray '#'") != std::string::npos &&
        !conditionMet) {
      std::cout << "Improperly placed Preprocessor Directive";
      conditionMet = true;
    }
    if (errorMessage.find("error: expected '}'") != std::string::npos &&
        !conditionMet) {
      std::cout << "Missing curly Bracket";
      conditionMet = true;
    }

    //* Type Errors
    if (errorMessage.find("error: incompatible types") != std::string::npos &&
        !conditionMet) {
      std::cout
          << "Suggests trying to assign or use Variables of incompatible Types";
      conditionMet = true;
    }
    if (errorMessage.find("error: implicit declaration of function") !=
            std::string::npos &&
        !conditionMet) {
      std::cout << "Function Call without a prior Function Declaration";
      conditionMet = true;
    }
    if (errorMessage.find(
            "error: assignment makes integer from pointer without a cast") !=
            std::string::npos &&
        !conditionMet) {
      std::cout << "Incorrect Assignment between a Pointer and an Integer";
      conditionMet = true;
    }
    if (errorMessage.find("error: dereferencing pointer to incomplete type") !=
            std::string::npos &&
        !conditionMet) {
      std::cout << "Suggests accessing a Structure or Type that hasn't been "
                   "fully defined";
      conditionMet = true;
    }

    //* Linker Errors
    if (errorMessage.find("undefined reference to") != std::string::npos &&
        !conditionMet) {
      std::cout << "Function or Variable being used without a corresponding "
                   "Definition";
      conditionMet = true;
    }
    if (errorMessage.find("multiple definition of") != std::string::npos &&
        !conditionMet) {
      std::cout << "Duplicate Function or Variable Definition";
      conditionMet = true;
    }
    if (errorMessage.find("error: ld returned") != std::string::npos &&
        !conditionMet) {
      std::cout << "Linking Problems";
      conditionMet = true;
    }

    //* Memory and Segmentation Errors
    if (errorMessage.find("Segmentation fault") != std::string::npos &&
        !conditionMet) {
      std::cout << "Accessing Memory that hasn't been allocated";
      conditionMet = true;
    }

    if (errorMessage.find("cannot be used as a function") !=
            std::string::npos &&
        !conditionMet) {
      std::cout << "Attempting to use a Non-Function as a Function Call";
      conditionMet = true;
    }

    //* Preprocessor Errors
    if (errorMessage.find("error: macro names must be identifiers") !=
            std::string::npos &&
        !conditionMet) {
      std::cout << "Incorrect Macro Definition";
      conditionMet = true;
    }
    if (errorMessage.find("error: unterminated argument list invoking macro") !=
            std::string::npos &&
        !conditionMet) {
      std::cout << "Macro Invocation without proper Arguments";
      conditionMet = true;
    }
    if (errorMessage.find("error: #include expects") != std::string::npos &&
        !conditionMet) {
      std::cout << "Incorrect Usage of the #include Directive";
      conditionMet = true;
    }

    //* Miscellaneous Errors
    if (errorMessage.find("undeclared") != std::string::npos && !conditionMet) {
      std::cout << "Using a Variable without a prior Declaration";
      conditionMet = true;
    }
    if (errorMessage.find("was not declared in this scope") !=
            std::string::npos &&
        !conditionMet) {
      std::cout << "Accessing a Variable or Function outside its Scope";
      conditionMet = true;
    }
    if (errorMessage.find("error: request for member") != std::string::npos &&
        !conditionMet) {
      std::cout
          << "Trying to access a Member of a Non-Structure or Non-Union Type";
      conditionMet = true;
    }

    if (!conditionMet) {
      std::cout << "Unknown Error Type";
    }

    std::string number = "";
    auto is_num = [](char num) { return std::isdigit(num); };
    auto num_start =
        std::find_if(errorMessage.begin(), errorMessage.end(), is_num);
    auto num_end = std::find_if_not(num_start, errorMessage.end(), is_num);
    number = std::string(num_start, num_end);
    std::cout << " in Line " << number << std::endl;

  } else {
    //! Students Code compiles

    std::cout << "+ Program compiled without error" << std::endl;
    std::cout << "________________________________" << std::endl;

    const std::string Task_File =
        "Tasks/CPPChecker_Uni_Task_" M_Task_Number ".cpp";
    const std::string Task_File_compiled = M_task_file_compiled;
    std::string compileCommand_Task =
        "g++ -std=c++23 -IHeaders -include Headers/pch_uni.hpp -o " +
        Task_File_compiled + " " + Task_File;

    // Compile Task File
    FILE* compilePipe = popen(compileCommand_Task.data(), "r");
    pclose(compilePipe);

    // Execute Task File
    std::stringstream task_fStream;
    FILE* executePipe = popen(Task_File_compiled.data(), "r");

    while (fgets(buffer, sizeof(buffer), executePipe) != nullptr) {
      task_fStream << buffer;
    }
    pclose(executePipe);

    std::cout << task_fStream.str() << std::endl;
  }

  std::cout.rdbuf(std_buffer);

#ifdef _WIN32
  std::system("del *.exe");
#endif

  return 0;
}
