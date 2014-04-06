#include <stdio.h>
#include "expression.h"
#include "lexer.h"
#include "parser.h"

extern int yyparse();

node_t *zfilter;

int main(int argc, char *argv[])
{
    if (argc != 2)
        return printf("Usage: %s rule", argv[0]);

    YY_BUFFER_STATE buffer_stat = yy_scan_string(argv[1]);
    int ret = yyparse();
    yy_delete_buffer(buffer_stat);

    if (ret == 0) {
        printf ("Expression: ");
        print_expression(zfilter);
        printf("\n");
        printf("Result: %d\n", evaluate_expression(zfilter));
    }
	return 0;
}
