//Gamze Nur Madan - 260201084
//Halil İbrahim Buğday - 280201094

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_PATH_LENGTH 250

void printErrorAndExit(const char* errorMsg) { //function to print the necessary error message and exit the system.
    printf("%s\n", errorMsg);
    exit(1);
}


//below two functions is to check the argument Type
int isId(const char* argType){ 
    return strcmp(argType, "-pid");
}

int isName(const char* argType){
    return strcmp(argType, "-pname");
}


//function to remove module.
void removeModule(){
    int exitCode = system("sudo rmmod proc_info_module");
    if (exitCode != 0) {
        printf("Module could not be removed.\n");
    }
}

//function to insert the module
void insertModule(const char* filePath, const char* argType, const char* argVal){
    char insertModule[MAX_PATH_LENGTH];

    
    if (isId(argType) == 0){
        if (atoi(argVal) <= 0){//check if the provided Process Id value is valid.
            printErrorAndExit("Process ID cannot be 0 or negative number");
        }else{
            snprintf(insertModule, sizeof(insertModule), "sudo insmod %s upid=%s", filePath, argVal); //to construct the module insertion if id
        }
    }
    else if (isName(argType) == 0) {
        snprintf(insertModule, sizeof(insertModule), "sudo insmod %s upname=%s", filePath, argVal); //to construct the module insertion if name
    }
    else{
        printErrorAndExit("Invalid Argument Type");
    }

    int exitCode = system(insertModule); //here we execute the insertion command that we constructed
    if (exitCode != 0){
        removeModule(); //we remove the module if the insertion is unssuccesfull
        printErrorAndExit("Module could not be inserted");
    }
}

//function to read and print the contents of the /proc file
void readProcFile(){
    FILE* procFilePtr = fopen("/proc/proc_info_module", "r");
    if (procFilePtr == NULL){
        removeModule();
        printErrorAndExit("/proc file could not be opened");
    }

    char* line = NULL;
    size_t len = 0;
    ssize_t readValue;
    //read each line of the proc file and print it
    do {
        readValue = getline(&line, &len, procFilePtr);
        if (readValue != -1) {
            printf("%s", line);
        }
    } while (readValue != -1);

    fclose(procFilePtr);
    free(line); //to clean up resources 
}


int main(int argc, char *argv[]) {

    if(argc != 4) {
        printErrorAndExit("The number of arguments is not valid. Please enter 4 arguments.");
    }

    char* filePath = argv[1];
    char* argType = argv[2];
    char* argVal = argv[3];

    insertModule(filePath, argType, argVal);
   
    readProcFile();

    removeModule(); //to clean up resources

    exit(1);
}
