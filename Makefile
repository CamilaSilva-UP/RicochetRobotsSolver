all: compile link clean

compile:
	g++ -c main.cpp Board.cpp Robot.cpp Solver.cpp State.cpp Utils.cpp Controller.cpp
link:
	g++ main.o -o ricochet -lsfml-graphics -lsfml-window -lsfml-system	

clean:
	rm -f *.o
