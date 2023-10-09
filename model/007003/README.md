<pre>
📎 7.3 String Table

<span style="color: rgb(245,245,245);">witness{</span>

--------------------------------------------------------------------------------
001 EXI uses a string table to assign &quot;compact identifiers&quot; to some string
002 values. Occurences of string values found in the string table are
003 represented using the associated compact identifier rather than encoding
004 the entire &quot;string literal&quot;. The string table is initially pre-populated
005 with string values that are likely to occur in certain contexts and is
006 dynamically expanded to include additional string values encounterd in the
007 document. The following content items are encoded using a string table:
008
009  - uris
010  - prefixes
011  - uri and local-name in qnames 
012  - values
013
014 When a string value is found in the string table, the value is encoded
015 using the compact identifier and no changes are made to the string table
016 as a result. When a string value is not found in the string table, its 
017 string literal is encoded as a String without using a compact identifier,
018 only after which the string table is augmented by including the string
019 value with an assigned compact identifier unless the string value 
020 represents a vlaue content item and fails to satisfy the criteria in 
021 effect by virtue of valuePartitionCapacity and valueMaxLength options.
022
023 The string table is divided into partitions and each partition is
024 optimized for more frequent use of either compact identifiers or
025 string literals depending on the purpose of the partition. Section
026 7.3.1 String Table Partitions describes how EXI string table is
027 partitioned. Section 7.3.2 Partitions Optimized for Frequent use
028 of Compact Identifiers describes how string values are encoded
029 when the associated partition is optimized for more frequent use of
030 compact identifiers. Section 7.3.3 Partitions Optimized for Frequent
031 use of String Literals describes how string values are encoded when the
032 associated partition is optimized for more frequent use of string literals.
033
034 The life cycle of a string table spans the processing of a single EXI
035 stream. String tables are not represented in an EXI stream or exchanged
036 between EXI processors. A string table cannot be reused across multiple 
037 EXI streams; therefore, EXI processors MUST use a string table that is
038 equivalent to the one that would have been newly created and pre-
039 populated with initial values for processing each EXI stream.

<span style="color: rgb(245,245,245);">}</span>

</pre>


