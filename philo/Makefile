# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/02 08:32:06 by lpupier           #+#    #+#              #
#    Updated: 2023/04/07 08:23:41 by lpupier          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Constants
NAME		=	philo
CFLAGS		=	-Wall -Wextra -Werror -pthread #-fsanitize=thread
RM			=	rm -rf

# Directories path
DIR_SRCS	=	sources/
DIR_HEADERS	=	headers/

# Files path
HEADERS	=	$(DIR_HEADERS)philo.h

SRCS	=	$(DIR_SRCS)main.c \
			$(DIR_SRCS)ft_atoi.c \
			$(DIR_SRCS)parameters.c \
			$(DIR_SRCS)philosopher.c \
			$(DIR_SRCS)utils.c

# Objects
DIR_OBJS	=	.objs/
OBJS		=	${patsubst %.c, ${DIR_OBJS}%.o, ${SRCS}}

# Rules
.PHONY :	all clean fclean re watermark

all :	 	${NAME}

%.o: %.c	$(HEADERS) Makefile
			$(CC) $(CFLAGS) -c $< -o $@

${DIR_OBJS}%.o: %.c	${HEADERS}
			@mkdir -p ${shell dirname $@}
			${CC} ${CFLAGS} -c $< -o $@ -I ${DIR_HEADERS}

${NAME}:	${OBJS}
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
			${RM} ${OBJS} ${DIR_OBJS}

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