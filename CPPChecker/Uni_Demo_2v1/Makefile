TASK := 19

N1 := Anderson Sofia
N2 := Patel Jackson
N3 := Williams Noah Benjamin
N4 := Anna Na
N5 := Johnson Ethan Michael
N6 := Ramirez Elena

EXECUTABLE := ./Tasks/SBProgram

CPP_VERSION := c++20

all: run

save: srun

$(EXECUTABLE):
	g++ -std=$(CPP_VERSION) SBProgram.cpp -include Headers/pch_uni.hpp -IHeaders -o $(EXECUTABLE)

EXECUTABLE_S:
	g++ -std=$(CPP_VERSION) SBProgram.cpp -include Headers/pch_uni.hpp -IHeaders -o $(EXECUTABLE) -DSAVE

Headers/pch_uni.pch: Headers/pch_uni.hpp
	g++ -std=$(CPP_VERSION) Headers/pch_uni.hpp -o Headers/pch_uni.pch

run: Headers/pch_uni.pch $(EXECUTABLE)
	$(EXECUTABLE) $(TASK) $(N1)
	$(EXECUTABLE) $(TASK) $(N2)
	$(EXECUTABLE) $(TASK) $(N3)
	$(EXECUTABLE) $(TASK) $(N4)
	$(EXECUTABLE) $(TASK) $(N5)
	$(EXECUTABLE) $(TASK) $(N6)

srun: Headers/pch_uni.pch EXECUTABLE_S
	$(EXECUTABLE) $(TASK) $(N1)
	$(EXECUTABLE) $(TASK) $(N2)
	$(EXECUTABLE) $(TASK) $(N3)
	$(EXECUTABLE) $(TASK) $(N4)
	$(EXECUTABLE) $(TASK) $(N5)
	$(EXECUTABLE) $(TASK) $(N6)

clean:
	rm -f Results/*.txt Archive/*.txt Headers/pch_uni.pch $(EXECUTABLE) Tasks/CPPChecker_Uni_Task_19 Tasks/CPPChecker_Uni_Task_20
