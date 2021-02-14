# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: astripeb <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/03 21:08:35 by astripeb          #+#    #+#              #
#    Updated: 2021/02/14 13:20:23 by astripeb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN 				:= \033[0;32m
RED 				:= \033[0;31m
RESET				:= \033[0m
BLINK				:= \033[5m
NORMAL				:= \033[25m
BOLDU				:= \033[1m\033[4m

NAME				:= ft_ssl

#COMPILER
CC 					:= gcc

#LIBFT
LIB_DIR				:= ./libft
LIBFT				:= libft.a

#PROJECT_DIRS
INC_DIR				:= ./inc
OBJ_DIR				:= ./.obj
SRC_DIR				:= ./src

#COMPILER FLAGS
CFLAGS				?= -Wall -Wextra -Werror -O3
LFLAGS				:= -I $(LIB_DIR)/includes -I $(INC_DIR)
LIB					:= -L $(LIB_DIR) -lft
DEPEND				:= -MD -MT


################################################################################
#									SOURCE FILES					 		   #
################################################################################

SRC					:= main.c ft_options.c ft_parse_params.c ft_process.c\
					ft_md5.c ft_md5_utils.c\
					ft_sha256.c ft_sha224.c ft_sha256_utils.c\
					ft_sha512.c ft_sha384.c ft_sha512_utils.c\
					ft_sha512_256.c ft_sha512_224.c\
					ft_utils.c ft_print_hash.c

################################################################################
#																	 		   #
################################################################################

OBJ					:= $(SRC:.c=.o)

vpath %.c $(SRC_DIR) $(SRC_DIR)/hash
vpath %.o $(OBJ_DIR)
vpath %.h $(INC_DIR)
vpath %.a $(LIB_DIR)

all: lib $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(LFLAGS) $(addprefix $(OBJ_DIR)/, $(OBJ)) -o $@ $(LIB)
	echo "$(GREEN)Creating $(BOLDU)$@$(RESET)"
	echo "$(GREEN)$(BLINK)DONE✅$(NORMAL)$(RESET)"

$(OBJ):%.o:%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(LFLAGS) -c $< -o $(OBJ_DIR)/$@ $(DEPEND) $@
	echo "$(GREEN)Creating $(BOLDU)$@$(RESET)"

lib:
	$(MAKE) -C $(LIB_DIR)

$(OBJ_DIR):
	mkdir -p $@

Debug:
	$(MAKE) CFLAGS="-g3"

clean:
	$(MAKE) clean -C $(LIB_DIR)
	rm -rf $(OBJ_DIR)
	echo "$(RED)Deleting $(BOLDU)objs files$(RESET)"

fclean: clean
	$(MAKE) fclean -C $(LIB_DIR)
	echo "$(RED)Deleting $(BOLDU)$(LIBFT)$(RESET)"
	rm -rf $(NAME)
	echo "$(RED)Deleting $(BOLDU)$(NAME)$(RESET)"

re: fclean all

include $(wildcard $(OBJ_DIR)/*.d)

.SILENT: all clean lib Debug re fclean $(NAME) $(OBJ) $(OBJ_DIR)

.PHONY: clean fclean re all Debug
