#ifndef LINKEDLIST_H
#define LINKEDLIST_H

struct linked_list
{
  struct linked_list* prev;
  char value;
  struct linked_list* next;
};

struct linked_list*
list_init(void);
struct linked_list*
list_create(void);
void
list_print(struct linked_list*);
char
list_pop(struct linked_list**, struct linked_list*);
void
list_append(struct linked_list**, char);
struct linked_list*
list_tail(struct linked_list*);
void
example_linked_list(void);

#endif
