<pre>
📎 7.3.3 Partitions Optimized for Frequent use of String Literals

<span style="color: rgb(245,245,245);">witness{</span>

--------------------------------------------------------------------------------
001 The remaining string table partitions are optimized for the frequent use
002 of string literals. This includes all string table partitions containing
003 local-names and all string table partitions containing value content
004 items.
005
006 When a string value is found in the partitions containing local-names, the
007 string value is represented as zero (0) encoded as an Unsigned Integer
008 (see 7.1.6 Unsigned Integer) followed by the compact identifier of the 
009 string value. The compact identifier of the string value is encoded as an
010 n-bit unsigned integer (7.1.9 n-bit Unsigned Integer), where n is 
011 ceil(log_2(m)) and m is the number of entries in the string table partition
012 at the time of the operation.
013
014 When a string value is not found in the partitions containing local-names,
015 its string literal is encoded as a String (see 7.1.10 String) with the
016 length of the string incremented by one. After encoding the string value,
017 it is added to the string table partition and assigned the next available
018 compact identifier m.
019
020 As described above, each value content item is assigned to two partitions,
021 a &quot;local&quot; value partition and the global value partition. When a string
022 value is found in the global or &quot;local&quot; partition, it is represented using 
023 a compact identifier. When a string value is found in the &quot;local&quot; value
024 partition, the string value may be represented as zero (0) encoded as an
025 Unsigned Integer (see 7.1.6 Unsigned Integer) followed by the compact
026 identifier of the string value in the &quot;local&quot; value partition. When a 
027 string value is found in the global value partition, the String value may
028 be represented as one (1) encoded as an Unsigned Integer (see 7.1.6 Unsigned
029 Integer) followed by the compact identifier of the String value in the 
030 global partition. The compact identifier is encoded as an n-bit unsigned
031 integer (7.1.9 n-bit Unsigned Integer), where n is ceil(log_2(m)) and m 
032 is the number of entries in the associated partition at the time of the
033 operation.
034
035 When a string value S is not found in the global or &quot;local&quot; value 
036 partition, its string literal is encoded as a String (see 7.1.19 String)
037 with the length L + 2 (incremented by two) where L is the number of
038 characters in the string value. If valuePartitionCapacity is not zero,
039 and L is greater than zero and no more than valueMaxLength, the string
040 S is added to the associated &quot;local&quot; value partition using the next
041 available compact identifier m and added to the global value partition
042 using the compact identifier globalID. When S is added to the global 
043 value partition and there was already a string V in the global value
044 partition associated with the compact identifier globalID, the string
045 S replaces the String V in the global table, and the string V is
046 removed from its associated local value partition by rendering its
047 compact identifier permanently unassigned. When the string value is
048 added to the global value parition, the value of globalID is incremented
049 by one (1). If the resulting value of globalID is equal to
050 valuePartitionCapacity, its value is reset to zero (0),

<span style="color: rgb(245,245,245);">}</span>

</pre>


