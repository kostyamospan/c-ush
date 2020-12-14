# .PHONY: all libmx uninstall clean reinstall

# SRCS := $(wildcard *.c)
# HDRS := $(wildcard inc/*.h)

# all: libmx

# libmx:
# 	@clang -std=c11 -Wall -Wextra -Werror -Wpedantic -o main ${SRCS}
# 	@mkdir obj
# 	@mv *.o obj
# 	@ar -rc main obj/*.o
# 	@ranlib libmx.a

# uninstall: clean
# 	@rm -f libmx.a

# clean:
# 	@rm -f inc/*.gch
# 	@rm -rdf obj

# reinstall: uninstall libmx


NAME = libmx.a


OBJ = obj

INC = inc

SRCS = src/*.c

FLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

all: install clean

install:
		@clang $(FLAGS) -I $(INC) -c $(SRCS)
		@mkdir -p $(OBJ)
		@mv *.o $(OBJ)
		@ar -rc $(NAME) $(OBJ)/*.o
		@ranlib $(NAME)
		@rm -rf *.o

uninstall: clean
		@rm -rf $(NAME)

clean:
		@rm -rf $(OBJ)

reinstall: all
