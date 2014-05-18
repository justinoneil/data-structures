#ifndef LIST

#define LIST

struct node {
  int data;
  struct node *next;
};

struct node *listnew(size_t);
struct node *listcopy(const struct node *);
void listfree(struct node *);
struct node *listappend(struct node *, struct node *);
struct node *listappendcopy(struct node *, const struct node *);
struct node *listinsert(struct node *, int, struct node *);
struct node *listinsertcopy(struct node *, int, const struct node *);
size_t listsize(const struct node *);
struct node *listgetnode(struct node *, int);
int listgetdata(const struct node *, int);
void listsetdata(struct node *, int, int);
struct node *listdelelem(struct node *, int);

#endif
