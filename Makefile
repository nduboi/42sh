##
## EPITECH PROJECT, 2023
## alban
## File description:
## Makefile
##

MAIN	=	src/main.c

SRC	=	src/builtins/display_all_alias.c \
		src/builtins/display_alias.c \
		src/builtins/my_unsetenv.c \
		src/builtins/my_history.c \
		src/builtins/my_unalias.c \
		src/builtins/my_setenv.c \
		src/builtins/add_alias.c \
		src/builtins/my_alias.c \
		src/builtins/my_echo.c \
		src/builtins/my_exit.c \
		src/builtins/my_env.c \
		src/builtins/my_cd.c \
		src/tools/only_char_in_str.c \
		src/tools/chained_lists.c \
		src/tools/my_strsignal.c \
		src/tools/string_fcts.c	\
		src/tools/my_realloc.c \
		src/tools/my_strcpy.c \
		src/tools/my_strdup.c \
		src/tools/my_strcat.c \
		src/tools/my_memset.c \
		src/tools/my_malloc.c \
		src/tools/my_strstr.c \
		src/tools/num_fcts.c \
		src/tools/count_char.c \
		src/tools/my_strcat_s.c \
		src/tools/delete_char.c \
		src/handle_ambigous_redirect.c	\
		src/check_if_is_an_alias.c \
		src/handle_redirections.c \
		src/exclamation_mark.c \
		src/error_messages.c \
		src/errors_in_cmds.c \
		src/write_prompt.c \
		src/input_errors.c \
		src/handle_input.c \
		src/add_history.c \
		src/exit_status.c \
		src/parse_input.c \
		src/destroy_all.c \
		src/handle_cmd.c \
		src/handle_fd.c	\
		src/exe_com.c \
		src/my_sh.c

TEST_SRC	=	tests/test_chained_lists.c \
				tests/test_my_strcpy.c \
				tests/test_my_strdup.c \
				tests/test_num_fcts.c \
				tests/test_string_fcts.c \
				tests/test_error_messages.c \
				tests/test_my_strsignal.c \
				tests/test_my_strstr.c	\
				tests/test_history.c	\
				tests/test_my_cd.c	\
				tests/test_my_echo.c	\
				tests/test_my_env.c	\
				tests/test_my_setenv.c	\
				tests/test_my_unsetenv.c	\
				tests/test_count_char.c	\
				tests/test_my_exit.c \
				tests/test_parse_input.c

SRC_OBJ	=	$(SRC:%.c=%.o)

MAIN_OBJ	=	$(MAIN:%.c=%.o)

TEST_OBJ	=	$(TEST_SRC:%.c=%.o)

OBJ	=	$(SRC_OBJ) $(MAIN_OBJ)

NAME	=	42sh

TEST_NAME	=	unit_tests

C_STYLE	=	coding-style-reports.log

TEST_FLAGS	=	--coverage -lcriterion

INCLUDE	=	-I ./include

CFLAGS	+=	$(INCLUDE) -Wall -Wextra -Werror

DEBUG	=	-g

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) $(CFLAGS)

debug:	$(OBJ)
	gcc -o $(NAME) $(OBJ) $(CFLAGS) $(DEBUG)

clean:
	rm -rf $(OBJ)
	rm -rf $(TEST_OBJ)
	rm -rf *.gcno
	rm -rf *.gcda

fclean:	clean
	rm -rf $(NAME)
	rm -rf $(TEST_NAME)
	rm -rf $(C_STYLE)

re:	fclean all

unit_tests: $(SRC) $(TEST_SRC)
	gcc -o $(TEST_NAME) $(SRC) $(TEST_SRC) $(CFLAGS) $(TEST_FLAGS)

tests_run: unit_tests
	./$(TEST_NAME)

tester: all
	./tester.sh
	rm -rf noa*
	rm -rf salut

coverage: tests_run
	gcovr --exclude tests/
	gcovr --exclude tests/ --branches

sandwich: re
	make clean
	clear

code_line:
	find ./src -name '*.c' | xargs wc -l

.PHONY	=	all clean fclean sandwich coverage code_line tester
