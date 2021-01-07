

SRC_DIR = src

INC_DIR = inc

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
CC = clang
NCURSESLIB = -lncurses

CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

RM = rm -rf

all: $(NAME) clean client server

$(NAME): client server

client:
	@clang -o client clientSource/*.c -I $(INC_DIR)
	@printf "\r\33[2K$@\t \033[32;1mcreated\033[0m\n"

server:
	@clang -o server -I/Users/vdovgotko/.brew/Cellar/mysql/8.0.22_1/include -I $(INC_DIR) -W -lmysqlclient -L/Users/vdovgotko/.brew/Cellar/mysql/8.0.22_1/lib serverSource/*.c
	@printf "\r\33[2K$@\t \033[32;1mcreated\033[0m\n"

clean:
	@$(RM) $(OBJ_DIR)
	@printf "$(OBJ_DIR) in $(NAME)\t \033[31;1mdeleted\033[0m\n"

uninstall: clean
	@$(RM) client
	@$(RM) server
	@@printf "client and server\t \033[31;1muninstalled\033[0m\n"

reinstall: uninstall all

.PHONY: all uninstall clean reinstall