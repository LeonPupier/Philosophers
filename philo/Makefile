# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/02 08:32:06 by lpupier           #+#    #+#              #
#    Updated: 2023/01/12 15:37:28 by lpupier          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Constants
NAME		=	philo
CFLAGS		=	-Wall -Wextra -Werror -pthread #-fsanitize=thread

# Directories path
DIR_SRCS	=	sources/
DIR_HEADERS	=	headers/

# Files path
HEADERS	=	$(DIR_HEADERS)philo.h

SRCS	=	$(DIR_SRCS)main.c \
			$(DIR_SRCS)ft_atoi.c \
			$(DIR_SRCS)parameters.c \
			$(DIR_SRCS)philosopher.c

OBJS	=	$(SRCS:.c=.o)

# Rules
.PHONY :	all clean fclean re watermark

all :	 	${NAME}

%.o: %.c	$(HEADERS) Makefile
			$(CC) $(CFLAGS) -c $< -o $@

${NAME}:	${OBJS}
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re :		fclean all

watermark:
			@echo "$$WATERMARK"

# Text art
define WATERMARK

██╗  ██╗██████╗ 
██║  ██║╚════██╗ name:  Leon Pupier
███████║ █████╔╝ login: lpupier
╚════██║██╔═══╝  
     ██║███████╗
     ╚═╝╚══════╝lyon.fr

endef
export WATERMARK