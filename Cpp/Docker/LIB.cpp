#include "../../H/Docker/LIB/LIB.h"

bool ends_with(std::string& value, std::string& ending)
{
   if (ending.size() > value.size()) return false;

   return equal(ending.rbegin(), ending.rend(), value.rbegin());
}

std::vector<ObjectFile> LIB::ExtractAllObjectFiles(uint8_t* buffer, uint64_t length)
{
    return std::vector<ObjectFile>();
}

std::vector<ObjectFile> LIB::ExtractAllObjectFiles(std::vector<uint8_t> buffer)
{
    return ExtractAllObjectFiles(buffer.data(), buffer.size());
}
/*
std::vector<ObjectFile> LIB::ExtractAllObjectFiles(uint8_t* buffer, uint64_t length)
{
   constexpr int BUFFER_SIZE = 1024;
   constexpr double GROWTH_RATE = 1.30;

   std::vector<ObjectFile> object_files;

   archive* handle = archive_read_new();
   archive_read_support_format_all(handle);
   archive_read_support_compression_all(handle);
   archive_read_support_filter_all(handle);
   archive_read_open_memory(handle, buffer, length);

   uint8_t* temporary = new uint8_t[BUFFER_SIZE];

   archive_entry* entry;

   while (archive_read_next_header(handle, &entry) == ARCHIVE_OK) 
   {
       const char* path = archive_entry_pathname(entry);
       int64_t size = archive_entry_size(entry);
       char* buf = new char[size];
       if (archive_read_data(handle, buf, size) != size)
       std::cout << "Error reading " << path << std::endl;
       size++;
      std::vector<uint8_t> result;
      uint64_t position = 0;
      std::string entry_name = archive_entry_pathname(entry);
      if (ends_with(entry_name, std::string(".obj")) ||
          ends_with(entry_name, std::string(".o")))
      {
         for (;;) {
            uint64_t size = archive_read_data(handle, temporary, BUFFER_SIZE);

            if (size < 0) {
               throw std::runtime_error("Archive read error");
            }

            if (size == 0) break;

            if (position + BUFFER_SIZE >= result.size())
            {
               result.resize(int(GROWTH_RATE * (result.size() + BUFFER_SIZE)), 0);
            }

            memcpy(&result.data()[position], temporary, size);
            position += size;
         }
         
         result.resize(position);

         object_files.push_back(result);
      }
      else
      {
         archive_read_data_skip(handle);
      }
   }

   archive_read_free(handle);
   return object_files;
}*/