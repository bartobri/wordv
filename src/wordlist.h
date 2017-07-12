#ifndef WORDLIST_H
#define WORDLIST_H 1

typedef struct node *listlink;
struct node {
	char *word;
	listlink next;
};

void     wordlist_init(void);
listlink wordlist_new(char *);
void     wordlist_add(char *);
char    *wordlist_get(void);
void     wordlist_reset(void);
char    *wordlist_get2(void);
void     wordlist_reset2(void);

#endif
