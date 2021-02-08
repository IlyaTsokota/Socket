

SRC_DIR = src

INC_DIR = inc

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
CC = clang

LIBSDIR = libs

LIBS = -ljson-c -lmysqlclient

LIBS_PATH = -L$(LIBSDIR)/json-c/ -L$(LIBSDIR)/mysql/

CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

RM = rm -rf

all: $(NAME) clean  server

$(NAME): server

# client:
# 	@clang -o client clientSource/*.c -I $(INC_DIR)
# 	@printf "\r\33[2K$@\t \033[32;1mcreated\033[0m\n"

server:
	@clang -o server -I $(INC_DIR) `pkg-config --cflags --libs gmodule-2.0` -W $(LIBS_PATH) $(LIBS) serverSource/*.c
	@printf "\r\33[2K$@\t \033[32;1mcreated\033[0m\n"

clean:
	@$(RM) $(OBJ_DIR)
	@printf "$(OBJ_DIR) in $(NAME)\t \033[31;1mdeleted\033[0m\n"

uninstall: clean
	@$(RM) server
	@@printf "server\t \033[31;1muninstalled\033[0m\n"

reinstall: uninstall all

.PHONY: all uninstall clean reinstall