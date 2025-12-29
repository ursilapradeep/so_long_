NAME = so_long
CC = gcc
CFLAGS = -Wall -Wextra -Werror

INCLUDES = -Iincludes -I$(HOME)/.local/include -Ilibft
LDFLAGS = -L$(HOME)/.local/lib
LIBS = -lmlx42 -lglfw -lGL -ldl -lm -pthread

MLX42_DIR = MLX42

all: install_mlx42 $(LIBFT) $(NAME) 

install_mlx42:
	@if [ ! -d $(MLX42_DIR) ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git $(MLX42_DIR); \
	fi
	@cd $(MLX42_DIR) && cmake -B build -DCMAKE_INSTALL_PREFIX=$(HOME)/.local && cmake --build build -j && cmake --install build
	@echo "MLX42 installed to $(HOME)/.local"

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) $(LDFLAGS) $(LIBS) -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

run: $(NAME)
	LD_LIBRARY_PATH=$(HOME)/.local/lib:$$LD_LIBRARY_PATH ./$(NAME) $(MAP)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re run
