#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "StrList.h"

// --------------------
// Node struct
// --------------------

typedef struct _node{
    char *_data;
    struct _node* _next;

} Node;

// --------------------
// StrList struct
// --------------------

struct _StrList
{
    Node *_head;
    size_t _size;
};

// --------------------
// Node implementation
// --------------------

Node* Node_alloc(const char* data, Node* next) {
    Node* p = (Node*)malloc(sizeof(Node));
    if (!p) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    p->_data = strdup(data); // Copy the string
    if (!p->_data) {
        perror("String duplication failed");
        exit(EXIT_FAILURE);
    }
    p->_next = next;
    return p;
}

void Node_free(Node* node) {
    free(node->_data); // Free the string
    free(node);
}

// --------------------
// StrList implementation
// --------------------

StrList* StrList_alloc() {
    StrList* p = (StrList*)malloc(sizeof(StrList));
    if (!p) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    p->_head = NULL;
    p->_size = 0;
    return p;
}

void StrList_free(StrList* list) {
    if (!list) return;
    Node* current = list->_head;
    while (current) {
        Node* next = current->_next;
        Node_free(current);
        current = next;
    }
    free(list);
}





//-------------------
// List functions
//-------------------




/*
 * Returns the number of elements in the StrList.
 */
size_t StrList_size(const StrList* StrList){
    return StrList->_size;
}
/*
 * Inserts an element in the end of the StrList.
 */
void StrList_insertLast(StrList* StrList,const char* data){
    if(!StrList) return;
    Node* newNode = Node_alloc(data, NULL);
    if (!newNode) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    Node* p = StrList->_head;
    if (StrList->_head == NULL)
    {
        StrList->_head = newNode;
    }
    else{
        while (p->_next != NULL)
        {
            p = p->_next;
        }
        p->_next = newNode;
    }
    ++(StrList->_size);
}

/*
* Inserts an element at given index
*/
void StrList_insertAt(StrList* StrList,const char* data,int index){
    Node* p = StrList->_head;
    if(!p) return;
    if (index == 0)
    {
        StrList->_head = Node_alloc(data,p);

    }
    
    else if (index < (StrList->_size))
    {
        int i = 1;
        while (i != index)
        {
            p = p->_next;
            i++;
        }
        Node* next = p->_next;
        p->_next = Node_alloc(data,next);
    }
    else{
        StrList_insertLast(StrList,data);
    }
    ++(StrList->_size);
}

/*
 * Returns the StrList first data.
 */
char* StrList_firstData(const StrList* StrList){
    return StrList->_head->_data;
}

/*
 * Prints the StrList to the standard output.
 */
void StrList_print(const StrList* StrList){
    if (StrList->_size == 0)
    {
        return;
    }
    else{
        const Node* p1 = StrList->_head;
        int i = 0;
        while(i < StrList->_size-1){
            printf("%s ",p1->_data);
            p1 = p1->_next;
            i++;
        }
        printf("%s", p1->_data); // Print the last element without a space
    }
}

/*
 Prints the word at the given index to the standard output.
*/
void StrList_printAt(const StrList* Strlist,int index){
    const Node* p = Strlist->_head;
    if (!p) return;

    if (index == 0)
    {
        printf("%s",p->_data);
    }
    
    
    else{
        int i = 1;
        if (index < (Strlist->_size))
        {
            while (i != index)
            {
                p = p->_next;
                i++;
            }
            printf("%s",p->_next->_data);
        }
        else
        {
            while (i != (Strlist->_size)-1)
            {
                p = p->_next;
                i++;
            }
            printf("%s",p->_next->_data);
        }

    }

}

/*
 * Return the amount of chars in the list.
*/
int StrList_printLen(const StrList* Strlist){
    const Node* p = Strlist->_head;
    int count = 0;
    while(p){
        count += strlen(p->_data);
        p = p->_next;
    }
    return count;
}

/*
Given a string, return the number of times it exists in the list.
*/
int StrList_count(StrList* list, const char* data) {
    if (!list)
    {
        return 0;
    }
    
    int count = 0;
    Node* current = list->_head;
    while (current) {
        if (strcmp(current->_data, data) == 0) {
            count++;
        }
        current = current->_next;
    }
    return count;
}

/*
	Given a string and a list, remove all the appearences of this string in the list.
*/
void StrList_remove(StrList* StrList, const char* data) {
    Node* p1 = StrList->_head;
    Node* p2 = NULL;

    while (p1) {
        if (strcmp(p1->_data, data) == 0) {
            if (p1 == StrList->_head) {
                StrList->_head = p1->_next;
                Node_free(p1);
                p1 = StrList->_head;
            } else {
                p2->_next = p1->_next;
                Node_free(p1);
                p1 = p2->_next;
            }
            --(StrList->_size);
        } else {
            p2 = p1;
            p1 = p1->_next;
        }
    }
}


/*
	Given an index and a list, remove the string at that index.
*/
void StrList_removeAt(StrList* StrList, int index){
    if (StrList == NULL || StrList->_head == NULL) {
        return;
    }

    if (index == 0) {
        Node* p1 = StrList->_head;
        StrList->_head = p1->_next;
        Node_free(p1);
        --(StrList->_size);
        return;
    }

    int i = 0;
    Node* p1 = StrList->_head;
    while (p1 != NULL && i < index - 1) {
        p1 = p1->_next;
        i++;
    }

    if (p1 == NULL || p1->_next == NULL) {
        return;
    }

    Node* p2 = p1->_next;
    p1->_next = p2->_next;
    Node_free(p2);
    --(StrList->_size);
    
}

/*
 * Checks if two StrLists have the same elements
 * returns 0 if not and any other number if yes
 */
int StrList_isEqual(const StrList* StrList1, const StrList* StrList2){
    if (StrList1->_size != StrList2->_size) return 0;
    
    const Node* p1 = StrList1->_head;
    const Node* p2 = StrList2->_head;

    while (p1)
    {
        if (strcmp(p1->_data, p2->_data) != 0)
        {
            return 0;
        }
        p1 = p1->_next;
        p2 = p2->_next;
        
    }
    return 1;
}

/*
 * Clones the given StrList. 
 * It's the user responsibility to free it with StrList_free.
 */
StrList* StrList_clone(const StrList* Strlist){
    StrList* newlist = StrList_alloc();
    const Node* old = Strlist->_head;
    Node** copy = &(newlist->_head);
    newlist->_size = Strlist->_size;
    while (old)
    {
        *(copy) = Node_alloc(old->_data,NULL);
        old = old->_next;
        copy = &((*copy)->_next);
    }
    
    return newlist;
}

/*
 * Reverces the given StrList. 
*/

void StrList_reverse(StrList* Strlist) {
    if (Strlist == NULL || Strlist->_head == NULL || Strlist->_head->_next == NULL) {
        return;
    }

    Node* prev = NULL;
    Node* current = Strlist->_head;
    Node* next;

    while (current != NULL) {
        next = current->_next;
        current->_next = prev;
        prev = current;
        current = next;
    }

    Strlist->_head = prev;
}


// -------------------
// Auxiliary functions
//--------------------


/*
* Get node by index
*/
Node* StrList_getNodeAt(StrList* Strlist, int index) {
    if (!Strlist || index < 0) return NULL;

    Node* current = Strlist->_head;
    int i = 0;

    while (current && i < index) {
        current = current->_next;
        i++;
    }

    return current;
}

/*
* swap places of two nodes in LinkList
*/
void StrList_swap(StrList* Strlist, Node* p1, Node* p2) {
    if (!p1 || !p2 || p1 == p2 || !Strlist->_head) return;
    

    Node *prev_p1 = NULL, *prev_p2 = NULL;
    Node *current = Strlist->_head;

    while (current) {
        if (current->_next == p1) prev_p1 = current;
        if (current->_next == p2) prev_p2 = current;
        current = current->_next;
    }

    if (!prev_p1 && !prev_p2) return;

    if (!prev_p1) Strlist->_head = p2; 
    else prev_p1->_next = p2;

    if (!prev_p2) Strlist->_head = p1; 
    else prev_p2->_next = p1;

    Node* temp = p1->_next;
    p1->_next = p2->_next;
    p2->_next = temp;

}

/*
 * Sort the given list in lexicographical order 
 */
void StrList_sort( StrList* StrList){
    if (!StrList || !StrList->_head) return;

    int len = StrList->_size;
    Node* current_i = StrList->_head;

    for (int i = 0; i < len-1; i++){

        Node* current_j = current_i->_next;
        for (int j = i+1; j < len; j++){
            if (strcmp(current_j->_data, current_i->_data) < 0) {
                StrList_swap(StrList,current_i,current_j);                

                Node* temp = current_i;
                current_i = current_j;
                current_j = temp;


            }

            if(!current_j->_next) continue;
            else current_j = current_j->_next;

        }
        if(!current_i->_next) break;
        else current_i = current_i->_next;
    }  
}


/*
 * Checks if the given list is sorted in lexicographical order
 * returns 1 for sorted,   0 otherwise
 */
int StrList_isSorted(StrList* StrList){
    if (!StrList || !StrList->_head) return 0;
    int len = StrList->_size;
    Node* current_i = StrList->_head;
    for (int i = 0; i < len; i++){
        Node* current_j = current_i->_next;
        for (int j = i+1; j < len; j++){
            if (strcmp(current_j->_data, current_i->_data) < 0) {
                return 0;
            }
            if(current_j->_next) current_j = current_j->_next;
        }
        if(current_i->_next) current_i = current_i->_next;
    }
    return 1; 
}