.SILENT:

# Color variables
RED = \033[1;31m
GREEN = \033[1;32m
WHITE = \033[1;37m
RESET = \033[0m

# Executable name
NAME = philo

# Compiler options
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread -g #-fsanitize=thread

# Source and object files
SRCS =	$(wildcard ./*.c)
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
	./$(NAME) 5 200000 20 100

# Show help message
help:
	echo "\\nUsage: make [target]"
	echo ""
	echo "Targets:"
	echo "  all        Build executable"
	echo "  clean      Remove object files"
	echo "  fclean     Remove object files and the executable"
	echo "  re         Rebuild the project"
	echo "  run        Rebuild the project and remove object files"
