<pre>
📎 7.1.7. QName

<span style="color: rgb(245,245,245);">witness{</span>

--------------------------------------------------------------------------------
001 The QName datatype representation is a sequence of values representing the
002 URI, local-name and prefix components of the QName in theat order, where
003 the prefix component is present only when the Preserve.prefixes option is
004 set to true.
005
006 When the QName value is specified by a schema-informed grammar using the
007 SE (qname) or AT (qname) terminal symbols, URI and local-name are implicit
008 and are omitted. Similarly, when the URI of the QName value is derived 
009 from a schema-informed grammar using SE(uri:*) or AT(uri:*) terminal
010 symbols, URI is implicitly thus omitted in the representation, and only
011 the local-name component is encoded as a String (see 7.1.10 String).
012 Otherwise, URI and local-name components are encoded as Strings. If the
013 QName is in no namespace, the URI is represented by a zero length String.
014
015 When present, prefixes are represented as n-bit unsigned integers (7.1.9
016 n-bit Unsigned Integer), where n is ceil(log_2(N)) and N is the number of
017 prefixes in the prefix string table partition associated with the URI of
018 the QName or one (1) if there are no prefixes in this partition. If
019 the given prefix exists in the associated prefix string table partition,
020 it is represented using the compact identifier assigned by the partition.
021 If the given prefix does not exist in the associated partition, the QName
022 MUST be part of an SE event and the prefix MUST be part of an SE Event
023 and the prefix MUST be resolved by one of the NS events immediately 
024 following the SE event (see resolution rules below). In this case,
025 the unresolved prefix representation is not used and can be zero (0)
026 or the compact identifier of any prefix in the associated partition.
027
028 Note:
029
030  When N is one, the prefix is represented using zero bits (i.e. omitted).
031
032 Given a n-bit unsigned integer m that represents either the prefix value
033 or an unresolved prefix value, the effiective prefix value is determined
034 by following the rules described below in order. A QName is in error if
035 its prefix cannot be resolved by the rules below.
036
037 1. If the prefix string table partition associated with the URI of the
038    QName assigns the compact identifier m to a prefix value, select
039    this prefix value as the candidate prefix value. Otherwise, there
040    is no candidate prefix value.
041 2. If the QName value is part of an SE event followed by an associated
042    NS event with its local-element-ns flag value set to true, the
043    prefix value is the prefix of theis NS event. Otherwise, the prefix
044   value is the candidate value, if any, selected in step 1 above.

<span style="color: rgb(245,245,245);">}</span>

</pre>


