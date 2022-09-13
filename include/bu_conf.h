/* Main header file. A small documentation will follow now.
 *
 * This library does not have the best performance due to using linked lists. Thus you should consider
 * opting for a different solution if you wish to have thousands of options in config files of
 * thousands of lines. For smaller configs it should be more than good enough (which is exactly what it is meant to be use for).
 *
 * The most important function in this library is load_conf(buc_option* options, char* path)
 * which loads and parses a config file with the options stored in the options parameter.
 *
 * Another important function is add_option(buc_option* optionlist, char* name, var_types type, void* variable)
 * This one can be used to, as the name implies, create new options to be parsed.
 *
 * The function create_conf() can be used to create a new empty options list. This can be used for parsing different config files.
 */

#include <stdio.h>
#include <stdint.h>

#define BUC_STRINGIZE(X) #X

#define BUC_STRINGIZE_MACRO(X) BUC_STRINGIZE(X)

#ifndef BUC_MAX_OPTION_NAME_LENGTH
	#define BUC_MAX_OPTION_NAME_LENGTH 24
#endif

// Maximum possible length of a line in a config file.
#ifndef BUC_MAX_LINE_LENGTH
	#define BUC_MAX_LINE_LENGTH 64
#endif

// Benutils error function. 
#ifndef BU_ERR_FUNC
	#define BU_ERR_FUNC(...) fprintf(stderr, __VA_ARGS__);
#endif


enum var_types{BUC_INT, BUC_FLOAT, BUC_RGB, BUC_RGBA};
/* These correspond to the following types:
 * int
 * float
 * uint8_t[3]
 * uint8_t[4]
 * Please, do not, EVER, call add_option with a variable that does not correspond with the type you give it from the above enum. It leads to undefined behaviour. Things WILL go haywire.  Don't. For you own good. 
*/

// A linked list of these will represent all the possible options.
struct buc_option{
	struct buc_option* next;
	char name[BUC_MAX_OPTION_NAME_LENGTH + 1]; // The name of the option (its raw text, how it will look in the config file with an added null termination)
	enum var_types type; // What type does this value have?
	void* variable; // What variable should this option be saved to when loading a configuration?
};

typedef struct buc_option buc_option;

buc_option* create_conf();

// Again, do not, EVER, give add_option a variable that does not correspond with the type you gave it for you own good. 
void add_option(buc_option* optionlist, char* name, enum var_types type, void* variable);

void load_conf(char* path, buc_option* options);

