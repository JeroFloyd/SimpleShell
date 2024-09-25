#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>




char *history[100];
int count_hist = 0;

void history_adder(const char *command){
    if(count_hist < 100){
        history[count_hist++] = strdup(command);
    }else{
        free(history[0]);
        memmove(history, history + 1, (100 - 1) * sizeof(char *));
        history[100 - 1] = strdup(command);
    }
}

void dis_hist(){
    printf("This is the Command History:\n");
    for (int i = 0; i < count_hist; i++) {
        printf("%d: %s\n", i + 1, history[i]);
    }
}



//This is the function for ls 
void ls_func(const char *path){
    struct dirent *entry;
    DIR *dir = opendir(path);

    if(dir == NULL){
        perror("Unable to open directory");
    }

    while((entry = readdir(dir)) != NULL){
        printf("%s\n", entry->d_name);
    }

    closedir(dir);
}


//This is the function for ls/home
void ls_home_func(){
    const char *dir_path = "/home";
    struct dirent *entry;
    DIR *dir = opendir(dir_path);

    if(dir == NULL){
        perror("opendir");
    }

    printf("Directories of %s:\n", dir_path);

    while((entry = readdir(dir)) != NULL){
        printf("%s\n", entry->d_name);
    }

    closedir(dir);
}


//This is the echo function
void echo_func(int c, char *echo_value[]){
    for(int i = 1; i < c; i++){
        printf("%s ", echo_value[i]);
    }
    printf("\n");
}


//This is the line count function
void wc_l_func(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
    }

    int line_count = 0;
    char ch;

    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') { //This increments the line count on the file
            line_count++;
        }
    }

    fclose(file);
    printf("%d\n", line_count);
}


//This is the character count function
void wc_c_func(char *filename){
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
    }

    int char_count = 0;
    char ch;

    while((ch = fgetc(file)) != EOF){ //This reads the file character by character
        char_count++;
    }

    fclose(file);
    printf("%d\n", char_count);
}


//This is the printf finding function
void grep_func(const char *pattern, const char *filename){
    FILE *file = fopen(filename, "r");
    if(file == NULL){
        perror("Error opening file");
    }

    char line[256];
    int line_number = 0;

    printf("Searching for '%s' in '%s'\n", pattern, filename);

    while(fgets(line, sizeof(line), file) != NULL){
        line_number++;
        printf("Checking line %d: %s", line_number, line);
        if(strstr(line, pattern) != NULL){ //This checks if the word exists in the line
            printf("\n");
            printf("Match found on line %d: %s", line_number, line);
            printf("\n");
        }
    }
    fclose(file);
}


void ls_r_func(const char *path, int depth){
    struct dirent *entry;
    DIR *dir = opendir(path);
    if(dir == NULL){
        perror("Unable to open directory");
    }

    for(int i = 0; i < depth; i++){
        printf("  ");
    }
    printf("%s:\n", path);


    while((entry = readdir(dir)) != NULL){
        if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0){
            for(int i = 0; i < depth + 1; i++){
                printf("  ");
            }
            printf("%s\n", entry->d_name);

            if(entry->d_type == 4){ //4 shows the directory in d_type
                char new_path[512];
                snprintf(new_path, sizeof(new_path), "%s/%s", path, entry->d_name);
                ls_r_func(new_path, depth + 1); //This is the recursive call
            }
        }
    }
    closedir(dir);
}


long long fib_func(int n){
    if(n <= 1) {
        return n;
    }
    long long a = 0, b = 1, c;


    for(int i = 2; i <= n; i++){
        c = a + b;
        a = b;
        b = c;
    }
    return b; //This returns the nth fibonacci number
}


void sort_func(char *filename){
    FILE *file = fopen(filename, "r");
    if(file == NULL){
        perror("Error opening file");
    }

    char *lines[1000];
    char len[1000];
    int count = 0;


    while(fgets(len, sizeof(len), file)){
        lines[count] = malloc(strlen(len) + 1);
        strcpy(lines[count], len);
        count++;
        if(count >= 1000){
            printf("Reached maximum number of lines (%d)!\n", 1000);
            break;
        }
    }

    fclose(file);
    qsort(lines, count, sizeof(char *), (int (*)(const void*, const void*)) strcmp);

    printf("These are the sorted contents of %s:\n", filename);
    for (int i = 0; i < count; i++) {
        printf("%s", lines[i]);
        free(lines[i]);
    }
}


void uniq_func(const char *filename){
    FILE *file = fopen(filename, "r");
    if(file == NULL){
        perror("Error opening file");
    }

    char previousLine[256] = "";
    char currentLine[256];

    while(fgets(currentLine, sizeof(currentLine), file) != NULL){
        if(strcmp(currentLine, previousLine) != 0){
            printf("%s", currentLine);
            strcpy(previousLine, currentLine);
        }
    }
    fclose(file);
}



int main(int count, char *value[]){
    int bg = 0;
    int i = 1;
    while(i<5){
        char userin[100];
        int echo_count = 0;
        fgets(userin, 100, stdin); //This is the user input
        userin[strcspn(userin, "\n")] = 0; //This is for removing the new line character from input

        if(strcmp(userin, "./fib 40") == 0){
            int n = 40;
            long long result = fib_func(n); //This calculates the fibonacci number
            printf("Fibonacci(%d) = %lld\n", n, result);
            printf("\n");
        }

        
        int bg = 0;
        if(userin[strlen(userin)-1] == '&'){
            bg = 1;
            userin[strlen(userin)-1] = '\0'; //This removes the & from the command
        }


        history_adder(userin);

        if(strcmp(userin, "exit") == 0){
            break; //This exits the shell
        }

        if(strcmp(userin, "history") == 0){
            dis_hist();
            continue;
        }



        char *command = strtok(userin, " ");
        char *args[10];

        while (command != NULL) {
        args[echo_count++] = command;
        command = strtok(NULL, " ");
        }
        args[echo_count] = NULL;


        //Bonus background processes part
        pid_t pid = fork();
        if (pid < 0) {
            perror("Fork failed");
            continue; // If fork fails, prompt for the next command
        }
        if(pid == 0){
            if(strcmp(userin, "ls") == 0){
            const char *dir_path = (count > 1) ? value[1] : "."; //This is the ternary operator. It checks the condition and returns if it is true.
            // . refers to the current working directory.
            ls_func(dir_path);
            printf("\n");
        }
        if(strcmp(userin, "ls/home") == 0){
            ls_home_func();
            printf("\n");
        }
        if(strcmp(args[0], "echo") == 0){ //This checks if the input is echo
            echo_func(echo_count, args);
            printf("\n");
        }
        if(strcmp(args[0], "wc") == 0 && echo_count == 3 && strcmp(args[1], "-l") == 0){ //This basically ensures that the command begins with wc 
            wc_l_func(args[2]);                                                       // And if there are 3 arguments - wc, -l and fib.c
            printf("\n");                                                              //  And if the second value of args is the string -l. To check if the user is asking for a line count
        }
        if(strcmp(args[0], "wc") == 0 && echo_count == 3 && strcmp(args[1], "-c") == 0){
            wc_c_func(args[2]);
        }
        if(strcmp(args[0], "grep") == 0 && echo_count == 3) {
            grep_func(args[1], args[2]);
            printf("\n");
            printf("\n");
        }
        if(strcmp(userin, "ls -R") == 0){
            ls_r_func(".", 0);
            printf("\n");
        }
        if(strcmp(userin, "./helloworld") == 0){
            system("./helloworld");
            printf("\n");
        }
        if(strcmp(args[0], "sort") == 0 && echo_count == 2){
            sort_func(args[1]);
            printf("\n");
        }
        if(strcmp(args[0], "uniq") == 0 && echo_count == 2){
            uniq_func(args[1]);
            printf("\n");
            printf("\n");
        }
        }
    }

    for (int i = 0; i < count_hist; i++) { //This frees the allocated memory for history
        free(history[i]);
    }
   
    return 0;
}
