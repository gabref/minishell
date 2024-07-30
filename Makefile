# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/03 10:00:31 by galves-f          #+#    #+#              #
#    Updated: 2024/07/30 00:51:06 by galves-f         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                                     CONFIG                                   #
################################################################################


NAME	= minishell
CC 		= cc
CFLAGS	= -Wall -Werror -Wextra -ggdb
LDFLAGS = -lreadline
AUTHOR	= galves-f
DATE	= 2024/01/24

NOVISU 	= 0 # 1 = no progress bar usefull when tty is not available

################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

FILE_EXTENSION	= .c

SRCS_PATH		= src

INCLUDE_PATH	= inc

SRCS 			= initializer/init.c \
				  initializer/envs.c \
				  initializer/envs_utils.c \
				  initializer/history.c \
				  input/input.c \
				  signals/signals.c \
				  parser/parser.c \
				  utils/safe_functions.c \
				  utils/prints.c \
				  utils/globals.c \
  				  lexer/lexer.c \
  				  expander/expander.c \
  				  executor/executor.c \

# MAIN			= main.c
MAIN			= ../tests/parser/main.c

LIBS_DIR 		= libs
LIBFT_DIR 		= $(LIBS_DIR)/libft
PRINTF_DIR 		= $(LIBS_DIR)/ft_printf

################################################################################
#                                  Makefile  objs                              #
################################################################################

SHELL := /bin/bash


OBJS				= $(addprefix objs/, ${SRCS:$(FILE_EXTENSION)=.o})
OBJ_MAIN			= $(addprefix objs/, ${MAIN:$(FILE_EXTENSION)=.o})
DEPS				= $(addprefix objs/, ${SRCS:$(FILE_EXTENSION)=.d})
DEPS_MAIN			= $(addprefix objs/, ${MAIN:$(FILE_EXTENSION)=.d})

OBJS_B				= $(addprefix objs/, ${SRCS_B:$(FILE_EXTENSION)=.o})
OBJ_MAIN_B			= $(addprefix objs/, ${MAIN_B:$(FILE_EXTENSION)=.o})
DEPS_B				= $(addprefix objs/, ${SRCS_B:$(FILE_EXTENSION)=.d})
DEPS_MAIN_B			= $(addprefix objs/, ${MAIN_B:$(FILE_EXTENSION)=.d})

################################################################################
#                                Makefile testing                              #
################################################################################

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))
TEST = tests
# TESTS = $(call rwildcard, $(TEST), *.c)
TESTS = $(wildcard $(TEST)/*.c)
TESTS_BINS = $(patsubst $(TEST)/%.c, $(TEST)/bin/%, $(TESTS))

################################################################################
#                                 Makefile logic                               #
################################################################################

COM_COLOR   = \033[0;34m
OBJ_COLOR   = \033[0;36m
OK_COLOR    = \033[0;32m
ERROR_COLOR = \033[0;31m
WARN_COLOR  = \033[0;33m
NO_COLOR    = \033[m

COM_STRING   = "compiling"

HASH	= 

ifeq ($(OS),Windows_NT) 
    detected_OS := Windows
else
    detected_OS := $(shell sh -c 'uname 2>/dev/null || echo Unknown')
endif

ifeq ($(detected_OS),Darwin) 
	RUN_CMD = script -q $@.log $1 > /dev/null; \
				RESULT=$$?
else ifeq ($(detected_OS),Linux)
	RUN_CMD = script -q -e -c "$(1)" $@.log > /dev/null; \
				RESULT=$$?; \
				sed -i '1d' $@.log; \
				sed -i "$$(($$(wc -l < $@.log)-1)),\$$d" $@.log
else
	RUN_CMD = $(1) 2> $@.log; \
				RESULT=$$?
endif

ifeq ($(shell git rev-parse HEAD &>/dev/null; echo $$?),0)
	AUTHOR	:= $(shell git log --format='%aN' | sort -u | awk '{printf "%s, ", $$0}' | rev | cut -c 3- | rev)
	DATE	:= $(shell git log -1 --date=format:"%Y/%m/%d %T" --format="%ad")
	HASH	:= $(shell git rev-parse --short HEAD)
endif

# Progress vars
SRC_COUNT_TOT := $(shell expr $(shell echo -n $(SRCS) | wc -w) - $(shell ls -l objs 2>&1 | grep ".o" | wc -l) + 1)
ifeq ($(shell test $(SRC_COUNT_TOT) -lt 0; echo $$?),0)
	SRC_COUNT_TOT := $(shell echo -n $(SRCS) | wc -w)
endif
SRC_COUNT := 0
SRC_PCT = $(shell expr 100 \* $(SRC_COUNT) / $(SRC_COUNT_TOT))

MAKEFLAGS += --no-print-directory

################################################################################
#                                 Makefile rules                             #
################################################################################

all: header $(NAME)
	@rm -rf .files_changed

header:
	@printf "%b" "$(OK_COLOR)"
	@echo "        ___  _____ ___  ___      _        "
	@echo "       /   |/ __  \|  \/  |     | |       "
	@echo "      / /| |\`' / /'| .  . | __ _| | _____ "
	@echo "     / /_| |  / /  | |\/| |/ _\` | |/ / _ \\"
	@echo "     \___  |./ /___| |  | | (_| |   <  __/"
	@echo "         |_/\_____/\_|  |_/\__,_|_|\_\___| v2"
	@echo
	@echo "OS : $(detected_OS)"
ifneq ($(HASH),)
	@printf "%b" "$(OBJ_COLOR)Name:	$(WARN_COLOR)$(NAME)@$(HASH)\n"
else
	@printf "%b" "$(OBJ_COLOR)Name:	$(WARN_COLOR)$(NAME)\n"
endif
	@printf "%b" "$(OBJ_COLOR)Author:	$(WARN_COLOR)$(AUTHOR)\n"
	@printf "%b" "$(OBJ_COLOR)Date: 	$(WARN_COLOR)$(DATE)\n\033[m"
	@printf "%b" "$(OBJ_COLOR)CC: 	$(WARN_COLOR)$(CC)\n\033[m"
	@printf "%b" "$(OBJ_COLOR)Flags: 	$(WARN_COLOR)$(CFLAGS)\n\033[m"
	@echo


$(NAME):	install_libs ${OBJS} ${OBJ_MAIN}
			@make all -C $(LIBFT_DIR)
			@make all -C $(PRINTF_DIR)
			@$(CC) $(CFLAGS) -I$(INCLUDE_PATH) -o $@ ${OBJS} ${OBJ_MAIN} \
			-L$(LIBFT_DIR) -L$(PRINTF_DIR) -lft -lftprintf $(LDFLAGS) 

objs/%.o: 	$(SRCS_PATH)/%$(FILE_EXTENSION)
			@mkdir -p $(dir $@)
			@$(eval SRC_COUNT = $(shell expr $(SRC_COUNT) + 1))
			@printf "\r%100s\r[ %d/%d (%d%%) ] Compiling $(BLUE)$<$(DEFAULT)..." "" $(SRC_COUNT) $(SRC_COUNT_TOT) $(SRC_PCT)
			@$(CC) $(CFLAGS) -c $< -o $@ -I$(INCLUDE_PATH)

clean:		header
			@rm -rf objs objs_tests
			@make clean -C $(LIBFT_DIR)
			@make clean -C $(PRINTF_DIR)
			@printf "%-53b%b" "$(COM_COLOR)clean:" "$(OK_COLOR)[✓]$(NO_COLOR)\n"

fclean:		header clean
			@rm -rf $(NAME)
			@make fclean -C $(LIBFT_DIR)
			@make fclean -C $(PRINTF_DIR)
			@printf "%-53b%b" "$(COM_COLOR)fclean:" "$(OK_COLOR)[✓]$(NO_COLOR)\n"

re:	fclean 
	@make all

norminette:
	@printf "$(CYAN)\nChecking norm for libft...$(DEFAULT)\n"
	@norminette -R CheckForbiddenSourceHeader $(SRCS_PATH) $(INCLUDE_PATH) | nform

install_libs: $(LIBS_DIR)
	@$(MAKE) $(LIBFT_DIR)
	@$(MAKE) $(PRINTF_DIR)

valgrind: all
	@valgrind --leak-check=full --show-leak-kinds=all -s --track-origins=yes --suppressions=.ignore_readline_leaks.supp ./$(NAME)

$(LIBS_DIR):
	@mkdir -p $(LIBS_DIR)

$(LIBFT_DIR):
	@git clone https://github.com/gabref/libft.git $(LIBFT_DIR)

$(PRINTF_DIR):
	@git clone https://github.com/gabref/printf.git $(PRINTF_DIR)

$(TEST)/bin/%: $(TEST)/%.c
	@$(CC) $(CFLAGS) -I$(INCLUDE_PATH) -o $@ $< $(OBJS) \
	-L$(LIBFT_DIR) -L$(PRINTF_DIR) -lft -lftprintf -lcriterion $(LDFLAGS)

$(TEST)/bin:
	@mkdir $@

test: install_libs $(OBJS) $(TEST)/bin $(TESTS_BINS)
	@for test in $(TESTS_BINS); do \
		./$$test --verbose; \
	done

.PHONY:		all clean fclean re header norminette
