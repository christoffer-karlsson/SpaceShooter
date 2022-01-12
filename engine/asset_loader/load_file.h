#pragma once

#include <fstream>
#include <iostream>
#include <windows.h>
#include <algorithm>
#include "..\..\global_defines.h"

struct bitmap_info;
struct font_info;

class load_file
{
	protected:
	const char8 *ID;

	public:
	virtual void Read() = 0;

	virtual bitmap_info *GetBitmapInfo() const;
	virtual font_info *GetFontBitmapInfo() const;
	
	char8 *GetFileID() const;

	void SetID(const char8 *ID);

	load_file();
	virtual ~load_file();
};

struct bitmap_info
{
	uint32 *PixelPointer;

	int32 Width;
	int32 Height;
	int32 BufferSize;
};

struct font_info
{
	struct bitmap_info
	{
		uint32 *Bitmap;
		int16 Width;
		int16 Height;
		int16 XOffset;
		int16 YOffset;
	} *BitmapInfo;

	uint8 CharacterSize;
	char8 RangeStart;
	char8 RangeEnd;
};