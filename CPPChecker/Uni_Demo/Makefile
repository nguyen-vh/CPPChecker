ifeq ($(OS),Windows_NT)
    PLATFORM := windows
    EXECUTABLE := Super_Brain_Program.exe
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Darwin)
        PLATFORM := macos
        EXECUTABLE := Super_Brain_Program
    else
        PLATFORM := linux
        EXECUTABLE := Super_Brain_Program
    endif
endif

CPP_VERSION := c++23

ifeq ($(shell g++ -dumpversion | cut -d. -f1),11)
	
CPP_VERSION := c++20

endif

all: start Headers/pch_uni.pch compile run clean

compile:
	g++ -std=$(CPP_VERSION) Super_Brain_Program.cpp -include Headers/pch_uni.hpp -IHeaders -o $(EXECUTABLE)

Headers/pch_uni.pch: Headers/pch_uni.hpp
	g++ -std=$(CPP_VERSION) Headers/pch_uni.hpp -o Headers/pch_uni.pch

run:
	./$(EXECUTABLE)

start:
	rm -f Students_Results.txt

clean:
	rm -f $(EXECUTABLE) CPPChecker_Uni_Task_19 students_code

cleanall:
	rm -f $(EXECUTABLE) CPPChecker_Uni_Task_19 students_code Students_Results.txt Headers/pch_uni.pch