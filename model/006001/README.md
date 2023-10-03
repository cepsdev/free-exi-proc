<pre>
<span style="color: rgb(245,245,245);">Witness{</span>
 📎 6.1 Determining Event Codes

--------------------------------------------------------------------------------
001 The structure of an EXI stream is described by the EXI grammars, which are 
002 formally specified in section 8.EXI Grammars. Each grammar defines which
003 events are permitted to occur at any given point in the EXI stream and
004 provides a pre-assigned event code for each one.
005
006 For example, the grammar productions below describe the events that occur 
007 in a schema-informed EXI stream after the Start-Document (SD) event provided
008 there are four global elements defined in the schema an assign an event code
009 for each one. See 8.5.1 Schema-informed Document Grammar for the process 
010 used for generating the grammar productions below from the schema.
011
012 Example 6-1. Example productions with event codes
013
014 Syntax                               Event Code
015  DocContent
016   SE(&quot;A&quot;) DocEnd                    0
017   SE(&quot;B&quot;) DocEnd                    1
018   SE(&quot;C&quot;) DocEnd                    2
019   SE(&quot;D&quot;) DocEnd                    3
020   SE(*) DocEnd                        4
021   DT DocContent                       5.0
022   CM DocContent                       5.1.0
023   PI DocContent                       5.1.1
024
025 At the point in an EXI stream where the above grammar productions are in
026 effect, the event code of Start Element &quot;A&quot; (i.e. SE(&quot;A&quot;)) is 0.
027 The event code of a DOCTYPE(DT) event at this point in the stream is 5.0, 
028 and so on.
  
<span style="color: rgb(245,245,245);">}</span>

<span style="color: rgb(245,245,245);"></span><span style="font-weight:bold;color: rgb(245,245,245);">Macro </span><span style="color: rgb(245,245,245);"></span><span style="font-style:italic;color: rgb(245,245,245);"></span><span style="font-weight:bold;font-style:italic;color: rgb(245,245,245);">equal:</span>
 (((<span style="color: rgb(245,245,245);">symbolic_equality</span>(<span style="color: rgb(245,245,245);">as_nodeset</span>((<span style="color:teal;">arglist</span><span style="color: rgb(245,245,245);">.</span><span style="color: rgb(245,245,245);">at</span>(<span style="color: rgb(245,245,245);">0</span>))),<span style="color: rgb(245,245,245);">as_nodeset</span>((<span style="color:teal;">arglist</span><span style="color: rgb(245,245,245);">.</span><span style="color: rgb(245,245,245);">at</span>(<span style="color: rgb(245,245,245);">1</span>))))<span style="color: rgb(245,245,245);">.</span><span style="color:teal;">diff</span>)<span style="color: rgb(245,245,245);">.</span><span style="color:teal;">equal</span>)<span style="color: rgb(245,245,245);">.</span><span style="color: rgb(245,245,245);">content</span>()) 
 <span style="color: rgb(245,245,245);">exegesis{</span>
  📎 __6__1__ex_1
  <span style="color: rgb(245,245,245);">witness_ref{</span><span style="color: rgb(245,245,245);">id</span>(<span style="color:teal;">__6__1</span>)
<span style="color: rgb(245,245,245);">lines</span>((<span style="color: rgb(245,245,245);">12</span><span style="color: rgb(245,245,245);"> .. </span><span style="color: rgb(245,245,245);">28</span>))
  <span style="color: rgb(245,245,245);">}</span>  
 <span style="color: rgb(245,245,245);">}</span>
 <span style="color: rgb(245,245,245);">example_6_1{</span>
  <span style="color: rgb(245,245,245);">Grammar{</span><span style="color: rgb(0,175,255);">DocContent</span>
   <span style="color: rgb(245,245,245);">lhs{</span><span style="color: rgb(0,175,255);">DocContent</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">rhs{</span><span style="color: rgb(245,245,245);">SE</span>(<span style="color: rgb(245,245,245);">&quot;A&quot;</span>)
<span style="color: rgb(0,175,255);">DocEnd</span>
<span style="color: rgb(245,245,245);">EventCode</span>(<span style="color: rgb(245,245,245);">0</span>)
   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">rhs{</span><span style="color: rgb(245,245,245);">SE</span>(<span style="color: rgb(245,245,245);">&quot;B&quot;</span>)
<span style="color: rgb(0,175,255);">DocEnd</span>
<span style="color: rgb(245,245,245);">EventCode</span>(<span style="color: rgb(245,245,245);">1</span>)
   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">rhs{</span><span style="color: rgb(245,245,245);">SE</span>(<span style="color: rgb(245,245,245);">&quot;C&quot;</span>)
<span style="color: rgb(0,175,255);">DocEnd</span>
<span style="color: rgb(245,245,245);">EventCode</span>(<span style="color: rgb(245,245,245);">2</span>)
   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">rhs{</span><span style="color: rgb(245,245,245);">SE</span>(<span style="color: rgb(245,245,245);">&quot;D&quot;</span>)
<span style="color: rgb(0,175,255);">DocEnd</span>
<span style="color: rgb(245,245,245);">EventCode</span>(<span style="color: rgb(245,245,245);">3</span>)
   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">rhs{</span><span style="color: rgb(245,245,245);">SE</span>((<span style="color:teal;">_</span><span style="color: rgb(245,245,245);">*</span><span style="color:teal;">_</span>))
<span style="color: rgb(0,175,255);">DocEnd</span>
<span style="color: rgb(245,245,245);">EventCode</span>(<span style="color: rgb(245,245,245);">4</span>)
   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">rhs{</span><span style="color: rgb(0,175,255);">DT</span>
<span style="color: rgb(0,175,255);">DocContent</span>
<span style="color: rgb(245,245,245);">EventCode</span>(<span style="color: rgb(245,245,245);">5</span>,<span style="color: rgb(245,245,245);">0</span>)
   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">rhs{</span><span style="color: rgb(0,175,255);">CM</span>
<span style="color: rgb(0,175,255);">DocContent</span>
<span style="color: rgb(245,245,245);">EventCode</span>(<span style="color: rgb(245,245,245);">5</span>,<span style="color: rgb(245,245,245);">1</span>,<span style="color: rgb(245,245,245);">0</span>)
   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">rhs{</span><span style="color: rgb(0,175,255);">PI</span>
<span style="color: rgb(0,175,255);">DocContent</span>
<span style="color: rgb(245,245,245);">EventCode</span>(<span style="color: rgb(245,245,245);">5</span>,<span style="color: rgb(245,245,245);">1</span>,<span style="color: rgb(245,245,245);">1</span>)
   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
 <span style="color: rgb(245,245,245);">}</span>
 
 <span style="color: rgb(245,245,245);"></span><span style="font-weight:bold;color: rgb(245,245,245);">Macro </span> <span style="color: rgb(245,245,245);"></span><span style="font-style:italic;color: rgb(245,245,245);"></span><span style="font-weight:bold;font-style:italic;color: rgb(245,245,245);">determine_event_code:</span>
  <span style="color: rgb(245,245,245);"></span><span style="font-style:italic;color: rgb(245,245,245);">found </span><span style="color: rgb(245,245,245);"></span><span style="font-weight:bold;color: rgb(245,245,245);">:= </span><span style="color: rgb(245,245,245);">0</span><span style="color: rgb(245,245,245);"></span><span style="font-weight:bold;color: rgb(245,245,245);"></span>
  <span style="color: rgb(245,245,245);"></span><span style="font-weight:bold;color: rgb(245,245,245);">for each </span><span style="color: rgb(245,245,245);"></span><span style="font-style:italic;color: rgb(245,245,245);">r </span><span style="color: rgb(245,245,245);"></span><span style="font-weight:bold;color: rgb(245,245,245);">in </span>(((<span style="color:teal;">arglist</span><span style="color: rgb(245,245,245);">.</span><span style="color: rgb(245,245,245);">at</span>(<span style="color: rgb(245,245,245);">0</span>))<span style="color: rgb(245,245,245);">.</span><span style="color:teal;">Grammar</span>)<span style="color: rgb(245,245,245);">.</span><span style="color:teal;">rhs</span>)<span style="color: rgb(245,245,245);"></span><span style="font-weight:bold;color: rgb(245,245,245);"></span>
   <span style="color: rgb(245,245,245);"></span><span style="font-style:italic;color: rgb(245,245,245);">res </span><span style="color: rgb(245,245,245);"></span><span style="font-weight:bold;color: rgb(245,245,245);">:= </span><span style="color: rgb(245,245,245);">force_int</span>((((<span style="color: rgb(245,245,245);">symbolic_equality</span>(((<span style="color:teal;">r</span><span style="color: rgb(245,245,245);">.</span><span style="color: rgb(245,245,245);">content</span>())<span style="color: rgb(245,245,245);">.</span><span style="color: rgb(245,245,245);">at</span>(<span style="color: rgb(245,245,245);">0</span>)),(<span style="color:teal;">arglist</span><span style="color: rgb(245,245,245);">.</span><span style="color: rgb(245,245,245);">at</span>(<span style="color: rgb(245,245,245);">1</span>)))<span style="color: rgb(245,245,245);">.</span><span style="color:teal;">diff</span>)<span style="color: rgb(245,245,245);">.</span><span style="color:teal;">equal</span>)<span style="color: rgb(245,245,245);">.</span><span style="color: rgb(245,245,245);">content</span>()))<span style="color: rgb(245,245,245);"></span><span style="font-weight:bold;color: rgb(245,245,245);"></span>
   <span style="color: rgb(245,245,245);"></span><span style="font-weight:bold;color: rgb(245,245,245);">if </span>(<span style="color:teal;">res</span><span style="color: rgb(245,245,245);"> &amp;&amp; </span><span style="color: rgb(245,245,245);">!</span><span style="color:teal;">found</span>)<span style="color: rgb(245,245,245);"></span><span style="font-weight:bold;color: rgb(245,245,245);">:</span>
    found
<span style="color: rgb(245,245,245);"></span><span style="font-weight:bold;color: rgb(245,245,245);">← </span><span style="color: rgb(245,245,245);">1</span><span style="color: rgb(245,245,245);"></span><span style="font-weight:bold;color: rgb(245,245,245);"></span>
((<span style="color:teal;">r</span><span style="color: rgb(245,245,245);">.</span><span style="color: rgb(245,245,245);">content</span>())<span style="color: rgb(245,245,245);">.</span><span style="color: rgb(245,245,245);">at</span>(<span style="color: rgb(245,245,245);">2</span>))    
   <span style="color: rgb(245,245,245);"></span><span style="font-weight:bold;color: rgb(245,245,245);">if </span><span style="color: rgb(245,245,245);">!</span><span style="color:teal;">found</span><span style="color: rgb(245,245,245);"></span><span style="font-weight:bold;color: rgb(245,245,245);">:</span>
    <span style="color:teal;">undef</span>    
   
   <span style="color: rgb(245,245,245);">fact{</span>
<span style="color: rgb(245,245,245);">1</span>   <span style="color: rgb(245,245,245);">}</span>
   <span style="color: rgb(245,245,245);">fact{</span>
<span style="color: rgb(245,245,245);">1</span>   <span style="color: rgb(245,245,245);">}</span>
   
</pre>


