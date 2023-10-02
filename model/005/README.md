
<pre>
<span style="color: rgb(245,245,245);">witness{</span>
 📎 5. EXI Header

--------------------------------------------------------------------------------
001 Each EXI stream begins with an EXI Header.
002 [Definition:] The EXI header can identify EXI streams, distinguish EXI
003 streams from XNL documents, identify the version of the EXI format being 
004 used, and specify the options used to process the body of the EXI stream. 
005 The EXI header has the following structure:

 <span style="color: rgb(245,245,245);">EXIHeader{</span>  <span style="color: rgb(245,245,245);">EXICookie{</span>  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">DistinguisihingBits{</span>  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">PresenceBitForEXIOptions{</span>  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">EXIFormatVersion{</span>  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">EXIOptions{</span>  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">PaddingBits{</span>  <span style="color: rgb(245,245,245);">}</span>  
 <span style="color: rgb(245,245,245);">}</span> 

--------------------------------------------------------------------------------
006 The EXI Options field within an EXI header is optional. Its presence is
007 indicated by the value of the presence bit that follows Distinguishing Bits.
008 The presence and absence is indicated by the value 1 and 0, respectively.
009
010 When the compression option is true, or the alignment option is byte-
011 alignment or pre-compression, padding bits of minimum length required
012 to make the whole length of the headr bat-aligned are added at the end
013 of the header. On the other hand, there are no padding bits wehn the
014 alignment in use is bit-packed. The padding bits field if it is 
015 present can contain any values of bits as it contents. 
016
017 The details of the EXI Cookie, Distinguishing Bits, EXI Format Version 
018 and EXI Options are described in the following section.


<span style="color: rgb(245,245,245);">}</span>

</pre>

