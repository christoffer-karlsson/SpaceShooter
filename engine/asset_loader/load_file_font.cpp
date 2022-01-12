#include "load_file_font.h"

// Initiate the extern library.
#define STB_TRUETYPE_IMPLEMENTATION
#include "..\..\extern_libs\stb_truetype.h"

load_file_font::load_file_font(const char8 *ID, uint8 CharacterSize) 
	: FontInfo(nullptr), CharacterSize(CharacterSize)
{
	SetID(ID);
	Read();
}

void load_file_font::Read()
{
	bool Error = 0;

	FontInfo = new font_info;
	FontInfo->BitmapInfo = new font_info::bitmap_info[255];
	FontInfo->RangeStart = RangeStart;
	FontInfo->RangeEnd = RangeEnd;
	FontInfo->CharacterSize = CharacterSize;
	
	std::ifstream File(ID, std::ifstream::binary);
	if (!File)
	{
		std::cout << "DEBUG: Could not load file: " << ID << "\n";
		Error = 1;
	}

	if (Error)
	{
		SetID(0);
		delete[] FontInfo;
	}
	else
	{
		File.seekg(0, File.end);
		uint32 SizeInBytes = (uint32)File.tellg();
		File.seekg(0, File.beg);

		uint8 *ReadBuffer = new uint8[SizeInBytes];
		File.read((char8*)ReadBuffer, SizeInBytes);

		stbtt_fontinfo Font;
		stbtt_InitFont(&Font, ReadBuffer, stbtt_GetFontOffsetForIndex(ReadBuffer, 0));
		
		for (char8 Character = RangeStart; Character < RangeEnd; Character++)
		{
			int16 Width, Height, XOffset, YOffset;
			uint8 *TempBitmapBuffer = stbtt_GetCodepointBitmap(&Font, 0, stbtt_ScaleForPixelHeight(&Font, CharacterSize), Character, &Width, &Height, &XOffset, &YOffset);
			
			// NOTE: Since we get a 8-bit bitmap from the stbtt-library, just go through the buffer
			// and shift the LSB to uint32 MSB to get the alpha, and copy the right bit format to new buffer.
			uint8 *Source = TempBitmapBuffer;
			uint32 *Destination = new uint32[Width * Height];
			std::transform(Source, Source + (Width * Height), Destination, shift_up());

			// Library states that it need to deallocate.
			stbtt_FreeBitmap(TempBitmapBuffer, 0);

			// When the character bitmap is created and transformation is done, save it in the proper structure.
			FontInfo->BitmapInfo[Character].Bitmap = Destination;
			FontInfo->BitmapInfo[Character].Width = Width;
			FontInfo->BitmapInfo[Character].Height = Height;
			FontInfo->BitmapInfo[Character].XOffset = XOffset;
			FontInfo->BitmapInfo[Character].YOffset = YOffset;
		}

		delete[] ReadBuffer;
	}
}

font_info *load_file_font::GetFontBitmapInfo() const
{
	return FontInfo;
}

uint8 load_file_font::GetCharacterSize() const
{
	return CharacterSize;
}

char8 load_file_font::GetRangeStart() const
{
	return RangeStart;
}

char8 load_file_font::GetRangeEnd() const
{
	return RangeEnd;
}