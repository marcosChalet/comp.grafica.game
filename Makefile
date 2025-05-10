SRC = ./src
OBJ = ./obj
BIN = ./bin
INCLUDE = ./include
APP = ./app
FLAG = -O3

OS := $(shell uname)

ifeq ($(OS), Linux)
	LIBS = -lm -lGL -lGLU -lglut
else ifeq ($(OS), Darwin)
	LIBS = -lm -framework OpenGL -framework GLUT
else
	LIBS = -lm -lopengl32 -lglu32 -lfreeglut
endif

all: libsGame Game

libsGame: \
	$(OBJ)/platform.o \
	$(OBJ)/player.o \
	$(OBJ)/scene.o \
	$(OBJ)/blocks.o \
	$(OBJ)/parse-blocks.o

Game: clear_app \
	$(BIN)/game

$(OBJ)/%.o: $(SRC)/%.c $(INCLUDE)/%.h
	gcc $(FLAG) -c $< -I $(INCLUDE) -o $@

$(BIN)/%: $(APP)/%.c
	gcc $(FLAG) $< $(OBJ)/*.o -I $(INCLUDE) -lm ${LIBS} -Wall -o $@

run:
	$(BIN)/game

clear:
	rm -rf $(BIN)/* $(OBJ)/*

clear_app:
	rm -rf $(BIN)/*