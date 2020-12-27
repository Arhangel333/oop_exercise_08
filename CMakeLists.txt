all: oop_exercise_08

oop_exercise_08: main.o
	g++ main.o -pthread -o oop_exercise_08

main.o: main.cpp
	g++ -pthread -c main.cpp


clean:
	rm -rf *.o oop_exercise_08 out*