//WHAT EVER YOU THINK, WHAT EVER YOU WANT
//DONT!! FUCKING CHANGE THE ORDER OF THESE FUCKING HEADER DECLARATIONS YOU NOBNOB.
#include "../../H/UI/Producer.h"
#define CURL_STATICLIB  
#include "../../Dependencies/Curl/curl.h"
#include <regex>
#include "../../H/Docker/HTTPS.h"
#include "../../H/UI/Safe.h"


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
        if (arch == "x86")
            return "Linkers\\x86_ld.exe ";
        else if (arch == "arm")
            return "Linkers\\arm_ld.exe ";
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
        if (arch == "x86")
            return "Assemblers\\x86_as.exe ";
        else if (arch == "arm")
            return "Assemblers\\arm_as.exe ";
    }
    else if (OS == "unix")
    {
        return "yasm ";
    }
    return "";
}

string Producer::Get_Debug()
{
    if (Debug)
    {
        return " -gdwarf3";
    }
    return "";
}

string Producer::Get_Type()
{
    return "";//" --" + Size + " ";
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
    if (HOST_OS == "win")
    {
        string r = "";
        for (auto i : Libs)
        {
            r += i + " ";
        }
        return r + " -l kernel32";
    }
    else if (HOST_OS == "unix")
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
    char* Path = getenv("Path");
    if (Path == nullptr) {
        throw::runtime_error("ERROR!");
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

    if (sys->Info.VT_API != "") {
        CURL* curl;
        CURLcode res;

        std::string contents;
        std::ifstream f("file.txt", std::ios::in | std::ios::binary);

        if (f)
        {
            f.seekg(0, std::ios::end);
            contents.resize(f.tellg());
            f.seekg(0, std::ios::beg);
            f.read(&contents[0], contents.size());
            f.close();
        }

        struct curl_httppost* formpost = NULL;
        struct curl_httppost* lastptr = NULL;
        struct curl_slist* headerlist = NULL;
        static const char buf[] = "Expect:";

        curl_global_init(CURL_GLOBAL_ALL);

        // set up the header
        curl_formadd(&formpost,
            &lastptr,
            CURLFORM_COPYNAME, "cache-control:",
            CURLFORM_COPYCONTENTS, "no-cache",
            CURLFORM_END);

        curl_formadd(&formpost,
            &lastptr,
            CURLFORM_COPYNAME, "content-type:",
            CURLFORM_COPYCONTENTS, "multipart/form-data",
            CURLFORM_END);

        curl_formadd(&formpost, &lastptr,
            CURLFORM_COPYNAME, "file",  // <--- the (in this case) wanted file-Tag!
            CURLFORM_BUFFER, "data",
            CURLFORM_BUFFERPTR, contents.data(),
            CURLFORM_BUFFERLENGTH, contents.size(),
            CURLFORM_END);

        curl_formadd(&formpost, &lastptr,
            CURLFORM_COPYNAME, "apikey",  // <--- the (in this case) wanted file-Tag!
            CURLFORM_BUFFER, "data",
            CURLFORM_BUFFERPTR, sys->Info.VT_API.data(),
            CURLFORM_BUFFERLENGTH, sys->Info.VT_API.size(),
            CURLFORM_END);

        curl = curl_easy_init();

        headerlist = curl_slist_append(headerlist, buf);
        CURL* curl_handle;
        res;

        MemoryStruct chunk;
        string Resource = "";
        if (curl) {

            curl_easy_setopt(curl, CURLOPT_URL, "https://www.virustotal.com/vtapi/v2/file/scan");

            curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &chunk);
            //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

            res = curl_easy_perform(curl);
            /* Check for errors */
            if (res != CURLE_OK)
                Report(Observation(1, curl_easy_strerror(res), Position()));

            regex expression("\"resource\": \"[a-f0-9]+\"");
            smatch matches;
            string Buffer = chunk.memory;
            if (!regex_search(Buffer, matches, expression)) {
                Report(Observation(2, "Could not get VT report.", Position()));
            }

            Resource = matches.str().substr(13, matches.str().size() - 1 - 13);

            curl_easy_cleanup(curl);


            curl_formfree(formpost);

            curl_slist_free_all(headerlist);
        }
        curl = curl_easy_init();
        free(chunk.memory);
        chunk = MemoryStruct();

        curl_easy_setopt(curl, CURLOPT_URL, "https://www.virustotal.com/vtapi/v2/file/report");
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
        string Data = "apikey=" + sys->Info.VT_API + "&resource=" + Resource;
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, Data.c_str());

        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            Report(Observation(1, curl_easy_strerror(res), Position()));

        regex expression("\"positives\": [0-9]+");
        smatch matches;
        string Buffer = chunk.memory;
        if (!regex_search(Buffer, matches, expression)) {
            Report(Observation(2, "VT is in cooldown, please wait moment, then re-try.", Position()));
        }
        else {
            int Positives = atoi(matches.str().substr(12).c_str());
            if (Positives > 0) {
                Report(Observation(1, "Dangereous binary detected " + Output_File, Position()));
            }
        }
    }
}
