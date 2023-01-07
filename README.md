# A Truely Free EXI Processor
## Goals
- Complete implementation of an EXI "Efficient XML Interchange" processor (https://www.w3.org/TR/exi/), 
- in modern, idiomatic and portable C++,
- designed and implemented using the cepS - Ansatz,
- extends EXI significantly by providing a general framework for gammar based compression,
- truely open.

Truely open includes:

- opem source,
- and open architecture, i.e. the inner workings of the software are open for inspection and experimentation (complete executable spec in model/).

## Installation
### Requirements
- Unixish OS
- recent C++ compiler (e.g. g++ version >= 9)
- cmake
- https://github.com/cepsdev/machines4ceps
### Build
- ./rebuild_all.sh 
### Test
- ./run_primer_encode_example.sh 
