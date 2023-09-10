#include <fstream>
#include <iostream>

#define YEAR "2023"

std::string cleanName(const std::string& input) {
  std::string result;

  bool inWhitespace = false;

  for (char c : input) {
    if (!std::isspace(c)) {
      result += c;
      inWhitespace = false;
    } else if (!inWhitespace) {
      result += ' ';
      inWhitespace = true;
    }
  }

  result.erase(result.find_last_not_of(' ') + 1);

  return result;
}

int main(int argc, char* argv[]) {
  std::ofstream oStream_Makefile("../Makefile");

  oStream_Makefile << "TASK := 19\n" << std::endl;

  std::ifstream iStream_Makefile("Names" YEAR ".txt");
  std::string File_MakefileLine;

  int NumberCount{0};

  while (std::getline(iStream_Makefile, File_MakefileLine)) {
    File_MakefileLine = cleanName(File_MakefileLine);

    if (File_MakefileLine.empty()) {
      continue;
    }

    NumberCount++;

    oStream_Makefile << "N" << NumberCount << " := " << File_MakefileLine
                     << std::endl;
  }
  iStream_Makefile.close();

  oStream_Makefile << "\nEXECUTABLE := ./Tasks/SBProgram\n" << std::endl;

  oStream_Makefile << "CPP_VERSION := c++20\n" << std::endl;

  oStream_Makefile << "all: run\n" << std::endl;

  oStream_Makefile << "save: srun\n" << std::endl;

  oStream_Makefile << "$(EXECUTABLE):\n";
  oStream_Makefile << "\tg++ -std=$(CPP_VERSION) SBProgram.cpp -include "
                      "Headers/pch_uni.hpp -IHeaders -o $(EXECUTABLE)\n"
                   << std::endl;

  oStream_Makefile << "EXECUTABLE_S:\n";
  oStream_Makefile << "\tg++ -std=$(CPP_VERSION) SBProgram.cpp -include "
                      "Headers/pch_uni.hpp -IHeaders -o $(EXECUTABLE) -DSAVE\n"
                   << std::endl;

  oStream_Makefile << "Headers/pch_uni.pch: Headers/pch_uni.hpp\n";
  oStream_Makefile << "\tg++ -std=$(CPP_VERSION) Headers/pch_uni.hpp -o "
                      "Headers/pch_uni.pch\n"
                   << std::endl;

  oStream_Makefile << "run: Headers/pch_uni.pch $(EXECUTABLE)\n";
  for (int i = 1; i <= NumberCount; i++) {
    oStream_Makefile << "\t$(EXECUTABLE) $(TASK) $(N" << i << ")" << std::endl;
  }

  oStream_Makefile << "\nsrun: Headers/pch_uni.pch EXECUTABLE_S\n";
  for (int i = 1; i <= NumberCount; i++) {
    oStream_Makefile << "\t$(EXECUTABLE) $(TASK) $(N" << i << ")" << std::endl;
  }

  oStream_Makefile << "\nclean:\n";
  oStream_Makefile << "\trm -f Results/*.txt Archive/*.txt Headers/pch_uni.pch "
                      "$(EXECUTABLE) Tasks/CPPChecker_Uni_Task_19 "
                      "Tasks/CPPChecker_Uni_Task_20"
                   << std::endl;

  oStream_Makefile.close();

  return 0;
}