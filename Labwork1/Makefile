CXX = g++
CXXFLAGS = -g -Wall -pthread -I. -Werror -Wpedantic
PROJ_FILES = $(wildcard *.cpp)
OBJ_FILES = $(PROJ_FILES:.cpp=.o)
EXECUTABLE = labwork1
%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
$(EXECUTABLE): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $(OBJ_FILES) -o $(EXECUTABLE) 
clean:
	rm -f *.o $(EXECUTABLE)
cleanall:
	rm -f *.o GaussianBlur.bmp Rotated90Clockwise.bmp Rotate90CounterClockwise.bmp $(EXECUTABLE)
