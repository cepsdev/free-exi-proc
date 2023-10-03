<pre>
<span style="color: rgb(245,245,245);">Witness{</span>
 📎 6.1 Determining Event Codes
The structure of an EXI stream is described by the EXI grammars, which are 
  formally specified in section 8.EXI Grammars. Each grammar defines which
  events are permitted to occur at any given point in the EXI stream and provides
  a pre-assigned event code for each one.

  For example, the grammar productions below describe the events that occur in a
  schema-informed EXI stream after the Start-Document (SD) event provided there
  are four global elements defined in the schema an assign an event code for each
  one. See 8.5.1 Schema-informed Document Grammar for the process used for generating
  the grammar productions below from the schema.

  Example 6-1. Example productions with event codes

   Syntax                               Event Code
     DocContent
      SE(&quot;A&quot;) DocEnd                    0
      SE(&quot;B&quot;) DocEnd                    1
      SE(&quot;C&quot;) DocEnd                    2
      SE(&quot;D&quot;) DocEnd                    3
      SE(*) DocEnd                        4
      DT DocContent                       5.0
      CM DocContent                       5.1.0
      PI DocContent                       5.1.1

  At the point on an EXI stream where the above grammar productions are in effect,
  the event code of Start Element &quot;A&quot; (i.e. SE(&quot;A&quot;)) is 0. The event code of a
  DOCTYPE(DT) event at this point in the stream is 5.0, and so on.
  
<span style="color: rgb(245,245,245);">}</span>
<span style="color: rgb(245,245,245);">Exegesis{</span>
 <span style="color: rgb(245,245,245);">Grammar{</span><span style="color: rgb(0,175,255);">DocContent</span>
  <span style="color: rgb(245,245,245);">lhs{</span><span style="color: rgb(0,175,255);">DocContent</span>  <span style="color: rgb(245,245,245);">}</span>  
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
❗ 6.1. (extract_event_codes) Equality test failed

<span style="color: rgb(245,245,245);">reason{</span>
<span style="color: rgb(245,245,245);">exi_proc</span>(<span style="color: rgb(245,245,245);">operation{</span><span style="color: rgb(245,245,245);">extract_event_codes{</span><span style="color: rgb(245,245,245);">Grammar{</span><span style="color: rgb(0,175,255);">DocContent</span>
    <span style="color: rgb(245,245,245);">lhs{</span><span style="color: rgb(0,175,255);">DocContent</span>    <span style="color: rgb(245,245,245);">}</span>    
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
<span style="color: rgb(245,245,245);">}</span>)
 <span style="color: rgb(245,245,245);">result{</span><span style="color: rgb(245,245,245);">0</span>
<span style="color: rgb(245,245,245);">1</span>
<span style="color: rgb(245,245,245);">2</span>
<span style="color: rgb(245,245,245);">3</span>
<span style="color: rgb(245,245,245);">4</span>
<span style="color: rgb(245,245,245);">5</span><span style="color: rgb(245,245,245);">0</span>
<span style="color: rgb(245,245,245);">5</span><span style="color: rgb(245,245,245);">1</span><span style="color: rgb(245,245,245);">0</span>
<span style="color: rgb(245,245,245);">5</span><span style="color: rgb(245,245,245);">1</span><span style="color: rgb(245,245,245);">1</span>
 <span style="color: rgb(245,245,245);">}</span>
<span style="color: rgb(245,245,245);">}</span>

</pre>


