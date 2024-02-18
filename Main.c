
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "StrList.h"

void StrList_swap(StrList* Strlist, int index1, int index2) ;

int main() {
    // Create a new empty StrList
    StrList* list = StrList_alloc();

    // Insert elements into the list
    StrList_insertLast(list, "apple");
    StrList_insertLast(list, "banana");
    StrList_insertLast(list, "orange");
    StrList_insertLast(list, "kiwi");
    StrList_insertLast(list, "car");

    StrList_insertLast(list, "google");

    StrList_insertLast(list, "fml");

    StrList_insertLast(list, "bdkmv");


    // Print the original list
    printf("Original List:\n");
    StrList_print(list);

    // Insert an element at index 2
    StrList_insertAt(list, "grape", 2);

    // Print the modified list
    printf("\nList after insertion at index 2:\n");
    StrList_print(list);

    // Insert an element at index 2
    StrList_insertAt(list, "grape", 2);

    // Print the modified list
    printf("\nList after insertion at index 2:\n");
    StrList_print(list);


    // Print the number of chars
    printf("\nList numbers of char: %d\n", StrList_printLen(list));
    
    // Print how many time the string "grape" shows
    printf("\ngrape shows %d times\n", StrList_count(list,"grape"));

    // Print the first data in the list
    printf("\nFirst data in the list: %s\n", StrList_firstData(list));

    // Print the length of the list
    printf("Length of the list: %zu\n", StrList_size(list));

    // Print the word at index 3
    printf("Word at index 3: ");
    StrList_printAt(list, 3);

    // Remove an element from the list
    StrList_remove(list, "banana");

    // Print the list after removal
    printf("\nList after removing 'banana':\n");
    StrList_print(list);

    // Remove an element from the list
    StrList_remove(list, "grape");

    // Print the list after removal
    printf("\nList after removing 'grape':\n");
    StrList_print(list);

    // Clone the list
    StrList* clone = StrList_clone(list);

    // Check if the clone is equal to the original list
    printf("\nIs the clone equal to the original list? %s\n", StrList_isEqual(list, clone) ? "Yes" : "No");

    // Reverse the list
    StrList_reverse(list);
    
    // Print the length of the list
    printf("Length of the list: %zu\n", StrList_size(list));

    // Print the reversed list
    printf("\nReversed list:\n");
    StrList_print(list);

    // Sort the list
    StrList_sort(list);

    // Print the sorted list
    printf("\nSorted list:\n");
    StrList_print(list);

    // Check if the list is sorted
    printf("\nIs the list sorted? %s\n", StrList_isSorted(list) ? "Yes" : "No");

    // Free memory allocated for the list and its clone
    StrList_free(list);
    StrList_free(clone);

    return 0;
}