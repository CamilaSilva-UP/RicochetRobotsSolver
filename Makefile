TARGET = Ricochet
CXX = g++
CXXFLAGS = -std=c++17 -I/usr/local/include -DSFML_STATIC
LDFLAGS = -L/usr/local/lib \
          -lsfml-graphics-s -lsfml-window-s -lsfml-system-s \
          -lfreetype -lGL -lX11 -lXrandr -lXcursor -lXi -ludev -lpthread -ldl -lm

SRC = main.cpp Board.cpp Robot.cpp Solver.cpp State.cpp Utils.cpp Controller.cpp Quadrant.cpp Quadrants.cpp
OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

clean:
	rm -f $(OBJ) $(TARGET)