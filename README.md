# A Truly Free EXI Processor
## Status
Under Construction - Release planned for Q2 2026.
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

## Usage
### Browsing the model
#### Using a shell (no ceps installed)
```bash
$ cat model/SECTIONNUMBER/*ceps
```
Example:
```bash
$ cat model/001002/*ceps
```
Output (shortened)
```
kind DocgenStringPrintNoEscape;
DocgenStringPrintNoEscape docinfo_se;

witness{

label __1__2 title = "1.2 Notational Conventions and Terminology";
lbl{"1.2 Notational Conventions and Terminology";};
lbl2{"001002";};
docinfo_se(
"
    --------------------------------------------------------------------------------
001 1.
002 The key words ...
```
#### Using a shell (ceps installed)
```bash
$ ceps --pe --format ansi model/SECTIONNUMBER/*ceps
```
Example:
```bash
$ cat model/001002/*ceps
```
Output (shortened)

```
witness{
 📎 1.2 Notational Conventions and Terminology
 lbl{"1.2 Notational Conventions and Terminology" } 
 lbl2{"001002" } 

    --------------------------------------------------------------------------------
001 1.
002 The key words MUST, MUST NOT, REQUIRED, SHALL, SHALL NOT, SHOULD, SHOULD NOT, 
003 RECOMMENDED, MAY, and OPTIONAL, when they appear EMPHASIZED in this document, 
004 are to be interpreted as described in RFC 2119. Other terminology used to 
005 describe the EXI format is defined in the body of this specification.
006 The term event and stream is used throughout this document to denote EXI event 
007 and EXI stream respectively unless the words are qualified differently to mean 
008 otherwise.
...
```

