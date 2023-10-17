# A Truly Free EXI Processor
## Goals
- Complete implementation of an EXI "Efficient XML Interchange" processor (https://www.w3.org/TR/exi/), 
- in modern, idiomatic and portable C++,
- designed and implemented using the cepS - Ansatz,
- extends EXI significantly by providing a general framework for gammar based compression,
- truly open.

The meaning of the term "truly open" includes:

- open as in *open source*,
- and open as in *open architecture*, i.e. the inner workings of the software are open for inspection and experimentation (complete executable spec in [model/](model/README.md)),
- applies a corpus based approach to modelling, which allows for the incorporation of AI agents (e.g. Codepilot).

## Installation
### Requirements
#### Standalone EXI processor
- Unix*ish* OS
- recent*ish* C++ compiler (e.g. g++ version >= 9)
- cmake

#### Executable Specification and Tests
- https://github.com/cepsdev/machines4ceps

#### Building documents and statistics
- [aha](https://github.com/theZiz/aha) (not the band)
- gnuplot

