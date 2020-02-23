OUT=l5r
OBJS=main.o GameBoard.o Player.o Card.o Item.o Follower.o Holding.o Personality.o DeckBuilder.o TypeConverter.o inputMgr.o ui.o
CXX=g++ 
CXXFLAGS=-std=c++11
EXECUTION_PARAMETERS=

all: $(OUT)

$(OUT): $(OBJS)
	$(CXX) -o $(OUT) $(OBJS)

%.o: %.cpp
	$(CXX) -c -o $@ $<

# run the program
run: $(OUT)
	./$(OUT) $(EXECUTION_PARAMETERS)

# Debugging
db: clean param
param: COMPILATION_PARAMETERS += -g
param: $(OUT)

gdb: db
	gdb $(OUT)

vg: db
	valgrind $(EXECUTION_PARAMETERS) ./$(OUT)

vgleak: db
	valgrind --leak-check=full ./$(OUT) $(EXECUTION_PARAMETERS)

vgext: db
	valgrind --leak-check=full --show-leak-kinds=all --leak-resolution=high --track-origins=yes --vgdb=yes ./$(OUT) $(EXECUTION_PARAMETERS)

# Clean up
.PHONY: clean
clean:
	rm -f *o
