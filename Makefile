##
## EPITECH PROJECT, 2018
## Plazza
## File description:
## Plazza Makefile
##

CXX	= g++ -o2

RM	= rm -f

CXXFLAGS = -I./include
CXXFLAGS += -W -Wall -Wextra -Werror -std=c++14
LDFLAGS = -lpthread

NAME 	= plazza

SRCS	= $(wildcard src/**/*.cpp)  \
          src/main.cpp

OBJS    = $(SRCS:.cpp=.o)

SRCS_TEST	= $(wildcard tests/*.cpp)

OBJS_TEST	= $(SRCS_TEST:.cpp=.o)

NAME_TEST	= tests_bin

ifeq    ($(DEBUG),yes)
        CXX += -g3
endif

$(NAME): $(OBJS)
	@$(CXX) $(OBJS) -o $(NAME) $(LDFLAGS)
	@printf "\n-------------------\n"
	@printf "\n\033[32m[OK]\033[0m Binary : \033[36m$(NAME)\033[0m\n"
	@printf "\n-------------------\n\n"


%.o: %.cpp
	@printf "\033[32m[OK]\033[0m $<\n";
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

all: $(NAME)

tests_run: $(OBJS) $(OBJS_TEST)
	@$(CXX) $(OBJS) $(OBJS_TEST) -o $(NAME_TEST) $(LDFLAGS) -lcriterion -coverage
	@printf "\n-------------------\n"
	@printf "\n\033[32m[OK]\033[0m Binary : \033[36m$(NAME_TEST)\033[0m\n"
	@printf "\n-------------------\n"
	@printf "\nExecuting tests...\n\n"
	@./$(NAME_TEST)

clean:
	@$(RM) $(OBJS)
	@$(RM) $(OBJS_TEST)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(NAME_TEST)

re: fclean all

.PHONY: all tests_run clean fclean re
