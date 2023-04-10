# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/02 08:32:06 by lpupier           #+#    #+#              #
#    Updated: 2023/04/10 18:17:39 by lpupier          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Constants
NAME		=	philo
CFLAGS		=	-Wall -Wextra -Werror -pthread -fsanitize=thread
RM			=	rm -rf

# Directories path
DIR_SRCS	=	sources/
DIR_HEADERS	=	includes/

# Utils directorie path
DIR_UTILS	=	$(DIR_SRCS)utils/

# Philo directorie path
DIR_PHILO	=	$(DIR_SRCS)philo/

# Utils files
UTILS_FILES	=	$(DIR_UTILS)parameters.c	\
				$(DIR_UTILS)display.c		\
				$(DIR_UTILS)ft_atoi.c		\
				$(DIR_UTILS)mutex.c			\
				$(DIR_UTILS)utils.c

# Philo files
PHILO_FILES	=	$(DIR_PHILO)philosopher.c		\
				$(DIR_PHILO)activities.c		\
				$(DIR_PHILO)threads_gestion.c

# Sources and headers
SRCS		=	$(DIR_SRCS)main.c	\
				$(PHILO_FILES)		\
				$(UTILS_FILES)

HEADERS		=	$(DIR_HEADERS)philo.h

# Objects
DIR_OBJS	=	.objs/
OBJS		=	${patsubst %.c, ${DIR_OBJS}%.o, ${SRCS}}

# Rules
.PHONY :		all clean fclean re watermark

all :	 		${NAME}

%.o: %.c		$(HEADERS)
				$(CC) $(CFLAGS) -c $< -o $@

${DIR_OBJS}%.o: %.c	${HEADERS}
				@mkdir -p ${shell dirname $@}
				${CC} ${CFLAGS} -c $< -o $@ -I ${DIR_HEADERS}

${NAME}:		${OBJS}
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
				${RM} ${OBJS} ${DIR_OBJS}

fclean:			clean
				${RM} ${NAME}

re :			fclean all

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