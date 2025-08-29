NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread
RM = rm -rf

SRCS =	$(wildcard $(SRCDIR)/*.c)

OBJS = $(SRCS:$(SRCDIR)%.c=$(OBJDIR)%.o)
SRCDIR = ./src/
OBJDIR = obj/

all : $(OBJDIR) $(NAME) 

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "--->$(YELLOW)Compiling program.$(DEF_COLOR)"
	@sleep 1
	@echo "--->$(YELLOW)Creating Objects.$(DEF_COLOR)"
	@sleep 0.2
	@echo "--->$(GREEN)Program compiled.$(DEF_COLOR)"
	@echo "$(WHITE) ⠀⠀⠀⠀⠀⢀ ⠀⠀⠀⠀⠀⢠⡆⠀⠀⠀⠀⠀⠀⡀          "
	@echo "$(WHITE)⠀⠀⠀⠀⠀⠀⠈⣷⣄⠀⠀⠀⠀⣾⣷⠀⠀⠀⠀⣠⣾⠃⠀⠀⠀⠀⠀⠀⠀⠀$(DEF_COLOR)"
	@echo "$(WHITE)⠀⠀⠀⠀⠀⠀⠀⢿⠿⠃⠀⠀⠀⠉⠉⠁⠀⠀⠐⠿⡿⠀⠀⠀⠀⠀⠀⠀⠀⠀$(DEF_COLOR)"
	@echo "$(WHITE)⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣠⣤⣤⣶⣶⣶⣤⣤⣄⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀$(DEF_COLOR)"
	@echo "$(WHITE)⠀⠀⠀⠀⠀⢀⣤⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣦⣄⠀⠀⠀⠀⠀⠀$(DEF_COLOR)"
	@echo "$(WHITE)⠀⠀⠀⣠⣶⣿⣿⡿⣿⣿⣿⡿⠋⠉⠀⠀⠉⠙⢿⣿⣿⡿⣿⣿⣷⣦⡀⠀⠀⠀$(DEF_COLOR)"
	@echo "$(WHITE)⠀⢀⣼⣿⣿⠟⠁⢠⣿⣿⠏⠀⠀⢠⣤⣤⡀⠀⠀⢻⣿⣿⡀⠙⢿⣿⣿⣦⠀⠀$(DEF_COLOR)"
	@echo "$(WHITE)⣰⣿⣿⡟⠁  ⢸⣿$(DEF_COLOR)$(EYE)philosophers$(DEF_COLOR)$(WHITE)⣿⡇  ⠙⣿⣿⣷⡀   $(DEF_COLOR)"
	@echo "$(WHITE)⠈⠻⣿⣿⣦⣄⠀⠸⣿⣿⣆⠀⠀⠀⠉⠉⠀⠀⠀⣸⣿⣿⠃⢀⣤⣾⣿⣿⠟⠁$(DEF_COLOR)"
	@echo "$(WHITE)⠀⠀⠈⠻⣿⣿⣿⣶⣿⣿⣿⣦⣄⠀⠀⠀⢀⣠⣾⣿⣿⣿⣾⣿⣿⡿⠋⠁⠀⠀$(DEF_COLOR)"
	@echo "$(WHITE)⠀⠀⠀⠀⠀⠙⠻⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠛⠁⠀⠀⠀⠀⠀$(DEF_COLOR)"
	@echo "$(WHITE)⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠛⠛⠿⠿⠿⠿⠿⠿⠛⠋⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀$(DEF_COLOR)"
	@echo "$(WHITE)⠀⠀⠀⠀⠀⠀⠀⢰⣷⡦⠀⠀⠀⢀⣀⣀⠀⠀⠀⢴⣾⡇⠀⠀⠀⠀⠀⠀⠀⠀$(DEF_COLOR)"
	@echo "$(WHITE)⠀⠀⠀⠀⠀⠀⠀⣸⠟⠁⠀⠀⠀⠘⣿⡇⠀⠀⠀⠀⠙⢷⠀⠀⠀⠀⠀⠀⠀⠀$(DEF_COLOR)"
	@echo "$(WHITE)⠀⠀⠀⠀⠀⠀⠀⠁⠀⠀⠀⠀⠀⠀⠻⠀⠀⠀⠀⠀⠀⠈⠀⠀⠀⠀⠀⠀⠀⠀$(DEF_COLOR)"

$(OBJDIR)%.o: $(SRCDIR)%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $@

clean:
	@$(RM) obj
	@echo "--->$(YELLOW)Cleaning philo.$(DEF_COLOR)"
	@sleep 1
	@echo "--->$(GREEN)Cleaning success.$(DEF_COLOR)"

fclean:
	@$(RM) obj $(NAME)
	@echo "--->$(YELLOW)Full cleaning philo.$(DEF_COLOR)"
	@sleep 1
	@echo "--->$(GREEN)Full cleaning success.$(DEF_COLOR)"
re: fclean all

DEF_COLOR = \033[0;39m
GREEN = \033[1;92m
YELLOW = \033[1;93m
EYE = \033[1;95m
WHITE = \033[5;97m