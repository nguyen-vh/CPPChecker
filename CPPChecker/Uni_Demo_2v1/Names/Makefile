all: run clean

run: EXECUTABLE
	./makefileGEN

EXECUTABLE:
	g++ -std=c++20 makefileGEN.cpp -o makefileGEN

clean:
	rm makefileGEN