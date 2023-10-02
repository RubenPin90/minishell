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
SRC_F = builtin.c \
		builtin_cd.c \
		builtin_echo.c \
		builtin_exit.c \
		builtin_export.c \
		builtin_pwd.c \
		builtin_unset.c \
		env_create.c \
		env_utils.c \
		error_handling.c \
		executor.c \
		exec_cmdfinder.c \
		exec_fds.c \
		exec_fd_utils.c \
		exec_heredoc.c \
		expander.c \
		expander_utils.c \
		lexer.c \
		lexer_checks.c \
		lexer_list_utils.c \
		lexer_utils.c \
		signals.c \
		sys_cleanup.c \
		sys_init.c \
		sys_input.c \
		sys_utils.c \
		parser.c \
		parser_utils.c \

#OBJ FILES
OBJ_F = ${SRC_F:%.c=%.o}
OBJ_M = ${OBJDIR}/main.o
OBJDIR := obj
OBJ = ${addprefix ${OBJDIR}/, ${OBJ_F}}

#TEST FILES
TESTDIR		=	tests
TEST_SRC	=	test_parser.c \
				test_lexer.c \
				test_expander.c
TEST_F = ${TEST_SRC:%.c=%.o}
OBJ_TM = ${OBJ_TDIR}/testmain.o
OBJ_TDIR = obj_test
OBJ_T = ${addprefix ${OBJ_TDIR}/, ${TEST_F}}

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

${NAME}: ${OBJ} ${OBJ_M}
	@echo "${YELLOW}Compiling...${RESET}"
	${CC} ${CFLAGS} ${INC} ${OBJ} ${OBJ_M} ${LIBS} -o $@ 
	@echo "${GREEN}Code ready to run${RESET}"

${OBJDIR}/%.o: ${SRCDIR}/%.c
	@mkdir -p ${OBJDIR}
	${CC} ${CFLAGS} ${INC} -c $< -o $@
	
${OBJ_TDIR}/%.o: ${TESTDIR}/%.c
	@mkdir -p ${OBJ_TDIR}
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

test: ${OBJ} ${OBJ_T} ${OBJ_TM} ${LIB}
	@echo "${YELLOW}Compiling tests....${RESET}"
	${CC} ${CFLAGS} ${INC} ${OBJ} ${OBJ_T} ${OBJ_TM} ${LIBS} -o tester
	@echo "${GREEN}Code ready to run${RESET}"

.PHONY: all clean fclean  debug tebug re
