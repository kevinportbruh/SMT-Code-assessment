# Compiler and flags
CC = g++
CFLAGS = -g -c -O2

# Executable names
CODING_EXEC = coding-problems
TESTER_EXEC = tictactoe-tester

# Object files
CODING_OBJ = coding-problems.o
TESTER_OBJ = tictactoetester.o tictactoe.o

# Rule to compile .cpp files into .o files
%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@

# Build the coding-problems executable
coding: $(CODING_OBJ)
	$(CC) $(CODING_OBJ) -o $(CODING_EXEC)

# Build the tictactoe-tester executable
tester: $(TESTER_OBJ)
	$(CC) $(TESTER_OBJ) -o $(TESTER_EXEC)

# Run the coding-problems program
runcoding: 
	make coding
	./$(CODING_EXEC)

# Run the tictactoe-tester program
runtester: 
	make tester
	./$(TESTER_EXEC)

# Compile the coding-problems object file
coding-problems.o: coding-problems.cpp coding-problems.h

# Compile the tictactoetester object file
tictactoetester.o: tictactoetester.cpp tictactoe.h

# Compile the tictactoe object file
tictactoe.o: tictactoe.cpp tictactoe.h

# Clean the object files and executables
clean:
	rm -f $(CODING_OBJ) $(TESTER_OBJ) $(CODING_EXEC) $(TESTER_EXEC)
