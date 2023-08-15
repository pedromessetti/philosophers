#.SILENT:

# Color variables
RED = \033[1;31m
GREEN = \033[1;32m
WHITE = \033[1;37m
RESET = \033[0m

# Executable name
NAME = philo

# Compiler options
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g #-fsanitize=thread

# Source and object files
SRCS =	actions.c checks.c main.c sem.c settings.c utils.c

OBJS = $(SRCS:.c=.o)

# Default target
$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# Build executable
all: $(NAME)

# Clean object files
clean:
	rm -f $(OBJS)

# Clean object files and the executable
fclean: clean
	rm -f $(NAME)

# Rebuild the project
re: fclean all

# Rebuild the project and remove object files
run: re
	$(MAKE) clean
	./$(NAME) 5 800 200 200
#	./$(NAME) 5 800 200 200 7 | grep eating | wc -l # out -> 35
#	./$(NAME) 4 410 200 200 # no one dies
#	./$(NAME) 5 410 200 200 # one dies
#	./$(NAME) 3 310 200 100 # one dies

test1: re
	$(MAKE) clean
	./$(NAME) 5 800 200 200 7 | grep eating | wc -l

test0: re
	$(MAKE) clean
	./$(NAME) 2 400 200 200

test2: re
	$(MAKE) clean
	./$(NAME) 5 410 200 200

leak: re
	$(MAKE) clean
	valgrind 	./$(NAME) 5 800 200 200 5

# Show help message
help:
	echo "\\nUsage: make [target]"
	echo ""
	echo "Targets:"
	echo "  all        Build executable"
	echo "  clean      Remove object files"
	echo "  fclean     Remove object files and executable"
	echo "  re         Rebuild project"
	echo "  run        Rebuild, remove object files and run the program"
