CC=gcc
CFLAGS=-Wall -std=c99
CPPCHECK=cppcheck
GCOV=--coverage
C_SRCS := $(wildcard *.c)

DIR_SRC=src/
DIR_OBJ=build/

_OBJ= main.o snoopy.o snoopy_dump.o
OBJ = $(patsubst %,$(DIR_OBJ)%,$(_OBJ))

all : clean compile exec

# gcov :
# 	@echo "Checking coverage..."
# 	@gcov build/ClassFileReader build/ClassFilePrinter build/CpInfo build/FieldInfo build/MethodInfo build/AttributeInfo build/ReadBytes build/Instruction buiild/InterfaceInfo build/MethodsArea build/ClassLoader build/InstructionsFunc build/main
# 	@echo "Done checking!"

exec :
	@echo "Running main..."
	@echo "\n\n\n"
	@build/./main
	@echo "\n\n\n"
	@echo "Done running!"

$(DIR_OBJ)%.o: $(DIR_SRC)%.c
	@$(CC) $(CFLAGS) -c -o $@ $< -Iincludes $(GCOV)

compile: $(OBJ)
	@echo "Building objects..."
	@$(CC) $(CFLAGS) -o main $^ -Iincludes $(GCOV)
	@echo "Done building!"

# cppcheck :
# 	@echo "Static code analysis..."
# 	@$(CPPCHECK) snoopy.c snoopy_dump.c main.c
# 	@echo "Done static analysis!"

clean :
	@echo "Cleaning..."
	@rm -rf build
	@mkdir build
	@echo "Done cleaning!"
