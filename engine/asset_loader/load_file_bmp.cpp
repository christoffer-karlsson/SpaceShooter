#include "load_file_bmp.h"

load_file_bmp::load_file_bmp(const char8 *ID) 
	: BMPFileHeader(0), BMPInfoHeader(0), Pixel(0), FileInfoA(0), FileInfoB(0), BitmapInfo(0)
{
	SetID(ID);
	Read();
}

// NOTE: This can only handle 32-bit BMP files.
void load_file_bmp::Read()
{
	bool Error = 0;

	std::ifstream File(ID, std::ifstream::binary);
	if (!File)
	{
		std::cout << "DEBUG: Could not load file: \"" << ID << "\"\n";
		Error = 1;
	}

	// Read header first, to see file information and get the right offset before
	// reading the pixels. More info: https://msdn.microsoft.com/en-us/library/windows/desktop/dd183374(v=vs.85).aspx
	FileInfoA = new uint8[sizeof(BITMAPFILEHEADER)];
	FileInfoB = new uint8[sizeof(BITMAPV5HEADER)];

	File.read((char8*)FileInfoA, sizeof(BITMAPFILEHEADER));
	File.read((char8*)FileInfoB, sizeof(BITMAPV5HEADER));

	BMPFileHeader = (BITMAPFILEHEADER*)FileInfoA;
	BMPInfoHeader = (BITMAPV5HEADER*)FileInfoB;

	// Check to se if file type is BMP, and that it is 32-bit before proceeding.
	if (BMPFileHeader->bfType != 0x4D42)
	{
		std::cout << "DEBUG: File \"" << ID << "\" is not a bitmap file. Aborting asset load!\n";
		Error = 1;
	}

	if (BMPInfoHeader->bV5BitCount != 32)
	{
		std::cout << "DEBUG: File \"" << ID << "\" is not in a 32-bit format. Aborting asset load!\n";
		Error = 1;
	}

	if (Error)
	{
		delete[] FileInfoA;
		delete[] FileInfoB;
		BMPFileHeader = nullptr;
		BMPInfoHeader = nullptr;
		SetID(0);
	}
	else
	{
		Pixel = new uint8[BMPInfoHeader->bV5SizeImage];

		// Advance to the point where the actually image data starts which
		// is stated from the header, and read it to the buffer.
		File.seekg(BMPFileHeader->bfOffBits);
		File.read((char8*)Pixel, BMPInfoHeader->bV5SizeImage);

		// Gather all info, so that this can be returned easily in a struct.
		BitmapInfo = new bitmap_info;
		*BitmapInfo = {};
		BitmapInfo->Width = BMPInfoHeader->bV5Width;
		BitmapInfo->Height = BMPInfoHeader->bV5Height;
		BitmapInfo->BufferSize = BMPInfoHeader->bV5Width * BMPInfoHeader->bV5Height;
		BitmapInfo->PixelPointer = (uint32*)Pixel;

		// NOTE: Bytes are read in the wrong order for being used in window buffer, so just rearrange the
		// bytes to the proper format: 0x A8 R8 G8 B8.
		uint32 *Source = (uint32*)Pixel;
		std::transform(Source, Source + (BitmapInfo->Width * BitmapInfo->Height), Source, shift_alpha_bytes());
	}
}

bitmap_info *load_file_bmp::GetBitmapInfo() const
{
	return BitmapInfo;
}