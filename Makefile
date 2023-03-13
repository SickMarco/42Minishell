NAME = minishell

SRC = main.c builtins.c utils.c expander.c ft_countwords1.c ft_split1.c ft_createlist.c ft_subsplit.c env.c executor.c ft_ischarofset.c ft_trimone.c \
      reader.c reader_utils.c reader_utils2.c gnl.c expander2.c cmdlst_create.c cmdlst_utils.c exec_cmd.c redirect.c utils2.c debug.c utils3.c

SRC_DIR = ./Src/

OBJ_DIR = ./Src/.obj/

SRCP = $(addprefix $(SRC_DIR),$(SRC))

OBJP = $(addprefix $(OBJ_DIR),$(notdir $(SRCP:.c=.o)))

CFLAGS = -Wall -Wextra -Werror -fPIE -g 

LIB = ./Src/MyLib/mylib.a

all: lib $(NAME)

lib:
	@echo "\033[32mCompiling $(NAME) 🚀"
	make -s -C Src/MyLib

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJP)
	@gcc $(CFLAGS) $(OBJP) $(LIB) -lreadline -o $(NAME)
	@echo "Compiled ✅\033[0;37m"

clean:
	@echo "\033[0;31mCleaning objects 🧹"
	@rm -rf $(OBJ_DIR)
	@make clean -s -C Src/MyLib

fclean: clean
	@echo "\033[0;31mRemoving $(NAME) 🗑\033[0;37m"
	@rm -rf $(NAME)
	@make fclean -s -C Src/MyLib

re: fclean all

.SILENT: $(OBJ) lib

.PHONY: all lib clean fclean re
