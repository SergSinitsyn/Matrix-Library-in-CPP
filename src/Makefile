CC					= g++ -lstdc++
GCOVFLAGS 			= -coverage
WCHECK 				= -std=c++17
WFLAGS 				= -Wall -Werror -Wextra
CHECKFLAGS			= -lgtest -lm
CLEAN				= rm -rf

NAME				= matrix
LIB					= $(NAME).a

SOURCES_FILES		= *.cc
SRC_DIR				= .
SOURCES				= $(SRC_DIR)/$(SOURCES_FILES)
HEADERS 			= $(SRC_DIR)/*.h

TEST_FILE			= $(NAME)_test
TEST_FILE_FOR_LEAKS	= $(TEST_FILE)_leaks

TEST_SOURCE_FILE	= $(TEST_FILE).cc
TEST_SOURCE_FILE_2	= $(TEST_FILE)_throw.cc
TEST_DIR			= ./tests
TEST 				= $(TEST_DIR)/$(TEST_SOURCE_FILE) $(TEST_DIR)/$(TEST_SOURCE_FILE_2)
TEST_LEAKS 			= $(TEST_DIR)/$(TEST_SOURCE_FILE)

TEST_FILE_COV		= $(TEST_FILE)_cov

all: $(LIB)

$(LIB): $(SOURCES) $(HEADERS)
	$(CC) $(WCHECK) $(WFLAGS) -c $(SOURCES)
	ar rcs $(LIB) *.o
	$(CLEAN) *.o

clean: 
	$(CLEAN) *.o *.a *.gcno *.gcda *.info *.out *.gch *.dSYM $(TEST_FILE) report $(TEST_FILE_FOR_LEAKS) $(TEST_FILE_COV)

$(TEST_FILE): $(LIB) $(TEST)
	$(CC) $(CHECKFLAGS) $(LIB) $(TEST) -o $(TEST_FILE)

test: $(TEST_FILE)
	./$(TEST_FILE)

rebuild: clean all

report/index.html: $(SOURCES) $(TEST)
	$(CC) $(GCOVFLAGS) $(CHECKFLAGS) $(SOURCES) $(TEST) -o $(TEST_FILE_COV)
	./$(TEST_FILE_COV)
	lcov -t "$(TEST_FILE_COV)" -o $(TEST_FILE_COV).info -c -d . --no-external
	genhtml -o report $(TEST_FILE_COV).info

gcov_report: report/index.html
	open report/index.html

linter:
	@cp ../materials/linters/.clang-format ./
	@clang-format -n -style=google -verbose $(SOURCES)
	@clang-format -n -style=google -verbose $(TEST)
	@rm -f .clang-format

cppcheck:
	cppcheck --std=c++17 --enable=all --language=c++ --suppress=missingIncludeSystem $(SOURCES) $(HEADERS) $(TEST)

$(TEST_FILE_FOR_LEAKS): $(LIB)
	$(CC) $(CHECKFLAGS) $(LIB) $(TEST_LEAKS) -o $(TEST_FILE_FOR_LEAKS)

leaks: $(TEST_FILE_FOR_LEAKS)
	leaks --atExit -- ./$(TEST_FILE_FOR_LEAKS)

.PHONY: all clean test gcov_report rebuild linter cppcheck leaks matrix