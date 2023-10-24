CC=gcc -std=c11 -D_GNU_SOURCEs
CFLAGS=-c -Wall -Wextra -Werror
BUILD_DIR=build
INSTALL_DIR=3dViewer_v1_0
APP=3dViewer
GCOV=-fprofile-arcs -ftest-coverage
LIBC:=./sources/parser.c ./sources/affine.c
LIBH:=./headers/parser.h
LIBO:=./parser.o ./affine.o
TESTS=./tests/unit_tests.c

OS=$(shell uname)

ifeq ($(OS), Linux)
	OS_FLAGS=-lcheck -lsubunit -lrt -lpthread -lm
	CC+=-D OS_LINUX -g -s
	DIR=
	QTFLAGS=-spec linux-g++
	CHECK_LEAKS=CK_FORK=no valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=log.txt
	OPEN=firefox
else
	OS_FLAGS=-lcheck
	CC+=-D OS_MAC
	DIR=/$(APP).app/Contents/MacOS/
	QTFLAGS=
	CHECK_LEAKS=CK_FORK=no leaks --atExit --
	OPEN=open
endif

all: build

build: 
	qmake -o $(BUILD_DIR)/Makefile ./$(APP).pro $(QTFLAGS) CONFIG+=qtquickbuilder
	make -C $(BUILD_DIR)/ first

rebuild: clean all

install: build
	mkdir -p $(INSTALL_DIR)
	cp -r $(BUILD_DIR)$(DIR)/$(APP) $(INSTALL_DIR)/$(APP)

dist: install
	tar -czvf $(INSTALL_DIR).tgz $(INSTALL_DIR)/

uninstall:
	rm -rf $(INSTALL_DIR)

parser.a:
	$(CC) $(CFLAGS) $(LIBC)
	ar -rcs parser.a $(LIBO)
	ranlib $@
	cp $@ lib$@
	rm -rf *.o

tests: clean parser.a
	$(CC) $(CFLAGS) $(TESTS)
	$(CC) ./unit_tests.o parser.a -o Test $(OS_FLAGS)
	./Test
	rm -rf *.o *.a ./Test

gcov_report: $(LIBC) $(TESTS) $(LIBH)
	$(CC) $(TESTS) $(LIBC) -o Test $(OS_FLAGS) $(GCOV)
	./Test
	lcov -c -d . -o coverage.info
	genhtml coverage.info -o coverage
	$(OPEN) ./coverage/index.html
	
leaks: clean parser.a
	$(CC) $(TESTS) parser.a $(OS_FLAGS) -o ./Test
	$(CHECK_LEAKS) ./Test
	rm -f *.o *.a Test

style_formatter:	
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -style=Google -i ./sources/*.c ./headers/*.h ./sources/*.cpp ./headers/*.h ./tests/*.c
	rm -rf .clang-format

style:	
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -style=Google -n ./sources/*.c ./headers/*.h ./sources/*.cpp ./headers/*.h ./tests/*.c
	rm -rf .clang-format

dvi:
	open dvi.html

cppcheck:
	cppcheck $(LIBC) $(LIBH)

check: style cppcheck leaks

clean:
	rm -rf *.o *.a *.out *.txt *.gcno *.gch *.gcda *.info *.tgz coverage Test $(BUILD_DIR) $(INSTALL_DIR)