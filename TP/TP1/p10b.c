#include <stdio.h>
#include <string.h>

//The maximum length of each command
#define MAX_COMMAND_LENGTH 256
//The maximum number of tokens of each command
#define MAX_COMMAND_TOKENS 25

int main() {
	printf("Insert the desired command: ");
	char command_input[MAX_COMMAND_LENGTH];
	fgets(command_input, MAX_COMMAND_LENGTH, stdin);

	char * current_str = NULL;
	//Used by strtok_r, to preserve data between calls via the arguments instead of internal variables, in order to be reentrant
	char * save_ptr = NULL;

	//Array to store the strings
	char * command_arr[MAX_COMMAND_TOKENS];
	//The number of tokens passed into the command_arr, starts at 0, because it is empty
	int arr_length = 0;

	current_str = strtok_r(command_input, " ", &save_ptr);

	if(current_str == NULL) {
		return 1;
	}
	
	//BIG NOTE FOR THE FUTURE:
	//strtok does not allocate new strings, it returns a pointer to a section of the original string (thus, it mangles up the original string)
	//keep this in mind because freeing the base original string would cause all the other strings to be dangling pointers, causing potential segfaults

	command_arr[arr_length] = current_str;
	arr_length++;

	while((current_str = strtok_r(NULL, " ", &save_ptr)) != NULL) {
		command_arr[arr_length] = current_str;
		arr_length++;
	}

	printf("Split command parts:\n");

	int i;
	for(i = 0; i < arr_length; ++i) {
		//a newline was used instead of a space for printing for easier verification
		printf("%s\n", command_arr[i]);
	}

	return 0;
}