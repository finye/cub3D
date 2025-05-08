# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eelaine <eelaine@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/18 10:06:24 by eelaine           #+#    #+#              #
#    Updated: 2025/04/22 15:32:24 by eelaine          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCDIR = src
LIBFTDIR = $(SRCDIR)/libft/
PRINTF_DIR = $(SRCDIR)/ft_printf/
GNL_DIR = $(SRCDIR)/get_next_line/
INCL = incl

LIBFT_SRCS = $(addprefix $(LIBFTDIR),\
				ft_abs.c \
				ft_atoi.c \
				ft_atoi_err.c \
				ft_atol.c \
				ft_atoll.c \
				ft_bzero.c \
				ft_calloc.c \
				ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_isspace.c \
				ft_itoa.c \
				ft_lstadd_back.c \
				ft_lstadd_front.c \
				ft_lstclear.c \
				ft_lstdelone.c \
				ft_lstlast.c \
				ft_lstnew.c \
				ft_lstsize.c \
				ft_lstiter.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_memset.c \
				ft_putchar_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_putstr_fd.c \
				ft_realloc.c \
				ft_split.c \
				ft_strcmp.c \
				ft_strchr.c \
				ft_strcpy.c \
				ft_strdup.c \
				ft_strndup.c \
				ft_striteri.c \
				ft_strjoin.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strlen.c \
				ft_strmapi.c \
				ft_strncmp.c \
				ft_strnstr.c \
				ft_strpbrk.c \
				ft_strrchr.c \
				ft_strtrim.c \
				ft_substr.c \
				ft_tolower.c \
				ft_toupper.c)

PRINTF_SRCS = $(addprefix $(PRINTF_DIR),\
				ft_printf.c \
				ft_print_helper.c \
				ft_print_hex.c \
				ft_print_ptr.c \
				ft_print_u.c)

GNL_SRCS = $(addprefix $(GNL_DIR),\
				get_next_line.c \
				get_next_line_utils.c)

				
SRCS = $(LIBFT_SRCS) $(PRINTF_SRCS) $(GNL_SRCS)
OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

RM = rm -f

GREEN = \033[0;92m
BLUE = \033[0;94m
END_COLOR = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@echo "$(GREEN)Libft compiled$(END_COLOR)"

%.o: %.c
	@$(CC) $(CFLAGS) -I $(INCL) -c $< -o $@

clean:
	$(RM) $(OBJS)
	@echo "$(BLUE)Cleaned libft object files$(END_COLOR)"

fclean:
	$(RM) $(NAME) $(OBJS)
	@echo "$(BLUE)Fully cleaned libft$(END_COLOR)"

re: fclean all

.PHONY: all clean fclean re
