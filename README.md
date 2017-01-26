# cps360_assignment1
Random Number Sorter

##Problem
Create to linked lists of randomly generated numbers. One list will hold odd
numbers. The other will hold even numbers.

The program will generate as many numbers as specified in the first command
line argument. Each number will be placed into it's respective linked
list (odds in the odd list, evens in the even list).

##Solution
Create an interface for Linked List. This includes the following:
* struct lnode;
* void getnode(lnode **ptr);
* void freenode(lnode **ptr);
* void search(lnode *list, lnode **crnt, lnode **pred, int x);
* int delfromlist(lnode **list, lnode *after);
* int insertinlist(lnode **list, int x);
* void printlist(lnode *list);
* void freelist(lnode **list);
