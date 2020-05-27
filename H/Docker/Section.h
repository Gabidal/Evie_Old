#ifndef _SECTION_H_
#define _SECTION_H_

struct Section
{
	uint8_t* start;
	uint64_t size;
};

inline Section Get_Section_From_String(string& text)
{
	return Section { (uint8_t*)text.c_str(), text.size() };
}

#endif