<pre>
📎 7.1.8. Date-Time

<span style="color: rgb(245,245,245);">witness{</span>

--------------------------------------------------------------------------------
001 The Date-Time datatype represetation is a sequence of values representing 
002 the individual components of the Date-Time. The following table specifies
003 each of the possible date-time components along with how they are encoded.
004 The value ranges of the date-time components follow the definitions of the
005 XML Schema specfication [XML Schema Datatypes] which for example prescribes
006 the value range of the seconds to be between 0 and 60 to account for leap
007 second representation and hour between 0 and 24 among others.

 <span style="color: rgb(245,245,245);">table{</span>  📎 Date-Time components
  <span style="color: rgb(245,245,245);">header{</span>   <span style="color: rgb(245,245,245);">th{</span><span style="color: rgb(245,245,245);">&quot;Component&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">th{</span><span style="color: rgb(245,245,245);">&quot;Value&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">th{</span><span style="color: rgb(245,245,245);">&quot;Type&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">tr{</span>   <span style="color: rgb(245,245,245);">td{</span><span style="color:teal;">Year</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">&quot;Offset from 2000&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color:teal;">Integer</span> <span style="color: rgb(245,245,245);">&quot;(7.1.5 Integer)&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">tr{</span>   <span style="color: rgb(245,245,245);">td{</span><span style="color:teal;">MonthDay</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span>((<span style="color:teal;">Month</span><span style="color: rgb(245,245,245);">*</span><span style="color: rgb(245,245,245);">32</span>)<span style="color: rgb(245,245,245);">+</span><span style="color:teal;">Day</span>)
   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">&quot;9-bit Unsigned Integer (7.1.9 n-bit Unsigned Integer) where day is a value in the range 1-31 and month is a value in the range 1-12.&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">tr{</span>   <span style="color: rgb(245,245,245);">td{</span><span style="color:teal;">Time</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span>((((<span style="color:teal;">Hour</span><span style="color: rgb(245,245,245);">*</span><span style="color: rgb(245,245,245);">64</span>)<span style="color: rgb(245,245,245);">+</span><span style="color:teal;">Minutes</span>)<span style="color: rgb(245,245,245);">*</span><span style="color: rgb(245,245,245);">64</span>)<span style="color: rgb(245,245,245);">+</span><span style="color:teal;">seconds</span>)
   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">&quot;17-bit Unsigned Integer (7.1.9 n-bit Unsigned Integer) where Hour is a value in the range 0-24, Minutes is a value in the range 0-59 and seconds is a value in the range 0-60.&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">tr{</span>   <span style="color: rgb(245,245,245);">td{</span><span style="color:teal;">FractionalSecs</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">&quot;Fractionsal Seconds&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">&quot;Unsigned Integer (7.1.6 Unsigned Integer) representing the fractional part of the seconds with digits in reverse order to preserve leading zeros.&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">tr{</span>   <span style="color: rgb(245,245,245);">td{</span><span style="color:teal;">TimeZone</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span>((<span style="color:teal;">TZHousr</span><span style="color: rgb(245,245,245);">*</span><span style="color: rgb(245,245,245);">64</span>)<span style="color: rgb(245,245,245);">+</span><span style="color:teal;">TZMinutes</span>)
   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">&quot;11-bit Unsigned Integer (7.1.9 n-bit Unsigned Integer) representing a signed integer offset by 896 (=14*64) where TZHours is a value in the range [-14 .. 14] and TZMinutes is a value in the range [-59 .. 59].&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">tr{</span>   <span style="color: rgb(245,245,245);">td{</span><span style="color:teal;">presence</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">&quot;Boolean presence indicator&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span><span style="color: rgb(245,245,245);">&quot;Boolean (7.1.2 Boolean)&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
 <span style="color: rgb(245,245,245);">}</span> 

--------------------------------------------------------------------------------
008 The variety of components that constitute a value and their appearance order
009 depend on the XML Schema type associated with the value. The following table
010 shows which components are included in a value of each XML Schema type that
011 is relevant to Date-Time datatype. Items listed in square brackets are
012 included if and only if the value of its preceding presence indicator
013 (specified above) is set to true.

 <span style="color: rgb(245,245,245);">table{</span>  📎 Assortment of Date-Time components
  <span style="color: rgb(245,245,245);">header{</span>   <span style="color: rgb(245,245,245);">th{</span><span style="color: rgb(245,245,245);">&quot;XML Schema Datatype&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">th{</span><span style="color: rgb(245,245,245);">&quot;Included Components&quot;</span>   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">tr{</span>   <span style="color: rgb(245,245,245);">td{</span><span style="color:teal;">gYear</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span>((<span style="color:teal;">Year</span><span style="color: rgb(245,245,245);">,</span><span style="color:teal;">presence</span>)<span style="color: rgb(245,245,245);">,</span><span style="color:teal;">TimeZone</span>)
   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">tr{</span>   <span style="color: rgb(245,245,245);">td{</span><span style="color:teal;">gYearMonth</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span>(((<span style="color:teal;">Year</span><span style="color: rgb(245,245,245);">,</span><span style="color:teal;">MonthDay</span>)<span style="color: rgb(245,245,245);">,</span><span style="color:teal;">presence</span>)<span style="color: rgb(245,245,245);">,</span><span style="color:teal;">TimeZone</span>)
   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">tr{</span>   <span style="color: rgb(245,245,245);">td{</span><span style="color:teal;">date</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span>(((<span style="color:teal;">Year</span><span style="color: rgb(245,245,245);">,</span><span style="color:teal;">MonthDay</span>)<span style="color: rgb(245,245,245);">,</span><span style="color:teal;">presence</span>)<span style="color: rgb(245,245,245);">,</span><span style="color:teal;">TimeZone</span>)
   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">tr{</span>   <span style="color: rgb(245,245,245);">td{</span><span style="color:teal;">dateTime</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span>((((((<span style="color:teal;">Year</span><span style="color: rgb(245,245,245);">,</span><span style="color:teal;">MonthDay</span>)<span style="color: rgb(245,245,245);">,</span><span style="color:teal;">Time</span>)<span style="color: rgb(245,245,245);">,</span><span style="color:teal;">presence</span>)<span style="color: rgb(245,245,245);">,</span><span style="color:teal;">FractionalSecs</span>)<span style="color: rgb(245,245,245);">,</span><span style="color:teal;">presence</span>)<span style="color: rgb(245,245,245);">,</span><span style="color:teal;">TimeZone</span>)
   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">tr{</span>   <span style="color: rgb(245,245,245);">td{</span><span style="color:teal;">gMonth</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span>((<span style="color:teal;">MonthDay</span><span style="color: rgb(245,245,245);">,</span><span style="color:teal;">presence</span>)<span style="color: rgb(245,245,245);">,</span><span style="color:teal;">TimeZone</span>)
   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">tr{</span>   <span style="color: rgb(245,245,245);">td{</span><span style="color:teal;">gMonthDay</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span>((<span style="color:teal;">MonthDay</span><span style="color: rgb(245,245,245);">,</span><span style="color:teal;">presence</span>)<span style="color: rgb(245,245,245);">,</span><span style="color:teal;">TimeZone</span>)
   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">tr{</span>   <span style="color: rgb(245,245,245);">td{</span><span style="color:teal;">gDay</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span>((<span style="color:teal;">MonthDay</span><span style="color: rgb(245,245,245);">,</span><span style="color:teal;">presence</span>)<span style="color: rgb(245,245,245);">,</span><span style="color:teal;">TimeZone</span>)
   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
  <span style="color: rgb(245,245,245);">tr{</span>   <span style="color: rgb(245,245,245);">td{</span><span style="color:teal;">time</span>   <span style="color: rgb(245,245,245);">}</span>   
   <span style="color: rgb(245,245,245);">td{</span>((((<span style="color:teal;">Time</span><span style="color: rgb(245,245,245);">,</span><span style="color:teal;">presence</span>)<span style="color: rgb(245,245,245);">,</span><span style="color:teal;">FractionalSecs</span>)<span style="color: rgb(245,245,245);">,</span><span style="color:teal;">presence</span>)<span style="color: rgb(245,245,245);">,</span><span style="color:teal;">TimeZone</span>)
   <span style="color: rgb(245,245,245);">}</span>   
  <span style="color: rgb(245,245,245);">}</span>  
 <span style="color: rgb(245,245,245);">}</span> 
<span style="color: rgb(245,245,245);">}</span>

</pre>


