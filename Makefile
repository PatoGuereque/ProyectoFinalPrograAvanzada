# Specify extensions of files to delete when cleaning
CLEANEXTS = o

# Specify the target file and the library directory
SERVER  = ProyFinalServer
CLIENT  = ProyFinalClient
LIBDIR  = bin

# Compiler args
CC = gcc
args = -Wall -lm -lpthread

# Default target
.PHONY: all

all: prepare $(SERVER) $(CLIENT)

prepare:
	mkdir -p bin

# Pattern rule to build an object file from a .c file
bin/%.o: %.c
	$(CC) $(args) -c $^ -o $@
	
bin/%.o: problemas/%.c
	$(CC) $(args) -c $^ -o $@

# Build main
$(SERVER): ProyFinalServer.c bin/problema1.o bin/problema2.o bin/problema3.o bin/problema4.o bin/problema5.o bin/utils.o bin/client.o
	$(CC) $^ -g $(args) -o $@.o

$(CLIENT): ProyFinalClient.c bin/utils.o
	$(CC) $^ -g $(args) -o $@.o

.PHONY: clean 
clean:
	for file in $(CLEANEXTS); do rm -f *.$$file; done

# Dependencies
bin/problema1.o: problemas/problema1.c
bin/problema2.o: problemas/problema2.c
bin/problema3.o: problemas/problema3.c
bin/problema4.o: problemas/problema4.c
bin/problema5.o: problemas/problema5.c
bin/utils.o: utils.c
bin/client.o: client.c