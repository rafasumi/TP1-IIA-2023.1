CC = g++
CCFLAGS = -Wall

INCLUDE_FOLDER = ./include/
OBJ_FOLDER = ./obj/
SRC_FOLDER = ./src/

MAIN = main
TARGET = TP1
SRC = $(wildcard $(SRC_FOLDER)*.cpp)
OBJ = $(patsubst $(SRC_FOLDER)%.cpp, $(OBJ_FOLDER)%.o, $(SRC))

$(OBJ_FOLDER)%.o: $(SRC_FOLDER)%.cpp
	@mkdir -p $(OBJ_FOLDER)
	$(CC) $(CCFLAGS) -c $< -o $@ -I$(INCLUDE_FOLDER)

build: $(OBJ)
	$(CC) $(CCFLAGS) -o $(TARGET) $(OBJ)

clean:
	@rm -rf $(OBJ_FOLDER) $(TARGET)
