##
## EPITECH PROJECT, 2023
## makefile
## File description:
## makefile
##

# === CONFIGURATION ===
NAME        := strace
LIB_NAME    :=

CXX         := gcc
CXXFLAGS    := -Iincludes
LDFLAGS     :=

DEBUG       ?= 0
ifeq ($(DEBUG),1)
	CXXFLAGS += -g -DDEBUG
endif

# === VERBOSE SWITCH ===
ifndef V
	SILENT = @
else
	SILENT =
endif

# === PATHS ===
SRC_DIR     := src
INC_DIR     := includes
OBJ_DIR     := obj
TEST_DIR    := tests

# === FILES ===
SRCS        := $(wildcard $(SRC_DIR)/*.c)
OBJS        := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

TEST_SRCS   := $(wildcard $(TEST_DIR)/*.c)
TEST_OBJS   := $(TEST_SRCS:$(TEST_DIR)/%.c=$(OBJ_DIR)/%.test.o)
TEST_NAME   := run_tests

# === COLORS ===
GREEN   := $(shell echo -e "\033[0;32m")
RED     := $(shell echo -e "\033[0;31m")
NC      := $(shell echo -e "\033[0m")

# === RULES ===
all: $(NAME) $(LIB_NAME)
	@echo "$(GREEN)[OK] Build complete.$(NC)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(SILENT)$(CXX) $(CXXFLAGS) -fPIC -c $< -o $@

$(NAME): $(OBJS)
	$(SILENT)$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(LIB_NAME): $(OBJS)
	$(SILENT)$(CXX) -shared -o $@ $^

$(OBJ_DIR):
	$(SILENT)mkdir -p $(OBJ_DIR)

clean:
	$(SILENT)$(RM) -r $(OBJ_DIR)
	@echo "$(RED)[CLEAN] Object files removed.$(NC)"

fclean: clean
	$(SILENT)$(RM) $(NAME) $(LIB_NAME) $(TEST_NAME)
	@echo "$(RED)[FCLEAN] Binaries removed.$(NC)"

re: fclean all

tests: $(TEST_NAME)
	@./$(TEST_NAME)

$(OBJ_DIR)/%.test.o: $(TEST_DIR)/%.c | $(OBJ_DIR)
	$(SILENT)$(CXX) $(CXXFLAGS) -c $< -o $@

$(TEST_NAME): $(TEST_OBJS) $(OBJS)
	$(SILENT)$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

valgrind: $(NAME)
	@valgrind --leak-check=full ./$(NAME)

.PHONY: all clean fclean re tests valgrind
