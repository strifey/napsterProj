#include "fllist.h"

fllist* create_list(){
	fllist *new_list = (fllist *)malloc(sizeof(fllist));
	if(new_list == NULL){
		perror("Already out of memory. Quitting program\n");
		exit(1);
	}
	new_list->head = NULL;
	new_list->size = 0;
	return new_list;
}

void load_list(fllist* file_list, const char* lpath){
	FILE *listf = fopen(lpath, "r");
	if(listf == NULL){
		perror("Couldn't find file\n");
		return;
	}
	char* line_buff = NULL;
	for(int i = 0; i<MAX_FILES; i++){
		size_t n = 12;
		int eol = getline(&line_buff, &n, listf);
		if(eol == -1){
			break;
		}
		line_buff[eol-1] = '\0';
		if(add_node(file_list, line_buff) != 0){
			perror("Error loading a node from file\n");
			fclose(listf);
		}
		file_list->size++;
		line_buff = NULL;
	}
	fclose(listf);
}

int save_list(fllist *file_list, const char* lpath){
	FILE *listf = fopen(lpath, "w");
	if(listf == NULL){
		perror("Error opening file to save list\n");
		return -1;
	}
	for(filenode* i_node = file_list->head; i_node != NULL; i_node=i_node->next){
		char* s_file = serialize_node(i_node);
		fwrite(s_file, 1, strlen(s_file), listf);
		fwrite("\n", 1, 1, listf);
	}
	return 0;
}

char* serialize_node(filenode* fnode){
	char *serial_file = (char *)malloc(sizeof(char)*(strlen(fnode->ip)+strlen(fnode->filename)+2));
	for(unsigned int i = 0; i<strlen(fnode->ip); i++)
		serial_file[i] = fnode->ip[i];
	serial_file[strlen(fnode->ip)] = '\0';
	serial_file = strcat(serial_file, "|");
	serial_file = strcat(serial_file, fnode->filename);
	return serial_file;
}


int add_node(fllist *file_list, char*filestring){
	char* new_ip = strtok(filestring, "|");
	char* new_filename = strtok(NULL, "|");
	if(new_ip == NULL || new_filename == NULL){
		perror("Error tokenizing filestring\n");
		return -1;
	}
	filenode *new_node = (filenode *)malloc(sizeof(filenode));
	if(new_node == NULL){
		perror("System out of memory, closing\n");
		exit(1);
	}
	new_node->ip = new_ip;
	new_node->ip_len = strlen(new_ip);
	new_node->filename = new_filename;
	new_node->filename_len = strlen(new_filename);
	filenode*tmp = file_list->head;
	file_list->head = new_node;
	file_list->head->next = tmp;
	file_list->size++;
	return 0;
}

//retvals:
	//-1 = error
	//-2 = node not found
	// 0 = sucess
int del_node(fllist *file_list, char *filestring){
	if(file_list->size == 0)
		return -2;

	char* del_ip = strtok(filestring, "|");
	char* del_filename = strtok(NULL, "|");
	if(del_ip == NULL || del_filename == NULL){
		perror("Error tokenizing filestring\n");
		return -1;
	}
	filenode *del_node = malloc(sizeof(filenode));
	del_node->ip = del_ip;
	del_node->filename = del_filename;

	if(file_list->size == 1){
		if(nodes_eq(file_list->head, del_node)){
			free(file_list->head);
			file_list->head = NULL;
			file_list->size = 0;
			free(del_node);
			return 0;
		}
		else{
			free(del_node);
			return -2;
		}
	}
	filenode *prev_node = file_list->head;
	for(filenode *i_node = prev_node->next;i_node != NULL; i_node = i_node->next){
		if(nodes_eq(i_node, del_node)){
			//found node to del
			free(del_node);
			return 0;
		}
		prev_node = i_node;
		i_node = i_node->next;
	}
	free(del_node);
	return -2;
}

int nodes_eq(filenode *node1, filenode *node2){
	int ip_ret = strcmp(node1->ip, node2->ip);
	int fn_ret = strcmp(node1->filename, node2->filename);
	if(!ip_ret && !fn_ret)
		return 1;
	return 0;
}
