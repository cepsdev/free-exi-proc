<pre>
📎 8.5.4.1.6 Element Terms


Given a particle {term} PT_i that is an XML Schema element declaration wit properties {name},
{substitution group affiliation} and {target namespace}, let S be the set of element declarations that directly
or indirectly reaches the element declaration PT_i through the chain of {substitution group affiliation} property of the elements, plus PT_i itself
if [it] was not in the set. Sort the elment declarations in S lexicographically first by {name} then by {target namespace}, which makes a sorted
list of element declarations E_0,E_1, ... , E_{n-1} where n is the cardinality of S. Then create the grammar ParticleTerm_i with the following
grammar productions:

Syntax:

    ParticleTerm_{i,0}:
        SE(qname_0) ParticleTerm_{i,1}
        SE(qname_1) ParticleTerm_{i,1}
        .
        .
        .
        SE(qname_{n-1}) ParticleTerm_{i,1}
    ParticleTerm_{i,1}:
        EE

Note:

    In the productions above, qname_x (where 0 &lt;= x &lt; n) represents a qname of which local-name and uri are {name} property and
    {target namespace} property of the element declaration E_x, repectively.

Semantics:

    In a schema-informed grammar, all productions of the form LeftHandside: SE(qname) RightHandside are evaluated as follows:

    1. Evaluate the element contents using SE(qname) grammar.
    2. Evaluate the remainder of the event sequence using RightHandSide.

        
<span style="color: rgb(245,245,245);">Example{</span>
Notation: &lt;element_i&gt;...&lt;/element_i&gt; is written element_i{...};
  <span style="color: rgb(245,245,245);">elem_a{</span> <span style="color: rgb(245,245,245);">}</span>  <span style="color: rgb(245,245,245);">elem_b{</span><span style="color:teal;">substitution_group</span><span style="color: rgb(245,245,245);"> = </span><span style="color:teal;">elem_a</span>
 <span style="color: rgb(245,245,245);">}</span>means: anywhere where elem_a is allowed, elem_b is. The set S is {elem_a, elem_b}  <span style="color: rgb(245,245,245);">elem_a{</span> <span style="color: rgb(245,245,245);">}</span>  <span style="color: rgb(245,245,245);">elem_b{</span><span style="color:teal;">substitution_group</span><span style="color: rgb(245,245,245);"> = </span><span style="color:teal;">elem_a</span>
 <span style="color: rgb(245,245,245);">}</span>  <span style="color: rgb(245,245,245);">elem_c{</span><span style="color:teal;">substitution_group</span><span style="color: rgb(245,245,245);"> = </span><span style="color:teal;">elem_b</span>
 <span style="color: rgb(245,245,245);">}</span>S is <span style="color:teal;">elem_a</span><span style="color:teal;">elem_b</span><span style="color:teal;">elem_c</span> 
<span style="color: rgb(245,245,245);">}</span>

</pre>


