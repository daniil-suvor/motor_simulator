COMPILER=g++
CFLAGS=-c -Wall -Wextra -Werror

all: main

main: motor.o simulation.o main.o
	$(COMPILER) motor.o simulation.o main.o -o main

motor.o: motor.cpp motor.h
	$(COMPILER) $(CFLAGS) motor.cpp

simulation.o: simulation.cpp simulation.h
	$(COMPILER) $(CFLAGS) simulation.cpp

main.o: main.cpp
	$(COMPILER) $(CFLAGS) main.cpp

clean:
	rm *.o main