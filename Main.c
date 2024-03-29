
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "StrList.h"

#define CHUNK 12;

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
void printIfChoseNotZero(int chose,int lastChose){

    if ((lastChose == 3 || lastChose == 4 || lastChose == 5 || lastChose == 6 || lastChose == 7 || lastChose == 13) && chose !=0 )
    {
        printf("\n");
    }
    
}


int main() {


    int chose;
    int stop = 1;
    int lastChose = -1;
    
    StrList* list = StrList_alloc();
    
    
    do {
        
        scanf("%d",&chose);
        printIfChoseNotZero(chose,lastChose);
        if (chose == 1) {
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
                insertToList[j] = '\0'; // Null-terminate the string

                    
                StrList_insertLast(list, insertToList);
                    
                // Skip spaces if any
                while (readFromUser[index] == ' ') {
                    index++;
                }
            }
                
            free(readFromUser); // Free the original input string
            lastChose = chose;

            
        } 
        else if (chose == 2) {
            int index;
            scanf("%d", &index);
            char insertString[50] = {0};
            scanf("%s", insertString);
            StrList_insertAt(list, insertString,index);
            lastChose = chose;

        } 
        else if (chose == 3) {

            StrList_print(list);
            lastChose = chose;
            
        } 
        else if (chose == 4) {
            printf("%ld", StrList_size(list));
            lastChose = chose;

        } 
        else if (chose == 5) {
            int index;
            scanf("%d", &index);
            StrList_printAt(list, index);
            lastChose = chose;

        } 
        else if (chose == 6) {
            printf("%d", StrList_printLen(list));
            lastChose = chose;

            
        } 
        else if (chose == 7) {
            char insertString[50] = {0};
            scanf("%s", insertString);
            printf("%d", StrList_count(list, insertString));
            lastChose = chose;

        } 
        else if (chose == 8) {
            char* readFromUser = getString(stdin);
            StrList_remove(list, readFromUser);
            free(readFromUser);
            lastChose = chose;
        } 
        else if (chose == 9) {
            int index;
            scanf("%d", &index);
            StrList_removeAt(list,index);
            lastChose = chose;

        } 
        else if (chose == 10) {
            StrList_reverse(list);
            lastChose = chose;

        } 
        else if (chose == 11) {
            int listLen = StrList_size(list);
            while (listLen>=0) {
                StrList_removeAt(list,0);
                listLen--;
            }
            lastChose = chose;

        } 
        else if (chose == 12) {
            StrList_sort(list);
            lastChose = chose;

        } 
        else if (chose == 13) {
            printf("%s", StrList_isSorted(list) ? "true" : "false");
            lastChose = chose;
        } 
        else if (chose == 0) {

            stop = 0;
            printf("\n");
        } 
        
    } while(stop!=0);
    
    StrList_free(list);
    return 0;
}
