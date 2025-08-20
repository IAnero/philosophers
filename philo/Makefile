NAME = philo


SRCS = 	philo.c \
		errors_case/errors.c \
		utils/utils_nb_1.c \
		utils/utils_nb_2.c \
		utils/utils_nb_3.c \
		init/init_data_philo.c \
		init/init_data_routine.c \
		init/init_struct.c \
		program_engine/engine.c\
		program_engine/routine.c\
		program_engine/philo_create.c



OBJS = $(SRCS:.c=.o)

HDRS = /philosophers.h

CC = cc

RM = rm -rf

FLAG = -Wall -Werror -Wextra

.c.o:
	${CC} ${FLAG} -I ${HDRS} -c $< -o ${<:.c=.o}

$(NAME): $(OBJS)
		${CC} $(FLAG) -o $(NAME)  $(OBJS)  

all: $(NAME)

clean:
	${RM} $(OBJS)

fclean: clean
	${RM} $(NAME)

re: fclean all

run: all
	@./$(NAME) $(ARGS)

.PHONY: all clean fclean re run