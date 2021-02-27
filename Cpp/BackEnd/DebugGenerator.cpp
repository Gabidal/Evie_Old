#include "../../H/BackEnd/DebugGenerator.h"

DebugGenerator::DebugGenerator()
{
}

void DebugGenerator::Construct_Debug_Abbrev()
{
    //THE INFORMATION THAT IS DESCRIBED BELOW IS FROM http://www.dwarfstd.org/doc/DWARF4.pdf
    
    //Abbreviation Code describes the current section as an index
    IR* Abbreviation_Code_Describing_Index = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "1", 1) }, nullptr);
    Debug_Abbrev.push_back(Abbreviation_Code_Describing_Index);
    //A normal compilation unit is represented by a debugging information entry with the tag DW_TAG_compile_unit.
    IR* DW_TAG_Compile_Unit = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "17", 1) }, nullptr);
    Debug_Abbrev.push_back(DW_TAG_Compile_Unit);
    // determines whether a debugging information entry using this abbreviation has child entries or not.
    IR* DW_CHILDREN_Yes = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "1", 1) }, nullptr);
    Debug_Abbrev.push_back(DW_CHILDREN_Yes);
    //Name of the compiler that made this code
    IR* DW_AT_Producer = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "37", 1) }, nullptr);
    Debug_Abbrev.push_back(DW_AT_Producer);
    //Attribute values of class
    IR* DW_FORM_Strp = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "14", 1) }, nullptr);
    Debug_Abbrev.push_back(DW_FORM_Strp);
    // indicating the source language of the compilation unit.
    IR* DW_AT_Language = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "19", 1) }, nullptr);
    Debug_Abbrev.push_back(DW_AT_Language);
    // fixed length constant data forms for one, two, four and eight byte values
    IR* DW_FORM_Data2 = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "5", 1) }, nullptr);
    Debug_Abbrev.push_back(DW_FORM_Data2);
    //representing a program entity
    IR* DW_AT_Name = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "3", 1) }, nullptr);
    Debug_Abbrev.push_back(DW_AT_Name);
    //Attribute values of class
    DW_FORM_Strp;
    Debug_Abbrev.push_back(DW_FORM_Strp);
    //section offset to the line number information for this compilation unit.
    IR* DW_AT_Stmt_List = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "16", 1) }, nullptr);
    Debug_Abbrev.push_back(DW_AT_Stmt_List);
    //lineptr, loclistptr, macptr or rangelistptr.
    IR* DW_FORM_Sec_Offset = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "23", 1) }, nullptr);
    Debug_Abbrev.push_back(DW_FORM_Sec_Offset);
    //containing the current working directory of the compilation command that produced this compilation unit.
    IR* DW_AT_Comp_Dir = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "27", 1) }, nullptr);
    Debug_Abbrev.push_back(DW_AT_Comp_Dir);
    //Attribute values of class
    DW_FORM_Strp;
    Debug_Abbrev.push_back(DW_FORM_Strp);
    //The base address of a compilation unit
    IR* DW_AT_Low_Pc = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "17", 1) }, nullptr);
    Debug_Abbrev.push_back(DW_AT_Low_Pc);
    //Represented as an object of appropriate size to hold an address.
    IR* DW_FORM_Addr = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "1", 1) }, nullptr);
    Debug_Abbrev.push_back(DW_FORM_Addr);
    //addresses of a debugging information entry.
    IR* DW_AT_High_Pc = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "18", 1) }, nullptr);
    Debug_Abbrev.push_back(DW_AT_High_Pc);
    //Add a new attribute form for section offsets.
    IR* DW_FORM_Data4 = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "6", 1) }, nullptr);
    Debug_Abbrev.push_back(DW_FORM_Data4);
    //End of marker
    IR* EOM = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "0", 1) }, nullptr);
    Debug_Abbrev.push_back(EOM);
    //End of marker
    EOM;
    Debug_Abbrev.push_back(EOM);
    //Abbreviation Code describes the current section as an index
    IR* Abbreviation_Code_Describing_Index_1 = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "2", 1) }, nullptr);
    Debug_Abbrev.push_back(Abbreviation_Code_Describing_Index_1);
    //A template instantiation is represented by a debugging information entry with the tag.
    IR* DW_TAG_Subprogram = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "46", 1) }, nullptr);
    Debug_Abbrev.push_back(DW_TAG_Subprogram);
    //1-byte value that determines whether a debugging information entry using this abbreviation has child entries or not.
    IR* DW_CHILDREN_Yes = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "1", 1) }, nullptr);
    Debug_Abbrev.push_back(DW_CHILDREN_Yes);
    //attribute for a single address.
    IR* DW_AT_Low_Pc = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "17", 1) }, nullptr);
    Debug_Abbrev.push_back(DW_AT_Low_Pc);
    //Represented as an object of appropriate size to hold an address on the target machine.
    IR* DW_FORM_Addr = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "1", 1) }, nullptr);
    Debug_Abbrev.push_back(DW_FORM_Addr);
    //pair of attributes for a single contiguous range of addresses.
    IR* DW_AT_High_Pc = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "18", 1) }, nullptr);
    Debug_Abbrev.push_back(DW_AT_High_Pc);
    //Add a new attribute form for section offsets, DW_FORM_sec_offset, to replace the use of DW_FORM_data4and DW_FORM_data8 for section offsets.
    IR* DW_FORM_Data4 = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "6", 1) }, nullptr);
    Debug_Abbrev.push_back(DW_FORM_Data4);
    //offset from the address specified by the location description.
    IR* DW_AT_Frame_Base = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "64", 1) }, nullptr);
    Debug_Abbrev.push_back(DW_AT_Frame_Base);
    // takes a single operand encoded as a DW_FORM_exprloc value representing a DWARF expression.
    IR* DW_FORM_Exprloc = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "24", 1) }, nullptr);
    Debug_Abbrev.push_back(DW_FORM_Exprloc);
    //Debugging information entry representing a program entity that has been given a name.
    IR* DW_AT_Name = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "3", 1) }, nullptr);
    Debug_Abbrev.push_back(DW_AT_Name);
    //Attribute values of class
    DW_FORM_Strp;
    Debug_Abbrev.push_back(DW_FORM_Strp);
    //Any debugging information entry representing the declaration of an object, module, subprogram or type.
    IR* DW_AT_Decl_File = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "58", 1) }, nullptr);
    Debug_Abbrev.push_back(DW_AT_Decl_File);
    //There are fixed length constant data forms for one, two, fourand eight byte values.
    IR* DW_FORM_Data1 = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "11", 1) }, nullptr);
    Debug_Abbrev.push_back(DW_FORM_Data1);
    //attribute represents the source line number at which the first character of the identifier of the declared object appears.
    IR* DW_AT_Decl_Line = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "59", 1) }, nullptr);
    Debug_Abbrev.push_back(DW_AT_Decl_Line);
    //There are fixed length constant data forms for one, two, fourand eight byte values.
    DW_FORM_Data1;
    Debug_Abbrev.push_back(DW_FORM_Data1);
    //Describing a declaration that has a type
    IR* DW_AT_Type = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "73", 1) }, nullptr);
    Debug_Abbrev.push_back(DW_AT_Type);
    //identify any debugging information entry within the containing unit.
    IR* DW_FORM_Ref4 = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "19", 1) }, nullptr);
    Debug_Abbrev.push_back(DW_FORM_Ref4);
    //Containing compilation unit.
    IR* DW_AT_External = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "63", 1) }, nullptr);
    Debug_Abbrev.push_back(DW_AT_External);
    //Represented explicitly as a single byte of data.
    IR* DW_FORM_flag_present = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "25", 1) }, nullptr);
    Debug_Abbrev.push_back(DW_FORM_flag_present);
    //End of marker
    EOM;
    Debug_Abbrev.push_back(EOM);
    //End of marker
    EOM;
    Debug_Abbrev.push_back(EOM);
    //Abbreviation Code describes the current section as an index
    IR* Abbreviation_Code_Describing_Index_2 = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "3", 1) }, nullptr);
    Debug_Abbrev.push_back(Abbreviation_Code_Describing_Index_2);
    //associated with another entry that also has the tag.
    IR* DW_TAG_Variable = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "52", 1) }, nullptr);
    Debug_Abbrev.push_back(DW_TAG_Variable);
    //the next physically succeeding entry of any debugging information entry using this abbreviation is a sibling of that entry.
    IR* DW_CHILDREN_No = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "0", 1) }, nullptr);
    Debug_Abbrev.push_back(DW_CHILDREN_No);
    //Transfers control of DWARF expression evaluation to the DW_AT_location attribute of the referenced debugging information entry.
    IR* DW_AT_Location = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "2", 1) }, nullptr);
    Debug_Abbrev.push_back(DW_AT_Location);
    //This is an unsigned LEB128 length followed by the number of information bytes specified by the length.
    IR* DW_FORM_Exprloc = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "24", 1) }, nullptr);
    Debug_Abbrev.push_back(DW_FORM_Exprloc);
    //Any debugging information entry representing a program entity that has been given a name.
    IR* DW_AT_Name = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "3", 1) }, nullptr);
    Debug_Abbrev.push_back(DW_AT_Name);
    //Attribute values of class
    DW_FORM_Strp;
    Debug_Abbrev.push_back(DW_FORM_Strp);
    //Any debugging information entry representing the declaration of an object, module, subprogram or type.
    IR* DW_AT_Decl_File = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "58", 1) }, nullptr);
    Debug_Abbrev.push_back(DW_AT_Decl_File);
    //There are fixed length constant data forms for one, two, fourand eight byte values.
    DW_FORM_Data1;
    Debug_Abbrev.push_back(DW_FORM_Data1);
    //represents the source line number at which the first character of the identifier of the declared object appears.
    IR* DW_AT_Decl_Line = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "59", 1) }, nullptr);
    Debug_Abbrev.push_back(DW_AT_Decl_Line);
    //There are fixed length constant data forms for one, two, fourand eight byte values.
    DW_FORM_Data1;
    Debug_Abbrev.push_back(DW_FORM_Data1);
    //The entry referenced may describe a base type, that is, a type that is not defined in terms of other data types, or it may describe a user - defined type, such as an array, structure or enumeration.
    IR* DW_AT_Type = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "73", 1) }, nullptr);
    Debug_Abbrev.push_back(DW_AT_Type);
    //identify any debugging information entry within the containing unit.
    DW_FORM_Ref4;
    Debug_Abbrev.push_back(DW_FORM_Ref4);
    //End of marker
    EOM;
    Debug_Abbrev.push_back(EOM);
    //End of marker
    EOM;
    Debug_Abbrev.push_back(EOM);
    //Abbreviation Code describes the current section as an index
    IR* Abbreviation_Code_Describing_Index_3 = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "4", 1) }, nullptr);
    Debug_Abbrev.push_back(Abbreviation_Code_Describing_Index_3);
    //A base type is represented by a debugging information entry with the tag.
    IR* DW_TAG_Base_Type = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "36", 1) }, nullptr);
    Debug_Abbrev.push_back(DW_TAG_Base_Type);
    //the next physically succeeding entry of any debugging information entry using this abbreviation is a sibling of that entry.
    DW_CHILDREN_No;
    Debug_Abbrev.push_back(DW_CHILDREN_No);
    //Any debugging information entry representing a program entity that has been given a name.
    DW_AT_Name;
    Debug_Abbrev.push_back(DW_AT_Name);
    //Attribute values of class
    DW_FORM_Strp;
    Debug_Abbrev.push_back(DW_FORM_Strp);
    // describing how the base type is encoded and is to be interpreted.
    IR* DW_AT_Encoding = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "62", 1) }, nullptr);
    Debug_Abbrev.push_back(DW_AT_Encoding);
    //There are fixed length constant data forms for one, two, fourand eight byte values.
    DW_FORM_Data1;
    Debug_Abbrev.push_back(DW_FORM_Data1);
    //Many debugging information entries allow either a DW_AT_byte_size attribute or a DW_AT_bit_size attribute, whose integer constant value.
    IR* DW_AT_Byte_Size = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "11", 1) }, nullptr);
    Debug_Abbrev.push_back(DW_AT_Byte_Size);
    //There are fixed length constant data forms for one, two, fourand eight byte values.
    DW_FORM_Data1;
    Debug_Abbrev.push_back(DW_FORM_Data1);
    //End of marker
    EOM;
    Debug_Abbrev.push_back(EOM);
    //End of marker
    EOM;
    Debug_Abbrev.push_back(EOM);
    //End of marker
    EOM;
    Debug_Abbrev.push_back(EOM);

}
