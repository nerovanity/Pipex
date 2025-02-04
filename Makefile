CC= cc
FLAGS= -Wall -Wextra -Werror
HEADER= pipex.h
G = $(shell tput setaf 2)
R = $(shell tput setaf 1)
Y = $(shell tput setaf 3)
SRCS=	pipex.c \
		./utils/free_array.c \
		./utils/ft_split.c \
		./utils/ft_split_cmd.c \
		./utils/libft1.c \
		./utils/libft2.c \
		./utils/get_path.c \
		./utils/pipex_utils1.c
OBJECTS= $(SRCS:.c=.o)
NAME=pipex

all: $(NAME)
	@echo $(G) all functions are done

$(NAME): $(OBJECTS)
	@$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)
	
%.o: %.c $(HEADER)
	@echo $(Y) compailing file $< ... done
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@echo $(R) cleaned
	@rm -rf $(OBJECTS)

fclean: clean
	@echo $(R) fully cleaned
	@rm -rf $(NAME)

re: fclean all