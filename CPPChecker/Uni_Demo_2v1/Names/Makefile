#	Creates a Makefile with the names in the Names.txt 

YEAR := 2023

all: run clean

run: EXECUTABLE
	./makefileGEN $(YEAR)

EXECUTABLE:
	g++ -std=c++20 makefileGEN.cpp -o makefileGEN

clean:
	rm makefileGEN