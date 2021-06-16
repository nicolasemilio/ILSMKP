PROJECT = ILSMKP
CFLAGS = -Wall -g -O3
OBJECTS = Main.o Initialize.o CandidateSolution.o ILS-Functions.o

all: $(PROJECT)

.cpp.o:
	g++ -c $(CFLAGS) $<

$(PROJECT): $(OBJECTS)
	g++ $(CFLAGS) -o $(PROJECT) $(OBJECTS)
	
Main.o: Main.cpp
	g++ $(CFLAGS) -c Main.cpp
	
Initialize.o: Initialize.cpp Initialize.h
	g++ $(CFLAGS) -c Initialize.cpp

CandidateSolution.o: CandidateSolution.cpp CandidateSolution.h
	g++ $(CFLAGS) -c CandidateSolution.cpp

ILS-Functions.o: ILS-Functions.cpp ILS-Functions.h
	g++ $(CFLAGS) -c ILS-Functions.cpp

clean:
	rm $(OBJECTS) $(PROJECT)
