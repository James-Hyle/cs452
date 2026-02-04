#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "deq.h"
#include "error.h"

// AUTHOR: JAMES HYLE
// PROFESSOR: BUFFENBARGER
// CLASS: CS452 OPERATING SYSTEMS
// SEMESTER: SPRING 2026

// indices for array of node pointers
// Head is ~prev~
// Tail is ~next~
typedef enum { Head, Tail, Ends } End;

// struct for nodes holding data values in list
typedef struct Node {
	struct Node *np[Ends]; // next/prev neighbors
	Data data;
} *Node;

// struct for head/tail of list
typedef struct {
	Node ht[Ends]; // head/tail nodes
	int len;
} *Rep;

// representation for list
static Rep rep(Deq q) {
	if (!q) ERROR("zero pointer");
	return (Rep)q;
}

// method to insert nodes at either head or tail of list
static void put(Rep r, End e, Data d) {
	// guard
	if (!r) return;
	if (!d) return;

	// allocate new node for insertion, return 0 if malloc fails
	Node nn = malloc(sizeof(struct Node));
	if (!nn) return; // guard
	// put data inside new node
	nn->data = d;

	// if inserting at head, set new node previous(head) pointer to null
	// set newNodes next pointer to current head
	// set current heads prev pointer to newNode
	nn->np[e] = NULL;
	nn->np[!e] = r->ht[e];

	// if list is empty newNode.next(tail) points to null as well
	if (r->len == 0) r->ht[!e] = nn;
	// else current end to points to new node
	else r->ht[e]->np[e] = nn;

	// end points to new node
	r->ht[e] = nn;
	// increase length of deque
	r->len++;
}

// method to iterate through list by index
static Data ith(Rep r, End e, int i) {
	// guard
	if (!r || i < 0) return 0;

	// get node at end of list
	Node curr = r->ht[e];
	// iterate through list until i is reached
	for (int j = 0; j < i; j++) {
		curr = curr->np[!e];
	}
	// after correct node is reached return data inside
	return curr->data;
}

// return data from one end of the list
static Data get(Rep r, End e) {
	// guard
	if (!r || r->len == 0) return NULL;

	Node curr;
	if ((curr = r->ht[e])) {
		// get data to return 
		Data retData = curr->data;

		r->ht[e] = curr->np[!e];

		if (r->ht[e]) r->ht[e]->np[e] = NULL;	 
		else r->ht[!e] = NULL;

		// cleanup
		free(curr);
		// decrease length of list
		r->len--;

		return retData;
	}

	return NULL;
}

// method to remove node from end of list 
static Data rem(Rep r, End e, Data d) {
	if (!r || !d) return NULL;
	// get current node from end of list
	Node curr = r->ht[e];

	// iterate through nodes
	while (curr != NULL) {
		// check for correct node to remove
		if (curr->data == d) {
			// get data to return 
			Data retData = curr->data;

			// set pointers
			Node prevNode = curr->np[e];
			Node nextNode = curr->np[!e];

			if (prevNode) prevNode->np[!e] = nextNode;
			else r->ht[e] = nextNode;

			if (nextNode) nextNode->np[e] = prevNode;
			else r->ht[!e] = prevNode;

			// memory safety
			free(curr);
			r->len--;
			return retData;
		}
		// iterate on list
		curr = curr->np[!e];
	}
	return 0;
}

extern Deq deq_new() {
	// Allocate memory for new deq
	Rep r = (Rep)malloc(sizeof(*r));
	if (!r) ERROR("malloc() failed");
	r->ht[Head] = 0;
	r->ht[Tail] = 0;
	r->len = 0;
	return r;
}

extern int deq_len(Deq q) { return rep(q)->len; }

extern void deq_head_put(Deq q, Data d) { put(rep(q), Head, d); }
extern Data deq_head_get(Deq q) { return get(rep(q), Head); }
extern Data deq_head_ith(Deq q, int i) { return ith(rep(q), Head, i); }
extern Data deq_head_rem(Deq q, Data d) { return rem(rep(q), Head, d); }

extern void deq_tail_put(Deq q, Data d) { put(rep(q), Tail, d); }
extern Data deq_tail_get(Deq q) { return get(rep(q), Tail); }
extern Data deq_tail_ith(Deq q, int i) { return ith(rep(q), Tail, i); }
extern Data deq_tail_rem(Deq q, Data d) { return rem(rep(q), Tail, d); }

extern void deq_map(Deq q, DeqMapF f) {
	for (Node n = rep(q)->ht[Head]; n; n = n->np[Tail])
		f(n->data);
}

extern void deq_del(Deq q, DeqMapF f) {
	if (f) deq_map(q, f);
	Node curr = rep(q)->ht[Head];
	while (curr) {
		Node next = curr->np[Tail];
		free(curr);
		curr = next;
	}
	free(q);
}

extern Str deq_str(Deq q, DeqStrF f) {
	char *s = strdup("");
	for (Node n = rep(q)->ht[Head]; n; n = n->np[Tail]) {
		char *d = f ? f(n->data) : n->data;
		char *t;
		asprintf(&t, "%s%s%s", s, (*s ? " " : ""), d);
		free(s);
		s = t;
		if (f) free(d);
	}
	return s;
}
