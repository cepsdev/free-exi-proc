<pre>
📎 7.1.10 String

<span style="color: rgb(245,245,245);">witness{</span>

--------------------------------------------------------------------------------
001 The string datatype representation is a length prefixed sequence of 
002 characters. The length indicates the number of characers in the string
003 and is represented as an Unsigned Integer (see 7.1.6 Unsigned Integer).
004 If a restricted character set is defined for the string (see 7.1..10.1
005 Restricted Character Sets), each character is represented as an n-bit
006 Unsigned Integer (See 7.1.9 n-bit Unsigned Integer). Otherwise, each
007 character is represented by its Unicode [UNICODE] code point encoded
008 as an Unsigned Integer (see 7.1.6 Unsigned Integer).
009
010 EXI uses a string table to represent certain content items more
011 efficiently. Section 7.3 String Table describes the string table
012 and how it is applied to different content items.

<span style="color: rgb(245,245,245);">}</span>

</pre>


