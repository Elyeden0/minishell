#Shell to use
SHELL = /bin/bash

# Compiler and flags
CC       = clang
CFLAGS   = -Wall -Wextra -Werror


# Colors for messages
ORANGE = $(shell tput setaf 202)
RED = $(shell tput setaf 1)
YELLOW = $(shell tput setaf 3)
BLUE = $(shell tput setaf 27)
GREEN = $(shell tput setaf 46)
RESET = $(shell tput sgr0)
BOX_TOP    = ╔══════════════════════╗
BOX_MIDDLE = ║                      ║
BOX_BOTTOM = ╚══════════════════════╝

# Directories
SRC_DIR = srcs
LEXER_PATH 		= $(SRC_DIR)/lexer
PARSER_PATH 	= $(SRC_DIR)/parser
EXTENDER_PATH 	= $(SRC_DIR)/extender
EXECUTION_PATH	= $(SRC_DIR)/execution
BUILTINS_PATH 	= $(SRC_DIR)/builtins
READLINE_PATH 	= $(SRC_DIR)/readline
AST_PATH 		= $(SRC_DIR)/ast
OBJ_DIR  = objs

# Libraries
LIBFT_DIR = lib/LibFT
LIBMALLOC_DIR = lib/LibMalloc
LIBPRINTF_DIR = lib/LibPrintf
LIBLST_DIR = lib/LibLst

LIBFT = $(LIBFT_DIR)/libft.a
LIBMALLOC = $(LIBMALLOC_DIR)/libmalloc.a
LIBPRINTF = $(LIBPRINTF_DIR)/libftprintf.a
LIBLST = $(LIBLST_DIR)/liblst.a
LIBS = $(LIBFT) $(LIBLST) $(LIBMALLOC) $(LIBPRINTF)

# Includes
INCLUDE = -Iinclude -I$(LIBFT_DIR) -I$(LIBMALLOC_DIR) -I$(LIBLST_DIR) -I$(LIBPRINTF_DIR)
# BONUS_INCLUDES = -Ibonus_include -I$(LIBFT_DIR)

# Source files and object files
SRCS 	 =	$(SRC_DIR)/main.c \
			$(addprefix $(EXTENDER_PATH)/, expand.c expand_utils.c expand_wildcard.c expand_wildcard_utils.c init_env.c init_env_utils.c) \
			$(addprefix $(BUILTINS_PATH)/, b_cd.c b_cd2.c b_echo.c b_env.c b_exit.c b_export.c b_export_utils.c b_pwd.c) \
			$(addprefix $(LEXER_PATH)/, lexer.c lexer_utils.c lexer_handler.c lexer_handler_utils.c) \
			$(addprefix $(PARSER_PATH)/, input_check_paren.c input_error_parser.c input_error_tokenizer.c input_error_utils.c input_error.c) \
			$(addprefix $(EXECUTION_PATH)/, exec_builtin.c exec_cmds.c exec_heredoc.c exec_pipe.c exec_redirect.c exec.c) \
			$(addprefix $(READLINE_PATH)/, rd_edit.c rd_history.c rd_history_2.c rd_readline.c rd_reset.c rd_signal.c rd_term.c) \
			$(addprefix $(AST_PATH)/, ast_builders.c ast_parser_utils.c ast_parser.c)
# BONUS_SRCS = $(BONUS_DIR)/

OBJS     = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(filter %.c,$(SRCS)))

# BONUS_OBJS = $(BONUS_SRCS:$(BONUS_DIR)/%.c=$(OBJ_DIR)/%.o)

# Output executable
NAME     = minishell
# BONUS_NAME = minishell_bonus

# Rules
all: $(NAME)

# Make bonus version
# bonus: $(LIBFT) $(BONUS_NAME)

# Compile libs if not already compiled

$(LIBMALLOC):
	@echo -e "$(YELLOW)Compiling LibMalloc...$(RESET)"
	@$(MAKE) -C $(LIBMALLOC_DIR) > /dev/null

$(LIBPRINTF):
	@echo -e "$(YELLOW)Compiling LibPrintf...$(RESET)"
	@$(MAKE) -C $(LIBPRINTF_DIR) > /dev/null

$(LIBFT): $(LIBMALLOC)
	@echo -e "$(YELLOW)Compiling LibFT...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) > /dev/null

$(LIBLST): $(LIBMALLOC)
	@echo -e "$(YELLOW)Compiling LibLst...$(RESET)"
	@$(MAKE) -C $(LIBLST_DIR) > /dev/null

# Create object directory if it doesn't exist
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR) # Only need the top-level obj dir here

# Compile object files
# This pattern rule handles all .c files within the SRC_DIR structure and places .o files in OBJ_DIR mirroring the structure
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR) # Depends on the top-level dir existing
	@mkdir -p $(@D) # Ensure the specific target directory exists before compiling
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

# Link the executable
$(NAME): $(OBJS) $(LIBFT) $(LIBLST) $(LIBMALLOC) $(LIBPRINTF)
	@echo -e "$(BLUE)Linking the project...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) -L$(LIBFT_DIR) -lft -L$(LIBLST_DIR) -llst -L$(LIBMALLOC_DIR) -lmalloc -L$(LIBPRINTF_DIR) -lftprintf -o $(NAME)
	@echo "$(GREEN)$(BOX_TOP)"
	@echo "$(GREEN)║ Executable compiled. ║$(RESET)"
	@echo "$(GREEN)$(BOX_BOTTOM)$(RESET)"
	@echo "$(YELLOW) 		⠀⠀⠀⢸⣦⡀⠀⠀⠀⠀⢀⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "		⠀⠀⠀⢸⣏⠻⣶⣤⡶⢾⡿⠁⠀⢠⣄⡀⢀⣴⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀		"
	@echo "		 ⠀⣀⣼⠷⠀⠀⠁⢀⣿⠃⠀⠀⢀⣿⣿⣿⣇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀		"
	@echo "		⠴⣾⣯⣅⣀⠀⠀⠀⠈⢻⣦⡀⠒⠻⠿⣿⡿⠿⠓⠂⠀⠀⢀⡇⠀⠀⠀⠀⠀⠀⠀		"
	@echo "		⠀⠀⠀⠉⢻⡇⣤⣾⣿⣷⣿⣿⣤⠀⠀⣿⠁⠀⠀⠀⢀⣴⣿⣿⠀⠀⠀⠀⠀⠀⠀		"
	@echo "		⠀⠀⠀⠀⠸⣿⡿⠏⠀⢀⠀⠀⠿⣶⣤⣤⣤⣄⣀⣴⣿⡿⢻⣿⡆⠀⠀⠀⠀⠀⠀		"
	@echo "		⠀⠀⠀⠀⠀⠟⠁⠀⢀⣼⠀⠀⠀⠹⣿⣟⠿⠿⠿⡿⠋⠀⠘⣿⣇⠀⠀⠀⠀⠀⠀		"
	@echo "		⠀⠀⠀⠀⠀⢳⣶⣶⣿⣿⣇⣀⠀⠀⠙⣿⣆⠀⠀⠀⠀⠀⠀⠛⠿⣿⣦⣤⣀⠀⠀		"
	@echo "		⠀⠀⠀⠀⠀⠀⣹⣿⣿⣿⣿⠿⠋⠁⠀⣹⣿⠳⠀⠀⠀⠀⠀⠀⢀⣠⣽⣿⡿⠟⠃		"
	@echo "		⠀⠀⠀⠀⠀⢰⠿⠛⠻⢿⡇⠀⠀⠀⣰⣿⠏⠀⠀⢀⠀⠀⠀⣾⣿⠟⠋⠁⠀⠀⠀		"
	@echo "		⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠋⠀⠀⣰⣿⣿⣾⣿⠿⢿⣷⣀⢀⣿⡇⠁⠀⠀⠀⠀⠀		"
	@echo "		⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠋⠉⠁⠀⠀⠀⠀⠙⢿⣿⣿⠇⠀⠀⠀⠀⠀⠀		"
	@echo "		⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⢿⠀⠀⠀⠀⠀⠀⠀		"
	@echo "		⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠀⠀⠀⠀⠀⠀⠀		$(RESET)"
	@echo "$(GREEN)   _____ _          _ _     _______        _   _      ";
	@echo "  / ____| |        | | |   |__   __|      | | (_)     ";
	@echo " | (___ | |__   ___| | |______| | __ _ ___| |_ _  ___ ";
	@echo "  \___ \| '_ \ / _ | | |______| |/ _\` / __| __| |/ __|";
	@echo "  ____) | | | |  __| | |      | | (_| \__ | |_| | (__ ";
	@echo " |_____/|_| |_|\___|_|_|      |_|\__,_|___/\__|_|\___|";
	@echo "                                                      ";
	@echo "                                                      ";


# $(BONUS_NAME): $(BONUS_OBJS) $(LIBFT)
# 	@$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBS) -o $(BONUS_NAME)

# Clean object files
clean:
	@echo -e "$(ORANGE)Cleaning object files...$(RESET)"
	@$(MAKE) clean -s -C $(LIBFT_DIR)
	@$(MAKE) clean -s -C $(LIBLST_DIR)
	@$(MAKE) clean -s -C $(LIBMALLOC_DIR)
	@$(MAKE) clean -s -C $(LIBPRINTF_DIR)
	@rm -rf $(OBJ_DIR)
	@echo "$(ORANGE)Object files cleaned.$(RESET)"

# Clean object files and executable
fclean: clean
	@echo -e "$(ORANGE)Removing executables...$(RESET)"
	@$(MAKE) fclean -s -C $(LIBFT_DIR)
	@$(MAKE) fclean -s -C $(LIBLST_DIR)
	@$(MAKE) fclean -s -C $(LIBMALLOC_DIR)
	@$(MAKE) fclean -s -C $(LIBPRINTF_DIR)
	@rm -f $(NAME) $(BONUS_NAME)
	@echo "$(GREEN)Full clean done.$(RESET)"

# Rebuild
re: fclean all
# rebonus: fclean bonus
.PHONY: all clean fclean re

