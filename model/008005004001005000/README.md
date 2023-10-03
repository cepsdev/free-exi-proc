<pre>
📎 8.5.4.1.5 Particles


Given an XML Schema particle P_i with {min occurs}, {max occurs} and {term} properties, generate a grammar Particle_i for evaluating instances
of P_i as follows.

If {term} is an element declaration, generate the grammar Term_0 according to section 8.5.4.1.6 Element Terms. If {term} is a wildcard, generate
the grammar Term_0 according to section 8.5.4.1.6 Element Terms. If {term} is a wildcard, generate the grammar Term_0 according to section
8.5.4.1.7 Wildcard Terms. If {term} is a model group, generate the grammar Term_0 according to section 8.5.4.1.8 Model Group Terms.

Create {min occurs} copies of Term_0.

        G_0, G_1, ... . G_{ {min occurs} - 1}

If {max occurs} is not unbounded, create {max occurs} - {min occurs} additional copies of Term_0,

        G_{min occurs}, G_{{min occurs} + 1}, ... , G_{{max occurs}-1}

Add the following productions to each of the grammars that do not already have a production of this form.

        G_{i,0} :
                EE      where {min occurs} &lt;= i &lt; {max occurs}

indicating these instances of Term_0 may be omitted from the content model. Then, create the grammar for Particle_i using the grammar
concatenation operator defined in section 8.5.4.1.1 Grammar Concatenation Operator as follows:

        Particle_i = G_0 + G_1 + ... + G_{{max occurs }- 1}

Otherwise, if {max occurs} is unbounded, generate one additional copy of Term_{0, G_{min occurs}} and replace all productions of the form

        G_{{min occurs},k} :
                EE
        
        with productions of the form:
        
        G_{{min occurs}, k}:
                G_{{min occurs}, 0}

indicating this term may be repeated indefinitely. Then , when there is no more production of the form:

        G_{{min occurs},0}:
                EE

add one after the other productions with the non-terminal G_{{min occurs},0} on the left-hand side, indicating this term may be omitted from the 
content model. Then, create the grammar for Particle_i using the grammar concatenation operator defined in section 8.5.4.1.1 Grammar Concatenation
Operator as follows:

        Particle_i = G_0 + G_1 + ... + G_{min occurs}


</pre>


