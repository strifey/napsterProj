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
int add_node(fllist *file_list, char*filestring);
int del_node(fllist *file_list, char*filestring);
int nodes_eq(filenode *node1, filenode *node2);
char* serialize_node(filenode* fnode);


#endif
