# v2g-guru-exi
EXI Processor


## Building and running the example (3.3 Encoding Example) from the EXI Primer document (https://www.w3.org/TR/exi-primer/)
- Requirements: g++ >= 8 and https://github.com/cepsdev/machines4ceps
- ./build_all.sh && ./run_primer_encode_example.sh 

### How to read the output

Relevant are the last three lines:

```
encode_result = encoding{
    (FUNC_CALL (ID "EventCode" )(CALL_PARAMETERS (INT 0  )));
    (FUNC_CALL (ID "EventCode" )(CALL_PARAMETERS (INT 0  )));
    (FUNC_CALL (ID "EventCode" )(CALL_PARAMETERS (OPERATOR , "" (INT 0  )(INT 1  ))));
    (FUNC_CALL (ID "EventCode" )(CALL_PARAMETERS (OPERATOR , "" (INT 0  )(INT 4  ))));
}

Number of exi-events generated (should be 24): 4
expected_encoding{0;0;(0,1);(1,2);(0,1);(1,1);(2,2);(0,3);0;(1,0);(0,3);0;1;(1,0);1;0;0;0;0;0;0;1;1;0;}
```

where


```
(FUNC_CALL (ID "EventCode" )(CALL_PARAMETERS (INT i_1, INT i_2, ... , INT i_n   )));
```

means

```
EventCode(i_1,i_2,...,i_n)
```

where __i_1, i_2, ... , i_n__  are nonnegative integers.


