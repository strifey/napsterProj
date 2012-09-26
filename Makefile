CC = gcc-4.7
CFLAGS = -std=gnu11 -pedantic -Wall -Wextra
RELEASE_FLAGS = -O2
DEBUG_FLAGS = -g -DDEBUG

LIB_HFILES = fllist.h
LIB_CFILES = $(LIB_HFILES:.h=.c)
LIB_FILES = $(LIB_CFILES) $(LIB_HFILES)
LIB_DIR = ./lib

CLIENT_OUT = nClient
CLIENT_HFILES = client.h
CLIENT_CFILES  = $(CLIENT_HFILES:.h=.c)
CLIENT_SFILES = $(CLIENT_HFILES) $(CLIENT_CFILES)
CLIENT_OFILES  = $(CLIENT_HFILES:.h=.o)
CLIENT_DIR = ./client
CLIENT_DEPS = $(pathsubst %, $(CLIENT_DIR)/%, $(CLIENT_SFILES)) $(pathsubst %, $(LIB_DIR)/%, $(LIB_FILES))

SERVER_OUT = nServer
SERVER_HFILES = server.h
SERVER_CFILES  = $(SERVER_HFILES:.h=.c)
SERVER_OFILES  = $(SERVER_HFILES:.h=.o)
SERVER_DIR = ./server
SERVER_DEPS = $(pathsubst %, $(SERVER_DIR)/%, $(SERVER_SFILES)) $(pathsubst %, $(LIB_DIR)/%, $(LIB_FILES))

build: build-client build-server

remake: clean build

run-client: build-client
	./$(CLIENT_OUT)

run-server: build-server
	./$(SERVER_OUT)

build-client: $(CLIENT_DEPS)
	$(CC) $(CFLAGS) $(LIB_DIR)/fllist.c $(CLIENT_DIR)/src/*.c -o ./$(CLIENT_OUT)

build-server: $(SERVER_DEPS)
	$(CC) $(CFLAGS) $(LIB_DIR)/fllist.c $(SERVER_DIR)/src/*.c -o ./$(SERVER_OUT)

clean: clean-server clean-client

clean-server:
	rm $(SERVER_DIR)/bin/*.o ./$(SERVER_OUT)

clean-client:
	rm $(CLIENT_DIR)/bin/*.o ./$(CLIENT_OUT)
