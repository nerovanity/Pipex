FLAGS= -Wall -Wextra -Werror
HEADER= Mandatory/pipex.h
G = $(shell tput setaf 2)
R = $(shell tput setaf 1)
Y = $(shell tput setaf 3)
SRCS=	./Mandatory/pipex.c \
		./Mandatory/utils/free_array.c \
		./Mandatory/utils/ft_split.c \
		./Mandatory/utils/ft_split_cmd.c \
		./Mandatory/utils/libft1.c \
		./Mandatory/utils/libft2.c \
		./Mandatory/utils/get_path.c \
		./Mandatory/utils/pipex_utils1.c
BON= 	./Bonus/pipex_bonus.c \
		./Bonus/pipex_bonus_utils.c \
		./Bonus/get_next_line/get_next_line.c \
		./Bonus/get_next_line/get_next_line_utils.c \
		./Bonus/utils/free_array.c \
		./Bonus/utils/ft_split.c \
		./Bonus/utils/ft_split_cmd.c \
		./Bonus/utils/libft1.c \
		./Bonus/utils/libft2.c \
		./Bonus/utils/get_path.c \
		./Bonus/utils/pipex_utils1.c
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

Mandatory/%.o: Mandatory/%.c $(HEADER)
	@echo $(Y) compailing file $< ... done
	@cc  $(FLAGS) -c $< -o $@

Bonus/%.o: Bonus/%.c Bonus/pipex_bonus.h
	@echo $(Y) compailing file $< ... done
	@cc  $(FLAGS) -c $< -o $@

clean:
	@echo $(R) cleaned
	@rm -rf $(OBJECTS) $(BON_OBJ)

fclean: clean
	@echo $(R) fully cleaned
	@rm -rf $(NAME)

re: fclean all
