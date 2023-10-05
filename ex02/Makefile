NAME = PmergeMe
CXX = g++
FLAGS = -std=c++98
FLAGS += -Wall -Werror -Wextra
RM = rm -f

SRCS = main.cpp \
		PmergeMe.cpp \

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(FLAGS) $(OBJS) -o $(NAME)

%.o:%.cpp
	$(CXX) -c $(FLAGS) $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean re
