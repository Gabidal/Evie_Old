//WHAT EVER YOU THINK, WHAT EVER YOU WANT
//DONT!! FUCKING CHANGE THE ORDER OF THESE FUCKING HEADER DECLARATIONS YOU NOBNOB.
#define CURL_STATICLIB
#include "../../Dependencies/Curl/curl.h"
#include <regex>
#include "../../H/Docker/HTTPS.h"
#include "../../H/Docker/Obj.h"
#include "../../H/UI/Safe.h"
#include "../../H/Docker/Docker.h"
#include "../../H/UI/Producer.h"

#include "../../H/UI/Usr.h"
#include "../../H/Nodes/IR.h"

#include "../../H/BackEnd/BackEnd.h"
#include "../../H/Assembler/Assembler.h"
#include "../../H/Linker/Linker.h"
#include "../../H/Docker/DLL.h"

extern Usr* sys;

extern Assembler* assembler;

Producer::Producer(vector<IR*> IRs){

    if (sys->Info.Format == "asm" || sys->Info.Is_Service){
        string Output = "";

        if (sys->Info.Architecture == "x86")
            Output = ".intel_syntax noprefix\n";

        BackEnd Back(IRs, Output);

        ofstream o(sys->Info.Destination_File.c_str(), ios::binary);
        o << Output;
        o.close();
    }
    else{

        vector<PE::PE_OBJ*> Objects;

        //This only contains asm files, dll and lib files are in the sys->Info.Libs
        for (auto& i : sys->Info.Source_Files){
            Assembler a;
            a.Factory(i);

            Objects.push_back(new PE::PE_OBJ(a.Output));
        }

        assembler = new Assembler();
        assembler->Factory(IRs);

        PE::PE_OBJ* obj = new PE::PE_OBJ(assembler->Output);

        // This is for ALL obj files that are compiled with Evie ON COMPILETIME.
        if (sys->Info.Source_Files.size() > 0){
            Objects.push_back(obj);
            //This only gets asm files, dont bother with external obj files.
            obj = PE::Cluster_Local_PE_Objects(Objects);
        }

        //Now convert all the Evie Compiled obj files into same form as external obj files.
        // Since we dont want to play with obj->Content and obj->Raw_Section buffers at the same time.  
        vector<unsigned char> Buffer = PE::Write_Obj(*obj);

        ofstream o(sys->Info.Destination_File + ".obj", ios::binary);

        o.write((char*)Buffer.data(), Buffer.size());
        o.close();

        // This is for ALL obj files that were already compiled BEFORE EVIE COMPILETIME.
        if (sys->Info.Pre_Compiled_Sources.size() > 0){
            //now add the newly created obj file to the libs.
            sys->Info.Pre_Compiled_Sources.push_back(sys->Info.Destination_File + ".obj");
            obj = PE::Cluster_External_PE_Objects(sys->Info.Pre_Compiled_Sources);
            PE::Link_Pre_Compiled_Sources(obj);
        }
        else{
            // We still want to liquify the obj
            obj = new PE::PE_OBJ(Buffer, sys->Info.Destination_File + ".obj");
        }

        if (sys->Info.Format != "obj"){
            //if the desired output is not obj, then destroy the newly created obj file.
            remove((sys->Info.Destination_File + ".obj").c_str());
        }
        
        if (sys->Info.Format == "exe"){
            Linker::En_Large_PE_Header(obj);

            Linker::Inline_Relocations(obj);

            vector<unsigned char> Buffer = Linker::Write_PE_Executable(obj);

            ofstream o(sys->Info.Destination_File, ios::binary);

            o.write((char*)Buffer.data(), Buffer.size());
            o.close();
        }

        if (sys->Info.Format == "dll"){
            DLL::Enlarge_PE_Header(obj);

            Linker::Inline_Relocations(obj);

            vector<unsigned char> Buffer = DLL::Write_DLL(obj);

            ofstream o(sys->Info.Destination_File, ios::binary);

            o.write((char*)Buffer.data(), Buffer.size());
            o.close();
        }
    }
}

/*
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
            Check for errors
            if (res != CURLE_OK)
                Report(Observation(ERROR, curl_easy_strerror(res), Position()));

            regex expression("\"resource\": \"[a-f0-9]+\"");
            smatch matches;
            string Buffer = chunk.memory;
            if (!regex_search(Buffer, matches, expression)) {
                Report(Observation(MSG_Type::WARNING, "Could not get VT report.", Position()));
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
*/