##
## EPITECH PROJECT, 2023
## nanotekspice
## File description:
## Makefile
##

rwildc = $(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildc,$d/,$2))

SOURCEDIR = src

SRC = $(call rwildc,$(SOURCEDIR),*.cpp)

CXX = g++

OBJ = $(SRC:.cpp=.o)

NAME = nanotekspice

CXXFLAGS = -Wall -Wextra -I ./include -I ./include/components/abstracts \
		-I ./include/components/advanced -I ./include/components/elementary \
		-I ./include/components/special -std=c++20

all: try_clean $(NAME)

$(NAME):   $(OBJ)
	g++ -o $(NAME) $(OBJ) $(CXXFLAGS)

try_clean:
	(ls src/*.gc* > /dev/null 2>&1 && make -s clean) || true

tests_run:
	make -C tests/ && ./tests/tests

clean:
	rm -f $(OBJ)
	find . -name "vgcore.*" -delete
	find . -name "*~" -delete
	find . -name "\#*" -delete
	find . -name "*.gc*" -delete

fclean:    clean
	rm -f $(NAME)

re:        fclean all
