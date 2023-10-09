<pre>
📎 7.1.10.1 Restricted Character Sets

<span style="color: rgb(245,245,245);">witness{</span>

--------------------------------------------------------------------------------
001 If a string value is associated with a schema datatype directly or
002 indirectly derived from xsd:string and one or more of the datatypes
003 in its datatype hierarchy has one or more pattern facets, there may
004 be a restricted character set defined for the string value. The
005 following steps are used to determine the restricted character set,
006 if any, defined for a given string value associated with such a schema
007 datatype.
008
009 Given the schema datatype, let the target datatype definition of the
010 most-derived datatype that has one or more pattern facets immediately
011 specified in its definition in the schema among those in the datatype
012 inheritance hierarchy that traces backwards toward primitve datatypes
013 starting form the datatype. If the target datatype definition is a 
014 definition for a built-in datatype, there is no restricted character
015 set for the string value. Otherwise, determine the set of characters
016 for each immediate pattern facet of the target datatype definition 
017 according to section E Deriving Set of Characters from XML Schema Regular
018 Expressions. Then, compute the restricted set of characters for the string
019 value as the union of all the sets of characters computed in the previous
020 step. If the resulting set of characters contains less than 256 characters 
021 and contains only BMP characters, the string value has a restricted 
022 character set and each character is represented using an n-bit Unsigned
023 Integer (see 7.1.9 n-bit Unsigned Integer), where n is ceil(log_2(N+1))
024 and N is the number of characters in the restricted character set.
025
026 The characters in the restricted character set are sorted by Unicode
027 [UNICODE] code point and represented by integer values in the range
028 (0 .. N-1) according to their ordinal position in the set. Characters
029 that are not in this are represented by the n-bit Unsigned Integer N 
030 followed by the Unicode code point of the character represented as an
031 Unsigned Integer.
032
033 The figure below illustrates an overview of the process for determining
034 and using restricted characters sets described in this section.

 <span style="color:purple;"></span><span style="font-weight:bold;color:purple;">State Machine </span><span style="color: rgb(245,245,245);"></span><span style="font-style:italic;color: rgb(245,245,245);"></span><span style="font-weight:bold;font-style:italic;color: rgb(245,245,245);">StringProcessingModel</span>
  <span style="color: rgb(175,175,135);"></span><span style="font-weight:bold;color: rgb(175,175,135);">States:</span>   <span style="color: rgb(245,245,245);"></span><span style="color: rgb(245,245,245);"></span><span style="font-weight:bold;color: rgb(245,245,245);">Initial</span><span style="color: rgb(245,245,245);"></span><span style="color: rgb(245,245,245);"></span>  <span style="color:purple;"></span><span style="font-weight:bold;color:purple;">State Machine </span><span style="color: rgb(245,245,245);"></span><span style="font-style:italic;color: rgb(245,245,245);"></span><span style="font-weight:bold;font-style:italic;color: rgb(245,245,245);">StringProcessingModel.EXI_Stream_Processing</span>
   <span style="color: rgb(175,175,135);"></span><span style="font-weight:bold;color: rgb(175,175,135);">States:</span>    <span style="color: rgb(245,245,245);"></span><span style="color: rgb(245,245,245);"></span><span style="font-weight:bold;color: rgb(245,245,245);">Initial</span><span style="color: rgb(245,245,245);">, </span><span style="color: rgb(245,245,245);"></span><span style="font-weight:bold;color: rgb(245,245,245);">String</span><span style="color: rgb(245,245,245);">, </span><span style="color: rgb(245,245,245);"></span><span style="font-weight:bold;color: rgb(245,245,245);">EncoderDecoder</span><span style="color: rgb(245,245,245);">, </span><span style="color: rgb(245,245,245);"></span><span style="font-weight:bold;color: rgb(245,245,245);">EXIStringRepresentation</span><span style="color: rgb(245,245,245);"></span>   <span style="color: rgb(175,175,135);"></span><span style="font-weight:bold;color: rgb(175,175,135);">Transitions:</span>    <span style="color: rgb(245,245,245);"></span><span style="color:teal;">Initial</span><span style="color: rgb(245,245,245);">                </span><span style="color: rgb(245,245,245);"> -</span><span style="color: rgb(245,245,245);">-▶</span><span style="color:teal;">String</span><span style="color: rgb(245,245,245);"></span>    <span style="color: rgb(245,245,245);"></span>    <span style="color: rgb(245,245,245);"></span>    <span style="color: rgb(245,245,245);"></span><span style="color:teal;">EXIStringRepresentation</span><span style="color: rgb(245,245,245);"></span><span style="color: rgb(245,245,245);"> -</span><span style="color: rgb(0,175,255);">Decode</span><span style="color: rgb(245,245,245);">-▶</span><span style="color:teal;">EncoderDecoder</span><span style="color: rgb(245,245,245);"></span>    <span style="color: rgb(245,245,245);"></span>    <span style="color: rgb(245,245,245);"></span>    <span style="color: rgb(245,245,245);"></span><span style="color:teal;">EncoderDecoder</span><span style="color: rgb(245,245,245);">         </span><span style="color: rgb(245,245,245);"> -</span><span style="color: rgb(0,175,255);">Encode</span><span style="color: rgb(245,245,245);">-▶</span><span style="color:teal;">EXIStringRepresentation</span><span style="color: rgb(245,245,245);"></span>    <span style="color: rgb(245,245,245);"></span><span style="color: rgb(245,245,245);">           .           </span><span style="color: rgb(245,245,245);"> -</span><span style="color: rgb(245,245,245);">-▶</span><span style="color:teal;">String</span><span style="color: rgb(245,245,245);"></span>    <span style="color: rgb(245,245,245);"></span>    <span style="color: rgb(245,245,245);"></span>    <span style="color: rgb(245,245,245);"></span><span style="color:teal;">String</span><span style="color: rgb(245,245,245);">                 </span><span style="color: rgb(245,245,245);"> -</span><span style="color: rgb(245,245,245);">-▶</span><span style="color:teal;">EncoderDecoder</span><span style="color: rgb(245,245,245);"></span>  <span style="color: rgb(245,245,245);"></span><span style="color: rgb(245,245,245);"></span>  <span style="color:purple;"></span><span style="font-weight:bold;color:purple;">State Machine </span><span style="color: rgb(245,245,245);"></span><span style="font-style:italic;color: rgb(245,245,245);"></span><span style="font-weight:bold;font-style:italic;color: rgb(245,245,245);">StringProcessingModel.SchemaAnalysis</span>
   <span style="color: rgb(175,175,135);"></span><span style="font-weight:bold;color: rgb(175,175,135);">States:</span>    <span style="color: rgb(245,245,245);"></span><span style="color: rgb(245,245,245);"></span><span style="font-weight:bold;color: rgb(245,245,245);">Initial</span><span style="color: rgb(245,245,245);">, </span><span style="color: rgb(245,245,245);"></span><span style="font-weight:bold;color: rgb(245,245,245);">SetOfPatterns</span><span style="color: rgb(245,245,245);">, </span><span style="color: rgb(245,245,245);"></span><span style="font-weight:bold;color: rgb(245,245,245);">Datatype</span><span style="color: rgb(245,245,245);">, </span><span style="color: rgb(245,245,245);"></span><span style="font-weight:bold;color: rgb(245,245,245);">RestrictedCharacterSet</span><span style="color: rgb(245,245,245);"></span>   <span style="color: rgb(175,175,135);"></span><span style="font-weight:bold;color: rgb(175,175,135);">Transitions:</span>    <span style="color: rgb(245,245,245);"></span><span style="color:teal;">Initial</span><span style="color: rgb(245,245,245);">      </span><span style="color: rgb(245,245,245);"> -</span><span style="color: rgb(245,245,245);">-▶</span><span style="color:teal;">Datatype</span><span style="color: rgb(245,245,245);"></span>    <span style="color: rgb(245,245,245);"></span>    <span style="color: rgb(245,245,245);"></span>    <span style="color: rgb(245,245,245);"></span><span style="color:teal;">Datatype</span><span style="color: rgb(245,245,245);">     </span><span style="color: rgb(245,245,245);"> -</span><span style="color: rgb(245,245,245);">-▶</span><span style="color:teal;">SetOfPatterns</span><span style="color: rgb(245,245,245);"></span>    <span style="color: rgb(245,245,245);"></span>    <span style="color: rgb(245,245,245);"></span>    <span style="color: rgb(245,245,245);"></span><span style="color:teal;">SetOfPatterns</span><span style="color: rgb(245,245,245);"></span><span style="color: rgb(245,245,245);"> -</span><span style="color: rgb(0,175,255);">CharsetDerivation</span><span style="color: rgb(245,245,245);">-▶</span><span style="color:teal;">RestrictedCharacterSet</span><span style="color: rgb(245,245,245);"></span>  <span style="color: rgb(245,245,245);"></span> <span style="color: rgb(245,245,245);"></span> <span style="color: rgb(245,245,245);">:</span>
<span style="color: rgb(245,245,245);">}</span></pre>


