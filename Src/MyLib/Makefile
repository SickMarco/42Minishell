NAME = mylib.a

SRC =	ft_isalnum.c ft_isprint.c ft_memcmp.c \
		ft_strlcat.c ft_strncmp.c ft_substr.c ft_atoi.c ft_isalpha.c \
		ft_memcpy.c ft_strchr.c ft_strlcpy.c \
		ft_strnstr.c ft_tolower.c ft_bzero.c   ft_isascii.c \
		ft_memmove.c ft_strdup.c  ft_strlen.c  ft_strrchr.c \
		ft_toupper.c ft_calloc.c  ft_isdigit.c ft_memchr.c  ft_memset.c \
		ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
		ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
		ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c \
		ft_printf.c ft_itoa2.c ft_unsign.c ft_hexa2.c ft_utility.c ft_putptrn.c \
		get_next_line.c get_next_line_utils.c ft_atoi_long.c list_utils.c

SRC_DIR = ./Src/

SRCP = $(addprefix $(SRC_DIR),$(SRC))

OBJ = $(SRCP:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs  $(NAME) $(OBJ)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.SILENT: $(OBJ)
