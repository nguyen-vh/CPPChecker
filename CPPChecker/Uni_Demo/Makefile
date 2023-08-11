all: Headers/pch_uni.pch compile run clean

compile:
	g++ -std=c++23 Super_Brain_Program.cpp -include Headers/pch_uni.hpp -IHeaders -o Super_Brain_Program

Headers/pch_uni.pch: Headers/pch_uni.hpp
	g++ -std=c++23 Headers/pch_uni.hpp -o Headers/pch_uni.pch

run:
	.\Super_Brain_Program

clean:
	rm -f Super_Brain_Program CPPChecker_Uni_Task_19 students_code