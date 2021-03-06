#include "../../H/BackEnd/DebugGenerator.h"

namespace DW_TAG {
    constexpr int Namelist = 0x2b;
    constexpr int Namelist_item = 0x2c;
    constexpr int Packed_type = 0x2d;
    constexpr int Subprogram = 0x2e;
    constexpr int Template_type_parameter = 0x2f;
    constexpr int Template_value_parameter = 0x30;
    constexpr int Thrown_type = 0x31;
    constexpr int Try_block = 0x32;
    constexpr int Variant_part = 0x33;
    constexpr int Variable = 0x34;
    constexpr int Volatile_type = 0x35;
    constexpr int Dwarf_procedure = 0x36;
    constexpr int Restrict_type = 0x37;
    constexpr int Interface_type = 0x38;
    constexpr int Namespace = 0x39;
    constexpr int Imported_module = 0x3a;
    constexpr int Unspecified_type = 0x3b;
    constexpr int Partial_unit = 0x3c;
    constexpr int Imported_unit = 0x3d;
    constexpr int Condition = 0x3f;
    constexpr int Union_type = 0x17;
    constexpr int Unspecified_parameters = 0x18;
    constexpr int Variant = 0x19;
    constexpr int Common_block = 0x1a;
    constexpr int Common_inclusion = 0x1b;
    constexpr int Inheritance = 0x1c;
    constexpr int Inlined_subroutine = 0x1d;
    constexpr int Module = 0x1e;
    constexpr int Ptr_to_member_type = 0x1f;
    constexpr int Set_type = 0x20;
    constexpr int Subrange_type = 0x21;
    constexpr int With_stmt = 0x22;
    constexpr int Access_declaration = 0x23;
    constexpr int Base_type = 0x24;
    constexpr int Catch_block = 0x25;
    constexpr int Const_type = 0x26;
    constexpr int Constant = 0x27;
    constexpr int Enumerator = 0x28;
    constexpr int File_type = 0x29;
    constexpr int Friend = 0x2a;
    constexpr int Array_type = 0x01;
    constexpr int Class_type = 0x02;
    constexpr int Entry_point = 0x03;
    constexpr int Enumeration_type = 0x04;
    constexpr int Formal_parameter = 0x05;
    constexpr int Imported_declaration = 0x08;
    constexpr int Label = 0x0a;
    constexpr int Lexical_block = 0x0b;
    constexpr int Member = 0x0d;
    constexpr int Pointer_type = 0x0f;
    constexpr int Reference_type = 0x10;
    constexpr int Compile_unit = 0x11;
    constexpr int String_type = 0x12;
    constexpr int Structure_type = 0x13;
    constexpr int Subroutine_type = 0x15;
    constexpr int Typedef = 0x16;
}

namespace DW_CHILDREN {
    int No = 0x00;
    int Yes = 0x01;
}

namespace DW_AT {
    constexpr int Sibling = 0x01;
    constexpr int Location = 0x02;
    constexpr int Name = 0x03;
    constexpr int Ordering = 0x09;
    constexpr int Byte_size = 0x0b;
    constexpr int Bit_offset = 0x0c;
    constexpr int Bit_size = 0x0d;
    constexpr int Stmt_list = 0x10;
    constexpr int Low_pc = 0x11;
    constexpr int High_pc = 0x12;
    constexpr int Language = 0x13;
    constexpr int Discr = 0x15;
    constexpr int Discr_value = 0x16;
    constexpr int Visibility = 0x17;
    constexpr int Import = 0x18;
    constexpr int String_length = 0x19;
    constexpr int Common_reference = 0x1a;
    constexpr int Comp_dir = 0x1b;
    constexpr int Const_value = 0x1c;
    constexpr int Threads_scaled = 0x62;
    constexpr int Explicit = 0x63;
    constexpr int Object_pointer = 0x64;
    constexpr int Endianity = 0x65;
    constexpr int Elemental = 0x66;
    constexpr int Pure = 0x67;
    constexpr int Recursive = 0x68;
    constexpr int Signature = 0x69;
    constexpr int Main_subprogram = 0x6a;
    constexpr int Data_bit_offset = 0x6b;
    constexpr int Const_expr = 0x6c;
    constexpr int Enum_class = 0x6d;
    constexpr int Linkage_name = 0x6e;
    constexpr int Lo_user = 0x2000;
    constexpr int Hi_user = 0x3fff;
    constexpr int Decl_file = 0x3a;
    constexpr int Decl_line = 0x3b;
    constexpr int Declaration = 0x3c;
    constexpr int Discr_list = 0x3d;
    constexpr int Encoding = 0x3e;
    constexpr int External = 0x3f;
    constexpr int Frame_base = 0x40;
    constexpr int Friend = 0x41;
    constexpr int Identifier_case = 0x42;
    constexpr int Macro_info = 0x43;
    constexpr int Namelist_item = 0x44;
    constexpr int Priority = 0x45;
    constexpr int Segment = 0x46;
    constexpr int Specification = 0x47;
    constexpr int Static_link = 0x48;
    constexpr int Type = 0x49;
    constexpr int Use_location = 0x4a;
    constexpr int Variable_parameter = 0x4b;
    constexpr int Virtuality = 0x4c;
    constexpr int Vtable_elem_location = 0x4d;
    constexpr int Containing_type = 0x1d;
    constexpr int Default_value = 0x1e;
    constexpr int Inline = 0x20;
    constexpr int Is_optional = 0x21;
    constexpr int Lower_bound = 0x22;
    constexpr int Producer = 0x25;
    constexpr int Prototyped = 0x27;
    constexpr int Return_addr = 0x2a;
    constexpr int Start_scope = 0x2c;
    constexpr int Bit_stride = 0x2e;
    constexpr int Upper_bound = 0x2f;
    constexpr int Abstract_origin = 0x31;
    constexpr int Accessibility = 0x32;
    constexpr int Address_class = 0x33;
    constexpr int Artificial = 0x34;
    constexpr int Base_types = 0x35;
    constexpr int Calling_convention = 0x36;
    constexpr int Count = 0x37;
    constexpr int Data_member_location = 0x38;
    constexpr int Decl_column = 0x39;

}

namespace DW_FORM {
    constexpr int Addr = 0x01;
    constexpr int Block2 = 0x03;
    constexpr int Block4 = 0x04;
    constexpr int Data2 = 0x05;
    constexpr int Data4 = 0x06;
    constexpr int Data8 = 0x07;
    constexpr int String = 0x08;
    constexpr int Block = 0x09;
    constexpr int Block1 = 0x0a;
    constexpr int Data1 = 0x0b;
    constexpr int Flag = 0x0c;
    constexpr int Sdata = 0x0d;
    constexpr int Strp = 0x0e;
    constexpr int Udata = 0x0f;
    constexpr int Ref_addr = 0x10;
    constexpr int Ref1 = 0x11;
    constexpr int Ref2 = 0x12;
    constexpr int Ref4 = 0x13;
    constexpr int Ref8 = 0x14;
    constexpr int Ref_udata = 0x15;
    constexpr int Indirect = 0x16;
    constexpr int Sec_offset = 0x17;
    constexpr int Exprloc = 0x18;
    constexpr int Flag_present = 0x19;
    constexpr int Ref_sig8 = 0x20;
}

constexpr int DW_ATE_address = 0x01;
constexpr int DW_ATE_float = 0x04;
constexpr int DW_ATE_signed = 0x05;
constexpr int DW_ATE_signed_char = 0x06;

DebugGenerator::DebugGenerator(vector<IR*> &Input)
{
    Define_File_Index();
    Insert_Start_End_Labels(Input);
    Insert_Line_Change_Information(Input);
    Insert_Stack_Info(Input);

    Construct_Debug_Abbrev();
    Construct_Debug_Info();
    Construct_Debug_String();
    Construct_Line_Table();

    DOCKER::Append(Input, File_Index, 0);
    DOCKER::Append(Input, Debug_Abbrev);
    DOCKER::Append(Input, Debug_Info);
    DOCKER::Append(Input, Debug_Str);
    DOCKER::Append(Input, Debug_Line);
    DOCKER::Append(Input, Line_Table);

}

void DebugGenerator::Construct_Debug_Abbrev()
{
    //THE INFORMATION THAT IS DESCRIBED BELOW IS FROM http://www.dwarfstd.org/doc/DWARF4.pdf
    
    //                                                                                    .debug_abbrev,"",@progbits
    IR* Section = new IR(new Token(TOKEN::OPERATOR, "section"), {new Token(TOKEN::LABEL, ".debug_abbrev")}, nullptr);
    Debug_Abbrev.push_back(Section); 
    //tmp
    IR* debug_abbrev = new IR(new Token(TOKEN::LABEL, "debug_abbrev"), {}, nullptr);
    Debug_Abbrev.push_back(debug_abbrev);
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
    /*//Abbreviation Code describes the current section as an index
    IR* Abbreviation_Code_Describing_Index_1 = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "2", 1) }, nullptr);
    Debug_Abbrev.push_back(Abbreviation_Code_Describing_Index_1);
    //A template instantiation is represented by a debugging information entry with the tag.
    IR* DW_TAG_Subprogram = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "46", 1) }, nullptr);
    Debug_Abbrev.push_back(DW_TAG_Subprogram);
    //1-byte value that determines whether a debugging information entry using this abbreviation has child entries or not.
    DW_CHILDREN_Yes;
    Debug_Abbrev.push_back(DW_CHILDREN_Yes);
    //attribute for a single address.
    DW_AT_Low_Pc;
    Debug_Abbrev.push_back(DW_AT_Low_Pc);
    //Represented as an object of appropriate size to hold an address on the target machine.
    DW_FORM_Addr;
    Debug_Abbrev.push_back(DW_FORM_Addr);
    //pair of attributes for a single contiguous range of addresses.
    DW_AT_High_Pc;
    Debug_Abbrev.push_back(DW_AT_High_Pc);
    //Add a new attribute form for section offsets, DW_FORM_sec_offset, to replace the use of DW_FORM_data4and DW_FORM_data8 for section offsets.
    DW_FORM_Data4;
    Debug_Abbrev.push_back(DW_FORM_Data4);
    //offset from the address specified by the location description.
    IR* DW_AT_Frame_Base = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "64", 1) }, nullptr);
    Debug_Abbrev.push_back(DW_AT_Frame_Base);
    // takes a single operand encoded as a DW_FORM_exprloc value representing a DWARF expression.
    IR* DW_FORM_Exprloc = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "24", 1) }, nullptr);
    Debug_Abbrev.push_back(DW_FORM_Exprloc);
    //DW_AT_linkage_name
    //IR* DW_AT_Linkage_Name = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "110", 1) }, nullptr);
    //Debug_Abbrev.push_back(DW_AT_Linkage_Name);

    //Debugging information entry representing a program entity that has been given a name.
    DW_AT_Name;
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
    DW_FORM_Exprloc;
    Debug_Abbrev.push_back(DW_FORM_Exprloc);
    //Any debugging information entry representing a program entity that has been given a name.
    DW_AT_Name;
    Debug_Abbrev.push_back(DW_AT_Name);
    //Attribute values of class
    DW_FORM_Strp;
    Debug_Abbrev.push_back(DW_FORM_Strp);
    //Any debugging information entry representing the declaration of an object, module, subprogram or type.
    DW_AT_Decl_File;
    Debug_Abbrev.push_back(DW_AT_Decl_File);
    //There are fixed length constant data forms for one, two, fourand eight byte values.
    DW_FORM_Data1;
    Debug_Abbrev.push_back(DW_FORM_Data1);
    //represents the source line number at which the first character of the identifier of the declared object appears.
    DW_AT_Decl_Line;
    Debug_Abbrev.push_back(DW_AT_Decl_Line);
    //There are fixed length constant data forms for one, two, fourand eight byte values.
    DW_FORM_Data1;
    Debug_Abbrev.push_back(DW_FORM_Data1);
    //The entry referenced may describe a base type, that is, a type that is not defined in terms of other data types, or it may describe a user - defined type, such as an array, structure or enumeration.
    DW_AT_Type;
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
    */

    for (auto i : Global_Scope->Defined) {
        Generate_Abbrev(Abbrev_Type(i));
        for (auto j : i->Defined)
            Generate_Abbrev(Abbrev_Type(j));
    }
    EOM;
    Debug_Abbrev.push_back(EOM);
}

void DebugGenerator::Construct_Debug_Info()
{
    //THE INFORMATION THAT IS DESCRIBED BELOW IS FROM http://www.dwarfstd.org/doc/DWARF4.pdf

    //                                                                                    .debug_info,"",@progbits
    IR* Section = new IR(new Token(TOKEN::OPERATOR, "section"), { new Token(TOKEN::LABEL, ".debug_info") }, nullptr);
    Debug_Info.push_back(Section);
    //This is the variable which has the next section size init.
    IR* Section_Size = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::LABEL, "Debug_Info_End-Debug_Info_Start", 4) }, nullptr);
    Debug_Info.push_back(Section_Size);
    //This label indicates that the next variable defined, inlists the size of the debug_info section
    IR* Debug_Info_Start = new IR(new Token(TOKEN::LABEL, "Debug_Info_Start"), {}, nullptr);
    Debug_Info.push_back(Debug_Info_Start);
    //DWARF version number
    IR* DWARF_Version_Number = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "4", 2) }, nullptr);
    Debug_Info.push_back(DWARF_Version_Number);
    //Offset Into Abbrev. Section
    IR* Offset_Into_Abbrev_Section = new IR(new Token(TOKEN::SET_DATA, "secrel32"), { new Token(TOKEN::LABEL, "debug_abbrev", 4) }, nullptr);
    Debug_Info.push_back(Offset_Into_Abbrev_Section);
    //Bits size 8 == 64
    IR* Address_Size = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "8", 1) }, nullptr);
    Debug_Info.push_back(Address_Size);
    //represents a complete object file.
    IR* DW_TAG_Compile_Unit = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "1", 1) }, nullptr);
    Debug_Info.push_back(DW_TAG_Compile_Unit);
    //Containing information about the compiler that produced the compilation unit.
    IR* COMPILER = new IR(new Token(TOKEN::SET_DATA, "secrel32"), { new Token(TOKEN::NUM, ".COMPILER_NAME", 4) }, nullptr);
    Debug_Info.push_back(COMPILER);
    //Indicating the source language used to define the type. 
    IR* DW_AT_Language = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "0x29A", 2) }, nullptr);
    Debug_Info.push_back(DW_AT_Language);
    //Debugging information entry representing a program entity that has been given a name.
    IR* DW_AT_Name = new IR(new Token(TOKEN::SET_DATA, "secrel32"), { new Token(TOKEN::LABEL, ".FILE_NAME", 4) }, nullptr);
    Debug_Info.push_back(DW_AT_Name);
    //Attribute whose value is a section offset to the line number information for this compilation unit.
    IR* DW_AT_Stmt_List = new IR(new Token(TOKEN::SET_DATA, "secrel32"), { new Token(TOKEN::LABEL, ".LINE_TABLE", 4) }, nullptr);
    Debug_Info.push_back(DW_AT_Stmt_List);
    //Containing the current working directory of the compilation command that produced this compilation unit in whatever form makes sense for the host system.
    IR* DW_AT_Comp_Dir = new IR(new Token(TOKEN::SET_DATA, "secrel32"), { new Token(TOKEN::LABEL, ".DIRECTORY", 4) }, nullptr);
    Debug_Info.push_back(DW_AT_Comp_Dir);
    //Start of the all asm code
    IR* DW_AT_Low_Pc = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::LABEL, "Code_Start", 8) }, nullptr);
    Debug_Info.push_back(DW_AT_Low_Pc);
    //End of the all asm code
    IR* DW_AT_High_Pc = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::LABEL, "Code_End-Code_Start", 4) }, nullptr);
    Debug_Info.push_back(DW_AT_High_Pc);

    int j = 0;
    for (auto i : Global_Scope->Defined)
        if (i->is(FUNCTION_NODE))
            if (i->Calling_Count > 0 || (i->is("export") != -1))
                Function_Info(i, j++);

    Type_Info();

    //This label indicates the section start point.
    IR* Ldebug_Info_Start0 = new IR(new Token(TOKEN::LABEL, "Debug_Info_End"), {}, nullptr);
    Debug_Info.push_back(Ldebug_Info_Start0);

    /*
        .byte   2                               # Abbrev [2] 0x2a:0x28 DW_TAG_subprogram
        .quad   .Lfunc_begin0                   # DW_AT_low_pc
        .long   .Lfunc_end0-.Lfunc_begin0       # DW_AT_high_pc
        .byte   1                               # DW_AT_frame_base
        .byte   86
        .long   .Linfo_string3                  # DW_AT_name
        .byte   1                               # DW_AT_decl_file
        .byte   1                               # DW_AT_decl_line
        .long   82                              # DW_AT_type
                                        # DW_AT_external
        .byte   3                               # Abbrev [3] 0x43:0xe DW_TAG_variable
        .byte   2                               # DW_AT_location
        .byte   145
        .byte   120
        .long   .Linfo_string5                  # DW_AT_name
        .byte   1                               # DW_AT_decl_file
        .byte   2                               # DW_AT_decl_line
        .long   82                              # DW_AT_type
        .byte   0                               # End Of Children Mark
        .byte   4                               # Abbrev [4] 0x52:0x7 DW_TAG_base_type
        .long   .Linfo_string4                  # DW_AT_name
        .byte   5                               # DW_AT_encoding
        .byte   4                               # DW_AT_byte_size
        .byte   0                               # End Of Children Mark
.Ldebug_info_end0:
    */
}

void DebugGenerator::Construct_Debug_String()
{
    //the section for names
    IR* Section = new IR(new Token(TOKEN::OPERATOR, "section"), { new Token(TOKEN::LABEL, ".debug_str") }, nullptr);
    Debug_Str.push_back(Section);
    //Compiler name label indicator
    IR* Compiler_Name_Indicator = new IR(new Token(TOKEN::LABEL, ".COMPILER_NAME"), {}, nullptr);
    Debug_Str.push_back(Compiler_Name_Indicator);
    //Compiler name
    IR* Compiler_Name = new IR(new Token(TOKEN::OPERATOR, "ascii"), { new Token(TOKEN::STRING, "Evie engine 3.0.0 https://github.com/Gabidal/Evie") }, nullptr);
    Debug_Str.push_back(Compiler_Name);
    //File name label indicator
    IR* File_Name_Indicator = new IR(new Token(TOKEN::LABEL, ".FILE_NAME"), {}, nullptr);
    Debug_Str.push_back(File_Name_Indicator);
    //File name
    IR* File_Name = new IR(new Token(TOKEN::OPERATOR, "ascii"), { new Token(TOKEN::STRING, DOCKER::Included_Files[0]) }, nullptr);
    Debug_Str.push_back(File_Name);
    //Directory label indicator
    IR* Directory_Indicator = new IR(new Token(TOKEN::LABEL, ".DIRECTORY"), {}, nullptr);
    Debug_Str.push_back(Directory_Indicator);
    //Directory
    string Dir = "";
    DOCKER::Update_Working_Dir(DOCKER::Included_Files[0], Dir);
    IR* Directory = new IR(new Token(TOKEN::OPERATOR, "ascii"), { new Token(TOKEN::STRING, Dir) }, nullptr);
    Debug_Str.push_back(Directory);

    vector<string> Declarated_Local_Variable_Names;

    for (auto i : Global_Scope->Defined)
        if (i->is(FUNCTION_NODE) || i->is(CLASS_NODE) ) {
            bool Skip_Function_Declaration = false;
            for (auto defined : Declarated_Local_Variable_Names)
                if (defined == i->Name)
                    Skip_Function_Declaration = true;
            if (i->is(FUNCTION_NODE))
                if (i->Calling_Count < 1 && (i->is("export") == -1))
                    goto Skip_Func;
            Declarated_Local_Variable_Names.push_back(i->Name);
            if (!Skip_Function_Declaration) {
                //Funtion name label indicator
                IR* Function_Name_Indicator = new IR(new Token(TOKEN::LABEL, i->Name + "_NAME"), {}, nullptr);
                Debug_Str.push_back(Function_Name_Indicator);
                //Function name
                IR* Function_Name = new IR(new Token(TOKEN::OPERATOR, "ascii"), { new Token(TOKEN::STRING, i->Name) }, nullptr);
                Debug_Str.push_back(Function_Name);
            }
            for (auto v : i->Defined) {
                for (auto defined : Declarated_Local_Variable_Names)
                    if (defined == v->Name)
                        goto Skip_Variable;
                Declarated_Local_Variable_Names.push_back(v->Name);
                //Variable name label indicator
                IR* Variable_Name_Indicator = new IR(new Token(TOKEN::LABEL, v->Name + "_NAME"), {}, nullptr);
                Debug_Str.push_back(Variable_Name_Indicator);
                //Variable name
                IR* Variable_Name = new IR(new Token(TOKEN::OPERATOR, "ascii"), { new Token(TOKEN::STRING, v->Name) }, nullptr);
                Debug_Str.push_back(Variable_Name);

            Skip_Variable:;
            }
        Skip_Func:;
        }

    //forvoid functions too
    //Funtion name label indicator
    IR* Function_Name_Indicator = new IR(new Token(TOKEN::LABEL,  "func_NAME"), {}, nullptr);
    Debug_Str.push_back(Function_Name_Indicator);
    //Function name
    IR* Function_Name = new IR(new Token(TOKEN::OPERATOR, "ascii"), { new Token(TOKEN::STRING, "func_NAME") }, nullptr);
    Debug_Str.push_back(Function_Name);

    IR* Type_Name_Indicator = new IR(new Token(TOKEN::LABEL, "type_NAME"), {}, nullptr);
    Debug_Str.push_back(Type_Name_Indicator);
    //Function name
    IR* Type_Name = new IR(new Token(TOKEN::OPERATOR, "ascii"), { new Token(TOKEN::STRING, "type_NAME") }, nullptr);
    Debug_Str.push_back(Type_Name);


    /*
    .Linfo_string3:
    .asciz  "_Z5applev"                     // string offset=126
    .Linfo_string4:
    .asciz  "apple"                         // string offset=136
    .Linfo_string5:
    .asciz  "char"                          // string offset=142
    .Linfo_string6:
    .asciz  "_Z6bananav"                    // string offset=147
    .Linfo_string7:
    .asciz  "banana"                        // string offset=158
    .Linfo_string8:
    .asciz  "int"                           // string offset=165
    .Linfo_string9:
    .asciz  "a"                             // string offset=169
    .Linfo_string10:
    .asciz  "b"                             // string offset=171
    .Linfo_string11:
    .asciz  "c"                             // string offset=173
    .Linfo_string12:
    .asciz  "d"                             // string offset=175
    .ident  "clang version 13.0.0 (https://github.com/llvm/llvm-project.git 5de09ef02e24d234d9fc0cd1c6dfe18a1bb784b0)"
  
    */
}

void DebugGenerator::Construct_Line_Table()
{
    IR* Section = new IR(new Token(TOKEN::OPERATOR, "section"), { new Token(TOKEN::LABEL, ".LINE_TABLE") }, nullptr);
    Line_Table.push_back(Section);
    //tmp
    IR* debug_abbrev = new IR(new Token(TOKEN::LABEL, ".LINE_TABLE"), {}, nullptr);
    Line_Table.push_back(debug_abbrev);

}

void DebugGenerator::Define_File_Index()
{
    //.file [Num] [Path/File_Name]
    long long Current_File_Index = 1;
    for (auto i : DOCKER::Included_Files) {
        Files.push_back({ i, Current_File_Index });
        IR* File = new IR(new Token(TOKEN::OPERATOR, "file"), { new Token(TOKEN::LABEL, to_string(Current_File_Index++) + " \"" + i + "\"", 1) }, nullptr);
        File_Index.push_back(File);
    }
}

void DebugGenerator::Local_Variable_Info(Node* n)
{
    //Abrevation tag name, i have decided that this can be a constant
    IR* Abbrevation = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(Get_Abbrovation_Index(n)), 1) }, nullptr);
    Debug_Info.push_back(Abbrevation);
    // describes the location of a variable or parameter at run - time
    IR* DW_AT_Location = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "2", 1) }, nullptr);
    Debug_Info.push_back(DW_AT_Location);
    //Offset added to Stack representive register
    IR* DW_AT_Location_Offset_Representive = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "145", 1) }, nullptr);
    Debug_Info.push_back(DW_AT_Location_Offset_Representive);
    //the actual stack offset of the variable
    IR* DW_AT_Location_Offset = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(n->Memory_Offset), 1) }, nullptr);
    Debug_Info.push_back(DW_AT_Location_Offset);
    //The variable name as a string in data section
    IR* DW_AT_Name = new IR(new Token(TOKEN::SET_DATA, "secrel32"), { new Token(TOKEN::LABEL, n->Name + "_NAME", 4) }, nullptr);
    Debug_Info.push_back(DW_AT_Name);
    //The file that the variable is described.
    IR* DW_AT_Decl_File = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(Get_Index_From_File(n->Location->GetFilePath())), 1) }, nullptr);
    Debug_Info.push_back(DW_AT_Decl_File);
    //The line that the variable has defined in.
    IR* DW_AT_Decl_Line = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(n->Location->GetFriendlyLine()), 1) }, nullptr);
    Debug_Info.push_back(DW_AT_Decl_Line);
    //The inheritance type 
    if (Abbrev_Type(n).TYPE) {
        string Inheritted = n->Get_Inheritted("_", true, false, true);
        if (Inheritted == "")
            Inheritted = n->Get_Inheritted("_", true, false, false);
        IR* DW_AT_Type = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::LABEL, Inheritted + "_START-Debug_Info_Start", 8) }, nullptr);
        Debug_Info.push_back(DW_AT_Type);
    }
}

void DebugGenerator::Type_Info()
{
    for (auto i : Global_Scope->Defined)
        if (i->is(CLASS_NODE) && MANGLER::Is_Base_Type(i)) {
            //the label that others can reference to.
            IR* LINK = new IR(new Token(TOKEN::LABEL, "_" + i->Name + "_START"), {}, nullptr);
            Debug_Info.push_back(LINK);
            //the code that indicates that this is the type abbrovation.
            IR* Abrrovation = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(Get_Abbrovation_Index(i)), 1) }, nullptr);
            Debug_Info.push_back(Abrrovation);
            //The name that is represented in a string at the data section.
            IR* DW_AT_Name = new IR(new Token(TOKEN::SET_DATA, "secrel32"), { new Token(TOKEN::LABEL, i->Name + "_NAME", 8) }, nullptr);
            Debug_Info.push_back(DW_AT_Name);
            //Some constant for encoding the inlisted type.
            int Encoding = DW_ATE_signed;
            if (i->Format == "decimal")
                Encoding = DW_ATE_float;
            else if (i->is("ptr") != -1)
                Encoding = DW_ATE_address;
            else if (i->Size == 1)
                Encoding = DW_ATE_signed_char;
            IR* DW_AT_Encoding = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(Encoding), 1) }, nullptr);
            Debug_Info.push_back(DW_AT_Encoding);
            //Size of the type
            IR* DW_AT_Byte_Size = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(i->Size), 1) }, nullptr);
            Debug_Info.push_back(DW_AT_Byte_Size);
        }
        else if (i->is(CLASS_NODE)){
            IR* LINK = new IR(new Token(TOKEN::LABEL, "_" + i->Name + "_START"), {}, nullptr);
            Debug_Info.push_back(LINK);
            //the code that indicates that this is the type abbrovation.
            IR* Abrrovation = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(Get_Abbrovation_Index(i)), 1) }, nullptr);
            Debug_Info.push_back(Abrrovation);
            //the calling convensions for this class??
            IR* DW_AT_Calling_Convention = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "1", 1) }, nullptr);
            Debug_Info.push_back(DW_AT_Calling_Convention);
            //the name of this class
            IR* DW_AT_Name = new IR(new Token(TOKEN::SET_DATA, "secrel32"), { new Token(TOKEN::NUM, i->Name + "_NAME", 4) }, nullptr);
            Debug_Info.push_back(DW_AT_Name);
            //the size of this class
            IR* DW_AT_Byte_Size = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(i->Size), 1) }, nullptr);
            Debug_Info.push_back(DW_AT_Byte_Size);
            //the file that this class is defined in
            IR* DW_AT_Decl_File = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(Get_Index_From_File(i->Location->GetFilePath())), 1) }, nullptr);
            Debug_Info.push_back(DW_AT_Decl_File);
            //the line this class is defined in
            IR* DW_AT_Decl_Line = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(i->Location->GetFriendlyLine()), 1) }, nullptr);
            Debug_Info.push_back(DW_AT_Decl_Line);
            

            for (auto m : i->Defined) {
                if (m->is("const") != -1)
                    continue;
                //abrovation for this member variable

                //the code that indicates that this is the type abbrovation.
                IR* Abrrovation = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(Get_Abbrovation_Index(i)), 1) }, nullptr);
                Debug_Info.push_back(Abrrovation);
                //the name of this member variable
                IR* DW_AT_Name = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, m->Name + "_NAME", 4) }, nullptr);
                Debug_Info.push_back(DW_AT_Name);
                //type of this memebr variable
                if (Abbrev_Type(m).TYPE) {
                    string Inheritted = m->Get_Inheritted("_", true, false, true);
                    if (Inheritted == "")
                        Inheritted = m->Get_Inheritted("_", true, false, false);
                    IR* DW_AT_Type = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::LABEL, Inheritted + "_START-Debug_Info_Start", 8) }, nullptr);
                    Debug_Info.push_back(DW_AT_Type);
                }
                //the file that this class is defined in
                IR* DW_AT_Decl_File = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(Get_Index_From_File(m->Location->GetFilePath())), 1) }, nullptr);
                Debug_Info.push_back(DW_AT_Decl_File);
                //the line this class is defined in
                IR* DW_AT_Decl_Line = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(m->Location->GetFriendlyLine()), 1) }, nullptr);
                Debug_Info.push_back(DW_AT_Decl_Line);
                //the stack offset this variable dorments in
                IR* DW_AT_Data_Member_Location = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(m->Memory_Offset), 1) }, nullptr);
                Debug_Info.push_back(DW_AT_Data_Member_Location);
                //publicity of this member variable
                IR* DW_AT_Accessibility = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "1", 1) }, nullptr);
                Debug_Info.push_back(DW_AT_Accessibility);
            }
            
        }
   
    //End of the Type descriptors
    IR* End_Of_Children_Mark = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "0", 1) }, nullptr);
    Debug_Info.push_back(End_Of_Children_Mark);
}

int ID = 2;
void DebugGenerator::Generate_Abbrev(Abbrev_Type abbrev)
{
    if (abbrev.TAG == -1)
        return;     //unsupported type

    //first find if this abbrev does exist
    for (auto i : Abbrovation_IDs)
        if (abbrev == i.first)
            return;

    if (abbrev.ID)
        //Abbreviation Code describes the current section as an index
        Debug_Abbrev.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(ID++), 1) }, nullptr));
    if (abbrev.TAG == !- 1)
        Debug_Abbrev.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(abbrev.TAG), 1) }, nullptr));
    Debug_Abbrev.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(abbrev.HAS_CHILDREN), 1) }, nullptr));
    if (abbrev.CALLING_CONVENTION) {
        Debug_Abbrev.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(DW_AT::Calling_convention), 1) }, nullptr));
        Debug_Abbrev.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(DW_FORM::Data1), 1) }, nullptr));
    }
    if (abbrev.MEMORY_LOCATION) {
        Debug_Abbrev.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(DW_AT::Location), 1) }, nullptr));
        Debug_Abbrev.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(DW_FORM::Exprloc), 1) }, nullptr));
    }
    if (abbrev.START) {
        Debug_Abbrev.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(DW_AT::Low_pc), 1) }, nullptr));
        Debug_Abbrev.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(DW_FORM::Addr), 1) }, nullptr));
    }
    if (abbrev.END) {
        Debug_Abbrev.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(DW_AT::High_pc), 1) }, nullptr));
        Debug_Abbrev.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(DW_FORM::Data4), 1) }, nullptr));
    }
    if (abbrev.STACK_FRAME_LOCATION) {
        Debug_Abbrev.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(DW_AT::Frame_base), 1) }, nullptr));
        Debug_Abbrev.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(DW_FORM::Exprloc), 1) }, nullptr));
    }
    if (abbrev.MANGLED_NAME) {
        Debug_Abbrev.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(DW_AT::Linkage_name), 1) }, nullptr));
        Debug_Abbrev.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(DW_FORM::Strp), 1) }, nullptr));
    }
    if (abbrev.NAME) {
        Debug_Abbrev.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(DW_AT::Name), 1) }, nullptr));
        Debug_Abbrev.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(DW_FORM::Strp), 1) }, nullptr));
    }
    if (abbrev.ENCODING) {
        Debug_Abbrev.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(DW_AT::Encoding), 1) }, nullptr));
        Debug_Abbrev.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(DW_FORM::Data1), 1) }, nullptr));
    }
    if (abbrev.BYTE_SIZE) {
        Debug_Abbrev.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(DW_AT::Byte_size), 1) }, nullptr));
        Debug_Abbrev.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(DW_FORM::Data1), 1) }, nullptr));
    }
    if (abbrev.SOURCE_FILE) {
        Debug_Abbrev.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(DW_AT::Decl_file), 1) }, nullptr));
        Debug_Abbrev.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(DW_FORM::Data1), 1) }, nullptr));
    }
    if (abbrev.SOURCE_LINE) {
        Debug_Abbrev.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(DW_AT::Decl_line), 1) }, nullptr));
        Debug_Abbrev.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(DW_FORM::Data1), 1) }, nullptr));
    }
    if (abbrev.TYPE) {
        Debug_Abbrev.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(DW_AT::Type), 1) }, nullptr));
        Debug_Abbrev.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(DW_FORM::Ref4), 1) }, nullptr));
    }
    if (abbrev.EXTERNAL) {
        Debug_Abbrev.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(DW_AT::External), 1) }, nullptr));
        Debug_Abbrev.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(DW_FORM::Flag_present), 1) }, nullptr));
    }
    //EOM(0)
    Debug_Abbrev.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(0), 1) }, nullptr));
    Debug_Abbrev.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(0), 1) }, nullptr));

    Abbrovation_IDs.push_back({abbrev, ID});
}

void DebugGenerator::Insert_Start_End_Labels(vector<IR*>& input)
{
    IR* Debug_Info_Start = new IR(new Token(TOKEN::LABEL, "Code_Start"), {}, nullptr);
    input.insert(input.begin(), Debug_Info_Start);

    IR* Debug_Info_End = new IR(new Token(TOKEN::LABEL, "Code_End"), {}, nullptr);
    input.insert(input.end(), Debug_Info_End);

    IR* Section = new IR(new Token(TOKEN::OPERATOR, "section"), { new Token(TOKEN::LABEL, ".text") }, nullptr);
    input.insert(input.begin(), Section);


    for (int i = 0; i < input.size(); i++) {
        if (input[i]->is(TOKEN::START_OF_FUNCTION)) {
            input.insert(input.begin() + i, new IR(new Token(TOKEN::LABEL, input[i]->OPCODE->Get_Name() + "_START"), {}, nullptr));
            i++;
        }
        else if (input[i]->is(TOKEN::END_OF_FUNCTION)) {
            input.insert(input.begin() + i, new IR(new Token(TOKEN::LABEL, input[i]->OPCODE->Get_Name() + "_END"), {}, nullptr));
            i++;
        }
    }
}

void DebugGenerator::Insert_Line_Change_Information(vector<IR*>& input)
{
    int Current_Line = 0;
    for (int i = 0; i < input.size(); i++)
        if (input[i]->Location == nullptr)
            continue;
        else if (input[i]->Location->GetFriendlyLine() != Current_Line) {
            Current_Line = input[i]->Location->GetFriendlyLine();

            string Locatoin = to_string(Get_Index_From_File(input[i]->Location->GetFilePath())) + " " + to_string(Current_Line) + " " + to_string(input[i]->Location->GetFriendlyCharacter());
            input.insert(input.begin() + i, new IR(new Token(TOKEN::SET_DATA, "location"), { new Token(TOKEN::LABEL, Locatoin) }, input[i]->Location));
        }

}

void DebugGenerator::Insert_Stack_Info(vector<IR*> &Input)
{
    for (int i = 0; i < Input.size(); i++) {
        if (Input[i]->is(TOKEN::START_OF_FUNCTION)) {
            //cfi_startproc
            Input.insert(Input.begin() + i + 1, new IR(new Token(TOKEN::SET_DATA, "cfi_start"), {}, nullptr));
            //.cfi_def_cfa_offset 16
            Input.insert(Input.begin() + i + 2, new IR(new Token(TOKEN::SET_DATA, "cfi_offset"), {new Token(TOKEN::NUM, "16")}, nullptr));

        }
        else if (Input[i]->is(TOKEN::END_OF_FUNCTION)) {
            //cfi_endproc
            Input.insert(Input.begin() + i + 1, new IR(new Token(TOKEN::SET_DATA, "cfi_end"), {}, nullptr));
        }
    }
}

void DebugGenerator::Function_Info(Node* n, int i)
{
    
    //Function Abbrevation
    IR* Function_Abbrevation = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(Get_Abbrovation_Index(n)), 1) }, nullptr);
    Debug_Info.push_back(Function_Abbrevation);
    //The label that is in the start of the function
    IR* DW_AT_Low_Pc = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::LABEL, n->Name + "_START", 8) }, nullptr);
    Debug_Info.push_back(DW_AT_Low_Pc);
    //The label that is in the end of the function
    IR* DW_AT_High_Pc = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::LABEL, n->Name + "_END-" + n->Name + "_START", 4) }, nullptr);
    Debug_Info.push_back(DW_AT_High_Pc);
    //Location description.
    IR* DW_AT_Frame_Base = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "1", 1) }, nullptr);
    Debug_Info.push_back(DW_AT_Frame_Base);
    //The stack representive register number
    IR* DW_AT_Frame_Base_1 = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(selector->STACK_REPRESENTIVE_REGISTER), 1) }, nullptr);
    Debug_Info.push_back(DW_AT_Frame_Base_1);
    //Points into a string in data section which has the function name
    //IR* DW_AT_Linkage_Name = new IR(new Token(TOKEN::SET_DATA, "secrel32"), { new Token(TOKEN::LABEL, n->Name + "_NAME", 4) }, nullptr);
    //Debug_Info.push_back(DW_AT_Linkage_Name);
    //Points into a string in data section which has the function name
    IR* DW_AT_Name = new IR(new Token(TOKEN::SET_DATA, "secrel32"), { new Token(TOKEN::LABEL, n->Name + "_NAME", 4) }, nullptr);
    Debug_Info.push_back(DW_AT_Name);
    //The source file
    IR* DW_AT_Decl_File = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(Get_Index_From_File(n->Location->GetFilePath())), 1) }, nullptr);
    Debug_Info.push_back(DW_AT_Decl_File);
    //The source line the function starts at.
    IR* DW_AT_Decl_Line = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(n->Location->GetFriendlyLine()), 1) }, nullptr);
    Debug_Info.push_back(DW_AT_Decl_Line);
    //Return type declaration address
    if (Abbrev_Type(n).TYPE) {
        string Inheritted = n->Get_Inheritted("_", true, false, true);
        if (Inheritted == "")
            Inheritted = n->Get_Inheritted("_", true, false, false);
        IR* DW_AT_Type = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::LABEL, Inheritted + "_START-Debug_Info_Start", 4) }, nullptr);
        Debug_Info.push_back(DW_AT_Type);
    }
    for (auto v : n->Defined) {
        Local_Variable_Info(v);
    }

    if (n->Defined.size() > 0) {
        //End of the function
        IR* End_Of_Children_Mark = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "0", 1) }, nullptr);
        Debug_Info.push_back(End_Of_Children_Mark);
    }
}

int DebugGenerator::Get_Index_From_File(string s)
{
    for (auto i : Files)
        if (i.first == s)
            return i.second;
    throw::runtime_error("ERROR!");
}

int DebugGenerator::Get_Abbrovation_Index(Node* n)
{
    for (auto i : Abbrovation_IDs)
        if (Abbrev_Type(n) == i.first)
            return i.second;

    throw::runtime_error("ERROR");
}

Abbrev_Type::Abbrev_Type(Node* n)
{
    ID = true;
    NAME = true;
    TYPE = true;
    SOURCE_FILE = true;
    SOURCE_LINE = true;
    if (n->is(FUNCTION_NODE)) {
        TAG = DW_TAG::Subprogram;

        START = true;
        END = true;
        if (n->Defined.size() > 0)
            HAS_CHILDREN = true;

        STACK_FRAME_LOCATION = true;

        if (MANGLER::Is_Based_On_Base_Type(n)) {
            TYPE = false;
        }
    }
    else if (n->is(OBJECT_DEFINTION_NODE)) {
        TAG = DW_TAG::Variable;
        MEMORY_LOCATION = true;
    }
    else if (n->is(PARAMETER_NODE)) {
        TAG = DW_TAG::Formal_parameter;
        MEMORY_LOCATION = true;
    }
    else if (n->is(CLASS_NODE)) {
        if (MANGLER::Is_Base_Type(n)) {
            TAG = DW_TAG::Base_type;
            ENCODING = true;
        }
        else {
            if (n->Defined.size() > 0)
                HAS_CHILDREN = true;
            TAG = DW_TAG::Class_type;
            CALLING_CONVENTION = true;
        }
    }
    if (n->is("export")) {
        EXTERNAL = true;
        MANGLED_NAME = true;
    }
}