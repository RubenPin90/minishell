# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpinchas <rpinchas@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/15 16:58:54 by rpinchas          #+#    #+#              #
#    Updated: 2023/07/17 19:16:02 by rpinchas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#SETUP
NAME := minishell	
CFLAGS := -Werror -Wall -Wextra -g
CC := cc

#COLORS
GREEN := \033[32m
BLUE := \033[34m
YELLOW := \033[33m
RED := \033[31m
RESET := \033[0m

#FILES
SRCDIR := src
SRC_F := main.c \
		signals.c \
		env.c \
		input.c \
		lexer.c \
		buildins.c

#OBJ FILES
OBJ_F :=  ${SRC_F:%.c=%.o}
OBJDIR := obj
OBJ :=	${addprefix ${OBJDIR}/, ${OBJ_F}}

#LIBRARIES
##Directories
LDIR := lib
LDIR_FT := ${LDIR}/libft
LIB := ${LDIR_FT}/libft.a

##Linking Libraries
INC := -I./inc -I./${LDIR_FT} -I/usr/include
LIBFT := -L./${LDIR_FT} -lft
LIB_RL := -L/usr/lib -lreadline
LIBS := ${LIBFT} ${LIB_RL}

#RULES
all: ${LIB} ${NAME}

${NAME}: ${OBJ}
	@echo "${YELLOW}Compiling...${RESET}"
	${CC} ${CFLAGS} ${INC} ${OBJ} ${LIBS} -o $@
	@echo "${GREEN}Code ready to run${RESET}"

${OBJDIR}/%.o: ${SRCDIR}/%.c
	@mkdir -p ${OBJDIR}
	${CC} ${CFLAGS} ${INC} -c $< -o $@
	
${LIB}:
	@make -sC ${LDIR_FT}

clean:
	@echo "${GREEN}Removing object files...${RESET}"
	@rm -f ${OBJ}
	@rm -rf ${OBJDIR}
	@echo "${BLUE}DONE!${RESET}"

fclean: clean
	@echo "${GREEN}Removing executables...${RESET}"
	@rm	-rf ${NAME}
	@echo "${BLUE}DONE!${RESET}"

re: fclean all

.PHONY: all clean fclean  debug tebug re
