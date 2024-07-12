CC = gcc
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/main.o $(OBJ)/page.o ${OBJ}/frame.o $(OBJ)/table.o  ${OBJ}/util.o ${OBJ}/lru.o ${OBJ}/random.o
HDRS = 
CFLAGS = -pg -Wall -c -I$(INC)

EXE = $(BIN)/tp2virtual

exec: $(EXE)
	./$(BIN)/tp2virtual lru ./tp2-files/matriz.log 4 128

$(BIN)/tp2virtual: $(OBJS)
	$(CC) -o $(BIN)/tp2virtual $(OBJS) $(LIBS)
	
$(OBJ)/main.o: $(HDRS) $(SRC)/main.c
	$(CC) $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.c 

$(OBJ)/page.o: $(HDRS) $(SRC)/page.c
	$(CC) $(CFLAGS) -o $(OBJ)/page.o $(SRC)/page.c
	
$(OBJ)/table.o: $(HDRS) $(SRC)/table.c
	$(CC) $(CFLAGS) -o $(OBJ)/table.o $(SRC)/table.c

$(OBJ)/frame.o: $(HDRS) $(SRC)/frame.c
	$(CC) $(CFLAGS) -o $(OBJ)/frame.o $(SRC)/frame.c

$(OBJ)/util.o: $(HDRS) $(SRC)/util.c
	$(CC) $(CFLAGS) -o $(OBJ)/util.o $(SRC)/util.c

clean:
	rm -f $(EXE) $(OBJS)
