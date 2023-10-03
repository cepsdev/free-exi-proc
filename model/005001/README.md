<pre>
<span style="color: rgb(245,245,245);">witness{</span>
 📎 5.1 EXI Cookie

--------------------------------------------------------------------------------
001 [Definition:] An EXI header MAY start with an EXI Cookie, which is a four
002 byte field that serves to indicate that the stream of which it is a part
003 is an EXI stream. The four byte field consists of four characters
004 &quot;$&quot;,&quot;E&quot;,&quot;X&quot; and &quot;I&quot; in that order, each represented as an ASCII
005 octet, as follows:

 <span style="color: rgb(245,245,245);">EXICookie{</span><span style="color: rgb(245,245,245);">&quot;$&quot;</span> <span style="color: rgb(245,245,245);">&quot;E&quot;</span> <span style="color: rgb(245,245,245);">&quot;X&quot;</span> <span style="color: rgb(245,245,245);">&quot;I&quot;</span> <span style="color: rgb(245,245,245);">}</span> 

006 This four byte sequence is particular to EXI and specific enough to 
007 distinguish EXI streams from a board range of data types currently used on
008 the Web.
009 While the EXI cookie is optional, its use is RECOMMENDED in the EXI header
010 when the EXI stream is exchanged in a context where a longer, more specific
011 content-based datatype identifier is desired than that provided by the
012 Distinguishing Bits, whose role is more narrowly focused on Distinguishing
013 EXI streams from XML documents.

<span style="color: rgb(245,245,245);">}</span>

</pre>


