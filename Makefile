# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asekmani <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/18 17:21:09 by asekmani          #+#    #+#              #
#    Updated: 2022/12/01 12:18:11 by asekmani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= philo

SRCS= 	main.c \
		init.c \
		error_cases.c \
		simulation.c \
		

SRCSBO=	
		

INC_DIR= ./

OBJS= ${SRCS:.c=.o}

OBJS2 = ${SRCSBO:.c=.o}

CC=	cc
FLAGS=	-Wall -Wextra -Werror -g3
RM=	rm -f

all: $(NAME)

${NAME}: ${OBJS}
	$(CC) $(FLAGS) $(OBJS) -o ${NAME}

bonus:  ${OBJS2}
	$(CC) $(FLAGS) $(OBJS2) -o philo_bonus

AR= ar rcs

%.o: %.c 
	${CC} ${FLAGS} -MMD -MP -c $< -o $@

clean:
	${RM} ${OBJS} ${OBJS2}

fclean: clean
	${RM} ${NAME} *.d
	${RM} ${NAME} philo_bonus

re: fclean all


.PHONY: all clean fclean re bonus
