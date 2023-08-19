cc = gcc -g -Wall -Werror -Wextra -std=c11
GCOVFLAGS = -fprofile-arcs -ftest-coverage

OS = $(shell uname)
ifeq ($(OS), Linux)
	CHECK_FLAGS = -lpthread -lcheck -pthread -lrt -lm 
else
	CHECK_FLAGS = -lcheck
endif

ifeq ($(OS),Linux)
	OPEN_CMD = xdg-open
endif
ifeq ($(OS),Darwin)
	OPEN_CMD = open
endif

all: decimal.a 

decimal.a:
	$(cc) -c *.c
	ar rc libdecimal.a *.o
	rm -rf *.o
	ranlib libdecimal.a
	cp libdecimal.a decimal.a

test: decimal.a
	$(cc) decimal.a tests/*.c $(CHECK_FLAGS) -o test -L. -ldecimal
	./test

gcov_report: decimal.a
	$(cc) $(GCOVFLAGS) tests/*.c *.c $(CHECK_FLAGS) -o test -L. -ldecimal
	./test
	gcov testc/*.c
	lcov -t "test" -o test.info -c -d .
	genhtml -o report/ test.info
	rm -rf *.o *.gcno *.gcda 
	$(OPEN_CMD) ./report/index.html

clang:
	clang-format -style=Google -n *.c *.h tests/*.c

clang-fix:
	clang-format -style=Google -i *.c *.h tests/*.c


leaks: test
	CK_FORK=no leaks --atExit -- ./test

brew:
	cd ~
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh

lcov:
ifeq ($(OS),Linux)
	sudo apt install lcov
endif
ifeq ($(OS),Darwin)
	brew install lcov
endif

valgrind: decimal.a
	$(cc) decimal.a tests/*.c -lpthread -lcheck -pthread -lrt -lm -o test -L. -ldecimal
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./test

clean:
	rm -rf *.o *.gcno *.gcda *.a *.info report .clang-format test *.out *.dSYM

.PHONY:  all lcov test gcov_report

###
