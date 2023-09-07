#	19 or 20
TASK := 19

A := Anderson Sofia
B := Patel Jackson
C := Williams Noah Benjamin
D := Johnson Ethan Michael
E := Ramirez Elena 

EXECUTABLE := ./Tasks/SBProgram

CPP_VERSION := c++20

ifeq ($(shell g++ -dumpversion | cut -d. -f1),11)
	
CPP_VERSION := c++20

endif

all: $(EXECUTABLE) run

save: $(EXECUTABLE) srun

$(EXECUTABLE): 
	g++ -std=$(CPP_VERSION) SBProgram.cpp -include Headers/pch_uni.hpp -IHeaders -o $(EXECUTABLE)

EXECUTABLE_S: 
	g++ -std=$(CPP_VERSION) SBProgram.cpp -include Headers/pch_uni.hpp -IHeaders -o $(EXECUTABLE) -DSAVE

Headers/pch_uni.pch: Headers/pch_uni.hpp
	g++ -std=$(CPP_VERSION) Headers/pch_uni.hpp -o Headers/pch_uni.pch

#	Ultimately it should read the Names.txt
run: $(EXECUTABLE)
	$(EXECUTABLE) $(TASK) $(A)
	$(EXECUTABLE) $(TASK) $(B)
	$(EXECUTABLE) $(TASK) $(C)
	$(EXECUTABLE) $(TASK) $(D)
	$(EXECUTABLE) $(TASK) $(E)

srun: EXECUTABLE_S
	$(EXECUTABLE) $(TASK) $(A)
	$(EXECUTABLE) $(TASK) $(B)
	$(EXECUTABLE) $(TASK) $(C)
	$(EXECUTABLE) $(TASK) $(D)
	$(EXECUTABLE) $(TASK) $(E)

clean:
	rm -f Results/*.txt Archive/*.txt Headers/pch_uni.pch $(EXECUTABLE) Tasks/CPPChecker_Uni_Task_19 Tasks/CPPChecker_Uni_Task_20

