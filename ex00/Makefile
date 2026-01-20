NAME = btc

CXX := c++

CXXFLAGS := -Wall -Wextra -Werror -std=c++98

OBJDIR = build

SRC :=   main.cpp BitcoinExchange.cpp

OBJ = $(addprefix $(OBJDIR)/, $(SRC:.cpp=.o))

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@
	@echo  "\nCreated executable '$(NAME)'"


$(OBJDIR)/%.o: %.cpp Makefile *h  | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

exec : all clean
	./$(NAME)

.PHONY: all clean fclean re exec

ifdef DEBUG
CXXFLAGS += -DDEBUG
endif
