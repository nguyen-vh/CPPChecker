#	19 or 20
TASK = 19

A = Anderson Sofia
B = Patel Jackson
C = Williams Noah Benjamin
D = Johnson Ethan Michael
E = Ramirez Elena 

EXECUTABLE := SBProgram

CPP_VERSION := c++20

ifeq ($(shell g++ -dumpversion | cut -d. -f1),11)
	
CPP_VERSION := c++20

endif

all: Headers/pch_uni.pch run

$(EXECUTABLE): 
	g++ -std=$(CPP_VERSION) V2_Super_Brain_Program.cpp -include Headers/pch_uni.hpp -IHeaders -o $(EXECUTABLE)

Headers/pch_uni.pch: Headers/pch_uni.hpp
	g++ -std=$(CPP_VERSION) Headers/pch_uni.hpp -o Headers/pch_uni.pch

#	Ultimately it should read the Names.txt
run: $(EXECUTABLE)
	./$(EXECUTABLE) $(TASK) $(A)
	./$(EXECUTABLE) $(TASK) $(B)
	./$(EXECUTABLE) $(TASK) $(C)
	./$(EXECUTABLE) $(TASK) $(D)
	./$(EXECUTABLE) $(TASK) $(E)

clean:
	rm -f Results/*.txt Archive/*.txt Headers/pch_uni.pch $(EXECUTABLE) Tasks/CPPChecker_Uni_Task_19 Tasks/CPPChecker_Uni_Task_20

