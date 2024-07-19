#include <stdio.h>
#include <string.h>
#include <stdlib.h>


const char *FILE_NAME = "database_file.txt";
const char *DELIMITER = ",";


void set(char *key, char *value) {
    FILE *database_file_ptr = fopen(FILE_NAME, "a");
    if (strlen(key) > 50) {
        printf("Key too large, must be less than 50 characters");
    }
    if (strlen(value) > 50) {
        printf("Value too large, must be less than 50 characters");
    }
    fprintf(database_file_ptr, "%s%s%s\n", key, DELIMITER, value);
    fflush(database_file_ptr);
    fclose(database_file_ptr);
}



char* get(char *key) {
    char *result = malloc(51);
    FILE *read_ptr = fopen(FILE_NAME, "r");
    char line[110];
    while(fgets(line, 110, read_ptr) != NULL) {
        char* curr_key = strtok(line, DELIMITER);
        if (strcmp(curr_key, key) == 0) {
            char* value = strtok(NULL, DELIMITER);
            strcpy(result, value);
            fclose(read_ptr);
            return result;
        }
    }
    printf("Key not found.");
    fclose(read_ptr);
    return NULL;
}

int main() {
    set("test", "value");
    char* val = get("test");
    printf("Value for key test: %s", val);
    set("test2", "value2");
    char *val2 = get("test2");
    printf("Value for key test2: %s", val2);
    char *check_test_val = get("test");
    printf("Checking value for test is not overwritten: %s", check_test_val);
    // Get non existent key
    get("not_existent");
    return 0;
}

