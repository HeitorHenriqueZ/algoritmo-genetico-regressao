CXX      := g++
CXXFLAGS := -Wall -Wextra -Werror
LDFLAGS  := -lm
BUILD    := ./build
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := $(BUILD)
TARGET   := app
INCLUDE  := -Iinclude/
SRC      := $(wildcard src/*.cpp)

# Corrige o caminho dos objetos para não duplicar 'src/'
OBJECTS  := $(patsubst src/%.cpp,$(OBJ_DIR)/%.o,$(SRC))

all: build $(APP_DIR)/$(TARGET)

# Regra para compilar os .o
$(OBJ_DIR)/%.o: src/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

# Regra para compilar o executável
$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $^ -o $@ $(LDFLAGS)

.PHONY: all build clean debug release run

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CXXFLAGS += -DDEBUG -g
debug: all

release: CXXFLAGS += -O3
release: all

clean:
	-@rm -rvf $(OBJ_DIR)
	-@rm -rvf $(APP_DIR)/$(TARGET)

run:
	./$(APP_DIR)/$(TARGET)