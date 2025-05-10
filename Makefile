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
	$(OBJ)/grassPlatform.o \
	$(OBJ)/meshLoader.o \
	$(OBJ)/grassBlock.o \
	$(OBJ)/player.o \
	$(OBJ)/steve.o \
	$(OBJ)/sword.o \
	$(OBJ)/floor.o \
	$(OBJ)/scene.o

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