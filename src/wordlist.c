#include <stdlib.h>
#include "wordlist.h"

static listlink head, p, p2;

void wordlist_init(void) {
	head = NULL;
}

listlink wordlist_new(char *word) {
	listlink x = malloc(sizeof *x);
	x->word = word;
	x->next = NULL;

	return x;
}

void wordlist_add(char *word) {
	listlink x;

	if (head == NULL) {
		head = wordlist_new(word);
		p = head;
		return;
	}
	
	x = wordlist_new(word);
	x->next = p->next;
	p->next = x;
	p = x;
}

char *wordlist_get(void) {
	char *r;
	
	if (p == NULL) {
		r = NULL;
	} else {
		r = p->word;
		p = p->next;
	}
	
	return r;
}

void wordlist_reset(void) {
	p = head;
}

char *wordlist_get2(void) {
	char *r;
	
	if (p2 == NULL) {
		r = NULL;
	} else {
		r = p2->word;
		p2 = p2->next;
	}
	
	return r;
}

void wordlist_reset2(void) {
	p2 = head;
}
