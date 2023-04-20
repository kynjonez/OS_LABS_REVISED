// list/list.c
//
// Implementation for linked list.
//
// <Author - Kyndall Jones>
// Collaborated with: Zoe Carter / Abigail Thomas

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "list.h"
 
list_t *list_alloc() 
{ 
  list_t* list_new = (list_t*) malloc(sizeof(list_t));
   
  list_new->head = NULL;
  return list_new;
}

 node_t *node_alloc(elem val) 
 {
   node_t* new_node = (node_t*)malloc(sizeof(node_t));
   
   new_node->value = val;
   new_node->next = NULL;
   return new_node;
 }

 void list_free(list_t *l) 
 {
   node_t *curr = l->head;
   while (curr != NULL)
   {
     node_t *temp_curr = curr->next;
     free(curr);
     curr = temp_curr;
   }
   if (curr == NULL){
     printf("Empty list");
   }
 }

 char* toString(list_t *l) 
 {
   char temp[250];
 }

 void node_free(node_t *n)
 {
   free(n);
 }
 
void list_print(list_t *l)
{
 node_t *curr = l->head;
 while (curr != NULL)
 {
   print("%d", curr->value);
   curr = curr->next;
 }
 if (curr == NULL){
   printf("Empty list");
 }
}
 
int list_length(list_t *l)
{
 int count = 0;
 node_t *curr = l->head;
 while(curr != NULL){
   count++;
   curr = curr->next;
 }
 return count;
}

void list_add_to_back(list_t *l, elem value)
{
  node_t *app_value;
  node_t *curr = l->head;
  app_value = node_alloc(value);
  while(curr->next != NULL){
    curr = curr -> next;
  }
  curr -> next = app_value;
  app_value -> next = NULL;
  if (curr == NULL){
    printf("Empty list");
  }
}
 
void list_add_to_front(list_t *l, elem value)
{
 node_t *head = malloc(sizeof(node_t));
 head->value = value;
 head->next = l->head;
 l->head = head;
}
 
void list_add_at_index(list_t *l, elem value, int index)
{
  int add = 0;
  node_t *curr = l->head;
  node_t *temp = NULL;
  node_t *app_value;
  app_value = node_alloc(value);
  if (index == 0) {
    return list_add_to_front(l, value);
  }
  while (add < index) 
  {
    temp = curr; 
    curr = curr->next;
    add++;
  }
  temp->next = app_value;
  app_value->next = curr;
}

elem list_remove_from_back(list_t *l)
{
 node_t *curr = l->head;
 if (curr == NULL) {
   return;
 }
 while (curr->next != NULL) {
   curr = curr->next;
 }
 elem prev = curr->value;
 free(curr);
 return prev;
}
 
elem list_remove_from_front(list_t *l)
{
  node_t *curr = l->head;
  if (curr == NULL) 
  {
    printf("Empty list");
    return ;
  }
  node_t *list_start = l->head;
  
  elem retval = l->head->value;
  list_start = l->head;
  l->head = l->head->next;
  
  free(list_start);
  return retval;
}
 
elem list_remove_at_index(list_t *l, int index)
{
  node_t *curr = l->head;
  if (curr = NULL)
  {
    printf("Empty list");
    return ;
  }
  int remove = 0;
  node_t *temp = l->head;
  while(temp->next != NULL && remove < index)
  {
    temp = temp->next;
    remove++;
  }
  node_t *rem_elem = temp->next;
  elem val = temp->next->value;
  temp -> next = temp->next->next;
  free(rem_elem);
  return val;
}
 
bool list_is_in(list_t *l, elem value)
{
 node_t *curr = l->head;
 while (curr != NULL)
 {
   if (curr->value == value) 
   {
     return true;
   }
   curr = curr->next;
 }
 return false;
}
 
elem list_get_elem_at(list_t *l, int index)
{
  int get_element = 0;
  node_t *curr = l->head;
  while (curr != NULL)
  {
    if (get_element == index)
    {
      return curr->value;
    }
    curr = curr->next;
    get_element++;
 }
 return -1;
}
 
int list_get_index_of(list_t *l, elem value)
{
 node_t *curr = l->head;
 while (l->head != NULL)
 {
   if (l->head->value != value) 
   {
     l->head = l->head->next;
   }
   else
   {
     l->head = curr;
     return true;
   }
 }
 l->head = curr;
 return -1;
}

