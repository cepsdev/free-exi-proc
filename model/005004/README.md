
<pre>
<span style="color: rgb(245,245,245);">witness{</span>
 📎 5.4 EXI Options

--------------------------------------------------------------------------------
001 [Definition:] The fifth part of the EXI header is the EXI Options, which
002 provides a way to specify the options used to encode the body of the EXI 
003 stream.
004 [Definition:] The EXI Options are represented as an EXI Options document,
005 which is an XML document encoded using the EXI format described in this
006 specification. This results in a very compact header format that can be
007 read and written with very little additional software.
008 
009 The presence of EXI Options in its entirety is optional in EXI header,
010 and it is predicated on the value of the presence bit that follows the
011 Distinguishing Bits. When EXI Options are present in the header, an
012 EXI Processor MUST observe the specified options to process the EXI
013 stream that follows. Otherwise, an EXI Processor may obtain the EXI
014 options using another mechanism. There are no fallback option values 
015 provided by this specification for use in the absence of the whole
016 EXI Options part.
017
018 EXI processors MAY provide external means for applications or users to
019 specify EXI Options when the EXI Options document is absent. Such EXI
020 processors are typically used in controlled systems where the knowledge
021 about the effective EXI Options is shared prior to the exchange of 
022 EXI streams. The mechanisms to communicate out-of-band EXI Options
023 and their representation are implementation dependent.
024
025 The following table describes the EXI options that may be specified
026 in the EXI Options document.

 <span style="color: rgb(245,245,245);">table{</span>  📎 Table 5-1. EXI Options in Options Document
  <span style="color: rgb(245,245,245);">header{</span>   <span style="color: rgb(245,245,245);">th{</span><span style="color: rgb(245,245,245);">&quot;EXI Option&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">th{</span><span style="color: rgb(245,245,245);">&quot;Description&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">th{</span><span style="color: rgb(245,245,245);">&quot;Default Value&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">tr{</span>   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">&quot;alignment&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">&quot;Alignment of event codes and content items&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">&quot;bit-packed&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">tr{</span>   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">&quot;compression&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">&quot;EXI compression is used to achieve better compactness&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">&quot;false&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">tr{</span>   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">&quot;strict&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">&quot;Strict interpretation of schemas is used to achieve better compactness&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">&quot;false&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">tr{</span>   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">&quot;fragment&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">&quot;Body is encoded as an EXI fragment instead of an EXI document&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">&quot;false&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">tr{</span>   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">&quot;preserve&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">&quot;Specifies whether the support for the preservation of comments, pis, etc. is each enabled&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">&quot;LL false&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">tr{</span>   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">&quot;selfContained&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">&quot;Enables self-contained elements&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">&quot;false&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">tr{</span>   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">&quot;schemaId&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">&quot;Identify the schema information, if any, used to encode the body&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">&quot;no default value&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">tr{</span>   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">&quot;blockSize&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">&quot;Specifies the block size used for EXI compression&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">&quot;1,000,000&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">tr{</span>   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">&quot;valueMaxLength&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">&quot;Specifies the maimum string length of value content items to be considered for addition to the string table&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">&quot;unbounded&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">tr{</span>   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">&quot;valuePartitionCapacity&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">&quot;Specifies the total capacity of value partitions in a string table&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">&quot;unbounded&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">tr{</span>   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">&quot;[user defined meta-data]&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">&quot;User defined meta-data may be added&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">&quot;no default value&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
 <span style="color: rgb(245,245,245);">}</span> 

027 Appendix C XML Schema for EXI Options Document provides an XML 
028 Schema describing the EXI Options document. This schema is 
029 designed to produce smaller headers for option combinations used
030 when compactness is critical.
031
032 The EXI Options document is represented as an EXI body informed
033 by the above mentioned schema using the default options 
034 specified by the following XNL document. An EXI Options 
035 document consists only of an EXI body, and MUST NOT start with
036 an EXI header.
037
038 Header options used for encoding the EXI Options document
039 &lt;header xmlns=&quot;http://www.w3.org/2009/exi&quot;&gt;
040   &lt;strict/&gt;
041 &lt;/header&gt;
042
043 Note that this specification does not require EXI processors
044 to read and process the schema prescribed for EXI options
045 document (C XML Schema for EXI Options Document), in order
046 to process EXI options documents. EXI processors MUST use
047 the schema-informed grammars that stem form the schema in
048 processing EXI options documents, beyond which there is no
049 requirement as to the use of the schema, and implementations
050 are free to use any methods to retrieve the instructions 
051 that observe the grammars for processing EXI options 
052 documents. Section 8.5 Schema-informed Grammars describes
053 the system to derive schema-informed grammars from XML-
054 Schemas.
055
056 Below is a brief description of each EXI option.
057
058 [Definition:] The alignment option is used to control the
059 alignment of event codes and content items. The value is 
060 one of bit-packed, byte-alignment, or pre-compression, of
061 which bit-packed is the default value assumed when the
062 &quot;alignment&quot; element is absent in the EXI Options document.
063 The option values byte-alignment and pre-compression are
064 effected when &quot;byte&quot; and &quot;pre-compress&quot; elemensts are
065 present in the EXI Options document, respectively. When
066 the value of compression option is set to true, alignment
067 of the EXI Body is governed by the rules specified in 
068 9. EXI Compression instead of the alignment option value.
069 The &quot;alignment&quot; element MUST NOT appear in an exi
070 options document when the &quot;compression&quot; element is
071 present.
072
073 [Definition:] The alignment option value bit-packed
074 indicates that the event codes and associated content
075 are packed in bits without any padding in-between.
076
077 [Definition:] The alignment option value byte-
078 alignment indicates that the event codes and associated
079 content are aligned on byte boundaries. While byte-
080 alignment generally results in EXI streams of larger
081 sizes compared with their bit-packed equivalents, byte-
082 alignment may provide a help in some use cases that
083 involve frequent copying of large arrays of scalar
084 data directly out of the stream. It can also make
085 it possible to work with datat inlocated in the 
086 stream.
087
088 [Definition:] The alignment option value pre-
089 compression indicates that all steps involved in
090 compression (see section 9. EXI Compression) are
091 to be done with the exception of the final step
092 of applying the DEFLATE algorithm. The primary
093 use case of pre-compression is to avoid a 
094 duplicate compression capability is built into 
095 the transport protocol. In this case, pre-compression
096 just prepares the stream for later compression.
097
098 [Definition:] The compression option is a Boolean
099 used to increase compactness using additional computational
100 resources. The default value &quot;false&quot; is assumed when the
101 &quot;compression&quot; element is absent in the EXI Options document
102 whereas its presence denotes the value &quot;true&quot;. When set to
103 true, the event codes and associated content are compressed
104 according to 9. EXI Compression regardless of the alignment
105 option value. As mentioned above, the &quot;compression&quot; 
106 element MUST NOT appear in an EXI options document when the
107 &quot;alignment&quot; element is present.
108
109 [Definition:] The strict option is a Boolean used to increase
110 compactness by using a strict interpretation of the schemas 
111 and omitting preservation of certain items, such as comments,
112 processing instructions, and namespace prefixes.
113 The default value &quot;false&quot; is assumed when the &quot;strict&quot;
114 element is absent in the EXI Options document whereas its 
115 presence denotes the value &quot;true&quot;. When set to true,
116 those productions that have NS, CM, PI, ER, and SC terminal
117 symbols are omitted from the EXI grammars, and schema-informed
118 element and type grammars are restricted to only permit items
119 declared in the schemas. A note in section 8.5.4.4.2 Adding
120 Productions when Strict is True describes some additional 
121 restrictions consequential of the use of this option.
122 The &quot;strict&quot; element MUST NOT appear in an EXI options
123 document when one of &quot;dtd&quot;,&quot;prefixes&quot;,&quot;comments&quot;,
124 &quot;pis&quot; or &quot;selfContained&quot; element is present in the same 
125 options document.
126
127 [Definition:] The fragment option is a Boolean that indicates 
128 whether the EXI body is an EXI document or an EXI fragment.
129 When set to true, the EXI body is an EXI fragment. Otherwise,
130 the EXI body is an EXI document. The default value &quot;false&quot;
131 is assumed when the &quot;fragment&quot; element is absent in the EXI
132 Options document whereas its presence denotes the value &quot;true&quot;.
133
134 [Definition:] The preserve option is a set of Booleans that can be
135 set independently to each enable or disable a share of the format's
136 capacity determining whether or how certain information items can
137 be preserved in the EXI stream. Section 6.3 Fidelity Options
138 describes the set of information items affected by the preserve
139 option. The presence of &quot;dtd&quot;, &quot;prefixes&quot;,&quot;lexicalValues&quot;,
140 &quot;comments&quot;, and &quot;pis&quot; in the EXI Options document each turns
141 on fidelity Preserve.comments, Preserve.pis, Preserve.dtd, 
142 Preserve.prefixes and Preserve.lexicalValues whereas the absence
143 denotes turning each off. The elements &quot;dtd&quot;, &quot;prefixes&quot;, 
144 &quot;comments&quot; and &quot;pis&quot; MUST NOT appear in an EXI options document
145 when the &quot;strict&quot; element is present in the same options document.
146 The element &quot;lexicalValues&quot;, on the other hand, is permitted to
147 occur in the presence of &quot;strict&quot; element.
148 [Definition:] The selfContained option is Boolean used to enable
149 the use of self-contained elements in the EXI stream. Self-contained
150 elements may be read independently from the rest of the EXI body, 
151 allowing them to be indexed for random access. The &quot;selfContained&quot;
152 element MUST NOT appear in an EXI options document when one of 
153 &quot;compression&quot;, &quot;pre-compression&quot; or &quot;strict&quot; elemenbts are
154 present in the same options document. The default value &quot;false&quot;
155 is assumed when the &quot;selfContained&quot; element is absent from the
156 EXI Options document whereas its presence denotes the value &quot;true&quot;.
157
158 [Definition:] The schemaId option may be used to identify the schema 
159 information used for processing the EXI body. When the &quot;schemaId&quot;
160 element in the EXI options document contains the xsi:nil attribute
161 with its value set to true, no schema information is used for processing
162 the EXI body (i.e. a schema-less EXI stream). When the value of the
163 &quot;schemaId&quot; element is empty, no user defined schema information is
164 used for processing the EXI body; however, the built-in XML schema 
165 types are available for use in the EXI body. When the schemaId option
166 is absent (i.e., undefined), no statement is made about the schema
167 information used to encode the EXI body and this information MUST be
168 communicated out of band. This specification does not dictate the
169 syntax or semantics of other values specified in this field. An 
170 example schemaId scheme is the use of URI that is apt for globally
171 identifying schema resources on the Web. The parties involved in
172 the exchange are free to agree on the scheme of schemaId field that
173 is appropriate for their use to uniquely identify the schema
174 information.
175
176 [Definition:] The datatypeRepresentationMap option specifies an 
177 alternate set of datatype representations for typed values in the
178 EXI body as described in 7.4 Datatype Representation Map. When there
179 are no &quot;datatypeRepresentationMap&quot; elements in the EXI Options
180 document, no Datatype Representation Map is used for processing the
181 EXI body. This option does not take effect when the value of the
182 Preserve.lexicalValues fidelity option is true (see 6.3 Fidelity 
183 Options), or when the EXI stream is a schema-less EXI stream.
184
185 [Definition:] The blockSize option specifies the block size used
186 for EXI compression. When the &quot;blockSize&quot; element is absent in
187 the EXI Options document, the default blocksize of 1,000,000 is used.
188 The default blockSize is intentionally large but can be reduced for
189 processing large documents on devices with limited memory.
190
191 [Definition:] The valueMaxLength option specifies the maximum 
192 length of value content items to be considered for addition to
193 the string table. The default value &quot;unbounded&quot; is assumed when
194 the &quot;valueMaxLength&quot; element is absent in the EXI Options
195 document.
196 
197 [Definition:] The valuePartitionCapacity option specifies the 
198 maximum number of value content items in the string table at any
199 given time. The default value &quot;unbounded&quot; is assumed when the
200 &quot;valuePartitionCapacity&quot; element is absent in the EXI Options
201 document. Section 7.3.3 Partitions Optimized for Frequent use of
202 String Literals specifies the behavior of the string table when
203 this capacity is reached.
204
205 [Definition:] The user defined meta-data conveys auxiliary 
206 information that applications may use to facilitate 
207 interpretation of the EXI stream. The user defined meta-data
208 MUST NOT be interpreted in a way that alters or extends the 
209 EXI data format defined in this specification. User defined 
210 meta-data may be added to an EXI Options document just prior
211 to the alignment option.


<span style="color: rgb(245,245,245);">}</span>

</pre>
