<pre>
<span style="color: rgb(245,245,245);">witness{</span>
 📎 1.2 Notational Conventions and Terminology

    --------------------------------------------------------------------------------
001 1.
002 The key words MUST, MUST NOT, REQUIRED, SHALL, SHALL NOT, SHOULD, SHOULD NOT, 
003 RECOMMENDED, MAY, and OPTIONAL, when they appear EMPHASIZED in this document, 
004 are to be interpreted as described in RFC 2119. Other terminology used to 
005 describe the EXI format is defined in the body of this specification.
006 The term event and stream is used throughout this document to denote EXI event 
007 and EXI stream respectively unless the words are qualified differently to mean 
008 otherwise.
009 This document specifies an abstract grammar for EXI. In grammar notation, all 
010 terminal symbols are represented in plain text and all non-terminal symbols are 
011 represented in italics. Grammar productions are represented as follows:
012 
013 LeftHandSide: Terminal NonTerminal
014 
015 A set of one or more grammar productions that share the same left-hand side 
016 non-terminal symbol are often presented together annotated with event codes that 
017 specify how events matching the terminal symbols of the associated productions 
018 are represented in the EXI stream as follows:
019 
020 LeftHandSide:
021  Terminal_1 NonTerminal_1    EventCode_1
022  Terminal_2 NonTerminal_2    EventCode_2
023  Terminal_3 NonTerminal_3    EventCode_3
024 
025  ...
026 
027  Terminal_n NonTerminal_n    EventCode_n 
028 
029 Section 8.1 Grammar Notation introduces additional notations for describing 
030 productions and event codes in grammars. Those additional notations facilitate 
031 concise representation of the EXI grammar system.
032 
033 [Definition:] In this document, the term qname is used to denote a QName. 
034 QName values are composed of an uri, a local-name and an optional prefix. Two 
035 qnames are considered equal if they have the same uri and local-name, 
036 regardless of their prefix values. In cases where prefixes are not relevant, 
037 such as in the grammar notation, they are not specified by this document.
038 
039 Terminal symbols that are qualified with a qname permit the use of a wildcard 
040 symbol (*) in place of or as part of a qname. The forms of terminal symbols 
041 involving qname wildcards used in grammars and their definitions are described 
042 in the table below.
043 Wildcard               Definition
044 
045 
046 SE(*)                  The terminal symbol that matches a start element (SE)
047                        event with any qname.
048 SE(uri: *)             The terminal symbol that matches a start element (SE)
049                        event with any local-name in namespace uri.
050 AT(*)                  The terminal symbol that matches an attribute (AT)
051                        event with any qname
052 AT (uri:*)             The terminal symbol that matches an attribute (AT)
053                        event with any local-name in namespace uri.
054 
055 Several prefixes are used throughout this document to designate certain 
056 namespaces.
057 The bindings shown below are assumed, however, any prefixes can be used in 
058 practice if they are properly bound to the namespaces.
059 
060 Prefix                      Namespace Name
061 exi                         http://www.w3.org/2009/exi
062 xsd                         http://www.w3.org/2001/XMLSchema
063 xsi                         http://www.w3.org/2001/XMLSchema-instance
064 
065 In describing the layout of an EXI format construct, a pair of square 
066 brackets [] are used to surround the name of a field to denote that the 
067 occurrence of the field is optional in the structure of the part or component 
068 that contains the field.
069 In arithmetic expressions, the notation |^x^| where x represents a real 
070 number denotes the ceiling of x, that is, the smallest integer greater than 
071 or equal to x.
072 When it is stated that strings are sorted in lexicographical order, it is done 
073 so character by character, and the order among characters is determines by 
074 comparing their Unicode code points.
075 
076 Unless stated otherwise, when this specification indicates one type is derived 
077 form another type, it means the type is derived by extension or restriction, not
078 by union or list. Similarly, when this specification uses the term type 
079 hierarchy, it is referring to the hierarchy of types derived from another by 
080 extension or restriction.

<span style="color: rgb(245,245,245);">}</span>

<span style="color: rgb(245,245,245);"></span><span style="font-weight:bold;color: rgb(245,245,245);">Macro </span><span style="color: rgb(245,245,245);"></span><span style="font-style:italic;color: rgb(245,245,245);"></span><span style="font-weight:bold;font-style:italic;color: rgb(245,245,245);">equality_test:</span>
 (((<span style="color: rgb(245,245,245);">symbolic_equality</span>(<span style="color: rgb(245,245,245);">as_nodeset</span>((<span style="color:teal;">arglist</span><span style="color: rgb(245,245,245);">.</span><span style="color: rgb(245,245,245);">at</span>(<span style="color: rgb(245,245,245);">0</span>))),<span style="color: rgb(245,245,245);">as_nodeset</span>((<span style="color:teal;">arglist</span><span style="color: rgb(245,245,245);">.</span><span style="color: rgb(245,245,245);">at</span>(<span style="color: rgb(245,245,245);">1</span>))))<span style="color: rgb(245,245,245);">.</span><span style="color:teal;">diff</span>)<span style="color: rgb(245,245,245);">.</span><span style="color:teal;">equal</span>)<span style="color: rgb(245,245,245);">.</span><span style="color: rgb(245,245,245);">content</span>()) 
 <span style="color: rgb(245,245,245);">exegesis{</span>
  📎 __1__2__ex_1
  <span style="color: rgb(245,245,245);">witness_ref{</span><span style="color: rgb(245,245,245);">id</span>(<span style="color:teal;">__1__2</span>)
<span style="color: rgb(245,245,245);">lines</span>((<span style="color: rgb(245,245,245);">72</span><span style="color: rgb(245,245,245);"> .. </span><span style="color: rgb(245,245,245);">74</span>))
  <span style="color: rgb(245,245,245);">}</span>  
For UTF-8 this means the 'usual' ordering, i.e. the lexicographic order as induced by the '&lt;'-relation on bytes. 
    No locale aware collation (see https://unicode.org/reports/tr10/).
 <span style="color: rgb(245,245,245);">}</span>
 <span style="color: rgb(245,245,245);">exegesis{</span>
  📎 __1__2__ex_2
  <span style="color: rgb(245,245,245);">witness_ref{</span><span style="color: rgb(245,245,245);">id</span>(<span style="color:teal;">__1__2</span>)
<span style="color: rgb(245,245,245);">lines</span>((<span style="color: rgb(245,245,245);">33</span><span style="color: rgb(245,245,245);"> .. </span><span style="color: rgb(245,245,245);">37</span>))
  <span style="color: rgb(245,245,245);">}</span>  
 <span style="color: rgb(245,245,245);">}</span>
 
 <span style="color: rgb(245,245,245);"></span><span style="font-weight:bold;color: rgb(245,245,245);">Macro </span> <span style="color: rgb(245,245,245);"></span><span style="font-style:italic;color: rgb(245,245,245);"></span><span style="font-weight:bold;font-style:italic;color: rgb(245,245,245);">qnames_equivalent:</span>
  <span style="color: rgb(245,245,245);">equality_test{</span>
   <span style="color: rgb(245,245,245);">a{</span>((((<span style="color:teal;">arglist</span><span style="color: rgb(245,245,245);">.</span><span style="color:teal;">qname</span>)<span style="color: rgb(245,245,245);">.</span><span style="color: rgb(245,245,245);">at</span>(<span style="color: rgb(245,245,245);">0</span>))<span style="color: rgb(245,245,245);">.</span><span style="color: rgb(245,245,245);">content</span>())<span style="color: rgb(245,245,245);">.</span><span style="color:teal;">uri</span>)((((<span style="color:teal;">arglist</span><span style="color: rgb(245,245,245);">.</span><span style="color:teal;">qname</span>)<span style="color: rgb(245,245,245);">.</span><span style="color: rgb(245,245,245);">at</span>(<span style="color: rgb(245,245,245);">0</span>))<span style="color: rgb(245,245,245);">.</span><span style="color: rgb(245,245,245);">content</span>())<span style="color: rgb(245,245,245);">.</span><span style="color:teal;">local_name</span>)   <span style="color: rgb(245,245,245);">}</span>   <span style="color: rgb(245,245,245);">a{</span>((((<span style="color:teal;">arglist</span><span style="color: rgb(245,245,245);">.</span><span style="color:teal;">qname</span>)<span style="color: rgb(245,245,245);">.</span><span style="color: rgb(245,245,245);">at</span>(<span style="color: rgb(245,245,245);">1</span>))<span style="color: rgb(245,245,245);">.</span><span style="color: rgb(245,245,245);">content</span>())<span style="color: rgb(245,245,245);">.</span><span style="color:teal;">uri</span>)((((<span style="color:teal;">arglist</span><span style="color: rgb(245,245,245);">.</span><span style="color:teal;">qname</span>)<span style="color: rgb(245,245,245);">.</span><span style="color: rgb(245,245,245);">at</span>(<span style="color: rgb(245,245,245);">1</span>))<span style="color: rgb(245,245,245);">.</span><span style="color: rgb(245,245,245);">content</span>())<span style="color: rgb(245,245,245);">.</span><span style="color:teal;">local_name</span>)   <span style="color: rgb(245,245,245);">}</span>  <span style="color: rgb(245,245,245);">}</span>
  
  <span style="color: rgb(245,245,245);">fact{</span>
<span style="color: rgb(245,245,245);">1</span>  <span style="color: rgb(245,245,245);">}</span>
  <span style="color: rgb(245,245,245);">fact{</span>
<span style="color: rgb(245,245,245);">1</span>  <span style="color: rgb(245,245,245);">}</span>
  <span style="color: rgb(245,245,245);">non_fact{</span>
<span style="color: rgb(245,245,245);">0</span>  <span style="color: rgb(245,245,245);">}</span>
  <span style="color: rgb(245,245,245);">example{</span>
   📎 EXI knows Right Regular grammars only
   <span style="color: rgb(245,245,245);">Grammar{</span>    <span style="color: rgb(245,245,245);">lhs{</span><span style="color: rgb(0,175,255);">NonTerminal_1</span>    <span style="color: rgb(245,245,245);">}</span>    
    <span style="color: rgb(245,245,245);">rhs{</span><span style="color: rgb(0,175,255);">Terminal_1</span>
<span style="color: rgb(0,175,255);">NonTerminal_1</span>
<span style="color: rgb(245,245,245);">EventCode</span>(<span style="color: rgb(245,245,245);">1</span>)
    <span style="color: rgb(245,245,245);">}</span>    
    <span style="color: rgb(245,245,245);">rhs{</span><span style="color: rgb(0,175,255);">Terminal_2</span>
<span style="color: rgb(0,175,255);">NonTerminal_2</span>
<span style="color: rgb(245,245,245);">EventCode</span>(<span style="color: rgb(245,245,245);">2</span>)
    <span style="color: rgb(245,245,245);">}</span>    
    <span style="color: rgb(245,245,245);">rhs{</span><span style="color: rgb(0,175,255);">Terminal_3</span>
<span style="color: rgb(0,175,255);">NonTerminal_3</span>
<span style="color: rgb(245,245,245);">EventCode</span>(<span style="color: rgb(245,245,245);">3</span>)
    <span style="color: rgb(245,245,245);">}</span>    
    <span style="color: rgb(245,245,245);">rhs{</span><span style="color: rgb(0,175,255);">Terminal_n</span>
<span style="color: rgb(0,175,255);">NonTerminal_n</span>
<span style="color: rgb(245,245,245);">EventCode</span>(<span style="color:teal;">n</span>)
    <span style="color: rgb(245,245,245);">}</span>    
   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>
  📎 Concept: Grammar_EachLHSContainsExactlyOneNonTerminal
  
  <span style="color: rgb(245,245,245);">witness_ref{</span>
<span style="color: rgb(245,245,245);">id</span>(<span style="color:teal;">__1__2</span>)
<span style="color: rgb(245,245,245);">line</span>(<span style="color: rgb(245,245,245);">13</span>)
  <span style="color: rgb(245,245,245);">}</span>
  
  <span style="color: rgb(245,245,245);"></span><span style="font-weight:bold;color: rgb(245,245,245);">Macro </span>  <span style="color: rgb(245,245,245);"></span><span style="font-style:italic;color: rgb(245,245,245);"></span><span style="font-weight:bold;font-style:italic;color: rgb(245,245,245);">CheckEXIConcept_Grammar_EachLHSContainsExactlyOneNonTerminal:</span>
   <span style="color: rgb(245,245,245);"></span><span style="font-style:italic;color: rgb(245,245,245);">violation </span><span style="color: rgb(245,245,245);"></span><span style="font-weight:bold;color: rgb(245,245,245);">:= </span><span style="color: rgb(245,245,245);">0</span><span style="color: rgb(245,245,245);"></span><span style="font-weight:bold;color: rgb(245,245,245);"></span>
   <span style="color: rgb(245,245,245);"></span><span style="font-weight:bold;color: rgb(245,245,245);">for each </span><span style="color: rgb(245,245,245);"></span><span style="font-style:italic;color: rgb(245,245,245);">e </span><span style="color: rgb(245,245,245);"></span><span style="font-weight:bold;color: rgb(245,245,245);">in </span>((<span style="color:teal;">arglist</span><span style="color: rgb(245,245,245);">.</span><span style="color:teal;">Grammar</span>)<span style="color: rgb(245,245,245);">.</span><span style="color:teal;">rhs</span>)<span style="color: rgb(245,245,245);"></span><span style="font-weight:bold;color: rgb(245,245,245);"></span>
    <span style="color: rgb(245,245,245);"></span><span style="font-weight:bold;color: rgb(245,245,245);">if </span>(((<span style="color:teal;">e</span><span style="color: rgb(245,245,245);">.</span><span style="color: rgb(245,245,245);">contains_symbol</span>(<span style="color: rgb(245,245,245);">&quot;GrammarNonterminal&quot;</span>))<span style="color: rgb(245,245,245);">.</span><span style="color: rgb(245,245,245);">size</span>())<span style="color: rgb(245,245,245);"> == </span><span style="color: rgb(245,245,245);">0</span>)<span style="color: rgb(245,245,245);"></span><span style="font-weight:bold;color: rgb(245,245,245);">:</span>
     violation
<span style="color: rgb(245,245,245);"></span><span style="font-weight:bold;color: rgb(245,245,245);">← </span><span style="color: rgb(245,245,245);">1</span><span style="color: rgb(245,245,245);"></span><span style="font-weight:bold;color: rgb(245,245,245);"></span>
     
    <span style="color: rgb(245,245,245);">!</span><span style="color:teal;">violation</span>    
    📎 Example 1 (Grammar_EachLHSContainsExactlyOneNonTerminal)
    
Example of a grammar not satisfying EXIConcept_Grammar_EachLHSContainsExactlyOneNonTerminal.    
    <span style="color: rgb(245,245,245);">Grammar{</span>
     <span style="color: rgb(245,245,245);">lhs{</span><span style="color:teal;">LeftHandSide</span>     <span style="color: rgb(245,245,245);">}</span>     
     <span style="color: rgb(245,245,245);">rhs{</span><span style="color:teal;">Terminal_1</span>     <span style="color: rgb(245,245,245);">}</span>     
    <span style="color: rgb(245,245,245);">}</span>
<span style="color: rgb(245,245,245);">0</span>    
    <span style="color: rgb(245,245,245);">tests{</span>
    <span style="color: rgb(245,245,245);">}</span>
    
</pre>
