TASK := 19

N1 := Anderson Sofia
N2 := Patel Jackson
N3 := Williams Noah Benjamin
N4 := Anna Na
N5 := Johnson Ethan Michael
N6 := Ramirez Elena
N7 := Karl Mueller

EXECUTABLE := ./Tasks/SBProgram

CPP_VERSION := c++20

all: run

save: srun clean

$(EXECUTABLE):
	g++ -std=$(CPP_VERSION) SBProgram.cpp -include Headers/pch_uni.hpp -IHeaders -o $(EXECUTABLE) -DNODEBUG

EXECUTABLE_S:
	g++ -std=$(CPP_VERSION) SBProgram.cpp -include Headers/pch_uni.hpp -IHeaders -o $(EXECUTABLE) -DNODEBUG -DSAVE

Headers/pch_uni.pch: Headers/pch_uni.hpp
	g++ -std=$(CPP_VERSION) Headers/pch_uni.hpp -o Headers/pch_uni.pch

run: Headers/pch_uni.pch $(EXECUTABLE)
	$(EXECUTABLE) $(TASK) $(N1)
	$(EXECUTABLE) $(TASK) $(N2)
	$(EXECUTABLE) $(TASK) $(N3)
	$(EXECUTABLE) $(TASK) $(N4)
	$(EXECUTABLE) $(TASK) $(N5)
	$(EXECUTABLE) $(TASK) $(N6)
	$(EXECUTABLE) $(TASK) $(N7)

srun: Headers/pch_uni.pch EXECUTABLE_S
	$(EXECUTABLE) $(TASK) $(N1)
	$(EXECUTABLE) $(TASK) $(N2)
	$(EXECUTABLE) $(TASK) $(N3)
	$(EXECUTABLE) $(TASK) $(N4)
	$(EXECUTABLE) $(TASK) $(N5)
	$(EXECUTABLE) $(TASK) $(N6)
	$(EXECUTABLE) $(TASK) $(N7)

clean:
	rm -f Results/*.txt Archive/*.txt $(EXECUTABLE)
	rm -f Tasks/CPPChecker_Uni_Task_$(TASK)
	rm -f Student_Answers/studentCode_T$(TASK)_Anderson_Sofia
	rm -f Student_Answers/studentCode_T$(TASK)_Patel_Jackson
	rm -f Student_Answers/studentCode_T$(TASK)_Williams_Noah_Benjamin
	rm -f Student_Answers/studentCode_T$(TASK)_Anna_Na
	rm -f Student_Answers/studentCode_T$(TASK)_Johnson_Ethan_Michael
	rm -f Student_Answers/studentCode_T$(TASK)_Ramirez_Elena
	rm -f Student_Answers/studentCode_T$(TASK)_Karl_Mueller
