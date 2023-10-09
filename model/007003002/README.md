<pre>
📎 7.3.2 Partitions Optimized for Frequent use of Compact Identifiers

<span style="color: rgb(245,245,245);">witness{</span>

--------------------------------------------------------------------------------
001 String table partitions that are expected to contain a relatively small
002 number of entries used repeatedly throughout the document are optimized
003 for the frequent use of compact identifiers. This includes the uri partition
004 and all partitions containing prefix content items.
005
006 When a string value is found in a partition optimized for frequent use of
007 compact identifiers, the string value is represented as the value (i+1) 
008 encoded as an n-bit Unsigned Integer (7.1.9 n-bit Unsigned Integer), where
009 i is the value of the compact identifier, n is ceil(log_2 (m+1)) and m is
010 the number of entries in the string table partition at the time of the
011 operation.
012
013 When a string value is not found in a partition optimized for frequent use
014 of compact identifiers, the String value is represented as zero (0) encoded
015 as an n-bit Unsigned Integer, followed by the string literal encoded as a 
016 String (7.1.10 String). After encoding the String value, it is added to the
017 string table partition and assigned the next available compact identifier m.

<span style="color: rgb(245,245,245);">}</span>

</pre>


