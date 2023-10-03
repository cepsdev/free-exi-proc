<pre>
📎 8.5.4.1.2. Element Grammars


This section describes the process for creating an EXI element grammar from an XML Schema element declaration.
Given an element declaration E_i, with properties {name}, {target namespace}, {type definition}, {scope} and {nilanle}, create 
a corresponding EXI grammar Element_i for evaluating the contents of elements in the specified {scope} with qname local-name {name} and qname 
uri = {target namespace} where qname is the qname of the elements.

Let T_j be the {type definition} of E_i and Type_j be the type grammar created from T_j. The grammar Element_i describing the content model of
E_i is created as follows.

Syntax:

    Element_i,0:
        Type_j,0

</pre>


