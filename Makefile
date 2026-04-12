all: compile link clean

compile:
	g++ -c Board.cpp Controller.cpp Menu.cpp Quadrant.cpp Quadrants.cpp Robot.cpp Solver.cpp State.cpp Utils.cpp main.cpp
link:
	g++ *.o -o Ricochet -lsfml-graphics -lsfml-window -lsfml-system  -fopenmp	

clean:
	rm -f *.o

benchmark:
	g++ -c Board.cpp Controller.cpp Menu.cpp Quadrant.cpp Quadrants.cpp Robot.cpp Solver.cpp State.cpp Utils.cpp benchmark.cpp
	g++ *.o -o Benchmark -lsfml-graphics -lsfml-window -lsfml-system  -fopenmp	
	rm -f *.o
	
