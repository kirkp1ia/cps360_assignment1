/*
 * Problem:
 * Create to linked lists of randomly generated numbers. One list will hold odd
 *    numbers. The other will hold even numbers.
 *
 * The program will generate as many numbers as specified in the first command
 *    line argument. Each number will be placed into it's respective linked
 *    list (odds in the odd list, evens in the even list).
 *
 * Solution:
 * Create an interface for Linked List. This includes the following:
 *    - struct lnode;
 *    - void getnode(lnode **ptr);
 *    - void freenode(lnode **ptr);
 *    - void search(lnode *list, lnode **crnt, lnode **pred, int x);
 *    - int delfromlist(lnode **list, lnode *after);
 *    - int insertinlist(lnode **list, int x);
 *    - void printlist(lnode *list);
 *    - void freelist(lnode **list);
 *
 * In main, a random number is generated and added to it's respective
 *    list. NULL pointers were a nuisance. There's a lot of checks throughout
 *    the code to do something special if a NULL pointer is passed into
 *    a parameter.
 *
 *    A check is also done to make sure that no bad input is processed. If a
 *    non-numeric character is entered into the second argument or if no
 *    argument is supplied in the first place, then an error message is shown
 *    explaining that the user must input a number into the second argument.
 *
 * At the end, after all numbers have been generated and placed into a list,
 *    the program prints each list, frees up both lists' memory and then exits
 *    with a code of 0.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define RANGE 7

struct lnode {
  int value;
  struct lnode *next;
};
typedef struct lnode lnode;

/* Generates the next number */
int nextnum() {
  return random() % RANGE;
}

/* Gets a node for list using malloc(). The caller should check
a1.txt Page 2 of 3
for call failure */
void getnode(lnode **ptr) {
  *ptr = malloc(sizeof(lnode));
}

/* Returns node storage to system using free(). */
void freenode(lnode **ptr) {
  if(*ptr) free(*ptr);
  *ptr = NULL;
}

/* Searches list for node containing x, if found crnt is
defined and pred points to crnt’s predecessor node.
Crnt is undefined otherwise and pred has no meaning. */
void search(lnode *list, lnode **crnt, lnode **pred, int x) {
  *crnt = list;
  *pred = NULL;
  while(*crnt) {
    if((*crnt)->value == x) return;
    *pred = *crnt;
    *crnt = (*crnt)->next;
  }
}

/* Deletes the node from list that is successor of the node
pointed by after. Returns 1 on success, 0 otherwise. */
int delfromlist(lnode **list, lnode *after) {
  if (after == NULL) {
    lnode *todel = *list;
    lnode *data_after = todel->next;
    *list = data_after;
    freenode(&todel);
    return 1;
  }
  if (after->next) {
    lnode *todel = after->next;
    lnode *data_after = todel->next;
    after->next = data_after;
    freenode(&todel);
    return 1;
  } else return 0;
}

/* Inserts x at the front of list if not found in list, deletes it
from the list otherwise. Returns 1 on success, 0 otherwise,
calls search() */
int insertinlist(lnode **list, int x) {
  lnode *xnode;
  lnode *pred;

  if (*list == NULL) {
    lnode *newnode;
    getnode(&newnode);
    newnode->value = x;
    *list = newnode;
    return 1;
  }

  search(*list, &xnode, &pred, x);
  if (xnode) {
    delfromlist(list, pred);
    return 0;
  } else {
    lnode *newnode;
    getnode(&newnode);
    newnode->value = x;
    newnode->next = *list;
    *list = newnode;
    return 1;
  }
}

/* Prints the contents of given list (on one line on stdout) */
void printlist(lnode *list) {
  lnode *n = list;
  while (n) {
    printf("%d", n->value);
    if (n->next) {
      n = n->next;
      printf(" ");
    } else n = NULL;
  }
  printf("\n");
}

/* Returns the node storage to system for nodes in the list, one
node at a time. Calls freenode(). Returns empty list to caller. */
void freelist(lnode **list) {
  lnode *ptr, *tp;
  ptr = *list;
  while(ptr) {
    tp = ptr;
    ptr = ptr->next;
    freenode(&tp);
  }
  *list = NULL;
}

/* Returns 1 if num is odd and 0 if num is even. */
int isodd(int num) {
  return (int) (num & 0x01);
}

int main(int argc, char *argv[]) {
  lnode *lodds = NULL;
  lnode *levens = NULL;

  srand(time(NULL));

  long int iterations = 0;
  if (argc > 1) iterations = strtol(argv[1], NULL, 10);
  long int count = 0;

  if (iterations == 0) {
    fprintf(stderr, "Please enter a number as the second argument.\n");
    exit(1);
  }

  for (count; count < iterations; count++) {
    int n = nextnum();
    if (isodd(n)) insertinlist(&lodds, n);
    else insertinlist(&levens, n);
  }

  printf("odd-list:  ");
  if (lodds) printlist(lodds);
  else printf("empty\n");
  printf("even-list: ");
  if (levens) printlist(levens);
  else printf("empty\n");

  freelist(&lodds);
  freelist(&levens);
  exit(0);
}
