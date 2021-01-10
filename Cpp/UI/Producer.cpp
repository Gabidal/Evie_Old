#include "../../H/UI/Producer.h"
string Produce_Working_Dir = "";

void Producer::Assembly_Other_Source_Files()
{
    stringstream output;
    output << " ";
    for (string i : Source_Files)
        output << Get_Assembler() << Get_Debug() << Get_Type() << " -o " + i + ".obj " << i;
    for (string i : Source_Files)
        Libs.push_back(i + ".obj");
    system(output.str().c_str());
    return ;
}

string Producer::Get_Linker_Type()
{
    if (OS == "win")
    {
        return "Linkers\\ld.exe ";
    }
    else if (OS == "unix")
    {
        return "ld ";
    }
    return "";
}

string Producer::Get_Assembler()
{
    if (OS == "win")
    {
        return "Assemblers\\as.exe ";
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
    return " --" + Size + " ";
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
    return "";
}

string Producer::Get_Linker_aarch()
{
    if (Size == "32")
    {
        return " -m elf32-i386 ";
    }
    return "";
}

string Producer::Get_Assembler_Output()
{
    return " -o " + Output_File + Get_Assembly_Dest_Marker();
}

string Producer::Get_Linker_Input()
{
   return  Output_File + Get_Assembly_Dest_Marker();
}

string Producer::Get_Added_Libs()
{
    if (OS == "win")
    {
        string r = "";
        for (auto i : Libs)
        {
            r += i + " ";
        }
        return r + " -l kernel32";
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
    return " -e main ";
}

string Producer::Get_System_Paths()
{
    char Seperator = ';';
    if (OS == "unix")
        Seperator = ':';

    string Result = "";
    size_t size = 0;
    char* Path = nullptr;//getenv("Path");
    if (_dupenv_s(&Path, &size, "Path") != 0 || Path == nullptr) {
        throw::exception("ERROR!");
    }
    string List = string(Path);

    vector<string> Paths;
    string tmp = "";
    for (auto i : List) {
        if (i == '\\')
            i = '/';
        if (i == Seperator) {
            if (tmp == "")
                continue;
            Paths.push_back(tmp);
            tmp = "";
        }
        else
            tmp += i;
    }
    for (auto i : Paths)
        Result += " -L \"" + i + "\"";

    return Result;
}

string Producer::Link()
{
    return string();
}

string Producer::Get_Template()
{
    if (Find(Libs, "OpenGL32.lib") || Find(Libs, "OpenGL32.Lib"))
    {
        if (OS == "win")
        {
            return "ld -l \"glfw3\" \"OpenGL32\" \"kernel32\" \"user32\" \"gdi32\" \"shell32\" " + Output_File + ".obj -L \"C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.18362.0\\um\\x86\" -e main -o \"" + Output_File +".exe\" -L \"C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Tools\\MSVC\\14.25.28610\\lib\\x86\" -l vcruntime -L \"C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.18362.0\\ucrt\\x86\" -L \"" + Produce_Working_Dir + "\" -l ucrt";
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
    int i = (int)File_Name.find_last_of('/');
    if (i != -1)
    {
        Produce_Working_Dir += File_Name.substr(0, (size_t)i + 1);
        return File_Name.substr((size_t)i + 1);
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
    if (OS == "win"){
        if (Type == "exe")
            return " -o " + Output_File + ".exe ";
        else if (Type == "dll")
            return "--shared -o" + Output_File + ".dll ";
    }
    else if (OS == "unix"){
        if (Type == "exe")
            return "-o" + Output_File + ".ThisIsTotallyExecutable ";
    }
    return "";
}

void Producer::Assemble_Command()
{
    Assembly_Other_Source_Files();
    stringstream output;
    output << Get_Assembler() << Get_Debug() << Get_Type() << Get_Assembler_Output() << Output_File;
    system(output.str().c_str());
    output = stringstream();
    if (Get_Template() == "")
    {
        output << Get_Linker_Type() << Get_Linker_aarch() << Get_Linker_Debug_Type() << Get_Entry() << Get_Linker_Input() << Get_Linker_Output() << Get_Added_Libs() << Get_System_Paths();// << " /mix";
    }
    else
    {
        Update_Dir(Output_File);
        output << Get_Template();
    }
    system(output.str().c_str());
}
