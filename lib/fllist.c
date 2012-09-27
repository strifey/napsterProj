#include "fllist.h"

//initializes an empty file_list
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

//attempts to open and parse nodes from file saved by server
void load_list(fllist* file_list, const char* lpath){
	FILE *listf = fopen(lpath, "r");
	if(listf == NULL){
		perror("Couldn't find file\n");
		return;
	}
	char* line_buff = NULL;
	for(int i = 0; i<MAX_FILES; i++){
		size_t n = MAX_NAME_LEN +2;
		int eol = getline(&line_buff, &n, listf);
		if(eol == -1){
			break;
		}
		line_buff[eol-1] = '\0';
		if(add_node_from_file(file_list, line_buff) != 0){
			perror("Error loading a node from file\n");
			fclose(listf);
		}
		line_buff = NULL;
	}
	fclose(listf);
}

//writes list to file specified
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
	fclose(listf);
	return 0;
}

//takes node's filename and ip and packs them together with delim
char* serialize_node(filenode* fnode){
	char *serial_file = (char *)malloc(sizeof(char)*(strlen(fnode->ip)+strlen(fnode->filename)+2));
	for(unsigned int i = 0; i<strlen(fnode->ip); i++)
		serial_file[i] = fnode->ip[i];
	serial_file[strlen(fnode->ip)] = '\0';
	serial_file = strcat(serial_file, "|");
	serial_file = strcat(serial_file, fnode->filename);
	return serial_file;
}

//parses serialization and adds node info to list
//does not add if fails to parse data
int add_node_from_file(fllist *file_list, char*filestring){
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
	new_node->ip = malloc(sizeof(char)*strlen(new_ip));
	new_node->ip_len = strlen(new_ip);
	new_node->filename = malloc(sizeof(char)*strlen(new_filename));
	new_node->filename_len = strlen(new_filename);
	strcpy(new_node->ip, new_ip);
	strcpy(new_node->filename, new_filename);
	filenode*tmp = file_list->head;
	file_list->head = new_node;
	file_list->head->next = tmp;
	file_list->size++;
	return 0;
}

//adds node from new information from client
//returns -2 if already exists in list
int add_node(fllist *file_list, char *filename, char *new_ip){
	//don't allow duplicates
	if(list_contains(file_list, filename, new_ip))
		return -2;
	
	//create new new node
	filenode *new_node = (filenode *)malloc(sizeof(filenode));
	if(new_node == NULL){
		perror("System out of memory, closing\n");
		exit(1);
	}
	new_node->ip = malloc(sizeof(char)*strlen(new_ip));
	new_node->ip_len = strlen(new_ip);
	new_node->filename = malloc(sizeof(char)*strlen(filename));
	new_node->filename_len = strlen(filename);
	strcpy(new_node->ip, new_ip);
	strcpy(new_node->filename, filename);

	//add node to head of list
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
int del_node(fllist *file_list, char *del_filename, char* del_ip){
	//return -2 if empty
	if(file_list->size == 0)
		return -2;
	//check head for matching node
	if(node_eq(file_list->head, del_filename, del_ip)){
		printf("Deleting head!\n");
		filenode*tmp = file_list->head;
		file_list->head = file_list->head->next;
		tmp->next = NULL;
		free(tmp->ip);
		free(tmp->filename);
		free(tmp);
		file_list->size--;
		return 0;
	}
	//cause we've checked the head and if we're len1, we're done
	if(file_list->size == 1)
		return -2;
	//iterate through list to find to delete
	filenode *prev_node = file_list->head;
	for(filenode *i_node = prev_node->next;i_node != NULL; i_node = i_node->next){
		if(node_eq(i_node, del_filename, del_ip)){
			filenode*tmp = i_node;
			prev_node->next = i_node->next;
			tmp->next = NULL;
			free(tmp->ip);
			free(tmp->filename);
			free(tmp);
			file_list->size--;
			return 0;
		}
		prev_node = i_node;
	}
	return -2;
}

//just compare their ip and filename strings
int node_eq(filenode *node, char*fn, char*ip){
	int ip_ret = strcmp(node->ip, ip);
	int fn_ret = strcmp(node->filename, fn);
	if(!ip_ret && !fn_ret)
		return 1;
	return 0;
}

//prints out formatted version of list
void print_list(fllist *file_list){
	printf("File list size : %d\n", file_list->size);
	int i = 0;
	for(filenode *curr = file_list->head; curr != NULL; curr = curr->next){
		i++;
		printf("Node %d: (%s, %s)\n", i, curr->filename, curr->ip);
	}
}

//just does an equivalency check on all nodes to see if file exists
int list_contains(fllist *file_list, char*fn, char*ip){
	if(file_list->size == 0)
		return 0;
	for(filenode *i = file_list->head; i != NULL; i = i->next){
		if(node_eq(i, fn, ip))
			return 1;
	}
	return 0;
}

