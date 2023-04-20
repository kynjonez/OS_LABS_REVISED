// <Author - Kyndall Jones>
// Collaborated with: Zoe Carter and Julian Forbes
 
#include <stdio.h>
#include "list.h"
 
int main()
{
 printf("Write your Tests for your linked list implementation\n");
  list_t *mylist;
  mylist = list_alloc();
 
 list_add_to_front(mylist, 1);
 list_add_to_back(mylist, 3);
 list_add_at_index(mylist, 2, 1);
 list_add_to_back(mylist, 4);
 list_print(mylist);
 printf("My list contains %d elements\n", list_length(mylist));
 
 // 0
 int second_element = list_remove_at_index(mylist, 2);
 // 4
 int back_element = list_add_to_back(mylist, 2);
 // 1
 int front_element = list_remove_from_front(mylist);
 
 printf("3rd Element: %d\nBack of List: %d\nFront of List: %d\n", second_element, back_element, front_element);
 
 if (list_is_in(mylist, 2))
 {
   printf("2 was removed so it IS in the list.\n");
 }
 if (!list_is_in(mylist, 4))
 {
   printf("4 was removed so it is NOT in the list.\n");
 }
 int get_elem = list_get_elem_at(mylist, 1);
 int index = list_get_index_of(mylist, get_elem);
 printf("The element %d is at the index %d\n", get_elem, index);
}
