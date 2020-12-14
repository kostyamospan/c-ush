NAME = libmx.a

SRC = src

OBJ = obj

INC = inc

FLAGS = -std=c11 #-Wall -Wextra -Werror -Wpedantic

all: uninstall install

install:
		@make -C ./libmx
		@mv ./libmx/libmx.a ./
		@mkdir ${OBJ}
		@clang $(FLAGS) -o ush $(SRC)/*.c -L. -lmx

uninstall: clean
		@rm -rf $(NAME)

clean:
		@rm -rf $(OBJ)

reinstall: all
