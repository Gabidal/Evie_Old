# Evie- lang

<br/>
<br/>

### Catalog:
 - ### [Documentation](#Documentation)
 - ### [Arguments](#Arguments)
 - ### [Notices](#Notices)

 <br/>
 <br/>

# Documentation
### https://gabidal.github.io/Evie-Document/

<br/>
<br/>

# Arguments
###  -in  [relative path/source file]
###  -out  [relative path/output file name]
###  -os  [target operating system (win/unix)]\n";
###  -host  [the host operating system (win/unix)]
###  -arch  [output assembly type (x86/arm)]
###  -lib  [relative path/lib name]
###  -repo-dir  [relative/absolute path for saving git repos]
###  -f [ supported output file formats are:
### &emsp; exe(executable (works for unix as well)),
### &emsp;  lib(static lib),
### &emsp;  dll(dynamic library (support is not made yet!))
### ]
###  -mode [bit mode for assembly output (32/64)]
###  -debug [ supported debug symbol types: dwarf2 ]
###  -vt [virus total API-key]
###  -reference-count-size [reference count size]
###  -service [starts Evie as a service with a port returned in standard out ]
<br/><br/>

### Quick usage:\n";
###  ./Evie -in foo/bar/baz.e\
### Remember to set up an environment path named: \'Repo-Dir\'
### The order of arguments dont matter.

<br/><br/>

# Notices
#### If you are in Linux, then you need to install curllib for Evie to work :D
#### I recommend you to install "sudo apt install libcurl4-openssl-dev"
#### Other depencies that i recomend you install to compile Evie src:
#### Clang
#### Make