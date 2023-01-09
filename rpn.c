#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef __LINKEDLIST_H
#define __LINKEDLIST_H

/**
 * A doubly linked-list node.
 */
typedef struct ll_node_s {
    int value;
    struct ll_node_s *prev;
    struct ll_node_s *next;
} ll_node;


/**
 * Returns a pointer to the first node of a list, given a pointer to any node
 * in the list. If the provided pointer is `NULL`, instead returns `NULL`.
 */
ll_node *ll_head(ll_node *list);

/**
 * Returns a pointer to the last node of a list, given a pointer to any node
 * in the list. If the provided pointer is `NULL`, instead returns `NULL`.
 */
ll_node *ll_tail(ll_node *list);

/**
 * Returns the number of nodes in the list, which is the same for all nodes
 * in the list and 0 for `NULL`.
 */
unsigned long ll_length(ll_node *list);

/**
 * Given a pointer to a node in a list, returns a pointer to the first node
 * at or *before* that node which has the given `value`. If given `NULL`, or
 * if no such node exists, returns `NULL`.
 */
ll_node *ll_find(ll_node *list, int value);

/**
 * Given a pointer to a node in a list, remove that node from the list,
 * `free`ing its memory in the process. Returns a pointer to the node that now
 * occupies the same position in the list that the removed node used to occupy
 * (which may be `NULL` if the removed node was the last node in the list).
 *
 * If given `NULL`, this function does nothing and returns `NULL`.
 */
ll_node *ll_remove(ll_node *list);

/**
 * Extend a list by one by adding `value` next to `list`. If `before` is 0,
 * inserts `value` immediately following the node pointed to by `list`;
 * otherwise inserts `value` immediately before that node. If `list` is NULL,
 * the newly inserted node is the entire list. In all cases, the new node is
 * allocated using `malloc` and returned by the function.
 */
ll_node *ll_insert(int value, ll_node *list, int before);

/**
 * Displays the contents of the list separated by commas and surrounded by
 * brackets, with the pointed-to node highlighted with asterisks.
 */
void ll_show(ll_node *list);


#endif /* ifdef __LINKEDLIST_H */



ll_node *ll_head(ll_node *list){
    //TODO: Implement this function, see header file for description
    //TODO: Update return statement.
        if (list == NULL){
                return NULL;
        }
	if (list->prev == NULL){
                return list;
        }
	else {
              	return ll_head(list->prev);
        }
}
ll_node *ll_tail(ll_node *list) {
    //TODO: Implement this function, see header file for description
    //TODO: Update return statement.
        if (list == NULL){
                return NULL;
        }
	if (list->next == NULL){
                return list;
        }
	else {
              	return ll_tail(list->next);
        }
}
unsigned long ll_length(ll_node *list) {
    //TODO: Implement this function, see header file for description
    //TODO: Update return statement.
        if (list == NULL){
                return 0;
        }
	ll_node *i = ll_head(list);
        int length = 1;
        while (i->next != NULL){
                length += 1;
                i = i->next;
        }
	return length;
}
ll_node *ll_find(ll_node *list, int value) {
    //TODO: Implement this function, see header file for description
    //TODO: Update return statement.
        if (list == NULL){
                return NULL;
        }
	if (list->value == value){
                return list;
        }
	if (list->prev == NULL){
                return NULL;
        }
	else{
             	return ll_find(list->prev, value);
        }
}
ll_node *ll_remove(ll_node *list) {
    //TODO: Implement this function, see header file for description
    //TODO: Update return statement.
        if (list == NULL){
                return NULL;
        }
	if (list->next != NULL){
                if (list->prev != NULL){
                        ll_node *prev = list->prev;
                        ll_node *next = list->next;
                        prev->next = next;
                        next->prev = prev;
                        free(list);
	                return next;
                }
                else{
                     	ll_node *next = list->next;
                        next->prev = NULL;
                        free(list);
	                return next;
                }
        }
	if (list->prev != NULL){
                        ll_node *prev = list->prev;
                        prev->next = NULL;
                        free(list);
                        return NULL;
        }
        else{
                free(list);
                return NULL;
        }

}
ll_node *ll_insert(int value, ll_node *list, int before) {
    //TODO: Implement this function, see header file for description
    //TODO: Update return statement.
	if (list == NULL){
                ll_node *new_list = (ll_node *) malloc(sizeof(ll_node));
                new_list->value = value;
                new_list->prev = NULL;
                new_list->next = NULL;
                return new_list;
        }
	else{
             	if (before){
                        ll_node *new =(ll_node *) malloc(sizeof(ll_node));
                        new->value = value;
                        if (list->prev != NULL){
                                ll_node *prev = list->prev;
                                prev->next = new;
                                list->prev = new;
                                new->prev = prev;
                                new->next = list;
                                return new;                                       
                        }
                        else{
                             	new->next = list;
                                new->prev = NULL;
                                list->prev = new;
                                return new;
                        }
                }                
		else{
                     	ll_node *new =(ll_node *) malloc(sizeof(ll_node));
                        new->value = value;
                        if (list->next != NULL){
                                ll_node *next = list->next;
                                next->prev = new;
                                list->next = new;
                                new->prev = list;
                                new->next = next;
                                return new;
                        }
                        else{
                             	new->prev = list;
                                new->next = NULL;
                                list->next = new;
                                return new;
                        }
                }
        }
}
/**
 * Displays the contents of the list separated by commas and surrounded by
 * brackets, with the pointed-to node highlighted with asterisks.
 *
 * Reference solution provided with assignment description
 */
void ll_show(ll_node *list) {
    ll_node *ptr = ll_tail(list);
    putchar('[');
    while(ptr) {
        if (ptr->next) printf(", ");
        printf("%d", ptr->value);
        ptr = ptr->prev;
    }
    puts("]");
}


 int  main(){
	char *found;
        ll_node *stack = NULL;
        char buffer[256];
        char *string;
        int breaker = 0;
        while (breaker == 0){
                fgets(buffer, 256, stdin);
                string = strdup(buffer);
                while( (found = strsep(&string," ")) != NULL ){
                        char *non_num;
                        if ((strcmp (found, ""))&&((strcmp (found, "\n")))){
                                long num = strtol(found, &non_num, 10);
                                if ((strcmp (non_num, "")==0)||(strcmp (non_num, "\n")==0)){
                                /* Non-white space and number */
                                        stack = ll_insert(num, stack, 1);
                                        ll_show(ll_head(stack));
                                }
                                else{
                                /* Non-white space and non-number */
                                        if ((strcmp (non_num, "+")==0)||(strcmp (non_num, "+\n")==0)){
                                                if (ll_length(ll_head(stack)) >= 2){
                                                        ll_node *head = ll_head(stack);
                                                        head->next->value += head->value;
                                                        stack = ll_remove(head);
                                                        ll_show(ll_head(stack));
                                                }
                                                else{
                                                    /* not enough args*/
                                                        ll_show(ll_head(stack));
                                                        breaker += 1;
                                                }
                                        }
                                        else if ((strcmp (non_num, "-")==0)||(strcmp (non_num, "-\n"))==0){
                                                if (ll_length(ll_head(stack)) >= 2){
                                                        ll_node *head = ll_head(stack);
                                                        head->next->value -= head->value;
                                                        stack = ll_remove(head);
                                                        ll_show(ll_head(stack));
                                                }
                                                else{
                                                    /* not enough args*/
                                                        ll_show(ll_head(stack));
                                                        breaker += 1;
                                                }
                                        }
                                        else if ((strcmp (non_num, "*")==0)||(strcmp (non_num, "*\n")==0)){
                                                if (ll_length(ll_head(stack)) >= 2){
                                                        ll_node *head = ll_head(stack);
                                                        head->next->value *= head->value;
                                                        stack = ll_remove(head);
                                                        ll_show(ll_head(stack));
                                                }
                                                else{
                                                    /* not enough args*/
                                                        ll_show(ll_head(stack));
                                                        breaker += 1;
                                                }
                                        }
                                        else if ((strcmp (non_num, "/")==0)||(strcmp (non_num, "/\n")==0)){
                                                if (ll_length(ll_head(stack)) >= 2){
                                                        ll_node *head = ll_head(stack);
                                                        head->next->value /= head->value;
                                                        stack = ll_remove(head);
                                                        ll_show(ll_head(stack));
                                                }
                                                else{
                                                     	/* not enough args*/
                                                        ll_show(ll_head(stack));
                                                        breaker += 1;
                                                }
                                        }
                                        else{
                                             	/* invalid character*/
                                                breaker += 1;
                                                return(0);
                                        }
                                }
                        }
                        else{}
                }
                for (int i = 0; i<256; i+=1){
                        buffer[i] = (char) 0;
                }
                if(feof(stdin)) return(0);
        }
	return (0);
}













