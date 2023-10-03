<pre>
📎 6. Encoding EXI Streams

<span style="color: rgb(245,245,245);">witness{</span>

--------------------------------------------------------------------------------
001 6. Encoding EXI Streams
002
003 The rules for encoding a series of events as en EXI stream are very simple 
004 an are driven by a declarative set of grammars that describes the structure 
005 of an EXI stream.
006 Every event in the stream is encoded using the same set of encoding rules, 
007 which are summarized as follows:
008
009 1. Get the next event data to be encoded
010 2. If fidelity options (see 6.3 Fidelity Options) indicate this event type  
011    is not processed, go to step 1
012 3. Use the grammars to determins the event code of the event
013 4. Encode the event code followed by the event content (see Table 4-1)
014 5. Evalutae the grammar production matched by the event
015 6. Repeat until the End Document (ED) event is encoded
016
017 Self-contained (SC), namespace (NS) and attribute (AT) events associated 
018 with a given element occur directly after the start element (SE) event in  
019 the following order:

 <span style="color: rgb(245,245,245);">EXIStreamOrdering{</span><span style="color:teal;">SC</span>
<span style="color:teal;">NS</span>
<span style="color:teal;">NS</span>
<span style="color: rgb(245,245,245);">&quot;...&quot;</span>
<span style="color:teal;">NS</span>
<span style="color: rgb(245,245,245);">AT</span>((<span style="color:teal;">xsi</span><span style="color: rgb(245,245,245);">:</span><span style="color:teal;">type</span>))
<span style="color: rgb(245,245,245);">AT</span>((<span style="color:teal;">xsi</span><span style="color: rgb(245,245,245);">:</span><span style="color:teal;">nil</span>))
<span style="color:teal;">AT</span>
<span style="color:teal;">AT</span>
<span style="color: rgb(245,245,245);">&quot;...&quot;</span>
<span style="color:teal;">AT</span>
 <span style="color: rgb(245,245,245);">}</span> 


020 Namespace (NS) events occur in document order. The xsi:type and xsi:nil 
021 attributes occur before all other AT events. When the grammar currently in 
022 effect for the element is either a built-in element grammar (see 8.4.3  
023 Built-in Element Grammar) or a schema-informed element fragment grammar  
024 (see 8.5.3 Schema-informed Element Fragment Grammar), the remaining  
025 attribute (AT) events can occur in any order. Otherwise, when the grammar 
026 in effect is a schema-informed element grammar or a schema-informed type 
027 grammar (see 8.5.4 Schema-informed Element and Type Grammars), the remaining 
028  attributes can occur in any order that is permitted by the grammar, though 
029 in practice they SHOULD occur in lexicographical order sorted first by qname  
030 local-name then by qname uri for achieving better compactness, where a qname
031 is a qname of an attribute.
032
033 Note:
034
035 Under certain circumstances, it is not strictly required that the xsi:type 
036 or xsi:nil attributes occur before other AT events of the same elemnt. See 
037 the notes in section 8.4.3 Built-in Element Grammar for details.
038
039 EXI uses the same simple procedure described above, to encode well-formed 
040 documents, document fragments, schema-valid information items, schema- 
041 invalid information items, information items partially described by  
042 schemas and information items with no schema at all. Only the grammars that  
043 describe these items differ. For example, an element with no schema  
044 information is encoded according to the XML grammar defined by the XML  
045 specification, while an element with schema information is encoded according  
046 to the more specific grammar defined by that schema.
047
048 [Definition:] An event code is a sequence of 1 to 3 non-negative integers 
049 called parts used to identify each event in an EXI stream. The EXI grammars 
050 describe which events may occur at each point in an EXI stream and associate
051 an event code with each one (See 8.2. Grammar Event Codes for more 
052 description of event codes.)
053 
054 Section 6.1 Determining Event Codes describes in detail how the grammar is used
055 to determine the event code of an event. Section 6.2 Representing Event Codes
056 describes available fidelity options and how they affect the EXI stream.
057 Section 7. Representing Event Content describes how the typed event contents
058 are represented as bits.


<span style="color: rgb(245,245,245);">}</span>

</pre>


