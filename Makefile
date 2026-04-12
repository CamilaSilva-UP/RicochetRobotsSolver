all: compile link clean

compile:
	g++ -c *.cpp
link:
	g++ *.o -o Ricochet -lsfml-graphics -lsfml-window -lsfml-system  -fopenmp	

clean:
	rm -f *.o
