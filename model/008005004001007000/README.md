<pre>
📎 8.5.4.1.7 Wildcard Terms



Given a particle {term} PT_i that is an XML Schema wildcard declaration with property {namespace constraint}, a grammar that reflects the wildcard
definition is created as follows.

Create a grammar ParticleTerm_i containing the following grammar production:

    ParticleTerm_{i,1}:
        EE

When the wildcaard's {namespace constraint} is any, or a pair of not and either a namespace name or the special value absent indicating no namespace,
add the following production to ParticleTerm_i.

    ParticleTerm_{i,0}:
        SE(*) ParticleTerm_{i,1}

Otherwise, that is, when {namespace constraint} is a set of values whose members are namespace names or the special value absent indicating no namespace,
add the following production to ParticleTerm_i:

    ParticleTerm_{i,0}:
        SE(uri_x:*) ParticleTerm_{i,1}

for each member value uri_x in {namespace constraint}, provided that it is the empty string (i.e.&quot;&quot;) that is used as uri_x when the member value is
the special value absent. Each uri_x is used to augment the uri partition of the String table. Section 7.3 String Table Partitions describes how
these uri strings are put into String table for prepopulation.

Semantics:

In a schema-informed grammar, all productions of the form LeftHandSide: Terminal RightHandSide where Terminal is one of SE(*) or SE(uri_x:*) are evaluated
as follows:

    1. Let qname be the qname of the element matched by SE(*) or SE(uri_x:*)
    2. If a global element grammar does not exist for element qname, create one according to section 8.4.3. Built-in Element Grammar.
    3. Evaluate the element content using the global element grammar for element qname.
    4. Evaluate the remainder of the event sequence using RightHandSide


</pre>


