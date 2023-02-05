##
## EPITECH PROJECT, 2023
## nanotekspice
## File description:
## Makefile
##

rwildc = $(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildc,$d/,$2))

SOURCEDIR = ../src
TEST_SOURCEDIR = ./

TMP_SRC = $(call rwildc,$(SOURCEDIR),*.cpp) \
	$(call rwildc,$(TEST_SOURCEDIR),*.cpp)

SRC = $(filter-out $(call rwildc,$(SOURCEDIR),main.cpp),$(TMP_SRC))

CXX = g++

OBJ = $(SRC:.cpp=.o)

NAME = tests

CXXFLAGS = -Wall -Wextra -I ../include -std=c++20 -g --coverage

all: $(NAME)

$(NAME):   $(OBJ)
	g++ -o $(NAME) $(OBJ) $(CXXFLAGS)

clean:
	rm -f $(OBJ)
	find . -name "vgcore.*" -delete
	find . -name "*~" -delete
	find . -name "\#*" -delete

fclean:    clean
	rm -f $(NAME)

re:        fclean all
