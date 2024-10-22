#include "sorted-list.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Acknowledgements: stack representation as a linked list from in class demo
*/


/**
 * Initialize a sorted list.
 *
 * \param lst This is a pointer to space that should be initialized as a sorted list. The caller of
 * this function retains ownership of the memory that lst points to (meaning the caller must free it
 * if the pointer was returned from malloc)
 */
void sorted_list_init(sorted_list_t* lst) {
  //initialize the list
  lst->lowestValue = NULL;
  lst->highestValue = NULL;
}

/* Remove a value from the list. Used as a helper for sorted_list_destroy
 *
 * \param lst   The list that we wil remove the highestValue from
 * \returns int  The value that was removed or 0 if the list is empty
 */
int list_pop(sorted_list_t* lst) {
  // Check for an empty stack
  if (lst->lowestValue == NULL) {
    return 0;
  }

  // Get the value from the topmost node
  int result = lst->lowestValue->value;

  // Remove the top node
  node_t* oldtop = lst->lowestValue;
  lst->lowestValue = lst->lowestValue->next;

  // Clean up the old top node
  free(oldtop);

  return result;
}

/**
 * Destroy a sorted list. Free any memory allocated to store the list, but not the list itself.
 *
 * \param lst This is a pointer to the space that holds the list being destroyred. This function
 * should free any memory used to represent the list, but the caller retains ownership of the lst
 * pointer itself.
 */
void sorted_list_destroy(sorted_list_t* lst) {
  while (lst->lowestValue != NULL){
    list_pop(lst);
  }
}

/**
 * Add an element to a sorted list, maintaining the lowest-to-highest sorted order.
 *
 * \param lst   The list that is being inserted to
 * \param value The value being inserted
 */
void sorted_list_insert(sorted_list_t* lst, int value) {
  // create a new node and set its value to the parameter value
  node_t* newnode = malloc(sizeof(node_t));
  newnode->value = value;

  if (lst->highestValue == NULL && lst->lowestValue == NULL){
    //if the list is empty
    lst->lowestValue = newnode;
    // lst->lowestValue->next = NULL;

    lst->highestValue = newnode;
    lst->highestValue->next = NULL;

  } else {
    if (lst->lowestValue->value > value) {
      //when value is the new lowest value
      newnode->next = lst->lowestValue;
      lst->lowestValue = newnode;
    }else if (lst->highestValue->value < value) {
      //when value is the new highest value
      lst->highestValue->next = newnode;
      newnode->next = NULL;
      lst->highestValue = newnode;

    } else {
      //temporary nodes that will help with the traversal of the lst
      node_t* tempA;
      node_t* tempB;
      tempA = lst->lowestValue;
      tempB = tempA->next;

      //Keep track of the upper and lower node where newnode will recide between
      while (tempB != NULL && tempB->value < value) {
        tempA = tempA->next;
        tempB = tempB->next;
      }

      //place newnode between tempA and tempB
      tempA->next = newnode;
      newnode->next = tempB;
    }

  }
}

/**
 * Count how many times a value appears in a sorted list.
 *
 * \param lst The list being searched
 * \param value The value being counted
 * \returns the number of times value appears in lst
 */
size_t sorted_list_count(sorted_list_t* lst, int value) {
  //counter that will keep track of how many times value appears in lst
  int counter = 0;

  //temporary variable to keep track of position in the list
  node_t* temp;
  temp = lst->lowestValue;

  //traverse lst
  while(temp != NULL && value >= temp->value) {
    if (value == temp->value){
      counter++;
    }
    temp = temp->next;
  }

  return counter;
}

/**
 * Print the values in a sorted list in ascending order, separated by spaces and followed by a
 * newline.
 *
 * \param lst The list to print
 */
void sorted_list_print(sorted_list_t* lst) {

  //temporary variable to keep track of position in the list
  node_t* temp;
  temp = lst->lowestValue;

  //print the values
  while (temp != NULL) {
    printf("%d ", temp->value);
    temp = temp->next;
  }

  printf("\n");
}
