NAME = uchat

SRC_DIR = src

INC_DIR = inc
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
CC = clang
# CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic
LIBSPATH = libs

LIB_NAMES = json-c -pthread

LIB_PATH = $(LIBSPATH)/json-c/
RM = rm -rf

all: $(NAME) clean

$(NAME):
	@$(CC) `pkg-config --cflags gtk+-3.0` $(SRC_FILES) -I $(INC_DIR) -L$(LIB_PATH) -l$(LIB_NAMES) -o $(NAME) `pkg-config --libs gtk+-3.0`
	@printf "\r\33[2K$@\t \033[32;1mcreated\033[0m\n"

clean:
	@$(RM) $(OBJ_DIR)
	@printf "$(OBJ_DIR) in $(NAME)\t \033[31;1mdeleted\033[0m\n"

uninstall: clean
	@$(RM) $(NAME)
	@@printf "$(NAME)\t \033[31;1muninstalled\033[0m\n"

reinstall: uninstall all

.PHONY: all uninstall clean reinstall