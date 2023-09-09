#include "Headers/pch_uni.hpp"

// #define DEBUG
// #define SAVE

#ifdef _WIN32
#define CMD_Prefix "\\"
#define CMD_BlackHole "2>NUL"
#else
#define CMD_Prefix "/"
#define CMD_BlackHole "2>/dev/null"
#endif

void evaluateErrorMessage(const std::string& ErrorMessage) {
  bool OneConditionMatched = false;
  std::cout << std::endl;

  //* Error Messages by GCC
  //* Syntax Errors
  if (((ErrorMessage.find("error: expected ';'") != std::string::npos) ||
       (ErrorMessage.find("error: expected ',' or ';'") !=
        std::string::npos)) &&
      !OneConditionMatched) {
    std::cout << "Missing Semicolon";
    OneConditionMatched = true;
  }
  if (ErrorMessage.find("error: expected identifier") != std::string::npos &&
      !OneConditionMatched) {
    std::cout << "Missing Variable or Function Name";
    OneConditionMatched = true;
  }
  if (ErrorMessage.find("error: missing terminating") != std::string::npos &&
      !OneConditionMatched) {
    std::cout << "Unclosed Strings or Character Literals";
    OneConditionMatched = true;
  }
  if (ErrorMessage.find("error: unmatched") != std::string::npos &&
      !OneConditionMatched) {
    std::cout << "Mismatched Parentheses, Braces, or Brackets";
    OneConditionMatched = true;
  }
  if (ErrorMessage.find("error: invalid suffix") != std::string::npos &&
      !OneConditionMatched) {
    std::cout << "Points to an incorrect numeric Constant";
    OneConditionMatched = true;
  }
  if (ErrorMessage.find("error: stray '#'") != std::string::npos &&
      !OneConditionMatched) {
    std::cout << "Improperly placed Preprocessor Directive";
    OneConditionMatched = true;
  }
  if (ErrorMessage.find("error: expected '}'") != std::string::npos &&
      !OneConditionMatched) {
    std::cout << "Missing curly Bracket";
    OneConditionMatched = true;
  }

  //* Type Errors
  if (ErrorMessage.find("error: incompatible types") != std::string::npos &&
      !OneConditionMatched) {
    std::cout << "Suggests trying to assign or use Variables of "
                 "incompatible Types";
    OneConditionMatched = true;
  }
  if (ErrorMessage.find("error: implicit declaration of function") !=
          std::string::npos &&
      !OneConditionMatched) {
    std::cout << "Function Call without a prior Function Declaration";
    OneConditionMatched = true;
  }
  if (ErrorMessage.find(
          "error: assignment makes integer from pointer without a cast") !=
          std::string::npos &&
      !OneConditionMatched) {
    std::cout << "Incorrect Assignment between a Pointer and an Integer";
    OneConditionMatched = true;
  }
  if (ErrorMessage.find("error: dereferencing pointer to incomplete type") !=
          std::string::npos &&
      !OneConditionMatched) {
    std::cout << "Suggests accessing a Structure or Type that hasn't been "
                 "fully defined";
    OneConditionMatched = true;
  }

  //* Linker Errors
  if (ErrorMessage.find("undefined reference to") != std::string::npos &&
      !OneConditionMatched) {
    std::cout << "Function or Variable being used without a corresponding "
                 "Definition";
    OneConditionMatched = true;
  }
  if (ErrorMessage.find("multiple definition of") != std::string::npos &&
      !OneConditionMatched) {
    std::cout << "Duplicate Function or Variable Definition";
    OneConditionMatched = true;
  }
  if (ErrorMessage.find("error: ld returned") != std::string::npos &&
      !OneConditionMatched) {
    std::cout << "Linking Problems";
    OneConditionMatched = true;
  }

  //* Memory and Segmentation Errors
  if (ErrorMessage.find("Segmentation fault") != std::string::npos &&
      !OneConditionMatched) {
    std::cout << "Accessing Memory that hasn't been allocated";
    OneConditionMatched = true;
  }

  if (ErrorMessage.find("cannot be used as a function") != std::string::npos &&
      !OneConditionMatched) {
    std::cout << "Attempting to use a Non-Function as a Function Call";
    OneConditionMatched = true;
  }

  //* Preprocessor Errors
  if (ErrorMessage.find("error: macro names must be identifiers") !=
          std::string::npos &&
      !OneConditionMatched) {
    std::cout << "Incorrect Macro Definition";
    OneConditionMatched = true;
  }
  if (ErrorMessage.find("error: unterminated argument list invoking macro") !=
          std::string::npos &&
      !OneConditionMatched) {
    std::cout << "Macro Invocation without proper Arguments";
    OneConditionMatched = true;
  }
  if (ErrorMessage.find("error: #include expects") != std::string::npos &&
      !OneConditionMatched) {
    std::cout << "Incorrect Usage of the #include Directive";
    OneConditionMatched = true;
  }

  //* Miscellaneous Errors
  if (ErrorMessage.find("undeclared") != std::string::npos &&
      !OneConditionMatched) {
    std::cout << "Using a Variable without a prior Declaration";
    OneConditionMatched = true;
  }
  if (ErrorMessage.find("was not declared in this scope") !=
          std::string::npos &&
      !OneConditionMatched) {
    std::cout << "Accessing a Variable or Function outside its Scope";
    OneConditionMatched = true;
  }
  if (ErrorMessage.find("error: request for member") != std::string::npos &&
      !OneConditionMatched) {
    std::cout
        << "Trying to access a Member of a Non-Structure or Non-Union Type";
    OneConditionMatched = true;
  }

  if (!OneConditionMatched) {
    std::cout << "Unknown Error Type";
  }
}

void addLineNumber(const std::string& ErrorMessage) {
  std::string Number{};
  auto is_Number = [](char Number) { return std::isdigit(Number); };
  auto Number_start =
      std::find_if(ErrorMessage.begin(), ErrorMessage.end(), is_Number);
  auto Number_end =
      std::find_if_not(Number_start, ErrorMessage.end(), is_Number);
  Number = std::string(Number_start, Number_end);
  std::cout << " in Line " << Number << "\n" << std::endl;
}

void executeCPPChecker(const std::string& gcc_command_CPPCheckerEXE) {
  std::stringstream Stream_CPPChecker;
  FILE* FStream_CPPCheckerEXE = popen(gcc_command_CPPCheckerEXE.data(), "r");
  char buffer[128];

  while (fgets(buffer, sizeof(buffer), FStream_CPPCheckerEXE) != nullptr) {
    Stream_CPPChecker << buffer;
  }

  pclose(FStream_CPPCheckerEXE);
  std::cout << Stream_CPPChecker.str() << std::endl;
}

void archivedFile(const std::string& Task_NO, const std::string& StudentName,
                  const std::string& StudentName_, std::string& Hash_Control,
                  std::string& DateTime) {
  std::ofstream oStream_Archive("Archive/T" + Task_NO + "_" + StudentName_ +
                                ".txt");
  std::cout.rdbuf(oStream_Archive.rdbuf());

  std::ifstream iStream_Code("Student_Answers/studentCode_" + StudentName_ +
                             ".cpp");

  std::string File_Code;
  std::string File_CodeLine;

  while (std::getline(iStream_Code, File_CodeLine)) {
    File_Code += File_CodeLine + "\n";
  }

  iStream_Code.close();

  //? Hashing Students Code with their Name
  const std::string Hash_Answer = hmac_sha256(StudentName, File_Code);

  std::ifstream iStream_CPPChecker("Tasks/CPPChecker_Uni_Task_" + Task_NO +
                                   ".cpp");

  //! Here should be the input of the task in string
  std::string TaskTextInstructions{};

  std::string File_Task;
  std::string File_TaskLine;

  while (std::getline(iStream_CPPChecker, File_TaskLine)) {
    File_Task += File_TaskLine + "\n";
  }

  iStream_CPPChecker.close();

  const std::string Hash_Task = hmac_sha256(TaskTextInstructions, File_Task);

  Hash_Control = hmac_sha256(Hash_Task, Hash_Answer);

  std::ifstream iStream_Results("Results/studentResults_T" + Task_NO + "_" +
                                StudentName_ + ".txt");

  std::string File_Results;
  std::string File_ResultsLine;

  while (std::getline(iStream_Results, File_ResultsLine)) {
    File_Results += File_ResultsLine + "\n";
  }

  iStream_Results.close();
  std::cout << File_Results;

  auto now = std::chrono::system_clock::now();
  auto in_time_t = std::chrono::system_clock::to_time_t(now);

  std::stringstream Stream_DateTime;
  Stream_DateTime << std::put_time(std::localtime(&in_time_t), "%d-%m-%Y %X");
  DateTime = Stream_DateTime.str();

  std::cout << "---------------------------------" << std::endl;
  std::cout << "\n" << StudentName << " | Task: " << Task_NO << std::endl;
  std::cout << "Compiled with: GNU C++ Compiler | C++20" << std::endl;
  std::cout << "Compiled at: " << DateTime << std::endl;
  std::cout << "Answer Hash: " << Hash_Answer << std::endl;
  std::cout << "Task Hash: " << Hash_Task << "\n" << std::endl;
  std::cout << "---------------------------------" << std::endl;
  std::cout << "\nControl Hash: " << Hash_Control << "\n" << std::endl;
  std::cout << "---------------------------------" << std::endl;
  std::cout << "\n" << File_Code << std::endl;
  std::cout << "---------------------------------" << std::endl;

  oStream_Archive.close();
}

int main(int argc, char* argv[]) {
#ifdef DEBUG
  std::string Task_NO{"19"};
  std::string StudentName{"Anderson Sofia"};
#else
  //? Gets Tasknumber and Student Name
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
      " -IHeaders -include Headers/pch_uni.hpp " + CMD_BlackHole;

  const std::string gcc_command_CPPCheckerEXE =
      "cd Tasks && ." CMD_Prefix "CPPChecker_Uni_Task_" + Task_NO;

  std::ofstream oStream_Results("Results/studentResults_T" + Task_NO + "_" +
                                StudentName_ + ".txt");

  std::streambuf* std_buffer = std::cout.rdbuf();
  std::cout.rdbuf(oStream_Results.rdbuf());

  std::stringstream Stream_ErrorMessage;
  FILE* FStream_studentCode = popen(gcc_command_studentCode.data(), "r");

  char buffer[128];
  while (fgets(buffer, sizeof(buffer), FStream_studentCode) != nullptr) {
    Stream_ErrorMessage << buffer;
  }
  int compileResult = pclose(FStream_studentCode);

  std::cout << "---------------------------------" << std::endl;

  if (compileResult != 0) {
    //? Students Code didnt compile

    //? Filter out the first error message
    std::string ErrorMessage = Stream_ErrorMessage.str();

    std::string Marker = "      |";
    size_t MarkerPos = ErrorMessage.find(Marker);

    if (MarkerPos == std::string::npos) {
      std::cout << "\nCode is empty\n" << std::endl;

    } else {
      ErrorMessage.erase(MarkerPos);

      //? Outputs simplified Error Message
      evaluateErrorMessage(ErrorMessage);

      //? Adds the Line to the Error Message
      addLineNumber(ErrorMessage);
    }
  } else {
    //? Students Code compiles

    std::cout << "\nProgram compiled without error\n" << std::endl;
    std::cout << "---------------------------------" << std::endl;

    //? Paste studentCode into studentCodeOverwrite to run CPPChecker
    std::ifstream iStream_studentCode("Student_Answers/studentCode_" +
                                      StudentName_ + ".cpp");
    std::ofstream oStream_studentCodeOverwrite("studentCodeOverwrite.cpp");
    std::string File_studentCodeLine;

    while (std::getline(iStream_studentCode, File_studentCodeLine)) {
      oStream_studentCodeOverwrite << File_studentCodeLine << std::endl;
    }

    iStream_studentCode.close();
    oStream_studentCodeOverwrite.close();

    //? Compile CPPChecker
    FILE* FStream_CPPChecker = popen(gcc_command_CPPChecker.data(), "r");
    int CantCompileCode = pclose(FStream_CPPChecker);

    if (CantCompileCode == true) {
      std::cout << "\nClassname is used for a Value\n" << std::endl;

    } else {
      executeCPPChecker(gcc_command_CPPCheckerEXE);
    }

    std::cout.rdbuf(std_buffer);
  }

  //? Create File to be archived
  std::string DateTime{};
  std::string Hash_Control{};
  archivedFile(Task_NO, StudentName, StudentName_, Hash_Control, DateTime);

  std::cout.rdbuf(std_buffer);

#ifdef SAVE
  std::map<std::string, std::string> mapSave;
  std::ifstream iStream_Save("T" + Task_NO + "_Savefile.txt");
  std::string File_SaveLine;

  while (std::getline(iStream_Save, File_SaveLine)) {
    size_t SavePos = File_SaveLine.find('|');
    if (SavePos != std::string::npos) {
      std::string Save_StudentName = File_SaveLine.substr(0, SavePos);
      std::string Save_Hash_Control = File_SaveLine.substr(SavePos + 1);
      mapSave[Save_StudentName] = Save_Hash_Control;
    }
  }

  mapSave[StudentName] = Hash_Control;
  iStream_Save.close();

  std::ofstream oStream_Save("T" + Task_NO + "_Savefile.txt");

  oStream_Save << "Saved at: " << DateTime << "\n" << std::endl;

  for (const auto& pair : mapSave) {
    oStream_Save << pair.first << "|" << pair.second << std::endl;
  }

  oStream_Save.close();
#endif

  return 0;
}
