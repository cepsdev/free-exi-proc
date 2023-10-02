<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<!-- This file was created with the aha Ansi HTML Adapter. https://github.com/theZiz/aha -->
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="application/xml+xhtml; charset=UTF-8" />
<title>stdin</title>
</head>
<body>
<pre>
📎 1. Introduction

<span style="color: rgb(245,245,245);">witness{</span>

--------------------------------------------------------------------------------
001 The Efficient XML Interchange (EXI) format is a very compact, high 
002 performance XML representation that was designed to work well for a broad
003 range of applications. It simultaneously improves performance and
004 significantly reduces bandwitdth requirements without compromising efficient
005 use of other resources such as battery life, code size, processing power,
006 and memory.
007
008 EXI uses a grammar-driven approach that achieves very efficient encodings 
009 using a straightforward encoding algorithm and a small set of datatype
010 representations. Consequently, EXI processors are relatively simple and
011 can be implemented on devices with limited capacity.
012
013 EXI is schema 'informed', meaning that it can utilize available schema
014 information to improve compactness and performance, but does not depend on
015 accurate, complete or current schemas to work. It supports arbitrary schema
016 extensions and deviations and also works very efficiently with partial 
017 schemas or in absence of any schema. The format itself also does not depend
018 on any particular schema language, or format, for schema information.
019
020 [Definition:] A program module called an EXI processor, whether it is
021 software or hardware, is used by application programs to encode their 
022 structured data accessible. The former and latter aforementioned roles
023 are called [Definition:] EXI stream encoder and [Definition] EXI
024 stream decoder, respectively. This document not only specifies the
025 EXI format, but also defines errors that EXI processors are required to
026 detect and behave upon.
027
028 The primary goal of this document is to define the EXI format completely
029 without leaving ambiguity so as to make it feasible for implementations
030 to interoperate. As such, the document lends itself to describing the
031 design and features of the format in a systematic manner, often 
032 declaratively with relatively few prosaic annotations and examples.
033 Those readers who prefer a step-by-step introduction to the EXI format
034 design and features are suggested to start with the non-normative
035 [EXI Primer].

<span style="color: rgb(245,245,245);">}</span>
<span style="color:purple;"></span><span style="font-weight:bold;color:purple;">State Machine </span><span style="color: rgb(245,245,245);"></span><span style="font-style:italic;color: rgb(245,245,245);"></span><span style="font-weight:bold;font-style:italic;color: rgb(245,245,245);">EXI processor</span>
 <span style="color: rgb(175,175,135);"></span><span style="font-weight:bold;color: rgb(175,175,135);">States:</span>
  <span style="color: rgb(245,245,245);"></span><span style="font-weight:bold;color: rgb(245,245,245);">Initial</span>
 <span style="color: rgb(175,175,135);"></span><span style="font-weight:bold;color: rgb(175,175,135);">Transitions:</span>
  <span style="color:teal;">Initial</span> --▶<span style="color:teal;">stream decoder</span>     .    --▶<span style="color:teal;">stream encoder</span>
 <span style="color:purple;"></span><span style="font-weight:bold;color:purple;">State Machine </span><span style="color: rgb(245,245,245);"></span><span style="font-style:italic;color: rgb(245,245,245);"></span><span style="font-weight:bold;font-style:italic;color: rgb(245,245,245);">EXI processor.stream encoder</span>
  <span style="color: rgb(175,175,135);"></span><span style="font-weight:bold;color: rgb(175,175,135);">States:</span>
   <span style="color: rgb(245,245,245);"></span><span style="font-weight:bold;color: rgb(245,245,245);">Initial</span>, <span style="color: rgb(245,245,245);"></span><span style="font-weight:bold;color: rgb(245,245,245);">WaitForData</span>, <span style="color: rgb(245,245,245);"></span><span style="font-weight:bold;color: rgb(245,245,245);">ProcessData</span>
  <span style="color: rgb(175,175,135);"></span><span style="font-weight:bold;color: rgb(175,175,135);">Transitions:</span>
   <span style="color:teal;">Initial</span>     --▶<span style="color:teal;">WaitForData</span>      
   <span style="color:teal;">ProcessData</span> --▶<span style="color:teal;">WaitForData</span>      
   <span style="color:teal;">WaitForData</span> -<span style="color: rgb(0,175,255);">EncodeStructuredData</span>-▶<span style="color:teal;">ProcessData</span> 

 <span style="color:purple;"></span><span style="font-weight:bold;color:purple;">State Machine </span><span style="color: rgb(245,245,245);"></span><span style="font-style:italic;color: rgb(245,245,245);"></span><span style="font-weight:bold;font-style:italic;color: rgb(245,245,245);">EXI processor.stream decoder</span>
  <span style="color: rgb(175,175,135);"></span><span style="font-weight:bold;color: rgb(175,175,135);">States:</span>
   <span style="color: rgb(245,245,245);"></span><span style="font-weight:bold;color: rgb(245,245,245);">Initial</span>, <span style="color: rgb(245,245,245);"></span><span style="font-weight:bold;color: rgb(245,245,245);">WaitForData</span>, <span style="color: rgb(245,245,245);"></span><span style="font-weight:bold;color: rgb(245,245,245);">ProcessData</span>
  <span style="color: rgb(175,175,135);"></span><span style="font-weight:bold;color: rgb(175,175,135);">Transitions:</span>
   <span style="color:teal;">Initial</span>     --▶<span style="color:teal;">WaitForData</span>      
   <span style="color:teal;">ProcessData</span> --▶<span style="color:teal;">WaitForData</span>      
   <span style="color:teal;">WaitForData</span> -<span style="color: rgb(0,175,255);">DecodeStream</span>-▶<span style="color:teal;">ProcessData</span> 


</pre>
</body>
</html>
