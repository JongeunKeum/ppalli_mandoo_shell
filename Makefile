NAME = minishell
CC = gcc
# CFLAGS = -Wall -Wextra -Werror
CFLAGS = -g3 -fsanitize=address

# ifeq ($(DEBUG),true)
# 	CFLAGS += -g
# endif

SRCS_DIR =	./srcs	\
			./srcs/pre_setting	\
			./srcs/pre_setting/cursor	\
			./srcs/pre_setting/tokenize	\
			./srcs/run	\
			./srcs/run/blt_func	\
			./srcs/utils

OBJS_DIR = ./objs
INC_DIR = ./includes

SRCS =	./srcs/main.c	\
		./srcs/minishell.c	\
		./srcs/pre_setting/check_syntax_err.c	\
		./srcs/pre_setting/check_syntax_err2.c	\
		./srcs/pre_setting/init.c	\
		./srcs/pre_setting/read_cmd.c	\
		./srcs/pre_setting/cursor/cursor.c	\
		./srcs/pre_setting/tokenize/parse.c	\
		./srcs/pre_setting/tokenize/separate.c	\
		./srcs/pre_setting/tokenize/token.c	\
		./srcs/run/builtin.c	\
		./srcs/run/error.c	\
		./srcs/run/find.c	\
		./srcs/run/handle_file_or_dir.c	\
		./srcs/run/run.c	\
		./srcs/run/signal.c	\
		./srcs/run/blt_func/blt_cd.c	\
		./srcs/run/blt_func/blt_echo.c	\
		./srcs/run/blt_func/blt_env.c	\
		./srcs/run/blt_func/blt_exit.c	\
		./srcs/run/blt_func/blt_export.c	\
		./srcs/run/blt_func/blt_pwd.c	\
		./srcs/run/blt_func/blt_unset.c	\
		./srcs/utils/ft_atoi.c	\
		./srcs/utils/ft_calloc.c	\
		./srcs/utils/ft_isalnum.c	\
		./srcs/utils/ft_isalpha.c	\
		./srcs/utils/ft_isdigit.c	\
		./srcs/utils/ft_isprint.c	\
		./srcs/utils/ft_itoa.c	\
		./srcs/utils/ft_memcpy.c	\
		./srcs/utils/ft_memmove.c	\
		./srcs/utils/ft_memset.c	\
		./srcs/utils/ft_putstr_fd.c	\
		./srcs/utils/ft_split.c	\
		./srcs/utils/ft_str_char_del.c	\
		./srcs/utils/ft_str_char_embed.c	\
		./srcs/utils/ft_str_char_join.c	\
		./srcs/utils/ft_strchr.c	\
		./srcs/utils/ft_strcmp.c	\
		./srcs/utils/ft_strdup.c	\
		./srcs/utils/ft_strjoin.c	\
		./srcs/utils/ft_strlcpy.c	\
		./srcs/utils/ft_strlen.c	\
		./srcs/utils/ft_strncmp.c	\
		./srcs/utils/ft_strtrim.c	\
		./srcs/utils/ft_substr.c	\

OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.c=.o)))
vpath %.c $(SRCS_DIR)

RM = rm -f

all: $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) -lncurses -o $@ $^

$(OBJS_DIR) :
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o : %.c | $(OBJS_DIR)
	@$(CC) $(CFLAGS) -o $@ -I$(INC_DIR) -c $^

run: re
	@./$(NAME)

clean :
	@$(RM) -r $(OBJS_DIR)

fclean : clean
	@$(RM) $(NAME)

re : fclean all
