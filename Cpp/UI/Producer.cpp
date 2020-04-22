#include "../../H/UI/Producer.h"
string Produce_Working_Dir = "";

/*
    if (sys->Info.OS == "win32" && (sys->Info.Architecture == "x86"))
    {
        //target windows
        stringstream output;
        output << "..\\Cpp\\Assemblers\\yasm_win.exe -g dwarf2 -f win32 -o " << sys->Info.Destination_File << ".obj " << sys->Info.Destination_File;

        system(output.str().c_str());
        output = stringstream();

        output << "..\\Cpp\\Linkers\\GoLink.exe " << "/console " << "/debug coff " << "/entry main " << sys->Info.Destination_File << ".obj " << "kernel32.dll ";

        system(output.str().c_str());
    }
    else if (sys->Info.OS == "unix" && (sys->Info.Architecture == "x86"))
    {
        stringstream output;

        output << "yasm -g dwarf2 -f elf32 -o " << sys->Info.Destination_File + ".o " << sys->Info.Destination_File;

        system(output.str().c_str());
        output = stringstream();

        output << "ld -m elf_i386 -o " << sys->Info.Destination_File + ".this_is_the_runnable " << sys->Info.Destination_File + ".o ";
    }
*/

string Producer::Get_Linker_Type()
{
    if (OS == "win32")
    {
        return "Cpp\\Linkers\\GoLink.exe /console ";
    }
    else if (OS == "unix")
    {
        return "ld ";
    }
    return "";
}

string Producer::Get_Assembler()
{
    if (OS == "win32")
    {
        return "Cpp\\Assemblers\\yasm_win.exe ";
    }
    else if (OS == "unix")
    {
        return "yasm ";
    }
    return "";
}

string Producer::Get_Debug()
{
    if (Debug != "")
    {
        return " -g " + Debug;
    }
    return "";
}

string Producer::Get_Type()
{
    if (OS == "win32")
    {
        return " -f " + OS;
    }
    else if (OS == "unix")
    {
        if (Type == "exe")
        {
            return " -f " + (string)"elf32 ";
        }
        else
        {
            return " -f " + Type;
        }
    }
    return "";
}

string Producer::Get_File_Name()
{
    if (Output_File != "")
    {
        return "-o " + Output_File;
    }
    return "";
}

string Producer::Get_Assembly_Dest_Marker()
{
    return ".obj ";
}

string Producer::Get_Linker_Debug_Type()
{
    if (OS == "win32")
    {
        if (Type != "")
        {
            return "/debug coff ";
        }
        else
        {
            return "";
        }
    }
    else if (OS == "unix")
    {
        return "";
    }
    return "";
}

string Producer::Get_Linker_aarch()
{
    if (OS == "unix")
    {
        return " -m elf_i386 ";
    }
    return "";
}

string Producer::Get_Assembler_Output()
{
    return " -o " + Output_File + Get_Assembly_Dest_Marker();
}

string Producer::Get_Linker_Input()
{
    if (OS == "win32")
    {
        return Output_File + Get_Assembly_Dest_Marker();
    }
    else if (OS == "unix")
    {
        return  Output_File + Get_Assembly_Dest_Marker();
    }
    return "";
}

string Producer::Get_Added_Libs()
{
    if (OS == "win32")
    {
        string r = "";
        for (auto i : Libs)
        {
            r += i + " ";
        }
        return r + " kernel32.dll";
    }
    else if (OS == "unix")
    {
        string r = "";
        for (auto i : Libs)
        {
            r += "-l " + i + " ";
        }
        return r;
    }
    return "";
}

string Producer::Get_Entry()
{
    if (OS == "win32")
    {
        if (Type == "exe")
        {
            return "/entry main ";
        }
    }
    else if (OS == "unix")
    {
        return "";
    }
    return "";
}

string Producer::Link()
{
    return string();
}

string Producer::Get_Template()
{
    if (Find(Libs, "OpenGL32.lib"))
    {
        if (OS == "win32")
        {
            return "link \"glfw3.lib\" \"OpenGL32.lib\" \"kernel32.lib\" \"user32.lib\" \"gdi32.lib\" \"shell32.lib\" /DEBUG /SUBSYSTEM:CONSOLE /NOLOGO " + Output_File + ".obj /libpath:\"C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.18362.0\\um\\x86\" OpenGL32.lib /entry:main /out:\"" + Output_File +".exe\" /libpath:\"C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Tools\\MSVC\\14.25.28610\\lib\\x86\" vcruntime.lib /libpath:\"C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.18362.0\\ucrt\\x86\" /libpath:\"" + Produce_Working_Dir + "\" ucrt.lib";
        }
        else
        {
            cout << "Warning: Linker cannot find suitable template for:" << Get_All(Libs) << endl;
            cout << "Warning: Using fallback method for linking, might go wrong!" << endl;
            return "";
        }
    }
    return "";
}


string Producer::Update_Dir(string File_Name)
{
    int i = File_Name.find_last_of('/');
    if (i != -1)
    {
        Produce_Working_Dir += File_Name.substr(0, i + 1);
        return File_Name.substr(i + 1);
    }
    return "";
}

string Producer::Change_Dir()
{
    Update_Dir(Output_File);
    if (Produce_Working_Dir == "")
    {
        return "";
    }
    else
    {
       return (((string)"cd " + Produce_Working_Dir).c_str());
    }
}

bool Producer::Find(vector<string> in, string f)
{
    for (string s : in)
        if (s == f)
            return true;
    return false;
}

string Producer::Get_All(vector<string> in)
{
    string r = "";
    for (string s: in)
        r += s;
    return r;
}

string Producer::Get_Linker_Output(){
    if (OS == "win32"){
        return "";
    }
    else if (OS == "unix"){
        return "-o" + Output_File + ".ThisIsTotallyExecutable";
    }
    return "";
}

void Producer::Assemble_Command()
{
    stringstream output;
    output << Get_Assembler() << Get_Debug() << Get_Type() << Get_Assembler_Output() << Output_File;
    system(output.str().c_str());
    output = stringstream();
    if (Get_Template() == "")
    {
        output << Get_Linker_Type() << Get_Linker_aarch() << Get_Linker_Debug_Type() << Get_Entry() << Get_Linker_Input() << Get_Linker_Output() << Get_Added_Libs();// << " /mix";
    }
    else
    {
        Update_Dir(Output_File);
        output << Get_Template();
    }
    system(output.str().c_str());
}
