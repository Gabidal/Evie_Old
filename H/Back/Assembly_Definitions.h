#ifndef _ASSEMBLY_DEFINITIONS_H_
#define _ASSEMBLY_DEFINITIONS_H_


#define FROM ", "
#define NL string("\n")
#define OFFSET " + "
#define DEOFFSET " - "
#define SCALE " * "
#define LABEL(name) (name + ": " + NL)
#define TYPE(type, name) (type + "_" + name)
#define COMMENT string(" ; ")

#define FRAME(name) ("[" + name + "]")

#endif