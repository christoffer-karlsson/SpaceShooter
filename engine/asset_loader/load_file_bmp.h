#pragma once

#include "load_file.h"

class load_file_bmp : public load_file
{
	private:
	bitmap_info *BitmapInfo;
	BITMAPFILEHEADER *BMPFileHeader;
	BITMAPV5HEADER *BMPInfoHeader;
	uint8 *FileInfoA;
	uint8 *FileInfoB;
	uint8 *Pixel;

	public:
	load_file_bmp(const char8 *ID);

	void Read() override;

	bitmap_info *GetBitmapInfo() const override;
};

struct shift_alpha_bytes
{
	uint32 operator()(uint32 Source)
	{
		return (Source >> 8 | Source << 24);
	}
};

