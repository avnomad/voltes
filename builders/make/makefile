TESTS_DIRECTORY = ../../sample inputs
SRC_DIRECTORY = ../../sources
EXECUTABLE_NAME = voltes.exe
TEST_COMMAND_PREFIX = $(EXECUTABLE_NAME) < "$(TESTS_DIRECTORY)
DEPENDENCIES_FILE = dependencies.txt

OBJECT_FILES = main.o count\ paths.o

CPP_COMPILER = g++
CPP_FLAGS = -Wall
LINKER = g++
LINKER_FLAGS = 


all:	$(EXECUTABLE_NAME)

clean:
		del *.o $(DEPENDENCIES_FILE)

distclean:	clean
		del $(EXECUTABLE_NAME)

test:	all
		$(TEST_COMMAND_PREFIX)/test1.txt"
		$(TEST_COMMAND_PREFIX)/test2.txt"
		$(TEST_COMMAND_PREFIX)/test3.txt"
		$(TEST_COMMAND_PREFIX)/test4.txt"
		$(TEST_COMMAND_PREFIX)/test5.txt"
		$(TEST_COMMAND_PREFIX)/test6.txt"

$(EXECUTABLE_NAME): $(OBJECT_FILES)
		$(LINKER) $(LINKER_FLAGS) $(OBJECT_FILES) -o $(EXECUTABLE_NAME)

%.o:	$(SRC_DIRECTORY)/%.cpp
		$(CPP_COMPILER) -c "$<" -o "$@" $(CPP_FLAGS)

include $(DEPENDENCIES_FILE)

.PHONY: all clean distclean test