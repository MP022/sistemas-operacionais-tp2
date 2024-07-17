CC = gcc
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/main.o $(OBJ)/page.o ${OBJ}/frame.o $(OBJ)/table.o $(OBJ)/table_multilevel2.o $(OBJ)/table_multilevel3.o $(OBJ)/table_inverted.o ${OBJ}/util.o
HDRS = 
CFLAGS = -pg -Wall -c -I$(INC)

EXE = $(BIN)/tp2virtual

MEM_VAL := 128 256 512 1024 2048
PAGE_SIZE := 4

# Run only 5 times
matriz: $(EXE)
	@for mem in $(MEM_VAL); do \
		for page in $(PAGE_SIZE); do \
			echo "Running with page size $$page and memory size $$mem"; \
			./$(BIN)/tp2virtual lru ./tp2-files/compilador.log $$page $$mem ; \
		done \
	done

compilador: $(EXE)
	./$(BIN)/tp2virtual random ./tp2-files/compilador.log 4 2048

compressor: $(EXE)
	./$(BIN)/tp2virtual lru ./tp2-files/compressor.log 4 2048

simulador: $(EXE)
	./$(BIN)/tp2virtual lru ./tp2-files/simulador.log 4 2048
exec: $(EXE)
	./$(BIN)/tp2virtual lru ./tp2-files/matriz.log 2 128

$(BIN)/tp2virtual: $(OBJS)
	$(CC) -o $(BIN)/tp2virtual $(OBJS) $(LIBS)
	
$(OBJ)/main.o: $(HDRS) $(SRC)/main.c
	$(CC) $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.c 

$(OBJ)/page.o: $(HDRS) $(SRC)/page.c
	$(CC) $(CFLAGS) -o $(OBJ)/page.o $(SRC)/page.c
	
$(OBJ)/table.o: $(HDRS) $(SRC)/table.c
	$(CC) $(CFLAGS) -o $(OBJ)/table.o $(SRC)/table.c

$(OBJ)/table_multilevel2.o: $(HDRS) $(SRC)/table_multilevel2.c
	$(CC) $(CFLAGS) -o $(OBJ)/table_multilevel2.o $(SRC)/table_multilevel2.c
	
$(OBJ)/table_multilevel3.o: $(HDRS) $(SRC)/table_multilevel3.c
	$(CC) $(CFLAGS) -o $(OBJ)/table_multilevel3.o $(SRC)/table_multilevel3.c

$(OBJ)/table_inverted.o: $(HDRS) $(SRC)/table_inverted.c
	$(CC) $(CFLAGS) -o $(OBJ)/table_inverted.o $(SRC)/table_inverted.c

$(OBJ)/frame.o: $(HDRS) $(SRC)/frame.c
	$(CC) $(CFLAGS) -o $(OBJ)/frame.o $(SRC)/frame.c

$(OBJ)/util.o: $(HDRS) $(SRC)/util.c
	$(CC) $(CFLAGS) -o $(OBJ)/util.o $(SRC)/util.c

clean:
	rm -f $(EXE) $(OBJS)
