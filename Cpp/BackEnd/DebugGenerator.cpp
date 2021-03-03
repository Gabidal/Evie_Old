#include "../../H/BackEnd/DebugGenerator.h"


long long Function_Abbrovation_Count = 2;
constexpr long long Local_Variable_Abbrovation = 3;
long long Type_Abbrovation = 4;
long long Member_Abbrovation = 5;

DebugGenerator::DebugGenerator(vector<IR*> &Input)
{
    Insert_Start_End_Labels(Input);

    Define_File_Index();
    Construct_Debug_Abbrev();
    Construct_Debug_Info();
    Construct_Debug_String();
    Construct_Line_Table();

    DOCKER::Append(Input, File_Index);
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
    //Abbreviation Code describes the current section as an index
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
    IR* DW_AT_Linkage_Name = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "110", 1) }, nullptr);
    Debug_Abbrev.push_back(DW_AT_Linkage_Name);
    //Attribute values of class
    DW_FORM_Strp;
    Debug_Abbrev.push_back(DW_FORM_Strp);
    //Debugging information entry representing a program entity that has been given a name.
    DW_AT_Name;
    Debug_Abbrev.push_back(DW_AT_Name);
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
    IR* Offset_Into_Abbrev_Section = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::LABEL, "debug_abbrev", 4) }, nullptr);
    Debug_Info.push_back(Offset_Into_Abbrev_Section);
    //Bits size 8 == 64
    IR* Address_Size = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "8", 1) }, nullptr);
    Debug_Info.push_back(Address_Size);
    //represents a complete object file.
    IR* DW_TAG_Compile_Unit = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "1", 1) }, nullptr);
    Debug_Info.push_back(DW_TAG_Compile_Unit);
    //Containing information about the compiler that produced the compilation unit.
    IR* COMPILER = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, ".COMPILER_NAME", 4) }, nullptr);
    Debug_Info.push_back(COMPILER);
    //Indicating the source language used to define the type. 
    IR* DW_AT_Language = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "0x666", 2) }, nullptr);
    Debug_Info.push_back(DW_AT_Language);
    //Debugging information entry representing a program entity that has been given a name.
    IR* DW_AT_Name = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::LABEL, ".FILE_NAME", 4) }, nullptr);
    Debug_Info.push_back(DW_AT_Name);
    //Attribute whose value is a section offset to the line number information for this compilation unit.
    IR* DW_AT_Stmt_List = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::LABEL, ".LINE_TABLE", 4) }, nullptr);
    Debug_Info.push_back(DW_AT_Stmt_List);
    //Containing the current working directory of the compilation command that produced this compilation unit in whatever form makes sense for the host system.
    IR* DW_AT_Comp_Dir = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::LABEL, ".DIRECTORY", 4) }, nullptr);
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
            if (i->Calling_Count > 0)
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
                if (i->Calling_Count < 1)
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
    IR* Abbrevation = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(Local_Variable_Abbrovation), 1) }, nullptr);
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
    IR* DW_AT_Name = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::LABEL, n->Name + "_NAME", 4) }, nullptr);
    Debug_Info.push_back(DW_AT_Name);
    //The file that the variable is described.
    IR* DW_AT_Decl_File = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(Get_Index_From_File(n->Location->GetFilePath())), 1) }, nullptr);
    Debug_Info.push_back(DW_AT_Decl_File);
    //The line that the variable has defined in.
    IR* DW_AT_Decl_Line = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(n->Location->GetFriendlyLine()), 1) }, nullptr);
    Debug_Info.push_back(DW_AT_Decl_Line);
    //The inheritance type 
    string Inheritted = n->Get_Inheritted("_", true, false, true);
    if (Inheritted == "")
        Inheritted = n->Get_Inheritted("_", true, false, false);
    IR* DW_AT_Type = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::LABEL, Inheritted + "_START-Debug_Info_Start", 8) }, nullptr);
    Debug_Info.push_back(DW_AT_Type);
}

void DebugGenerator::Type_Info()
{
    for (auto i : Global_Scope->Defined)
        if (i->is(CLASS_NODE) && ((i->Defined.size() == 1 && i->Defined[0]->is("const") != -1) || (i->Defined.size() == 2 && i->Defined[0]->is("const") != -1 && i->Defined[0]->is("const") != -1))) {
            //the label that others can reference to.
            IR* LINK = new IR(new Token(TOKEN::LABEL, "_" + i->Name + "_START"), {}, nullptr);
            Debug_Info.push_back(LINK);
            //the code that indicates that this is the type abbrovation.
            IR* Abrrovation = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(Type_Abbrovation), 1) }, nullptr);
            Debug_Info.push_back(Abrrovation);
            //The name that is represented in a string at the data section.
            IR* DW_AT_Name = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::LABEL, i->Name + "_NAME", 8) }, nullptr);
            Debug_Info.push_back(DW_AT_Name);
            //Some constant for encoding the inlisted type.
            IR* DW_AT_Encoding = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "62", 1) }, nullptr);
            Debug_Info.push_back(DW_AT_Encoding);
            //Size of the type
            IR* DW_AT_Byte_Size = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(i->Size), 1) }, nullptr);
            Debug_Info.push_back(DW_AT_Byte_Size);
        }
        else if (i->is(CLASS_NODE)){
            while (Type_Abbrovation == Member_Abbrovation || Type_Abbrovation == Function_Abbrovation_Count || Type_Abbrovation == Local_Variable_Abbrovation)
                Type_Abbrovation++;
            IR* LINK = new IR(new Token(TOKEN::LABEL, "_" + i->Name + "_START"), {}, nullptr);
            Debug_Info.push_back(LINK);
            //the code that indicates that this is the type abbrovation.
            IR* Abrrovation = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(Type_Abbrovation), 1) }, nullptr);
            Debug_Info.push_back(Abrrovation);
            //the calling convensions for this class??
            IR* DW_AT_Calling_Convention = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "1", 1) }, nullptr);
            Debug_Info.push_back(DW_AT_Calling_Convention);
            //the name of this class
            IR* DW_AT_Name = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, i->Name + "_NAME", 4) }, nullptr);
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
                while (Member_Abbrovation == Type_Abbrovation || Member_Abbrovation == Function_Abbrovation_Count || Member_Abbrovation == Local_Variable_Abbrovation)
                    Member_Abbrovation++;

                //the code that indicates that this is the type abbrovation.
                IR* Abrrovation = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(Member_Abbrovation), 1) }, nullptr);
                Debug_Info.push_back(Abrrovation);
                //the name of this member variable
                IR* DW_AT_Name = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, m->Name + "_NAME", 4) }, nullptr);
                Debug_Info.push_back(DW_AT_Name);
                //type of this memebr variable
                string Inheritted = i->Get_Inheritted("_", true, false, true);
                if (Inheritted == "")
                    Inheritted = i->Get_Inheritted("_", true, false, false);
                IR* DW_AT_Type = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::LABEL, Inheritted + "_START-Debug_Info_Start", 8) }, nullptr);
                Debug_Info.push_back(DW_AT_Type);
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

    //make one for void return typed functions
    //the label that others can reference to.
    IR* LINK = new IR(new Token(TOKEN::LABEL, "_func_START"), {}, nullptr);
    Debug_Info.push_back(LINK);
    //the code that indicates that this is the type abbrovation.
    IR* Abrrovation = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(Type_Abbrovation), 1) }, nullptr);
    Debug_Info.push_back(Abrrovation);
    //The name that is represented in a string at the data section.
    IR* DW_AT_Name = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::LABEL, "func_NAME", 8) }, nullptr);
    Debug_Info.push_back(DW_AT_Name);
    //Some constant for encoding the inlisted type.
    IR* DW_AT_Encoding = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "1", 1) }, nullptr);
    Debug_Info.push_back(DW_AT_Encoding);
    //Size of the type
    IR* DW_AT_Byte_Size = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(0), 1) }, nullptr);
    Debug_Info.push_back(DW_AT_Byte_Size);

    IR* Type_LINK = new IR(new Token(TOKEN::LABEL, "_type_START"), {}, nullptr);
    Debug_Info.push_back(Type_LINK);
    //the code that indicates that this is the type abbrovation.
    IR* Type_Abrrovation = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(Type_Abbrovation), 1) }, nullptr);
    Debug_Info.push_back(Type_Abrrovation);
    //The name that is represented in a string at the data section.
    IR* Type_DW_AT_Name = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::LABEL, "type_NAME", 8) }, nullptr);
    Debug_Info.push_back(Type_DW_AT_Name);
    //Some constant for encoding the inlisted type.
    IR* Type_DW_AT_Encoding = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "1", 1) }, nullptr);
    Debug_Info.push_back(Type_DW_AT_Encoding);
    //Size of the type
    IR* Type_DW_AT_Byte_Size = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(0), 1) }, nullptr);
    Debug_Info.push_back(Type_DW_AT_Byte_Size);

   
    //End of the Type descriptors
    IR* End_Of_Children_Mark = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "0", 1) }, nullptr);
    Debug_Info.push_back(End_Of_Children_Mark);
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

void DebugGenerator::Function_Info(Node* n, int i)
{
    while ((Function_Abbrovation_Count == Local_Variable_Abbrovation) || (Function_Abbrovation_Count == Type_Abbrovation)) {
        Function_Abbrovation_Count++;
    }
    //Function Abbrevation
    IR* Function_Abbrevation = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(Function_Abbrovation_Count), 1) }, nullptr);
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
    IR* DW_AT_Linkage_Name = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::LABEL, n->Name + "_NAME", 4) }, nullptr);
    Debug_Info.push_back(DW_AT_Linkage_Name);
    //Points into a string in data section which has the function name
    IR* DW_AT_Name = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::LABEL, n->Name + "_NAME", 4) }, nullptr);
    Debug_Info.push_back(DW_AT_Name);
    //The source file
    IR* DW_AT_Decl_File = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(i), 1) }, nullptr);
    Debug_Info.push_back(DW_AT_Decl_File);
    //The source line the function starts at.
    IR* DW_AT_Decl_Line = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(n->Location->GetFriendlyLine()), 1) }, nullptr);
    Debug_Info.push_back(DW_AT_Decl_Line);
    //Return type declaration address
    string Inheritted = n->Get_Inheritted("_", true, false, true);
    if (Inheritted == "")
        Inheritted = n->Get_Inheritted("_", true, false, false);
    IR* DW_AT_Type = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::LABEL, Inheritted + "_START-Debug_Info_Start", 4) }, nullptr);
    Debug_Info.push_back(DW_AT_Type);

    for (auto v : n->Defined) {
        Local_Variable_Info(v);
    }

    //End of the function
    IR* End_Of_Children_Mark = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "0", 1) }, nullptr);
    Debug_Info.push_back(End_Of_Children_Mark);
}

int DebugGenerator::Get_Index_From_File(string s)
{
    for (auto i : Files)
        if (i.first == s)
            return i.second;
    throw::runtime_error("ERROR!");
}

