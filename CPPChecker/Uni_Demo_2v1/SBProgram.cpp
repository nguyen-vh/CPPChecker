#include "Headers/pch_uni.hpp"

// #define DEBUG
// #define SAVE

#ifdef _WIN32
#define CMD_Prefix "\\"
#else
#define CMD_Prefix "/"
#endif

int main(int argc, char* argv[]) {
#ifdef DEBUG
  std::string Task_NO{"19"};
  std::string StudentName{"Anderson Sofia"};
#else
  std::string Task_NO = argv[1];
  std::string StudentName{};

  for (int i = 2; i < argc; i++) {
    StudentName += argv[i];
    if (i < argc - 1) {
      StudentName += " ";
    }
  }
#endif

  std::string StudentName_ = StudentName;

  std::replace(StudentName_.begin(), StudentName_.end(), ' ', '_');

  const std::string gcc_command_studentCode =
      "g++ -std=c++20 -g Student_Answers/studentCode_" + StudentName_ +
      ".cpp -o Student_Answers/studentCode_T" + Task_NO + "_" + StudentName_ +
      " 2>&1";

  const std::string gcc_command_CPPChecker =
      "g++ -std=c++20 Tasks/CPPChecker_Uni_Task_" + Task_NO +
      ".cpp -o Tasks/CPPChecker_Uni_Task_" + Task_NO +
      " -IHeaders -include Headers/pch_uni.hpp";

  const std::string gcc_command_CPPCheckerEXE =
      "cd Tasks && ." CMD_Prefix "CPPChecker_Uni_Task_" + Task_NO;

  std::ofstream output("Results/studentResults_T" + Task_NO + "_" +
                       StudentName_ + ".txt");
  std::streambuf* std_buffer = std::cout.rdbuf();
  std::cout.rdbuf(output.rdbuf());

  std::stringstream errorStream;
  FILE* pipe = popen(gcc_command_studentCode.data(), "r");

  char buffer[128];
  while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
    errorStream << buffer;
  }
  int compileResult = pclose(pipe);

  std::cout << "---------------------------------" << std::endl;

  if (compileResult != 0) {
    //? Students Code didnt compile

    //? Filter out the first error message
    std::string errorMessage = errorStream.str();

    std::string marker = "      |";
    size_t markerPos = errorMessage.find(marker);

    if (markerPos == std::string::npos) {
      std::cout << std::endl;
      std::cout << "Code is empty" << std::endl;
      std::cout << std::endl;
    } else {
      errorMessage.erase(markerPos);

      bool conditionMet = false;

      std::cout << std::endl;
      //* Error Messages by GCC
      //* Syntax Errors
      if (((errorMessage.find("error: expected ';'") != std::string::npos) ||
           (errorMessage.find("error: expected ',' or ';'") !=
            std::string::npos)) &&
          !conditionMet) {
        std::cout << "Missing Semicolon";
        conditionMet = true;
      }
      if (errorMessage.find("error: expected identifier") !=
              std::string::npos &&
          !conditionMet) {
        std::cout << "Missing Variable or Function Name";
        conditionMet = true;
      }
      if (errorMessage.find("error: missing terminating") !=
              std::string::npos &&
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
        std::cout << "Suggests trying to assign or use Variables of "
                     "incompatible Types";
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
      if (errorMessage.find(
              "error: dereferencing pointer to incomplete type") !=
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
      if (errorMessage.find(
              "error: unterminated argument list invoking macro") !=
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
      if (errorMessage.find("undeclared") != std::string::npos &&
          !conditionMet) {
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

      //? Extracting the right Line Number
      std::string number = "";
      auto is_num = [](char num) { return std::isdigit(num); };
      auto num_start =
          std::find_if(errorMessage.begin(), errorMessage.end(), is_num);
      auto num_end = std::find_if_not(num_start, errorMessage.end(), is_num);
      number = std::string(num_start, num_end);
      std::cout << " in Line " << number << std::endl;
      std::cout << std::endl;
    }
  } else {
    //? Students Code compiles
    std::cout << std::endl;
    std::cout << "Program compiled without error" << std::endl;
    std::cout << std::endl;
    std::cout << "---------------------------------" << std::endl;

    //? Paste studentCode into different file to check
    std::ifstream studentCode_Name("Student_Answers/studentCode_" +
                                   StudentName_ + ".cpp");
    std::ofstream studentCodeOverwrite("studentCodeOverwrite.cpp");
    std::string sline;
    while (std::getline(studentCode_Name, sline)) {
      studentCodeOverwrite << sline << std::endl;
    }
    studentCode_Name.close();
    studentCodeOverwrite.close();

    //? Compile CPPChecker
    FILE* pipe = popen(gcc_command_CPPChecker.data(), "r");
    int cantCompile = pclose(pipe);

    if (cantCompile == true) {
      std::cout << std::endl;
      std::cout << "Classname is used for a Value" << std::endl;
      std::cout << std::endl;
    } else {
      //? Execute CPPChecker
      std::stringstream checkerStream;
      FILE* cpipe = popen(gcc_command_CPPCheckerEXE.data(), "r");

      while (fgets(buffer, sizeof(buffer), cpipe) != nullptr) {
        checkerStream << buffer;
      }
      pclose(cpipe);

      std::cout << checkerStream.str() << std::endl;
    }

    std::cout.rdbuf(std_buffer);
  }
  /*

  File to archive

  */

  std::ofstream outputArchive("Archive/T" + Task_NO + "_" + StudentName_ +
                              ".txt");
  std::cout.rdbuf(outputArchive.rdbuf());

  std::ifstream codeFile("Student_Answers/studentCode_" + StudentName_ +
                         ".cpp");

  std::string cFile;
  std::string cline;

  while (std::getline(codeFile, cline)) {
    cFile += cline + "\n";
  }
  codeFile.close();

  //? Hashing Students Code with their Name
  const std::string AnswerHash = hmac_sha256(StudentName, cFile);

  std::ifstream taskFile("Tasks/CPPChecker_Uni_Task_" + Task_NO + ".cpp");

  //? Here should be the input of the task in string
  std::string taskInstructions{""};
  std::string tFile;
  std::string tline;

  while (std::getline(taskFile, tline)) {
    tFile += tline + "\n";
  }
  taskFile.close();

  //? Hashing Task
  const std::string TaskHash = hmac_sha256(taskInstructions, tFile);

  const std::string ControlHash = hmac_sha256(TaskHash, AnswerHash);

  std::ifstream resultFile("Results/studentResults_T" + Task_NO + "_" +
                           StudentName_ + ".txt");

  std::string rFile;
  std::string rline;

  while (std::getline(resultFile, rline)) {
    rFile += rline + "\n";
  }
  resultFile.close();
  std::cout << rFile;

  auto now = std::chrono::system_clock::now();
  auto in_time_t = std::chrono::system_clock::to_time_t(now);

  std::stringstream ss;
  ss << std::put_time(std::localtime(&in_time_t), "%d-%m-%Y %X");
  std::string Time = ss.str();

  std::cout << "---------------------------------" << std::endl;
  std::cout << std::endl;
  std::cout << StudentName << " | Task: " << Task_NO << std::endl;
  std::cout << "Compiled with: GNU C++ Compiler | C++20" << std::endl;
  std::cout << "Compiled at: " << Time << std::endl;
  std::cout << "Answer Hash: " << AnswerHash << std::endl;
  std::cout << "Task Hash: " << TaskHash << std::endl;
  std::cout << std::endl;
  std::cout << "---------------------------------" << std::endl;
  std::cout << std::endl;
  std::cout << "Control Hash: " << ControlHash << std::endl;
  std::cout << std::endl;
  std::cout << "---------------------------------" << std::endl;
  std::cout << std::endl;
  std::cout << cFile << std::endl;
  std::cout << "---------------------------------" << std::endl;

  std::cout.rdbuf(std_buffer);

#ifdef SAVE
  std::map<std::string, std::string> Save;
  std::ifstream iSavefile("T" + Task_NO + "_Savefile.txt");
  std::string tnline;

  while (std::getline(iSavefile, tnline)) {
    size_t tnPos = tnline.find('|');
    if (tnPos != std::string::npos) {
      std::string name = tnline.substr(0, tnPos);
      std::string hash = tnline.substr(tnPos + 1);
      Save[name] = hash;
    }
  }

  Save[StudentName] = ControlHash;
  iSavefile.close();

  std::ofstream oSavefile("T" + Task_NO + "_Savefile.txt");
  for (const auto& pair : Save) {
    oSavefile << pair.first << "|" << pair.second << std::endl;
  }
  oSavefile.close();
#endif

  return 0;
}
