CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -Wextra
RELEASE_FLAGS = -O2
DEBUG_FLAGS = -g -DDEBUG
CLIENT_OUT = nClient
SERVER_OUT = nServer
CLIENT_FILES = client.c client.h
CLIENT_DIR = ./client/src/
CLIENT_DEPS = $(pathsubst %, $(CLIENT_DIR)/%, $(CLIENT_FILES))
SERVER_FILES = server.c server.h
SERVER_DIR = ./server/src
SERVER_DEPS = $(pathsubst %, $(SERVER_DIR)/%, $(SERVER_FILES))

build-client: $(CLIENT_DEPS)
	$(CC) $(CFLAGS) $(CLIENT_DIR)*.c -o ./$(CLIENT_OUT)

build-server: $(SERVER_DEPS)
	$(CC) $(CFLAGS) $(SERVER_DEPS)*.c -o ./$(SERVER_OUT)

