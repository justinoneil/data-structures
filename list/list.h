#ifndef LIST

#define LIST

struct node {
  int data;
  struct node *next;
};

struct node *listnew(size_t);
struct node *listcopy(const struct node *);
void listfree(struct node *);
void listappend(struct node *, struct node *);
void listappendcopy(struct node *, const struct node *);
void listinsert(struct node *, int, struct node *);
void listinsertcopy(struct node *, int, const struct node *);
size_t listsize(const struct node *);
int listgetdata(const struct node *, int);
void listsetdata(struct node *, int, int);
struct node *listdelelem(struct node *, int);

#endif
