// list/list.c
// 
// Implementation for linked list.

// <Author - Kyndall Jones>
// Collaborated with: Zoe Carter and Abigial Thomas
// Resources: stackoverflow and geeksforgeeks

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

list_t *list_alloc() { 
  list_t* list = (list_t*)malloc(sizeof(list_t));
  list->head = NULL;
  
  return list; 
}

node_t *node_alloc(block_t *blk) {   
  node_t* node = malloc(sizeof(node_t));
  node->next = NULL;
  node->blk = blk;
  
  return node; 
}

void list_free(list_t *l){
  free(l);
  return;
}

void node_free(node_t *node){
  free(node);
  return;
}

void list_print(list_t *l) {
  node_t *curr = l->head;
  block_t *b;
  
  if (curr == NULL)
  {
    printf("list is empty\n");
  }
  while (curr != NULL){
    b = curr->blk;
    printf("PID=%d START:%d END:%d", b->pid, b->start, b->end);
   
    curr = curr->next;
  }
}

int list_length(list_t *l) { 
  node_t *curr = l->head;
  int i=0;
  
  while (curr != NULL)
  {
    i++;
    curr = curr->next;
  }
  
  return i; 
}

void list_add_to_back(list_t *l, block_t *blk){  
  node_t* newNode = node_alloc(blk);
  newNode->next = NULL;
  
  if(l->head == NULL)
  {
    l->head = newNode;
  }
  else{
    node_t *curr = l->head;
    
    while(curr->next != NULL)
    {
      curr = curr->next;
    }
    curr->next = newNode;
  }
}

void list_add_to_front(list_t *l, block_t *blk){  
  node_t* newNode = node_alloc(blk);
 
  newNode->next = l->head;
  l->head = newNode;
}

void list_add_at_index(list_t *l, block_t *blk, int index){
  int i=0;
  
  node_t *newNode = node_alloc(blk);
  node_t *curr = l->head;

  if(index == 0){
    newNode->next = l->head->next;
    l->head = newNode;
  }
  else if(index > 0){
    while(i < index && curr->next != NULL){
      curr = curr->next;
      i++;
    }
  newNode->next = curr->next;
  curr->next = newNode;
  }
}

void list_add_ascending_by_address(list_t *l, block_t *blk){
  
   /*
   * 1. Insert newblk into list l in ascending order based on the START address of the block.
   * 
   *    node_t *c = l.head;
   *    Insert newblk After Current Node if:   newblk->start > c->start
   */
   
   node_t *curr;
   node_t *prev;
   node_t *newNode = node_alloc(blk);

   int newblk_add = blk->start;
   int curblk_add;

   if(l->head == NULL)
   {
     l->head = newNode;
   }
   else 
   {
     prev = curr = l->head;
     curblk_add = curr->blk->start;

     if (curr -> next == NULL) {
       if (newblk_add <= curblk_add) {
         newNode -> next = l->head;
         l->head = newNode;
       }
       else 
       {
         curr->next = newNode;
         newNode->next = NULL;
       }
     }
     else {
       if (newblk_add <= curblk_add) {
         newNode->next = l->head;
         l->head = newNode;
       }
       else {
         while (curr!= NULL && newblk_add > curblk_add) {
           prev = curr;
           curr = curr -> next;
         }
         prev->next = newNode;
         newNode->next = curr;
       }
     }
   }
}

void list_add_ascending_by_blocksize(list_t *l, block_t *newblk){
   /*
   * 1. Insert newblk into list l in ascending order based on the blocksize.
   *    blocksize is calculated :  blocksize = end - start +1
   * 
   *    Ex:  blocksize = newblk->end - newblk->start
   * 
   *         node_t *c = l.head;
   * 
   *         curr_blocksize = c->blk->end - c->blk->start +1;
   * 
   *         Insert newblk After Current Node if:   blocksize >= curr_blocksize
   * 
   *    USE the compareSize()
   */
   node_t *curr; 
   node_t *prev;
   node_t *newNode = node_alloc(newblk);
   int newblk_size = newblk->end - newblk->start;
   int currblock_size;

   if (l->head == NULL)
   {
     l->head = newNode;
   }
   else
   {
     prev = curr = l->head;
     currblock_size = (curr->blk->end) - (curr->blk->start) + 1;

     if (curr->next == NULL) {
       if (newblk_size <= currblock_size) { // puts in front of current node
         newNode->next = l->head;
         l->head = newNode;
       }
       else { // puts behind current node
         curr->next = newNode; 
         newNode->next = NULL;
       }
     }
     else {
       if (newblk_size <= currblock_size) {
         curr->next = l->head;
         newNode->next = NULL;
       }
       else {
         while (curr != NULL && newblk_size >= currblock_size)
         {
           prev = curr;
           curr = curr->next;
           
           if(curr != NULL)
           currblock_size = curr->blk->end - curr->blk->start;
          
          }
          prev->next = newNode;
          newNode->next = curr;
      }
    }
  }
}

void list_add_descending_by_blocksize(list_t *l, block_t *blk){
  node_t *curr;
  node_t *prev;
  node_t *newNode = node_alloc(blk);
  int newblk_size = blk->end - blk->start;
  int currblock_size;
  
  if(l->head == NULL){
    l->head = newNode;
  }
  else{
    prev = curr = l->head;
    
    currblock_size = curr->blk->end - curr->blk->start + 1;
    
    if(curr->next == NULL) {  //only one node in list
       if(newblk_size >= currblock_size) {  // place in front of current node
          newNode->next = l->head;
          l->head = newNode;
       }
       else {   // place behind current node
          curr->next = newNode;
          newNode->next = NULL;
       }
    }
    else {  // two or more nodes in list
      
       if(newblk_size >= currblock_size) {  // place in front of current node
          newNode->next = l->head;
          l->head = newNode;
       }
       else {
      
          while(curr != NULL && newblk_size <= currblock_size) {
               prev = curr;
               curr = curr->next;
               
               if(curr != NULL)  // the last one in the list
                     currblock_size = curr->blk->end - curr->blk->start;
          }
          prev->next = newNode;
          newNode->next = curr;
       }
    }
  }
}

void list_coalese_nodes(list_t *l){ 
  /*
   * 1. Assuming you have passed in a sorted list of blocks based on addresses in ascending order
   * 2. While list is not empty,
   *    a. compare two nodes at a time to see if the prev.END + 1 == current.START, if so, they are physically adjacent
   *    combine them by setting the prev.END = current.END. 
   *    b. If not adjacent go to #6
   * 3. point the prev.NEXT to the current.NEXT to skip over current.
   * 4. Free current
   * 5. go back to #2
   * 6. Advance prev = current, and current = current.NEXT
   * 7. go back to #2
   * 
   * USE the compareSize()
   */

   if (!l->head || !l->head->next) { return; }
   node_t *curr = l->head;
   node_t *prev = l->head->next;

   while (curr) 
   {
     if (prev->blk->end +1 == curr->blk->start) {
       prev->blk->end = curr->blk->end;
       prev->next = curr->next;
       free(curr);
       curr = prev->next;
     }
     else {
       prev = curr;
       curr = curr->next;
     }
   }
}

block_t* list_remove_from_back(list_t *l){
  block_t *value = NULL;
  node_t *curr = l->head;

  if(l->head != NULL){
    
    if(curr->next == NULL) { // one node
         l->head->next = NULL;
         value = curr->blk;
         node_free(curr);
    }
    else {
         while (curr->next->next != NULL){
            curr = curr->next;
         }
         value = curr->blk;
         node_free(curr->next);
         curr->next = NULL;
    }
  }
  return value;
}

block_t* list_get_from_front(list_t *l) {
  block_t *value = NULL;
  if(l->head == NULL){
    return value;
  }
  else{
    node_t *curr = l->head;
    value = curr->blk;
  }
  return value; 
}


block_t* list_remove_from_front(list_t *l) { 
  block_t *value = NULL;
  if(l->head == NULL){
    return value;
  }
  else{
    node_t *curr = l->head;
    value = curr->blk;
    l->head = l->head->next;
    node_free(curr);
  }
  return value; 
}

block_t* list_remove_at_index(list_t *l, int index) { 
  int i;
  block_t* value = NULL;
  
  bool found = false;
  
  if(l->head == NULL){
    return value;
  }
  else if (index == 0){
    return list_remove_from_front(l);
  }
  else if (index > 0){
    node_t *curr = l->head;
    node_t *prev = curr;
    
    i = 0;
    while(curr != NULL && !found){
      if(i == index)
          found = true;
      else {
         prev = curr;
         curr = curr->next;
         i++;
      }
    }
    
    if(found) {
      value = curr->blk; 
      prev->next = curr->next;
      node_free(curr);
    }
  }
  return value; 
}

bool compareBlks(block_t* a, block_t *b) {
  
  if(a->pid == b->pid && a->start == b->start && a->end == b->end)
     return true;
  
  return false;
}

bool compareSize(int a, block_t *b) {  // greater or equal
  
  if(a <= (b->end - b->start) + 1)
     return true;
  
  return false;
}

bool comparePid(int a, block_t *b) {
  
  if(a == b->pid)
     return true;
  
  return false;
}


bool list_is_in(list_t *l, block_t* value) { 
  node_t *curr = l->head;
  while(curr != NULL){
    if(compareBlks(value, curr->blk)){
      return true;
    }
    curr = curr->next;
  }
return false; 
}

block_t* list_get_elem_at(list_t *l, int index) { 
 int i;
  block_t* value = NULL;
  if(l->head == NULL){
    return value;
  }
  else if (index == 0){
    return list_get_from_front(l);
  }

  else if (index > 0){
    node_t *curr = l->head;
    
    i = 0;
    while(curr != NULL){
      if(i == index)
          return(curr->blk);
      else {
         curr = curr->next;
         i++;
      }
    }
  }
  return value; 
}

int list_get_index_of(list_t *l, block_t* value){
 int i = 0;
 node_t *curr = l->head;
 if(l->head == NULL){
    return -1;
  }
  
  while (curr != NULL){
   if (compareBlks(value,curr->blk)){
     return i;
    }
    curr = curr->next;
    i++;
  }
  return -1; 
}

/* Checks to see if block of Size or greater exists in the list. */
bool list_is_in_by_size(list_t *l, int Size){ 
  node_t *curr = l->head;
  while(curr != NULL){
    if(compareSize(Size, curr->blk)){
      return true;
    }
    curr = curr->next;
  }
return false; 
}

/* Checks to see if pid of block exists in the list. */
bool list_is_in_by_pid(list_t *l, int pid){ 
  
  /* Iterate through the list to find a node with a blk that has blk->pid = pid
   * 
   * USE the comparePID()
   * 
   * Look at list_is_in_by_size()
  */

  node_t *curr = l->head;

  if(l->head == NULL) {
    return -1;
  }
  while (curr != NULL) 
  {
    if (comparePid(pid, curr->blk)) {
      return true;
    }
    curr = curr->next;
  }
  return false;
}

/* Returns the index at which the given block of Size or greater appears. */
int list_get_index_of_by_Size(list_t *l, int Size){
 int i = 0;
 node_t *curr = l->head;

 if(l->head == NULL){
    return -1;
  }
  
  while (curr != NULL){
   if (compareSize(Size,curr->blk)){
     return i;
    }
    curr = curr->next;
    i++;
  }

  return -1; 
}
                   
/* Returns the index at which the pid appears. */
int list_get_index_of_by_Pid(list_t *l, int pid){
 int i = 0;
 node_t *curr = l->head;
 if(l->head == NULL){
    return -1;
  }
  
  while (curr != NULL){
   if (comparePid(pid,curr->blk)){
     return i;
    }
    curr = curr->next;
    i++;
  }

  return -1; 
}