NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

SRCS =	$(wildcard $(SRCDIR)/*.c)

OBJS = $(SRCS:$(SRCDIR)%.c=$(OBJDIR)%.o)
SRCDIR = ./src/
OBJDIR = obj/

all : $(OBJDIR) $(NAME) 

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(YELLOW)Compiling program.$(DEF_COLOR)"
	@sleep 1
	@echo "$(YELLOW)Creating Objects.$(DEF_COLOR)"
	@sleep 0.2
	@echo "$(GREEN)Philosophers compiled.$(DEF_COLOR)"
	@echo " _      _____ _     ____  ____  _      _____   _____  ____           "
	@echo "/ \  /|/  __// \   /   _\/  _ \/ \__/|/  __/  /__ __\/  _ \          "
	@echo "| |  |||  \  | |   |  /  | / \|| |\/|||  \      / \  | / \|          "
	@echo "| |/\|||  /_ | |_/\|  \__| \_/|| |  |||  /_     | |  | \_/|          "
	@echo "\_/  \|\____|\____/\____/\____/\_/  \|\____\    \_/  \____/          "
	@echo " ____  _     _  _     ____  ____  ____  ____  _     _____ ____  ____ "
	@echo "/  __\/ \ /|/ \/ \   /  _ \/ ___\/  _ \/  __\/ \ /|/  __//  __\/ ___\ "
	@echo "|  \/|| |_||| || |   | / \||    \| / \||  \/|| |_|||  \  |  \/|| |__  "
	@echo "|  __/| | ||| || |_/\| \_/|\___ || \_/||  __/| | |||  /_ |    /\___ | "
	@echo "|_|   \_/ \|\_/\____/\____/\____/\____/\_/   \_/ \|\____\|_/\_\|____/ "
	@echo "                                                                     "

$(OBJDIR)%.o: $(SRCDIR)%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $@

clean:
	@$(RM) obj
	@echo "$(YELLOW)Cleaning philo.$(DEF_COLOR)"
	@sleep 1
	@echo "$(GREEN)Cleaning success.$(DEF_COLOR)"

fclean:
	@$(RM) obj $(NAME)
	@echo "$(YELLOW)Full cleaning philo.$(DEF_COLOR)"
	@sleep 1
	@echo "$(GREEN)Full cleaning success.$(DEF_COLOR)"
re: fclean all

DEF_COLOR = \033[0;39m
GREEN = \033[0;92m
YELLOW = \033[0;93m