#include "expression.h"

static node_t* alloc_node()
{
    node_t *node = (node_t*)malloc(sizeof(node_t));
    if (node == NULL)
        return 0;
    memset(node, 0, sizeof(node_t));
    return node;
}

static int eval_eq_node(node_t *node)
{
    int ret = strcmp(node->left_child->value.string_literal, node->right_child->value.string_literal);
    return (ret == 0);
}

static int eval_ct_node(node_t *node)
{
    char *ret = strstr(node->left_child->value.string_literal, node->right_child->value.string_literal);
    return (ret != 0);
}

node_t* make_op_node(enum operation op)
{
    node_t* node = alloc_node();
    node->type = OP;
    node->value.op = op;
    return node;
}

node_t* make_left_node(char *literal)
{
    node_t *node = alloc_node();
    node->type = LEFT;
    node->value.string_literal = literal;
    return node;
}

node_t * make_right_node(char *literal)
{
    node_t *node = alloc_node();
    node->type = RIGHT;
    node->value.string_literal = literal;
    return node;
}

int evaluate_expression(node_t *root)
{
    if (!root) return 1;
    switch (root->type) {
        case LEFT:
        case RIGHT:
            return 1;
        case OP:
            break;
    }
    switch (root->value.op) {
        case EQ:
            return eval_eq_node(root);
        case CT:
            return eval_ct_node(root);
        case AND:
            return (evaluate_expression(root->left_child)
                    && evaluate_expression(root->right_child));
        case OR:
            return (evaluate_expression(root->left_child)
                    || evaluate_expression(root->right_child));
    }
    return 0;
}

void print_expression(node_t *root)
{
    static const char *ops[] = {"&&", "||", "==", "^^"};
    if (!root) return;
    printf("%s", "(");
    print_expression(root->left_child);
    switch(root->type) {
        case OP:
            printf(" %s ", ops[root->value.op]);
            break;
        case LEFT:
            printf("(%s", root->value.string_literal);
            break;
        case RIGHT:
            printf("%s)", root->value.string_literal);
            break;
        default:
            break;
    }
    print_expression(root->right_child);
    printf("%s", ")");
}
