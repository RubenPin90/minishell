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
SRC_F = builtins.c \
		builtin_cd.c \
		builtin_echo.c \
		builtin_exit.c \
		builtin_export.c \
		builtin_pwd.c \
		builtin_unset.c \
		builtin_env.c \
		builtin_env_utils.c \
		error_handling.c \
		executor.c \
		exec_cmdfinder.c \
		exec_fds.c \
		exec_fd_utils.c \
		exec_heredoc.c \
		exec_utils.c \
		exec_exstatus.c \
		expander.c \
		expander_tokens.c \
		expander_utils.c \
		lexer.c \
		lexer_check_tokens.c \
		lexer_check_quotes.c \
		lexer_list_utils.c \
		lexer_utils.c \
		parser.c \
		signals.c \
		sys_env_create.c \
		sys_init.c \
		sys_input.c \
		sys_cleanup.c \
		sys_cleanup2.c \
		sys_utils.c 

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

#VALGRIND
SUP_FILE := rl_leaks.supp
VALGRIND := valgrind --leak-check=full --tool=memcheck \
			--track-origins=yes --show-leak-kinds=all \
			--suppressions=${SUP_FILE} --track-fds=yes
SUP_TEXT := "{\n \
    ignore_libreadline_leaks\n \
    Memcheck:Leak\n \
    ...\n \
    obj:*/libreadline.so.*\n \
}"

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
	@${MAKE} -sC ${LDIR_FT}

clean:
	@echo "${GREEN}Removing object files...${RESET}"
	@${MAKE} clean -sC ${LDIR_FT}
	@rm -f ${OBJ}
	@rm -rf ${OBJDIR}
	@echo "${BLUE}DONE!${RESET}"

fclean: clean
	@echo "${GREEN}Removing executables...${RESET}"
	@${MAKE} fclean -sC ${LDIR_FT}
	@rm	-rf ${NAME}
	@rm -rf ${SUP_FILE}
	@echo "${BLUE}DONE!${RESET}"

re: fclean all

test: ${OBJ} ${OBJ_T} ${OBJ_TM} ${LIB}
	@echo "${YELLOW}Compiling tests....${RESET}"
	${CC} ${CFLAGS} ${INC} ${OBJ} ${OBJ_T} ${OBJ_TM} ${LIBS} -o tester
	@echo "${GREEN}Code ready to run${RESET}"

mini: all
	@echo ${SUP_TEXT} > ${SUP_FILE}
	@-${VALGRIND} ./${NAME}
	@rm -rf ${SUP_FILE}

.PHONY: all clean fclean re test mini
