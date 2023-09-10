#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

std::string CleanName(const std::string& Name) {
  std::stringstream cleanedName;
  bool leadingWhitespace = true;

  for (char c : Name) {
    if (!std::isspace(c)) {
      cleanedName << c;
      leadingWhitespace = false;
    } else if (!leadingWhitespace) {
      cleanedName << ' ';
      leadingWhitespace = true;
    }
  }

  std::string CleanedName = cleanedName.str();

  size_t lastNonSpace = CleanedName.find_last_not_of(' ');

  if (lastNonSpace != std::string::npos) {
    CleanedName.erase(lastNonSpace + 1);
  }

  return CleanedName;
}

int main(int argc, char* argv[]) {
  std::string year = argv[1];

  std::ofstream oStream_Makefile("../Makefile");

  oStream_Makefile << "TASK := 19\n" << std::endl;

  std::ifstream iStream_Makefile("Names" + year + ".txt");
  std::string File_MakefileLine;

  int NumberCount{0};

  while (std::getline(iStream_Makefile, File_MakefileLine)) {
    File_MakefileLine = CleanName(File_MakefileLine);

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

  oStream_Makefile << "save: srun clean\n" << std::endl;

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
  oStream_Makefile << "\trm -f Results/*.txt Archive/*.txt $(EXECUTABLE)\n";
  oStream_Makefile << "\trm -f Tasks/CPPChecker_Uni_Task_$(TASK)" << std::endl;

  std::ifstream iStream2_Makefile("Names" + year + ".txt");

  NumberCount = 0;

  while (std::getline(iStream2_Makefile, File_MakefileLine)) {
    File_MakefileLine = CleanName(File_MakefileLine);

    if (File_MakefileLine.empty()) {
      continue;
    }

    NumberCount++;
    std::replace(File_MakefileLine.begin(), File_MakefileLine.end(), ' ', '_');

    oStream_Makefile << "\trm -f Student_Answers/studentCode_T$(TASK)_"
                     << File_MakefileLine << std::endl;
  }

  iStream2_Makefile.close();

  oStream_Makefile.close();

  return 0;
}