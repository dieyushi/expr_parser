#ifndef EXPRESSION_TREE_H_
#define EXPRESSION_TREE_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

enum operation {
	AND, OR, EQ, CT
};

enum node_type {
	OP, LEFT, RIGHT
};

union node_value {
	char *string_literal;
	enum operation op;
};

typedef struct node {
	struct node *left_child;
	struct node *right_child;
	enum node_type type;
	union node_value value;
} node_t;

node_t* make_op_node(enum operation op);

node_t* make_left_node(char *literal);

node_t* make_right_node(char *literal);

int evaluate_expression(node_t *root);

void print_expression(node_t *root);

#endif
