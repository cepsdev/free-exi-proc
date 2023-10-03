<pre>
📎 8.5.4.1.3. Type Grammars


Given an XML Schema type definition T_i with properties {name} and {target namespace}, two type grammars are created,
which are denoted by Type_i and TypeEmpty_i. [Definition:] Type_i is a grammar that fully reflects
the type definition of T_i, whereas [Definition:] TypeEmpty_i is a grammar that regards only the
attribute uses and attribute wildcards of T_i, if any.

The grammar Type_i is used for evaluating the content of elements that are defined to be of type T_i in the schema.
[Definition:] Type_i is a global type grammar when T_i is a named type. Type_i, when it is a global type grammar,
can additionally be used as the effective grammar designated by a xsi:type attribute with the attribute value
that is a qname with local-name = {name} and uri={target namespace}. TypeEmpty_i is used in place of Type_i when
the element instamce that is being evaluated has a xsi:nil attribute with the value true.

Sections 8.5.4.1.3.1 Simple Type Grammars and 8.5.4.1.3.2. Complex Type Grammars describe the processes for
creating Type_i and TypeEmpty_i from XML Schema simple type definitions and complex type definitions defined
in schemas as well as built-in primitive types, built-in derived types, simple ur-type and complex ur-type defined
by XML Schema specification [XML Schema Datatypes].
📎 8.5.4.1.3.1 Simple Type Grammars


This section describes the process for creating an EXI type grammar from an XML Schema simple type defintion.
Given a simple type definition T_i, create two new EXI grammars Type_i and TypeEmpty_i following the
procedure described below. Add the following grammar productions to Type_i and TypeEmpty_i:

Syntax:

    Type_i,0 :
            CH[schema-typed value] Type_i,1
    Type_i,1:
            EE 
    typeEmpty_i,0:
            EE

Note:
    Productions of the form LEftHandSide:CH [schema-typed value] RightHandSide represent typed character data 
    that can be represented using the EXI datatype representation associated with the simple type definition
    (see 7. Representing Event Content). Character data that can be represented using EXI datatype representation
    associated with the simple type SHOULD be represented this way. Character data that is not represented using the
    EXI datatype representation associated with the simple type definition is represented by productions of the
    form LeftHandSide: CH[untyped value] RightHandSide described in section 8.5.4.4 Undeclared Productions.

📎 8.5.4.1.3.2 Complex Type Grammars


This section describes the process for creating an EXI type grammar from an XML Schema complex type defnition.

Given a complex type definition T_i, with properties {name}, {target namespace}, {attribute uses}, {attribute wildcard} and {content type}, create
two EXI grammars Type_i and TypeEmpty_i following the procedure described below.

Generate a grammar Attribute_i , for each attribute use A_i in {attribute uses} according to section 8.5.4.1.4 Attribute Uses.

Sort the attribute use grammars first by qname local-name, then by qname uri to form a sequence of grammars G_0,G_1,..., G_{n-1}, where n is the number of attributes
uses in {attribute uses}. If an {attribute wildcard} is specified, increment n and generate additional attribute use grammars G_{n-1} as follows:

        G_{n-1},0 :
                EE
        G_{n-1},1 :
                EE

When the {attribute wildcard}'s {namespace constraint} is any, or a pair of not and either a namespace name or the special value absent indicating no namespace,
add the following production to each grammar G_i generated above where 0 &lt;= i &lt; n:

        G_{i,0}:
                AT(*) G_{i,0}

Otherwise, that is, when {namespace constraint} is a set of values whose members are namespace names or the special value absent indicating no namespace, add the
following production to each grammar G_i generated above where 0 &lt;= i &lt; n:

        G_{i,0} :
                AT(uri_X:*) G_{i,0}
where uri_X is a member value of {namespace constraint}, provided that it is the empty string (i.e. &quot;&quot;) that is used as uri_X when the member value is the 
special value absent. Each uri_X is used to augment the uri partition of the String table. Section 7.3.1 String Table Partition describes how these uri strings are production
into String table for pre-population.

If there is neither an attribute use or an {attribute wildcard}, G_0 of the following form is used as an attribute use grammar.

        G_{0,0}:
                EE

Note:

When xsi:type and/or xsi:nil attributes appear in an element where schema-informed grammars are in effect, they MUST occur before any AT events of the same element,
with xsi:type placed before xsi:nil when both occur.

Semantics:

In complex type grammars, all productions of the form LeftHandSide: AT(*) RightHandSide and LeftHandSide: AT(uri_X:*) RightHandSide that stem from attribute wildcards
are evaluated as follows:
        1. Let qname be the qname of the attribute matched by AT(*) or AT(uri_x:*)
        2. If a global attribute definition exists for qname, let global-type be the datatype of the global attribute. If the attribute value can be represented using
           the datatype representation associated with global-type, it SHOULD be represented using the datatype representation associated with global-type (see
           7. Representing Event Content). If the attribute value is not represented using the datatype representation associated with global-type, represent the
           attribute event using the AT(*) [untyped value] terminal (see 8.5.4.4 Undeclared Productions).

        Note: 

        When a schema-informed grammar is in effect, xsi:type and xsi:nil attributes MUST NOT be represented using [the] AT(*) terminal.

The grammar TypeEmpty_i is created by combining the sequence of attribute use grammars terminated by an empty {content type} grammar as follows:

        TypeEmpty_i = G_0 + G_1 + ... + G_{n-1} + Content_i

where the grammar Content_i is created as follows:

        Content_{i,0} :
                        EE

The grammar Type_i is generated as follows.

If {content type} is a simple type definition T_j, generate a grammar Content_i as Type_j according to section 8.5.4.1.3.1 Simple Type Grammars.
If {content type} has a content model particle, generate a grammar Content_i according to section 8.5.4.1.5 Particles. Otherwise, if
{content type} is empty, create a grammar Content_i as follows:

        Content_i :
                        EE

If {content type} is a content model particle with mixed content, add a production for each non-terminal Content_{i,j} in Content_i as follows:

        Content_{i,j}:
                        CH [untyped value] Content_{i,j}

Note:
        The value of each Characters event that has an [untyped value] is represented as a String (see 7.1.10 String).

Then, create a copy H_i of each attribute use grammar G_i and create the grammar Type_i by combining this sequence of attribute use grammars
and the Content_i grammar using the grammar concatenation operator defined in section 8.5.4.1.1 Grammar Concatenation Operator as follows:

        Type_i = H_0 + H_1 + ... H_{n-1} + Content_i

📎 8.5.4.1.4 Attribute Uses


Given an attribute use A_i with properties {required} and {attribute declaration}, where {attribute declaration} has properties {name}, 
{target namespace}, {type definition} and {scope}, generate a new EXI grammar Attribute_i for evaluating attributes in the specified {scope} 
with qname local-name = {name} and qname uri = {target namespace} where qname is the qname of attributes.
Add the following grammar productions to Attribute_i:

        Attribute_{i,0} :
                        AT(qname) [schema-typed value] Attribute_{i,1}
        Attriute_{i,1}  :
                        EE

If the {required} property of A_i is false, add the following grammar production to indicate this attribute occurence may be omitted from
the content model.

        Attribute_{i,0} :
                        EE

Note:
        Productions of the form LeftHandSide:AT(qname) [schema-typed value] RightHandSide represent typed attributes that occur in
        schema-valid contexts with values that can be represented using the EXI datatype representation associated with the attribute's name
        {type definition} (see 7.Representing Event Content). Attributes that occur in schema-valid contexts that can be represented using
        the EXI datatype representation associated with the attribute's {type definition}, SHOULD be represented this way. Attributes that
        are not represented this way, are represented using the alternate forms of AT events described in section 8.5.4.4 Undeclared Productions.
       


</pre>


