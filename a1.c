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
 *
 * TODO:
 *    Finish methods: listtos, printlist, divide, add. Then use printlist to
 *      print both lists out.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int listlen(lnode *list) {
  int count = 0;
  lnode *nextnode;

  if (list) {
    count = 1;
    nextnode = list;
  }
  while (nextnode->next) {
    count += 1;
    nextnode = nextnode->next;
  }
  return count;
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
  } else {
    return 0;
  }
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

/* Returns a string representation of node. */
char *nodetos(lnode *node) {
  char *ptrstrval = malloc(6);

  int lenstr = sprintf(ptrstrval, "%d", node->value);

  char *toret = malloc(lenstr);
  strncpy(toret, ptrstrval, lenstr);
  return toret;
}

/* Prints the contents of given list (on one line on stdout) */
void printlist(lnode *list) {
  lnode *n = list;
  while (n) {
    char *nodestr = nodetos(n);
    printf("%s", nodestr);
    free(nodestr);
    if (n->next) {
      n = n->next;
      printf(" -> ");
    } else {
      n = NULL;
    }
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
  lnode *lodds, *levens;
  // getnode(&lodds);
  // getnode(&levens);
  printf("%d\n", lodds);
  printf("%d\n", levens);

  long int iterations = 0;
  if (argc > 1) iterations = strtol(argv[1], NULL, 10);
  long int count = 0;

  if (iterations == 0) {
    fprintf(stderr, "Expected 2 arguments in the command line. 0 given.\n");
    exit(1);
  }

  for (count; count < iterations; count++) {
    int n = nextnum();
    printf("Next number: %d\n", n);
    if (isodd(n)) {
      insertinlist(&lodds, n);
    } else {
      insertinlist(&levens, n);
    }
    printf("%d\n", lodds);
    printf("%d\n", levens);
    if (lodds) {
      printf("yo\n");
      printlist(lodds);
    } else {
      printf("Odd list has no contents.\n");
    }
    if (levens) {
      printf("hey\n");
      printlist(levens);
    } else {
      printf("Even list has no contents.\n");
    }
  }

  freelist(&lodds);
  freelist(&levens);
  exit(0);
}
