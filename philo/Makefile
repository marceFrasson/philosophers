# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/31 18:38:37 by mfrasson          #+#    #+#              #
#    Updated: 2022/11/01 22:35:08 by mfrasson         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR	=	./source
SRC			=	actions.c \
					end_simulation.c \
					philo.c \
					start_simulation.c \
					utils.c

OBJ_DIR	=	./builds
OBJ			=	$(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

INCD_DIR	=	./includes
INCD			=	philo.h

vpath %.c $(SRC_DIR)
vpath %.h $(INCD_DIR)

NAME	=	philo

CFLAGS	=	-Wall -Wextra -Werror -g3 

#-fsanitize=thread

FLAGS	=	-pthread

RM		=	rm -rf

CC		=	clang

all:			$(NAME)

$(NAME):	$(OBJ)
	@ $(VALGRIND) $(CC) $(CFLAGS) $(FLAGS)$(OBJ) -I $(INCD_DIR) -o $(NAME)

	@echo ""
	@echo ""
	@echo "|		philosophers created		|"
	@echo ""
	@echo ""

$(OBJ_DIR)/%.o:	%.c $(INCD)
	@mkdir -p $(OBJ_DIR)
	@$(CC) -c -o $@ $(CFLAGS) -I $(INCD_DIR) $<

clean:
	@$(RM) $(OBJ_DIR)

	@echo ""
	@echo ""
	@echo "|		philosophers deleted		|"
	@echo ""
	@echo ""

fclean:		clean
	@$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
