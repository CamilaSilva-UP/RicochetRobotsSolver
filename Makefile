all: compile link clean

compile:
	g++ -c *.cpp
link:
	g++ *.o -o Ricochet -lsfml-graphics -lsfml-window -lsfml-system	

clean:
	rm -f *.o
