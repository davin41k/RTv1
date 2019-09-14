#-------------------------- Key Values ---------------------------------------
NAME		:=	RTv1
CFLAGS		:=	-g#-Wall -Werror -Wextra -g
CC			:=	gcc

DIR_INC		:=	includes/
DIR_SRC		:=	srcs/
DIR_OBJ		:=	objs/
CH_SRC		:=	c
CH_OBJ		:=	o

DIR_LIB		:=	libft/
DIR_LIB_INC	:=	$(DIR_LIB)

DIR_SDL_INC	:=	./frameworks/SDL2.framework/Headers/

LIBFT		:=	$(DIR_LIB)libft.a
SDL			:=	-F ./frameworks/ -framework SDL2

#-------------------------- Paths --------------------------------------------



#-------------------------- Header files -------------------------------------
COR_H		:=	$(DIR_INC)rtv1.h

#-------------------------- Source files -------------------------------------
COR_C		:=	$(DIR_SRC)draw_three.c\
				$(DIR_SRC)lightning.c\
				$(DIR_SRC)more_draw_func.c\
				$(DIR_SRC)exits_func.c\
				$(DIR_SRC)figure_factory.c\
				$(DIR_SRC)scene_reader.c\
				$(DIR_SRC)init_functions.c\
				$(DIR_SRC)intersec_basic.c\
				$(DIR_SRC)intersec_ray_cylin_and_cone.c\
				$(DIR_SRC)draw_one.c\
				$(DIR_SRC)main.c\
				$(DIR_SRC)scene_reader_two.c\
				$(DIR_SRC)scene_reader_three.c\
				$(DIR_SRC)camera_movement.c\
				$(DIR_SRC)work_with_textures.c\

#-------------------------- Init OBJ, INC ------------------------------------
OBJ			:=	$(patsubst $(DIR_SRC)%,$(DIR_OBJ)%,\
				$(COR_C:.$(CH_SRC)=.$(CH_OBJ)))

INC			:=	$(addprefix -I, $(DIR_LIB_INC) $(DIR_INC) $(DIR_SDL_INC))

#-------------------------- Make ---------------------------------------------
all: lib $(DIR_OBJ) $(NAME)

lib:
	@make -C $(DIR_LIB) > /dev/null

$(DIR_OBJ):
	@mkdir -p $(DIR_OBJ)

#-------------------------- Link Block ---------------------------------------
$(NAME): $(OBJ) $(LIBFT)
	@$(CC) -o $(NAME) $(OBJ) $(SDL) $(LIBFT)
	@echo "Linking" [ $(NAME) ]

#-------------------------- Compil Block -------------------------------------
#COR
$(DIR_OBJ)%.$(CH_OBJ): $(DIR_SRC)%.$(CH_SRC)\
$(COR_H)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -c -o $@ $<
	@echo "Compiling" [ $< ]

#-------------------------- Clean --------------------------------------------
clean:
	@make -C $(DIR_LIB) clean
	@rm -rf $(DIR_OBJ)
	@echo "Clean [ obj files $(NAME) ]"

fclean:
	@make -C $(DIR_LIB) fclean
	@rm -rf $(DIR_OBJ)
	@echo "Clean [ obj files $(NAME) ]"
	@rm -f $(NAME)
	@echo "Clean" [ $(NAME) ]

re: fclean all

.PHONY: all clean fclean re
