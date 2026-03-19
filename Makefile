all: compile link clean

compile:
	g++ -c main.cpp Board.cpp Robot.cpp Solver.cpp State.cpp Utils.cpp Controller.cpp
link:
	g++ main.o Board.o Robot.o Solver.o State.o Utils.o Controller.o -o Ricochet -lsfml-graphics -lsfml-window -lsfml-system	

clean:
	rm -f *.o
