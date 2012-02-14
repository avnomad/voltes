TESTS_DIRECTORY = C:\input\benchmark
EXECUTABLE_NAME = voltes.exe
TEST_COMMAND = $(EXECUTABLE_NAME) < $(TESTS_DIRECTORY)
DEPENDENCIES_FILE = dependencies.txt

OBJECT_FILES = main.o count-paths.o

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
		$(TEST_COMMAND)\test1.txt
		$(TEST_COMMAND)\test2.txt
		$(TEST_COMMAND)\test3.txt
		$(TEST_COMMAND)\test4.txt
		$(TEST_COMMAND)\test5.txt
		$(TEST_COMMAND)\test6.txt

$(EXECUTABLE_NAME): $(OBJECT_FILES)
		$(LINKER) $(LINKER_FLAGS) $(OBJECT_FILES) -o $(EXECUTABLE_NAME)

%.o:	%.cpp
		$(CPP_COMPILER) -c $< -o $@ $(CPP_FLAGS)

include $(DEPENDENCIES_FILE)

.PHONY: all clean distclean test