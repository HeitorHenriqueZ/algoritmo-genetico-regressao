CXX = g++
CXXFLAGS = -Wall -Wextra -O3 -std=c++17
TARGET = programa

SRCS = main.cpp utils.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

tudo: all

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all tudo run clean