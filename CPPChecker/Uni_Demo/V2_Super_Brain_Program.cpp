#include "Headers/pch_uni.hpp"

//? Comment out if not debugging
// #define DEBUG

//? Task Number of the Program
#define TASK_NO "20"

//? Windows vs MacOS/Linux
#ifdef _WIN32

#else

#endif

//! Test Variables

//? Students Full Name
std::string Name_Student = "Elena Ramirez";

//! End of Test Variables

int CompileTest() {
  const std::string gcc_Command_StudentCode =
      "g++ -std=c++20 -g students_code.cpp -o students_code 2>&1";
  return 0;
}

void EvaluateError() {}

void EvaluateCode() {
  const std::string gcc_command_CPPChecker =
      "g++ -std=c++20 Task/CPPChecker_Uni_Task_" TASK_NO
      ".cpp -o CPPChecker_Uni_Task_" TASK_NO
      " -IHeaders -include Headers/pch_uni.hpp";
}

int main(int argc, char* argv[]) {
  if (CompileTest()) {
    EvaluateError();
  } else {
    EvaluateCode();
  }

  if (argc < 2) {
    std::cout << "No Tasknumber specified!" << std::endl;
    return 0;
  }
  std::string Task_NO = argv[1];
  std::string StudentName{};
  for (int i = 2; i < argc; i++) {
    StudentName += argv[i];
    if (i < argc - 1) {
      StudentName += "_";
    }
  }

  std::cout << StudentName << " Task_NO: " << Task_NO << std::endl;

  return 0;
}
