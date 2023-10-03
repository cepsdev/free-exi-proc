<pre>
📎 8.5.4.1.1. Grammar Concatenation Operator


Proto-grammars are specified in a modular, comstructive fashion. XML Schema components such as terms, particles, attribute uses are transformed
each into a distinct proto-grammar, leveraging proto-grammars of their sub-components.
At various stages of proto-grammar construction, two, or more of proto-grammars are concatenated one after another to form more composite 
grammars.

The grammar concatenation operator + is a binary operator that creates a new grammar from its left and right grammar operands. The new Grammar
accepts any set of symbols accepted by its left operand followed by any set of symbols accepted by its right operand.

Given a left operand Grammar_L and a right operand Grammar_R, the following operation

    Grammar_L + Grammar_R 

creates a combined grammar by replacing each production of the from

    Grammar_L_k:
        EE
        
where 0 &lt;= k &lt; n and n is the number of non-terminals that occur on the left-hand side of productions in Grammar_L, with a production of the 
form 

    Grammar_L_k:
        Grammar_R_0

connecting each accepted state of Grammar_L with the start state of Grammar_R.


</pre>


