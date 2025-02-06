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
BON= 	./pipex_bonus.c \
		./pipex_bonus_utils.c \
		./get_next_line/get_next_line.c \
		./get_next_line/get_next_line_utils.c \
		./utils/free_array.c \
		./utils/ft_split.c \
		./utils/ft_split_cmd.c \
		./utils/libft1.c \
		./utils/libft2.c \
		./utils/get_path.c \
		./utils/pipex_utils1.c
OBJECTS= $(SRCS:.c=.o)
BON_OBJ= $(BON:.c=.o)
NAME=pipex
NAME_BON=pbonus

all: $(NAME)
	@echo $(G) all functions are done

bonus: $(NAME_BON)
	@echo $(G) all functions are done

$(NAME): $(OBJECTS)
	@cc $(CFLAGS) $(OBJECTS) -o $(NAME)
	
$(NAME_BON): $(BON_OBJ)
	@cc  $(CFLAGS) $(BON_OBJ) -o $(NAME)

%.o: %.c $(HEADER)
	@echo $(Y) compailing file $< ... done
	@cc  $(FLAGS) -c $< -o $@

clean:
	@echo $(R) cleaned
	@rm -rf $(OBJECTS) $(BON_OBJ)

fclean: clean
	@echo $(R) fully cleaned
	@rm -rf $(NAME)

re: fclean all
