# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rubsky <rubsky@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/15 16:58:54 by rpinchas          #+#    #+#              #
#    Updated: 2023/07/03 17:50:34 by rubsky           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#SETUP
NAME := minishell	
CFLAGS := -Werror -Wall -Wextra
CC := cc

#FILES
SRCDIR := src
SRC_F := main.c \

SRC := 	${addprefix ${SRCDIR}/, ${SRC_F}}
OBJDIR := obj
OBJ_F :=  ${SRC_F:%.c=%.o}
OBJ :=	${addprefix ${OBJDIR}/, ${OBJ_F}}

#COLORS
GREEN := \033[32m
BLUE := \033[34m
YELLOW := \033[33m
RED := \033[31m
RESET := \033[0m

#RULES
all: ${NAME}

${NAME}: ${OBJ}
	@echo "${YELLOW}Compiling...${RESET}"
	${CC} ${CFLAGS} -o $@ ${OBJ}
	@echo "${GREEN}Code ready to run${RESET}"

${OBJDIR}/%.o: ${SRCDIR}/%.c obj_check
	${CC} ${CFLAGS} -I. -c $< -o $@

obj_check: 
	@echo "${BLUE}Making object files...${RESET}"
	@mkdir -p ${OBJDIR}

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
