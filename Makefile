INCLUDE 	= -Iinclude

CFLAGS = -Wall -Wextra -Werror $(INCLUDE) -fpic 

ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
LIB_NAME = ft_malloc_$(HOSTTYPE)

SRC_DIR = ./src

MY_SOURCES = $(SRC_DIR)/main.c 

MY_OBJECTS = $(MY_SOURCES:.c=.o)

all: $(NAME)


$(NAME): $(MY_OBJECTS)
	@gcc -shared -o $(NAME) $(MY_OBJECTS)
	@echo "$(NAME) compiled."

%.o :%.c
	@cc $(CFLAGS) -c $< -o $@ 
	@echo "$< compiled."

clean:
	@$(RM) $(MY_OBJECTS) $(MY_OBJECTS_BONUS)
	@echo "Objects files removed."

fclean: clean
	@$(RM) $(NAME)
	@echo "$(NAME) removed."

test: all
	gcc test.c -Wl,-rpath=$(pwd) -L./ -l$(LIB_NAME) -o maltest

re: fclean all

.PHONY: all clean fclean re 