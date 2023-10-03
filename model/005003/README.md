<pre>
<span style="color: rgb(245,245,245);">witness{</span>
 📎 5.3 EXI Format Version

--------------------------------------------------------------------------------
001 [Definition:] The fourth part in the EXI header is the EXI Format Version,
002 which identifies the version of the EXI format being used.
003 ESI format version numbers are integers. Each version of the EXI Format
004 Specification specifies the corresponding EXI format version number to be
005 used by conforming implementations. The EXI format version number that
006 corresponds with this version of the EXI format specification is 1 (one).
007
008 The first bit of the version field indicates whether the version is a 
009 preview or final version of the EXI format. A value of 0 indicates this
010 is a final version and a value of 1 indicates this is a preview version.
011 Final versions correspond to final, approved versions of the EXI format
012 specification. An EXI processor that implements a final version of the
013 EXI format specification is REQUIRED to process EXI streams that have a 
014 versionfield with its first bit set to 0 followed by a 
015 version number that corresponds to the version of the EXI specification
016 the processor implements. The behavior  of an EXI processor on an EXI
017 stream with its first bit set to 0 followed ba a version not corresponding
018 to a version implemented by the processor is not constrained by this 
019 specification. For example, the EXI processor MAY reject such a stream
020 outright or it MAY attempt to process the EXI body. Preview versions of
021 the EXI format are useful for gaining implementation and deployment
022 experience prior to finalizing a particular version of the EXI format.
023 While preview versions may match drafts of this specification, they
024 are not governed by this specification and the behaviour of EXI 
025 processors encountering preview versions of the EXI format is 
026 implementation dependent. Implementers are free to coordinate
027 to achieve interoperability between different preview versions of the
028 EXI format.
029
030 Following the first bit of the version is a sequence of one or more
031 4-bit unsigned integers representing the version number. The version
032 number is determined by summing this sequence of 4-bit unsigned 
033 values and adding 1 (0ne). The sequence is terminated by any 4-bit
034 unsigned integer with a value in the range 0 - 14. As such, the 
035 first 15 version numbers are represented by 4 bits, the next 15 are
036 represented by 8 bits, etc.
037
038 Given an EXI stream with its stream cursor positioned just past 
039 the first bit of the EXI format version field, the EXI format
040 version number can be computed by going through the following steps
041 with version number initially set to 1.
042
043 1. Read next 4 bits as an unsigned integer value.
044 2. Add the value that was just read to the version number.
045 3. If the value is 15, go to step 1, otherwise (i.e. the value
046 being in the range of 0-14), use the current value of the version
047 number as the EXI version number.
048
049 The following are example EXI format version numbers.

 <span style="color: rgb(245,245,245);">table{</span>  📎 Example 5-1. EXI Format Version Examples
  <span style="color: rgb(245,245,245);">header{</span>   <span style="color: rgb(245,245,245);">th{</span><span style="color: rgb(245,245,245);">&quot;EXI Format Version Field&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">th{</span><span style="color: rgb(245,245,245);">&quot;Description&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">tr{</span>   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">1</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">&quot;Preview version 1&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">tr{</span>   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">&quot;Final version 1&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">tr{</span>   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">1</span> <span style="color: rgb(245,245,245);">1</span> <span style="color: rgb(245,245,245);">1</span> <span style="color: rgb(245,245,245);">0</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">&quot;Final version 15&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">tr{</span>   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">1</span> <span style="color: rgb(245,245,245);">1</span> <span style="color: rgb(245,245,245);">1</span> <span style="color: rgb(245,245,245);">1</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">&quot;Final version 16&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">tr{</span>   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">1</span> <span style="color: rgb(245,245,245);">1</span> <span style="color: rgb(245,245,245);">1</span> <span style="color: rgb(245,245,245);">1</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">0</span> <span style="color: rgb(245,245,245);">1</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">&quot;Final version 17&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
 <span style="color: rgb(245,245,245);">}</span> 

050 EXI processors conforming with the final version of this specificatiuon 
051 MUST use the 5-bit value 0 0000 as the version number.

<span style="color: rgb(245,245,245);">}</span>

</pre>


