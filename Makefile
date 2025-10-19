
CC = gcc
INCLUDE = -Iinclude
CFLAGS = -g -Wall -Wextra -Werror $(INCLUDE) -fPIC

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

PWD = $(shell pwd)

NAME = malloc
LIB_FULL_NAME = libft_malloc_$(HOSTTYPE).so
LINK_NAME = libft_malloc.so
TEST_NAME = mtest
LIB_NAME = ft_malloc

SRC_DIR = ./src
OBJ_DIR = ./obj
LIB_DIR = $(PWD)/lib

MY_SOURCES = $(SRC_DIR)/sballoc.c


MY_OBJECTS = $(MY_SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(MY_OBJECTS)
	@mkdir -p $(LIB_DIR)
	@$(CC) -shared -o $(LIB_DIR)/$(LIB_FULL_NAME) $(MY_OBJECTS)
	@ln -s $(LIB_FULL_NAME) $(LIB_DIR)/$(LINK_NAME)
	@echo "Shared library built: $(LIB_FULL_NAME)"
	@echo "Symlink created: $(LINK_NAME)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled: $<"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "Object directory removed."

fclean: clean
	@rm -rf $(LIB_DIR) $(TEST_NAME) $(LINK_NAME)
	@echo "Library and test removed."

re: fclean all

test: re
	@$(CC) -g  mtest.c -L$(LIB_DIR) -l$(LIB_NAME) -Wl,-rpath=$(abspath $(LIB_DIR)) -o $(TEST_NAME)
	@echo "Test program built: ./$(TEST_NAME)"

.PHONY: all clean fclean re test
