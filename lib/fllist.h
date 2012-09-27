#ifndef FLLIST_H
#define FLLIST_H

#include "stdlib.h"
#include "string.h"
#include "stdio.h"

#define MAX_FILES 200

typedef struct _filenode{
	char* ip;
	size_t ip_len;
	char* filename;
	size_t filename_len;
	struct _filenode * next;
} filenode;

typedef struct _filelist{
	struct _filenode *head;
	unsigned int size;
} fllist;

fllist* create_list();
void load_list(fllist* file_list, const char* lpath);
int save_list(fllist *file_list, const char* lpath);
int add_node_from_file(fllist *file_list, char*filestring);
int add_node(fllist *file_list, char *filename, char *new_ip);
int del_node(fllist *file_list, char *del_filename, char* del_ip);
int node_eq(filenode *node, char*fn, char*ip);
char* serialize_node(filenode* fnode);
void print_list(fllist *file_list);
int list_contains(fllist *file_list, char*fn, char*ip);
#endif
