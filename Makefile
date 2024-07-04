CC = gcc
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/main.o
HDRS = 
CFLAGS = -pg -Wall -c -I$(INC)

EXE = $(BIN)/tp2virtual

exec: $(EXE)
	./$(BIN)/tp2virtual lru arquivo.log 4 128

$(BIN)/tp2virtual: $(OBJS)
	$(CC) -o $(BIN)/tp2virtual $(OBJS) $(LIBS)
	
$(OBJ)/main.o: $(HDRS) $(SRC)/main.c
	$(CC) $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.c 

clean:
	rm -f $(EXE) $(OBJS)
