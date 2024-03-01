
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "StrList.h"

#define CHUNK 12;

// char* getStringList(){
//     char* input = NULL;
//     char tempbuf[CHUNK];
//     size_t inputlen = 0;
//     size_t templen = 0;
//     do{
//         fgets(tempbuf,CHUNK,stdin);
//         templen = strlen(tempbuf);
//         input = realloc(input, inputlen+templen+1);
//         strcpy(input + inputlen,tempbuf);
//         inputlen += templen;
//         if ((*(input + inputlen - 1)) == '\n'){
//             *(input + inputlen - 1) = '\0';   
//         }
//     }while (templen == CHUNK-1 && tempbuf[CHUNK-2] != '\n');
    
//     return input;
// }
char* getString(FILE *fp){
    char *str;
    int ch;
    size_t len = 0;
    size_t size = CHUNK;
    str = realloc(NULL, sizeof(*str)*size);//size is start size
    if(!str)return str;
    while(EOF!=(ch=fgetc(fp)) && ch != '\n'){
        str[len++]=ch;
        if(len==size){
            str = realloc(str, sizeof(*str)*(size+=16));
            if(!str)return str;
        }
    }
    str[len++]='\0';

    return realloc(str, sizeof(*str)*len);
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
                char *readFromUser = getString(stdin);
        
                int index = 0;
                for (int i = 0; i < numOfStrings; i++) {
                    char *insertToList = malloc(strlen(readFromUser)); // Allocate memory for each string
                    if (insertToList == NULL) {
                        fprintf(stderr, "Memory allocation failed\n");
                        return 1;
                    }
                    
                    int j = 0;
                    // Copy characters until space or end of string
                    while (readFromUser[index] != ' ' && readFromUser[index] != '\0') {
                        insertToList[j++] = readFromUser[index++];
                    }
                    insertToList[j+1] = '\0'; // Null-terminate the string

                    
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
                char* readFromUser = getString(stdin);
                StrList_insertAt(list, readFromUser,index);
                free(readFromUser);
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
				char insertString[50] = {0};
				scanf("%s", insertString);
				printf("%d\n", StrList_count(list, insertString));
				break;
            }
            case 8: {
                char* readFromUser = getString(stdin);
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
                break;
            }
            default: {
                printf("Enter a number from 0 to 13.\n");
                break;
            }
        }
    } while(stop!=0);
    
    StrList_free(list);
    return 0;
}
   