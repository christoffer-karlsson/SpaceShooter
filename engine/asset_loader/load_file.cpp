#include "load_file.h"

load_file::load_file()
{
}

load_file::~load_file()
{
}

bitmap_info *load_file::GetBitmapInfo() const
{
	return nullptr;
}

font_info *load_file::GetFontBitmapInfo() const
{
	return nullptr;
}

char8 *load_file::GetFileID() const
{
	return (char8 *)ID;
}

void load_file::SetID(const char8 *ID)
{
	this->ID = ID;
}
