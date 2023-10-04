<pre>
📎 6.2 Representing Event Codes


--------------------------------------------------------------------------------
001 Each event code is represented by a sequence of 1 to 3 parts that 
002 uniquely identify an event. Event code parts are encoded in order
003 starting with the first part followed by subsequent parts.
004 
005 The i-th part of an event code is encoded as an n-bit unsigned 
006 integer (7.1.9 n-bit Unsigned Integer) where n is ceil(log_2 m)
007 and m is the number of distinct values used as the i-th part
008 of its own and all its sibling event codes in the current grammar.
009 Two event codes are siblings at the i-th part if and only if they
010 share the same valies in all preceding parts. 
011 All event codes are siblings at the first part.
012
013 If there is only one distinct value for a given part, the part
014 is omitted (i.e.. encoded in log_2 1 bits = 0 bits = 0 bytes).
015
016 For example, the eight event codes shown in the DocContent 
017 grammar above have values ranging form 0 to 5 for the first part.
018 Six distinct values are needed to identify the first part of
019 these event codes. Therefore, the first part can be encoded as an
020 n-bit unsigned integer where n = ceil(log_2 6) = 3. In the same
021 fashion, the second and third part (if present) are represented as
022 n-bit unsigned integers where n is ceil (log_2 2) = 1 and 
023 ceil(log_2 2) = 1 respectively.
024
025 When the value of the compression option is false and bit-packed
026 alignment is used, n-bit unsigned integers are represented using
027 n bits. The first table below illustrates how the event codes of
028 each event matched by the DocContent grammar above are represented
029 in this case.
030
031 When the value of compression option is true, or either byte-
032 alignment or pre-compression alignment option is used, n-bit
033 unsigned integers are represented using the minimum number of
034 bytes required to store n bits. The second table below illustrates
035 how the event codes of each event matched by the DocContent grammar
036 above are represented in this case.

📎 Example event code encoding

<span style="color: rgb(245,245,245);">table{</span>
 📎 Example event code encoding when EXI compression is not in effect and bit-packed alignment is used
 <span style="color: rgb(245,245,245);">header{</span>  <span style="color: rgb(245,245,245);">th{</span><span style="color: rgb(245,245,245);">&quot;Event&quot;</span>  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">th{</span><span style="color: rgb(245,245,245);">&quot;Part values&quot;</span>  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">th{</span><span style="color: rgb(245,245,245);">&quot;Event Code Encoding&quot;</span>  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">th{</span><span style="color: rgb(245,245,245);">&quot;# bits&quot;</span>  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">tr{</span>   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">SE</span>(<span style="color: rgb(245,245,245);">&quot;A&quot;</span>)
   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span>    <span style="color: rgb(245,245,245);">part{</span><span style="color: rgb(245,245,245);">0</span>    <span style="color: rgb(245,245,245);">}</span>    
    <span style="color: rgb(245,245,245);">part{</span>    <span style="color: rgb(245,245,245);">}</span>    
    <span style="color: rgb(245,245,245);">part{</span>    <span style="color: rgb(245,245,245);">}</span>    
   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">3</span>   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">tr{</span>   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">SE</span>(<span style="color: rgb(245,245,245);">&quot;B&quot;</span>)
   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span>    <span style="color: rgb(245,245,245);">part{</span><span style="color: rgb(245,245,245);">1</span>    <span style="color: rgb(245,245,245);">}</span>    
    <span style="color: rgb(245,245,245);">part{</span>    <span style="color: rgb(245,245,245);">}</span>    
    <span style="color: rgb(245,245,245);">part{</span>    <span style="color: rgb(245,245,245);">}</span>    
   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">1</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">3</span>   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">tr{</span>   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">SE</span>(<span style="color: rgb(245,245,245);">&quot;C&quot;</span>)
   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span>    <span style="color: rgb(245,245,245);">part{</span><span style="color: rgb(245,245,245);">2</span>    <span style="color: rgb(245,245,245);">}</span>    
    <span style="color: rgb(245,245,245);">part{</span>    <span style="color: rgb(245,245,245);">}</span>    
    <span style="color: rgb(245,245,245);">part{</span>    <span style="color: rgb(245,245,245);">}</span>    
   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">1</span> <span style="color: rgb(245,245,245);">0</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">3</span>   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">tr{</span>   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">SE</span>(<span style="color: rgb(245,245,245);">&quot;D&quot;</span>)
   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span>    <span style="color: rgb(245,245,245);">part{</span><span style="color: rgb(245,245,245);">3</span>    <span style="color: rgb(245,245,245);">}</span>    
    <span style="color: rgb(245,245,245);">part{</span>    <span style="color: rgb(245,245,245);">}</span>    
    <span style="color: rgb(245,245,245);">part{</span>    <span style="color: rgb(245,245,245);">}</span>    
   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">1</span> <span style="color: rgb(245,245,245);">1</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">3</span>   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">tr{</span>   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">SE</span>((<span style="color:teal;">_</span><span style="color: rgb(245,245,245);">*</span><span style="color:teal;">_</span>))
   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span>    <span style="color: rgb(245,245,245);">part{</span><span style="color: rgb(245,245,245);">4</span>    <span style="color: rgb(245,245,245);">}</span>    
    <span style="color: rgb(245,245,245);">part{</span>    <span style="color: rgb(245,245,245);">}</span>    
    <span style="color: rgb(245,245,245);">part{</span>    <span style="color: rgb(245,245,245);">}</span>    
   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">1</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">3</span>   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">tr{</span>   <span style="color: rgb(245,245,245);">td{</span><span style="color:teal;">DT</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span>    <span style="color: rgb(245,245,245);">part{</span><span style="color: rgb(245,245,245);">5</span>    <span style="color: rgb(245,245,245);">}</span>    
    <span style="color: rgb(245,245,245);">part{</span><span style="color: rgb(245,245,245);">0</span>    <span style="color: rgb(245,245,245);">}</span>    
    <span style="color: rgb(245,245,245);">part{</span>    <span style="color: rgb(245,245,245);">}</span>    
   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">1</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">1</span> <span style="color: rgb(245,245,245);">0</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">4</span>   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">tr{</span>   <span style="color: rgb(245,245,245);">td{</span><span style="color:teal;">CM</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span>    <span style="color: rgb(245,245,245);">part{</span><span style="color: rgb(245,245,245);">5</span>    <span style="color: rgb(245,245,245);">}</span>    
    <span style="color: rgb(245,245,245);">part{</span><span style="color: rgb(245,245,245);">1</span>    <span style="color: rgb(245,245,245);">}</span>    
    <span style="color: rgb(245,245,245);">part{</span><span style="color: rgb(245,245,245);">0</span>    <span style="color: rgb(245,245,245);">}</span>    
   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">1</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">1</span> <span style="color: rgb(245,245,245);">1</span> <span style="color: rgb(245,245,245);">0</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">5</span>   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">tr{</span>   <span style="color: rgb(245,245,245);">td{</span><span style="color:teal;">PI</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span>    <span style="color: rgb(245,245,245);">part{</span><span style="color: rgb(245,245,245);">5</span>    <span style="color: rgb(245,245,245);">}</span>    
    <span style="color: rgb(245,245,245);">part{</span><span style="color: rgb(245,245,245);">1</span>    <span style="color: rgb(245,245,245);">}</span>    
    <span style="color: rgb(245,245,245);">part{</span><span style="color: rgb(245,245,245);">1</span>    <span style="color: rgb(245,245,245);">}</span>    
   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">1</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">1</span> <span style="color: rgb(245,245,245);">1</span> <span style="color: rgb(245,245,245);">1</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">5</span>   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">tr{</span>   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">&quot;# distinct values(m)&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span>    <span style="color: rgb(245,245,245);">part{</span><span style="color: rgb(245,245,245);">6</span>    <span style="color: rgb(245,245,245);">}</span>    
    <span style="color: rgb(245,245,245);">part{</span><span style="color: rgb(245,245,245);">2</span>    <span style="color: rgb(245,245,245);">}</span>    
    <span style="color: rgb(245,245,245);">part{</span><span style="color: rgb(245,245,245);">2</span>    <span style="color: rgb(245,245,245);">}</span>    
   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span>   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">tr{</span>   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">&quot;# bits per part ceil(log_2 m)&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span>    <span style="color: rgb(245,245,245);">part{</span><span style="color: rgb(245,245,245);">3</span>    <span style="color: rgb(245,245,245);">}</span>    
    <span style="color: rgb(245,245,245);">part{</span><span style="color: rgb(245,245,245);">1</span>    <span style="color: rgb(245,245,245);">}</span>    
    <span style="color: rgb(245,245,245);">part{</span><span style="color: rgb(245,245,245);">1</span>    <span style="color: rgb(245,245,245);">}</span>    
   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span>   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
 <span style="color: rgb(245,245,245);">}</span> 
<span style="color: rgb(245,245,245);">}</span>
<span style="color: rgb(245,245,245);">table{</span>
 📎 Example event code encoding when EXI compression is in effect, or either byte-alignment or pre-compression alignment option is used
 <span style="color: rgb(245,245,245);">header{</span>  <span style="color: rgb(245,245,245);">th{</span><span style="color: rgb(245,245,245);">&quot;Event&quot;</span>  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">th{</span><span style="color: rgb(245,245,245);">&quot;Part values&quot;</span>  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">th{</span><span style="color: rgb(245,245,245);">&quot;Event Code Encoding&quot;</span>  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">th{</span><span style="color: rgb(245,245,245);">&quot;# bytes&quot;</span>  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">tr{</span>   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">SE</span>(<span style="color: rgb(245,245,245);">&quot;A&quot;</span>)
   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span>    <span style="color: rgb(245,245,245);">part{</span><span style="color: rgb(245,245,245);">0</span>    <span style="color: rgb(245,245,245);">}</span>    
    <span style="color: rgb(245,245,245);">part{</span>    <span style="color: rgb(245,245,245);">}</span>    
    <span style="color: rgb(245,245,245);">part{</span>    <span style="color: rgb(245,245,245);">}</span>    
   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">1</span>   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">tr{</span>   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">SE</span>(<span style="color: rgb(245,245,245);">&quot;B&quot;</span>)
   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span>    <span style="color: rgb(245,245,245);">part{</span><span style="color: rgb(245,245,245);">1</span>    <span style="color: rgb(245,245,245);">}</span>    
    <span style="color: rgb(245,245,245);">part{</span>    <span style="color: rgb(245,245,245);">}</span>    
    <span style="color: rgb(245,245,245);">part{</span>    <span style="color: rgb(245,245,245);">}</span>    
   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">1</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">1</span>   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">tr{</span>   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">SE</span>(<span style="color: rgb(245,245,245);">&quot;C&quot;</span>)
   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span>    <span style="color: rgb(245,245,245);">part{</span><span style="color: rgb(245,245,245);">2</span>    <span style="color: rgb(245,245,245);">}</span>    
    <span style="color: rgb(245,245,245);">part{</span>    <span style="color: rgb(245,245,245);">}</span>    
    <span style="color: rgb(245,245,245);">part{</span>    <span style="color: rgb(245,245,245);">}</span>    
   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">1</span> <span style="color: rgb(245,245,245);">0</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">1</span>   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">tr{</span>   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">SE</span>(<span style="color: rgb(245,245,245);">&quot;D&quot;</span>)
   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span>    <span style="color: rgb(245,245,245);">part{</span><span style="color: rgb(245,245,245);">3</span>    <span style="color: rgb(245,245,245);">}</span>    
    <span style="color: rgb(245,245,245);">part{</span>    <span style="color: rgb(245,245,245);">}</span>    
    <span style="color: rgb(245,245,245);">part{</span>    <span style="color: rgb(245,245,245);">}</span>    
   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">1</span> <span style="color: rgb(245,245,245);">1</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">1</span>   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">tr{</span>   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">SE</span>((<span style="color:teal;">_</span><span style="color: rgb(245,245,245);">*</span><span style="color:teal;">_</span>))
   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span>    <span style="color: rgb(245,245,245);">part{</span><span style="color: rgb(245,245,245);">4</span>    <span style="color: rgb(245,245,245);">}</span>    
    <span style="color: rgb(245,245,245);">part{</span>    <span style="color: rgb(245,245,245);">}</span>    
    <span style="color: rgb(245,245,245);">part{</span>    <span style="color: rgb(245,245,245);">}</span>    
   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">1</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">1</span>   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">tr{</span>   <span style="color: rgb(245,245,245);">td{</span><span style="color:teal;">DT</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span>    <span style="color: rgb(245,245,245);">part{</span><span style="color: rgb(245,245,245);">5</span>    <span style="color: rgb(245,245,245);">}</span>    
    <span style="color: rgb(245,245,245);">part{</span><span style="color: rgb(245,245,245);">0</span>    <span style="color: rgb(245,245,245);">}</span>    
    <span style="color: rgb(245,245,245);">part{</span>    <span style="color: rgb(245,245,245);">}</span>    
   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">1</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">1</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">2</span>   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">tr{</span>   <span style="color: rgb(245,245,245);">td{</span><span style="color:teal;">CM</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span>    <span style="color: rgb(245,245,245);">part{</span><span style="color: rgb(245,245,245);">5</span>    <span style="color: rgb(245,245,245);">}</span>    
    <span style="color: rgb(245,245,245);">part{</span><span style="color: rgb(245,245,245);">1</span>    <span style="color: rgb(245,245,245);">}</span>    
    <span style="color: rgb(245,245,245);">part{</span><span style="color: rgb(245,245,245);">0</span>    <span style="color: rgb(245,245,245);">}</span>    
   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">1</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">1</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">1</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">3</span>   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">tr{</span>   <span style="color: rgb(245,245,245);">td{</span><span style="color:teal;">PI</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span>    <span style="color: rgb(245,245,245);">part{</span><span style="color: rgb(245,245,245);">5</span>    <span style="color: rgb(245,245,245);">}</span>    
    <span style="color: rgb(245,245,245);">part{</span><span style="color: rgb(245,245,245);">1</span>    <span style="color: rgb(245,245,245);">}</span>    
    <span style="color: rgb(245,245,245);">part{</span><span style="color: rgb(245,245,245);">1</span>    <span style="color: rgb(245,245,245);">}</span>    
   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">1</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">1</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">1</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">1</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">3</span>   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">tr{</span>   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">&quot;# distinct values(m)&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span>    <span style="color: rgb(245,245,245);">part{</span><span style="color: rgb(245,245,245);">6</span>    <span style="color: rgb(245,245,245);">}</span>    
    <span style="color: rgb(245,245,245);">part{</span><span style="color: rgb(245,245,245);">2</span>    <span style="color: rgb(245,245,245);">}</span>    
    <span style="color: rgb(245,245,245);">part{</span><span style="color: rgb(245,245,245);">2</span>    <span style="color: rgb(245,245,245);">}</span>    
   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span>   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">tr{</span>   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">&quot;# bytes per part ceil( (log_2 m )/ 8)&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span>    <span style="color: rgb(245,245,245);">part{</span><span style="color: rgb(245,245,245);">1</span>    <span style="color: rgb(245,245,245);">}</span>    
    <span style="color: rgb(245,245,245);">part{</span><span style="color: rgb(245,245,245);">1</span>    <span style="color: rgb(245,245,245);">}</span>    
    <span style="color: rgb(245,245,245);">part{</span><span style="color: rgb(245,245,245);">1</span>    <span style="color: rgb(245,245,245);">}</span>    
   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span>   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
 <span style="color: rgb(245,245,245);">}</span> 
<span style="color: rgb(245,245,245);">}</span>



</pre>


