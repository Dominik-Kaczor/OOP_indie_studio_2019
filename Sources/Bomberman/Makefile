##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## No description
##

SRC_PACMAN	= 	Bomberman.cpp	\
			Map.cpp	\
			Player.cpp \
			Bot.cpp \
			Bomb.cpp

OBJ_PACMAN =	$(SRC_PACMAN:.cpp=.o)

CCX =	g++

RM =	rm -f

PACMAN_LIB_GAMES = test/games/lib_arcade_bomberan.so

OUTPUT = -o

CXXFLAGS = -fPIC -shared -rdynamic

CPPFLAGS = -I../../Includes/

debug:  CPPFLAGS += -g3
debug:  re

all:  games

games:		$(OBJ_PACMAN)
		$(CCX) $(OUTPUT) $(PACMAN_LIB_GAMES) $(OBJ_PACMAN) $(CXXFLAGS) $(CPPFLAGS)

clean:
		$(RM) $(OBJ_NIBBLER)
		$(RM) $(OBJ_PACMAN)
		$(RM) $(PACMAN_LIB_GAMES)

fclean:	clean
	$(RM) bomberman

re:		fclean all

.PHONY: all clean fclean re
