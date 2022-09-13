#include "bu_conf.h"
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

buc_option* create_conf(){
	buc_option* conf = malloc( sizeof(buc_option) );
	
	if(conf == NULL){
		BU_ERR_FUNC("ERR: Could not allocate memory.")
		return NULL;
	}

	conf->next = NULL; // No more elements in the list
	conf->variable = NULL; // Not yet filled with any option.

	return conf;
}

void add_option(buc_option* optionlist, char* name, enum var_types type, void* variable){
	if(optionlist == NULL || name == NULL || variable == NULL){
		BU_ERR_FUNC("Nullpointer passed to add_option, where a non-null pointer is expected.");
	return;
	}

	if(strlen(name) > BUC_MAX_OPTION_NAME_LENGTH){
		BU_ERR_FUNC("Option name too long.");
		return;
	}
	

	// Handle the case when the list was just created and has no elements
	if(optionlist->variable == NULL){
		strcpy(optionlist->name, name);
		optionlist->type=type;
		optionlist->variable = variable;
		return;
	}

	// Handle the case when there are multiple elements in the list
	buc_option* curr_option = optionlist;
	
	while(curr_option->next != 0){
		curr_option = curr_option->next;
	}

	// Allocate and add new element to the list
	buc_option* new_option = malloc( sizeof(buc_option) );
	if(new_option == NULL){
		BU_ERR_FUNC("ERR: Could not allocate memory.")
		return;
	}
	
	strcpy(new_option->name, name);
	new_option->type = type;
	new_option->variable = variable;
	new_option->next = NULL;
	
	curr_option->next = new_option;
}

// Forward declaration of a forced inline function
#ifdef __clang__
	__attribute__((always_inline))
#elif __GNUC__
	__attribute__((always_inline))
#elif _MSC_VER
	__forceinline
#elif
	__attribute__((always_inline))
#endif
static inline void match(char* name, buc_option* conf, char* line, int eq_loc); 

	void load_conf(char* path, buc_option* conf){
	FILE* f;
	f = fopen(path, "r");

	if(f == NULL){
		BU_ERR_FUNC("Could not open the specified config file.");
		return;
	}
	

	char line[BUC_MAX_LINE_LENGTH + 1] = {0};
	
	// Reading the entire file.
	while( fgets( &line[0], BUC_MAX_LINE_LENGTH + 1, f ) != 0 ){

		// Remove equals signs and spaces from the name (happend when no space is used before it in the config)
		int eq_loc;
		for(eq_loc = 0; line[eq_loc] != '=' && eq_loc < BUC_MAX_OPTION_NAME_LENGTH + 3; eq_loc++);
		
		line[eq_loc] = '\0';

		if(line[eq_loc - 1] == ' ')
			line[eq_loc - 1] = '\0';

		match(line, conf, line, eq_loc);

	}	


fclose(f);
}

#ifdef __clang__
	__attribute__((always_inline))
#elif __GNUC__
	__attribute__((always_inline))
#elif _MSC_VER
	__forceinline
#elif
	__attribute__((always_inline))
#endif
static inline void match(char* name, buc_option* conf, char* line, int eq_loc) 
{
		buc_option* curr_option = conf;
		
		while(true){
			if(strcmp(curr_option->name, name) == 0 ){
				switch(curr_option->type){
					case BUC_INT:
						sscanf(&line[eq_loc + 1], " %d ", (int*)curr_option->variable); 
						break;
					case BUC_FLOAT:
						sscanf(&line[eq_loc + 1], " %f ", (float*)curr_option->variable); 
						break;
					case BUC_RGB:
						sscanf(&line[eq_loc + 1], " %hhu , %hhu , %hhu ", 
								(unsigned char*)curr_option->variable,
								(unsigned char*)curr_option->variable + 1,
								(unsigned char*)curr_option->variable + 2
						      );
						break;
					case BUC_RGBA:
						sscanf(&line[eq_loc + 1], " %hhu , %hhu , %hhu , %hhu", 
								(unsigned char*)curr_option->variable,
								(unsigned char*)curr_option->variable + 1,
								(unsigned char*)curr_option->variable + 2,
								(unsigned char*)curr_option->variable + 3
						      );
						break;
					}

			}
			if(curr_option->next == NULL)
				break;
			curr_option = curr_option->next;
		}
}
