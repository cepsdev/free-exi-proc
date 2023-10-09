<pre>
📎 7.3.1 String Table Partitions

<span style="color: rgb(245,245,245);">witness{</span>

--------------------------------------------------------------------------------
001 The string table is organized into partitions so that the indices assigned
002 to compact identifiers can stay relatively small. Smaller number of indices
003 results in improved average compactness and the efficiency of table 
004 operations. Each partition has a separate set of compact identifiers and
005 content items are assigned to specific partitions as described below.
006
007 Uri content items and the URI portion of qname content items are assigned
008 to the uri partition. The uri partition is optimized for frequent use of
009 compact identifiers and is pre-populated with initial entries as described
010 in D.1 Initial Entries in Uri Partition. When a schema is provided, the uri
011 partition is also pre-populated with initial entries as described in D.1
012 Initial Entries in Uri Partition. When a schema is provided, the uri 
013 partition is also pre-populated with the name of each target namespace URI
014 declared in the schema, plus some of the namespace URIs used in wildcard
015 terms and attribute wildcards (see section 8.5.4.1.7 Wildcard Terms and
016 8.5.4.1.3.2 Complex Type Grammars, respectively for the condition), 
017 appended in lexicographical order.
018
019 Prefix content items are assigned to partitions based on their associated
020 namespace URI. Partitions containing prefix content items are optimized for
021 frequent use of compact identifiers and the string table is pre-populated
022 with entries as described in D.2 Initial Entries in Prefix Partitions.
023 
024 The local-name portion of qname content items are assigned to partitions
025 based on the namespace URI of the qnmae content item of whcih the local-
026 name is a part. Partitions containing local-names are optimized for 
027 frequent use of string literals and the string table is pre-populated with
028 entries as described in D.3 Initial Entries in Local-Name Partitions.
029
030 Each value content item is assigned to both the global value partition and
031 a &quot;local&quot; value partition based on the qname of the attribute or element
032 in context at the time the value is added to the value partitions.
033 Partitions containing value content items are optimized for frequent use
034 of string literals and are initially empty. [Definition:] The variable
035 globalID is a non-negative integer representing the compact identifier of
036 the next item added to the global value partition. Its value is initially
037 set to 0 (zero) and changes while processing an EXI stream per the rule
038 described in 7.3.3 Partitions Optimized for Frequent use of String 
039 Literals.

<span style="color: rgb(245,245,245);">}</span>

</pre>


