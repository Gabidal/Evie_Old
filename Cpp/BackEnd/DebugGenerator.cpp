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
    constexpr int Allocated = 0x4e;
    constexpr int Associated = 0x4f;
    constexpr int Data_location = 0x50;
    constexpr int Byte_stride = 0x51;
    constexpr int Entry_pc = 0x52;
    constexpr int Use_UTF8 = 0x53;
    constexpr int Extension = 0x54;
    constexpr int Ranges = 0x55;
    constexpr int Trampoline = 0x56;
    constexpr int Call_column = 0x57;
    constexpr int Call_file = 0x58;
    constexpr int Call_line = 0x59;
    constexpr int Description = 0x5a;
    constexpr int Binary_scale = 0x5b;
    constexpr int Decimal_scale = 0x5c;
    constexpr int Small = 0x5d;
    constexpr int Decimal_sign = 0x5e;
    constexpr int Digit_count = 0x5f;
    constexpr int Picture_string = 0x60;
    constexpr int Mutable = 0x61;
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
    IR* DW_AT_Low_Pc = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(DW_AT::Low_pc), 1) }, nullptr);
    Debug_Abbrev.push_back(DW_AT_Low_Pc);
    //Represented as an object of appropriate size to hold an address.
    IR* DW_FORM_Addr = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(DW_FORM::Addr), 1) }, nullptr);
    Debug_Abbrev.push_back(DW_FORM_Addr);
    //addresses of a debugging information entry.
    IR* DW_AT_High_Pc = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(DW_AT::High_pc), 1) }, nullptr);
    Debug_Abbrev.push_back(DW_AT_High_Pc);
    //Add a new attribute form for section offsets.
    IR* DW_FORM_Data4 = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(DW_FORM::Data4), 1) }, nullptr);
    Debug_Abbrev.push_back(DW_FORM_Data4);
    //End of marker
    IR* EOM = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "0", 1) }, nullptr);
    Debug_Abbrev.push_back(EOM);
    //End of marker
    EOM;
    Debug_Abbrev.push_back(EOM);

    for (auto i : Global_Scope->Defined) {
        if (i->Is_Template_Object)
            continue;
        Generate_Abbrev(Abbrev_Type(i));
        for (auto j : i->Defined)
            if (!j->Is_Template_Object)
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
    //This label indicates that the next variable defined, inlists the size of the debug_info section
    Debug_Info.push_back(new IR(new Token(TOKEN::LABEL, "Debug_Info_Start"), {}, nullptr));
    //This is the variable which has the next section size init.
    IR* Section_Size = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::LABEL, "Debug_Info_End-Debug_Info", 4) }, nullptr);
    Debug_Info.push_back(Section_Size);
    //This label indicates that the next variable defined, inlists the size of the debug_info section
    IR* Debug_Info_Start = new IR(new Token(TOKEN::LABEL, "Debug_Info"), {}, nullptr);
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
    IR* DW_AT_High_Pc = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::LABEL, "Code_End", 8) }, nullptr);
    Debug_Info.push_back(DW_AT_High_Pc);

    int j = 0;
    for (auto i : Global_Scope->Defined) {
        if (i->Is_Template_Object)
            continue;

        bool Has_Template_Parameter = false;

        if (i->Has({ FUNCTION_NODE, PROTOTYPE, IMPORT, EXPORT }))
            for (auto P : i->Parameters)
                if (P->Inherits_Template_Type())
                    Has_Template_Parameter = true;

        if (Has_Template_Parameter)
            continue;

        Info_Generator(i);
    }        

    //Generate abref info for the void consept.
    Node* Void = new Node(CLASS_NODE, Global_Scope->Location);
    Void->Name = "func";
    Void->Scope = Global_Scope;

    Info_Generator(Void);
    
    Debug_Info.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(0), 1) }, nullptr));

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
    /*
    vector<string> Declarated_Local_Variable_Names;
    vector<string> Declarated_Local_Variable_Mangles;

    for (auto i : Global_Scope->Defined) {
        if (i->is(FUNCTION_NODE) || i->is(IMPORT) || i->is(PROTOTYPE))
            if (i->Calling_Count < 1 && (i->is("export") == -1))
                continue;
            if (i->is(FUNCTION_NODE) || i->is(CLASS_NODE)) {
                Abbrev_Type Info(i);
                bool Skip_Function_Declaration = false;
                for (auto defined : Declarated_Local_Variable_Names)
                    if (defined == i->Name) {
                        Skip_Function_Declaration = true;
                        break;
                    }
                Declarated_Local_Variable_Names.push_back(i->Name);
                if (!Skip_Function_Declaration) {
                    if (Info.MANGLED_NAME) {
                        for (auto defined : Declarated_Local_Variable_Mangles)
                            if (defined == MANGLER::Mangle(i) + "_MANGLE")
                                goto Skip_Mangle_1;
                        Declarated_Local_Variable_Mangles.push_back(MANGLER::Mangle(i) + "_MANGLE");
                        //Funtion name label indicator
                        Debug_Str.push_back(new IR(new Token(TOKEN::LABEL, MANGLER::Mangle(i) + "_MANGLE"), {}, nullptr));
                        //Function name
                        Debug_Str.push_back(new IR(new Token(TOKEN::OPERATOR, "ascii"), { new Token(TOKEN::STRING, MANGLER::Mangle(i)) }, nullptr));
                    Skip_Mangle_1:;
                    }
                    if (Info.NAME) {
                        //Funtion name label indicator
                        Debug_Str.push_back(new IR(new Token(TOKEN::LABEL, i->Name + "_NAME"), {}, nullptr));
                        //Function name
                        Debug_Str.push_back(new IR(new Token(TOKEN::OPERATOR, "ascii"), { new Token(TOKEN::STRING, i->Name) }, nullptr));
                    }
                }
                for (auto v : i->Defined) {
                    if (v->is("const") != -1)
                        continue;
                    for (auto defined : Declarated_Local_Variable_Names)
                        if (defined == v->Name)
                            goto Skip_Variable;

                    Declarated_Local_Variable_Names.push_back(v->Name);
                    Info = Abbrev_Type(v);
                    if (Info.MANGLED_NAME) {
                        for (auto defined : Declarated_Local_Variable_Mangles)
                            if (defined == MANGLER::Mangle(v) + "_MANGLE")
                                goto Skip_Mangle;
                        Declarated_Local_Variable_Mangles.push_back(MANGLER::Mangle(v) + "_MANGLE");
                        //Funtion name label indicator
                        Debug_Str.push_back(new IR(new Token(TOKEN::LABEL, MANGLER::Mangle(v) + "_MANGLE"), {}, nullptr));
                        //Function name
                        Debug_Str.push_back(new IR(new Token(TOKEN::OPERATOR, "ascii"), { new Token(TOKEN::STRING, MANGLER::Mangle(v)) }, nullptr));
                    Skip_Mangle:;
                    }
                    if (Info.NAME) {
                        //Funtion name label indicator
                        Debug_Str.push_back(new IR(new Token(TOKEN::LABEL, v->Name + "_NAME"), {}, nullptr));
                        //Function name
                        Debug_Str.push_back(new IR(new Token(TOKEN::OPERATOR, "ascii"), { new Token(TOKEN::STRING, v->Name) }, nullptr));
                    }

                Skip_Variable:;
                }
            }
    }
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
        Debug_Abbrev.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(ID), 1) }, nullptr));
    if (abbrev.TAG != - 1)
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
    if (abbrev.STACK_FRAME_REPRESENTIVE_REGISTER) {
        Debug_Abbrev.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(DW_AT::Frame_base), 1) }, nullptr));
        Debug_Abbrev.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(DW_FORM::Exprloc), 1) }, nullptr));
    }
    if (abbrev.STACK_FRAME_LOCATION) {
        Debug_Abbrev.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(DW_AT::Data_member_location), 1) }, nullptr));
        Debug_Abbrev.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(DW_FORM::Data2), 1) }, nullptr));
    }
    if (abbrev.MANGLED_NAME) {
        Debug_Abbrev.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(DW_AT::Linkage_name), 1) }, nullptr));
        Debug_Abbrev.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(DW_FORM::String), 1) }, nullptr));
    }
    if (abbrev.NAME) {
        Debug_Abbrev.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(DW_AT::Name), 1) }, nullptr));
        Debug_Abbrev.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(DW_FORM::String), 1) }, nullptr));
    }
    if (abbrev.ENCODING) {
        Debug_Abbrev.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(DW_AT::Encoding), 1) }, nullptr));
        Debug_Abbrev.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(DW_FORM::Data1), 1) }, nullptr));
    }
    if (abbrev.BYTE_SIZE) {
        Debug_Abbrev.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(DW_AT::Byte_size), 1) }, nullptr));
        Debug_Abbrev.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(DW_FORM::Data8), 1) }, nullptr));
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

    Abbrovation_IDs.push_back({abbrev, ID++});
}

void DebugGenerator::Insert_Start_End_Labels(vector<IR*>& input)
{
    IR* Debug_Info_Start = new IR(new Token(TOKEN::LABEL, "Code_Start"), {}, nullptr);
    input.insert(input.begin(), Debug_Info_Start);

    int Data_Section_Start;
    for (Data_Section_Start = 0; Data_Section_Start < input.size(); Data_Section_Start++)
        if (input[Data_Section_Start]->Arguments.size() > 0)
            if (input[Data_Section_Start]->OPCODE->Get_Name() == "section")
                if (input[Data_Section_Start]->Arguments[0]->Get_Name() == ".data")
                    break;
    IR* Debug_Info_End = new IR(new Token(TOKEN::LABEL, "Code_End"), {}, nullptr);
    input.insert(input.begin() + Data_Section_Start, Debug_Info_End);

    //IR* Section = new IR(new Token(TOKEN::OPERATOR, "section"), { new Token(TOKEN::LABEL, ".text") }, nullptr);
    //input.insert(input.begin(), Section);


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

void DebugGenerator::Info_Generator(Node* n)
{
    Abbrev_Type Info(n);
    string Mangled_Name;
    if (Info.TAG == -1)
        return;
    if (n->is(FUNCTION_NODE))
        if (n->Calling_Count == 0 && !n->is("export"))
            return;

    bool Skip_Scope_Generation = false;
    for (auto i : Genrated_Info)
        if ((i == n->Name /*|| i == MANGLER::Mangle(n, "")*/) && !n->is(OBJECT_DEFINTION_NODE)) {
            Skip_Scope_Generation = true;
            goto Go_Straight_To_Childs;
        }

    if (!Skip_Scope_Generation) {
        Genrated_Info.push_back(n->Name);
        //Genrated_Info.push_back(MANGLER::Mangle(n, ""));
    }

    Mangled_Name = n->Name;
    if (n->is(CLASS_NODE) && !MANGLER::Is_Base_Type(n))
        Mangled_Name = MANGLER::Mangle(n, "");

    if (n->is(CLASS_NODE))
        Debug_Info.push_back(new IR(new Token(TOKEN::LABEL, "_" + Mangled_Name + "_START"), {}, nullptr));

    Debug_Info.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(Get_Abbrovation_Index(n)), 1) }, nullptr));
    if (Info.CALLING_CONVENTION) {
        Debug_Info.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(1), 1) }, nullptr));
    }
    if (Info.STACK_FRAME_LOCATION) {
        Debug_Info.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(n->Memory_Offset), 2) }, nullptr));
    }
    if (Info.START)
        //The label that is in the start of the function
        Debug_Info.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::LABEL, MANGLER::Mangle(n, "") + "_START", 8)}, nullptr));
    if (Info.END)
        //The label that is in the end of the function
        Debug_Info.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::LABEL, MANGLER::Mangle(n, "") + "_END", 8) }, nullptr));
    if (Info.MEMORY_LOCATION) {
        Debug_Info.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(2), 1) }, nullptr));
        Debug_Info.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(145), 1) }, nullptr));
        Debug_Info.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(n->Memory_Offset), 1) }, nullptr));
    }
    if (Info.STACK_FRAME_REPRESENTIVE_REGISTER) {
        //Location description.
        Debug_Info.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, "1", 1) }, nullptr));
        //The stack representive register number
        Debug_Info.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(selector->STACK_REPRESENTIVE_REGISTER), 1) }, nullptr));
    }
    if (Info.MANGLED_NAME)
        //Points into a string in data section which has the function name
        Debug_Info.push_back(new IR(new Token(TOKEN::SET_DATA, "ascii"), { new Token(TOKEN::STRING, MANGLER::Mangle(n, "")) }, nullptr));
    if (Info.NAME)
        //Points into a string in data section which has the function name
        Debug_Info.push_back(new IR(new Token(TOKEN::SET_DATA, "ascii"), { new Token(TOKEN::STRING, n->Name) }, nullptr));
    if (Info.ENCODING) {
        //Some constant for encoding the inlisted type.
        int Encoding = DW_ATE_signed;
        if (n->Format == "decimal")
            Encoding = DW_ATE_float;
        else if (n->is("ptr"))
            Encoding = DW_ATE_address;
        else if (n->Size == 1)
            Encoding = DW_ATE_signed_char;
        Debug_Info.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(Encoding), 1) }, nullptr));
    }
    if (Info.BYTE_SIZE) {
        Debug_Info.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(0), 8) }, nullptr));
    }
    if (Info.SOURCE_FILE)
        //The source file
        Debug_Info.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(Get_Index_From_File(n->Location->GetFilePath())), 1) }, nullptr));
    if (Info.SOURCE_LINE)
        //The source line the function starts at.
        Debug_Info.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(n->Location->GetFriendlyLine()), 1) }, nullptr));
    //Return type declaration address
    if (Info.TYPE) {
        string Inheritted = "";
        //purify the inheritted.
        for (auto i : n->Inheritted) {
            if (Lexer::GetComponent(i).is(Flags::KEYWORD_COMPONENT))
                continue;

            string Base_Type = MANGLER::Mangle(n->Find(i, n, CLASS_NODE), "");

            if (MANGLER::Is_Base_Type(n->Find(i, n, CLASS_NODE)))
                Base_Type = i;

            Inheritted = "_" + Base_Type;
            break;
        }
        if (Inheritted == "") {
            for (auto i : n->Inheritted) {
                if (i == "func") {
                    Inheritted = "_func";
                    break;
                }
            }
        }
        MANGLER::Clear_Class_Zipping_List();
        /*= n->Get_Inheritted((string)"_", true, false, true);
        if (Inheritted == "")
            Inheritted = n->Get_Inheritted((string)"_", true, false, false);*/
        IR* DW_AT_Type = new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::LABEL, Inheritted + "_START-Debug_Info_Start", 4) }, nullptr);
        Debug_Info.push_back(DW_AT_Type);
    }
Go_Straight_To_Childs:;
    if (!n->is(OBJECT_DEFINTION_NODE))
        for (auto v : n->Defined) {
            if (v->is("internal") || v->Is_Template_Object)
                continue;
            if (v->is(FUNCTION_NODE))
                continue;
            Info_Generator(v);
        }
    if (Info.HAS_CHILDREN && !Skip_Scope_Generation)
        Debug_Info.push_back(new IR(new Token(TOKEN::SET_DATA, "init"), { new Token(TOKEN::NUM, to_string(0), 1) }, nullptr));
}

int DebugGenerator::Get_Index_From_File(string s)
{
    for (auto i : Files)
        if (i.first == s)
            return i.second;
    if (s == "No File")
        return 1;
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

        //STACK_FRAME_LOCATION = true;
        STACK_FRAME_REPRESENTIVE_REGISTER = true;

        if (MANGLER::Is_Based_On_Base_Type(n)) {
            TYPE = false;
        }
    }
    else if (n->is(OBJECT_DEFINTION_NODE)) {
        TAG = DW_TAG::Variable;
        if (n->Scope->is(FUNCTION_NODE))
            MEMORY_LOCATION = true;
        else if (n->Scope->is(CLASS_NODE))
            STACK_FRAME_LOCATION = true;
    }
    else if (n->is(PARAMETER_NODE)) {
        TAG = DW_TAG::Formal_parameter;
        MEMORY_LOCATION = true;
    }
    else if (n->is(CLASS_NODE)) {
        BYTE_SIZE = true;        
        if (MANGLER::Is_Based_On_Base_Type(n)) {
            TYPE = false;
        }
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