
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "StrList.h"

#define CHUNK 100

char* getStringList(){
    char* input = NULL;
    char tempbuf[CHUNK];
    size_t inputlen = 0;
    size_t templen = 0;
    do{
        fgets(tempbuf,CHUNK,stdin);
        templen = strlen(tempbuf);
        input = realloc(input, inputlen+templen+1);
        strcpy(input + inputlen,tempbuf);
        inputlen += templen;
        if ((*(input + inputlen - 1)) == '\n'){
            *(input + inputlen - 1) = '\0';   
        }
    }while (templen == CHUNK-1 && tempbuf[CHUNK-2] != '\n');
    
    return input;
}

void getString(char** readFromUser) {    

    char buffer[50]; 
    fgets(buffer, sizeof(buffer), stdin);

    size_t inputLength = strlen(buffer);

    *readFromUser = (char *)malloc((inputLength + 1) * sizeof(char));
    if (*readFromUser == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    strcpy(*readFromUser, buffer);

    if ((*readFromUser)[inputLength - 1] == '\n')
        (*readFromUser)[inputLength - 1] = '\0';   
}


int main() {
    int chose;
    int stop = 1;
    
    StrList* list = StrList_alloc();
    do {
        scanf("%d", &chose);
        switch (chose) {
            case 1: {
                int numOfStrings;
                scanf("%d", &numOfStrings);
                getchar();
                char *readFromUser = getStringList();
        
                int index = 0;
                for (int i = 0; i < numOfStrings; i++) {
                    char *insertToList = malloc(strlen(readFromUser) + 1); // Allocate memory for each string
                    if (insertToList == NULL) {
                        fprintf(stderr, "Memory allocation failed\n");
                        return 1;
                    }
                    
                    int j = 0;
                    // Copy characters until space or end of string
                    while (readFromUser[index] != ' ' && readFromUser[index] != '\0') {
                        insertToList[j++] = readFromUser[index++];
                    }
                    insertToList[j] = '\0'; // Null-terminate the string
                    
                    StrList_insertLast(list, insertToList);
                    
                    // Skip spaces if any
                    while (readFromUser[index] == ' ') {
                        index++;
                    }
                }
                
                free(readFromUser); // Free the original input string
                break;
            }
            case 2: {
                int index;
                scanf("%d", &index);
                char* readFromUser;
                getString(&readFromUser);
                StrList_insertAt(list, readFromUser,index);
                free(readFromUser);
                index++;
                break;
            }
            case 3: {
                StrList_print(list);
                break;
            }
            case 4: {
                printf("%ld\n", StrList_size(list));
                break;
            }
            case 5: {
                int index;
                scanf("%d", &index);
                StrList_printAt(list, index);
                break;
            }
            case 6: {
                printf("%d\n", StrList_printLen(list));
                break;
            }
            case 7: {
                char* readFromUser;
                getString(&readFromUser);
                printf("%d\n",StrList_count(list,readFromUser));
                free(readFromUser);
                break;
            }
            case 8: {
                char* readFromUser;
                getString(&readFromUser);
                StrList_remove(list, readFromUser);
                free(readFromUser);
                break;
            }
            case 9: {
                int index;
                scanf("%d", &index);
                StrList_removeAt(list,index);
                break;
            }
            case 10: {
                StrList_reverse(list);
                break;
            }
            case 11: {
                int listLen = StrList_size(list);
                while (listLen>=0) {
                    StrList_removeAt(list,0);
                    listLen--;
                }
                break;
            }
            case 12: {
                StrList_sort(list);
                break;
            }
            case 13: {
                printf("%s\n", StrList_isSorted(list) ? "true" : "false");
                break;
            }
            case 0: {
                stop = 0;
                printf("\n");
                break;
            }
            default: {
                printf("Invalid option. Please enter a number from 0 to 13.\n");
                break;
            }
        }
    } while(stop!=0);
    
    StrList_free(list);
    return 0;
}
   