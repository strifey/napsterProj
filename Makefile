CC = gcc
CFLAGS = -pedantic -Wall -Wextra
RELEASE_FLAGS = -O2
DEBUG_FLAGS = -g -DDEBUG

CLIENT_OUT = nClient
CLIENT_HFILES = client.h
CLIENT_CFILES  = $(CLIENT_HFILES:.h=.c)
CLIENT_OFILES  = $(CLIENT_HFILES:.h=.o)
CLIENT_DIR = ./client/
CLIENT_DEPS = $(pathsubst %, $(CLIENT_DIR)/%, $(CLIENT_FILES))

SERVER_OUT = nServer
SERVER_HFILES = server.h
SERVER_CFILES  = $(SERVER_HFILES:.h=.c)
SERVER_OFILES  = $(SERVER_HFILES:.h=.o)
SERVER_DIR = ./server/
SERVER_DEPS = $(pathsubst %, $(SERVER_DIR)/%, $(SERVER_FILES))

build: build-client build-server

remake: clean build

run-client: build-client
	./$(CLIENT_OUT)

run-server: build-server
	./$(SERVER_OUT)

build-client: $(CLIENT_DEPS)
	$(CC) $(CFLAGS) $(CLIENT_DIR)src/*.c -o ./$(CLIENT_OUT)

build-server: $(SERVER_DEPS)
	$(CC) $(CFLAGS) $(SERVER_DIR)src/*.c -o ./$(SERVER_OUT)

clean: clean-server clean-client

clean-server:
	rm $(SERVER_DIR)bin/*.o ./$(SERVER_OUT)

clean-client:
	rm $(CLIENT_DIR)bin/*.o ./$(CLIENT_OUT)
