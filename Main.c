
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "StrList.h"

void getString(char** readFromUser) {
    printf("You can write");
    while (getchar() != '\n');
    

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

    int len = strlen(*readFromUser);
    int flag = 1;
    for (int i = 0; i < len; i++) {
        if ((*readFromUser)[i] == ' ') {
            flag = 0;
            break; // No need to continue, we already found a space
        }
    }
    if (flag == 0) {
        printf("\nInput contains spaces, only one word allowed!\n"); 
        free(*readFromUser);
        *readFromUser = NULL; // Set to NULL to indicate failure or invalid input
    }
}


int main() {
    int chose;
    int stop = 1;
    
    StrList* list = StrList_alloc();
    while(stop!=0){
        scanf("%d" , &chose );
    
        if (chose == 1) {
            printf("\nPress 'A' to add to the list: ");
            char read;
            scanf(" %c", &read); 

        if (read == 'A') {
            printf("\nChoose the number of words to add to the list: ");
            int numOfStrings;
            scanf(" %d", &numOfStrings);

            while (getchar() != '\n');

            printf("\nYou can write:\n ");
            char *readFromUser; 
            char buffer[50]; 

            fgets(buffer, sizeof(buffer), stdin);

            size_t inputLength = strlen(buffer);

            readFromUser = (char *)malloc((inputLength + 1) * sizeof(char));

            if (readFromUser == NULL) {
            printf("Memory allocation failed.\n");
            return 0;
            }

            strcpy(readFromUser, buffer);

            if (readFromUser[inputLength - 1] == '\n')
            readFromUser[inputLength - 1] = '\0';

            printf("You insert to the list: %s\n", readFromUser);

 
            char *stringsList[numOfStrings]; 
            int currentStringIndex = 0; 

            for (int i = 0; i < numOfStrings; i++) {
                stringsList[i] = (char *)malloc(1 * sizeof(char)); 
                stringsList[i][0] = '\0'; 
            }

            for (int i = 0; readFromUser[i] != '\0'; i++) {
                if (readFromUser[i] != ' ') {
                    int length = strlen(stringsList[currentStringIndex]);
                    stringsList[currentStringIndex] = (char *)realloc(stringsList[currentStringIndex], (length + 2) * sizeof(char));
                    stringsList[currentStringIndex][length] = readFromUser[i];
                    stringsList[currentStringIndex][length + 1] = '\0'; 
                } else {
                    currentStringIndex++;
                    if (currentStringIndex >= numOfStrings) {
                        printf("Invalid input: too many words.\n");
                        break; 
                    }
                    }
            }   

            for (int i = 0; i < numOfStrings; i++) {
                StrList_insertLast(list, stringsList[i]);

                free(stringsList[i]);
            }  
            free(readFromUser);       
        }

        }else if(chose == 2) {
            printf("choose index\n:");
            int index;
            scanf("%d", &index);
            printf("Word at index %d: ", index);
            printf("\nYou can write:\n ");

            char* readFromUser;
            getString(&readFromUser);
            printf("%s\nS", readFromUser);
            StrList_insertAt(list, readFromUser,index);
            free(readFromUser);    

        }else if (chose == 3) {
            printf("\nThe full List:\n");

            StrList_print(list);
            

            
        }else if (chose == 4) {
            printf("Length of the list: %zu\n", StrList_size(list));

        }else if (chose == 5) {
            printf("choose index\n:");
            int index;
            printf("Word at index %d: ", index);
            scanf(" %d", &index);
            StrList_printAt(list, index);

        }else if (chose == 6) {
            printf("\nList numbers of char: %d\n", StrList_printLen(list));            

        }else if (chose == 7) {
            char* readFromUser;
            getString(&readFromUser);
            printf("%s\nS", readFromUser);
            printf("\nthe word %s shows %d times\n",readFromUser, StrList_count(list,readFromUser));
            free(readFromUser);  

        }else if (chose == 8) {
            printf("Write which word do you want to delete from the list\n");
            char* readFromUser;
            getString(&readFromUser);
            printf("%s\nS", readFromUser);
             
            StrList_remove(list, readFromUser);
            free(readFromUser);

        }else if (chose == 9) {
            printf("choose index that you want to remove\n:");
            int index;
            scanf("%d", &index);
            
            StrList_removeAt(list,index);
            printf("Word at index %d removed ", index);


        }else if (chose == 10) {
            StrList_reverse(list);

        }else if (chose == 11) {
            int listLen = StrList_size(list);

            while (listLen>=0)
            {
                StrList_removeAt(list,0);
                listLen--;

            }

        }else if (chose == 12) {
            StrList_sort(list);

        }else if (chose == 13) {
            printf("\nIs the list sorted? %s\n", StrList_isSorted(list) ? "Yes" : "No");

        }else if (chose == 0) {
            stop = 0;
        }
    }
    StrList_free(list);

    return 0;

}
   