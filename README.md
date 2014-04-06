## expr_parser
---

#### What is this

A parser to calculate AND-OR string expression.

For example,

    ./expr_parser "abc == abc && ab ^^ a"

means `abc equals abc AND ab contains a`, which is True.

This program's output is


    Expression: ((((abc) == (abc))) && (((ab) ^^ (a))))
    Result: 1

expr_parser supports below four Operators and `(`,`)`

Operator|Description
---|---
A && B|A AND B
A \|\ B||A OR B
A == B| string A equals to string B
A ^^ B| string A contains string B

#### What this can do

Many applications need to support filtering input or output.

They can simply extend this code for their programs for supporting more operators.

To use this code, you need replace the **RIGHT** string with your own data.
