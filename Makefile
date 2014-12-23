##
## Makefile for  in /home/maigna_j/rendu/cpp_nibbler
##
## Made by Jeremy Maignan
## Login   <maigna_j@epitech.net>
##
## Started on  mar. avril  01 15:20:39 2014 Jeremy Maignan
## Last update mar. avril  01 15:20:39 2014 Jeremy Maignan
##

BIN = 			nibbler

SDL_NAME = 		lib_nibbler_sdl.so
OPENGL_NAME = lib_nibbler_opengl.so
NCURSES_NAME = 		lib_nibbler_ncurses.so

SDL_PATH = 		./sdl/
NCURSES_PATH = 		./ncurses/
OPENGL_PATH  = ./opengl/

SRC =			main.cpp \
			lib_loading.cpp

SDL_SRC = 		$(SDL_PATH)sdl.cpp \
	                $(SDL_PATH)event.cpp \

OPENGL_SRC = $(OPENGL_PATH)opengl.cpp

NCURSES_SRC = 		$(NCURSES_PATH)ncurses.cpp

SDL_OBJ = 		$(SDL_SRC:.cpp=.o)	
OPENGL_OBJ = $(OPENGL_SRC:.cpp=.o)
NCURSES_OBJ=		$(NCURSES_SRC:.cpp=.o)

CC = 			g++

CXXFLAGS  += 	 	-Wall -Wextra -fpic -I ./

SDL_LDFLAGS += 		-shared -lSDL -lSDL_image
OPENGL_LDFLAGS +=   -shared -lSDL -lGL -lGLU
NCURSES_LDFLAGS += 	-shared -lncurses

all: $(NCURSES_NAME) $(SDL_NAME) $(OPENGL_NAME)

$(SDL_NAME): $(SDL_OBJ)
	$(CC) $(SDL_OBJ) -o $(SDL_NAME) $(SDL_LDFLAGS)

$(OPENGL_NAME): $(OPENGL_OBJ)
	$(CC) $(OPENGL_OBJ) -o $(OPENGL_NAME) $(OPENGL_LDFLAGS)

$(NCURSES_NAME): $(NCURSES_OBJ)
	$(CC) $(NCURSES_OBJ) -o $(NCURSES_NAME) $(NCURSES_LDFLAGS)
	g++ $(SRC) -ldl -I ./ -o $(BIN)

clean:
	rm -f $(SDL_OBJ) $(NCURSES_OBJ) $(OPENGL_OBJ) $(BIN)

fclean: clean
	rm -f $(SDL_NAME) $(NCURSES_NAME) $(OPENGL_NAME)

re: fclean all

##g++ main.cpp -ldl -I ./sdl/ -I ./
