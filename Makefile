CXX = g++
CXXFLAGS = -Werror -Wpedantic -Wall
GTEST_LIBS = -lgtest -lgtest_main -pthread

EXECUTABLE_1 = labwork1
EXECUTABLE_2 = tests

$(EXECUTABLE_1): BMP.o main.o 
	$(CXX) $(CXXFLAGS) BMP.cpp main.cpp -o $(EXECUTABLE_1)
$(EXECUTABLE_2): BMP.o tests.o
	$(CXX) BMP.cpp tests.cpp -o $(EXECUTABLE_2) $(GTEST_LIBS)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
clean:
	rm -f *.o
cleanall:
	rm -f *.o GaussianBlur.bmp GaussianBlur_paralell.bmp Rotated90Clockwise.bmp Rotated90Clockwise_paralell.bmp Rotate90CounterClockwise.bmp Rotate90CounterClockwise_paralell.bmp $(EXECUTABLE_1) $(EXECUTABLE_2)
