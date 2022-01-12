#pragma once

#include "load_file.h"
#include "load_file_bmp.h"
#include "load_file_font.h"
#include <vector>
#include <memory>

/**
*	Loads assets to memory. Can load bmp-files (32-bit 0x A8 R8 G8 B8 format) and tff-files.
*	Pointers to the assets loaded are stored in a vector. 
*/
class asset_loader
{
	private:
	static std::vector<std::unique_ptr<load_file>> *AssetData;			//!< Static vector, storing pointers to load_file objects.

	public:
	void MainLoader();													//!< Load some bmp-files.
	void FontLoader();													//!< Load some tff-files.
	bitmap_info *GetBitmapInfo(const char8 *ID);						//!< @brief Get bitmap information, such as size and pixel buffer. @param *ID The asset id, same as path and filename. @return A pointer to a bitmap_info structure.
	font_info *GetFontBitmapInfo(const char8 *ID, uint8 FontSize);		//!< @brief Get font information, such as size and pixel buffer. @param *ID The asset id, same as path and filename. @param FontSize The font size. @return A pointer to a font_info structure.

	public:
	asset_loader();														//!< Default constructor.
};

/**
*	Predicate to get a file by its ID.
*/
struct get_id
{
	const char8 *ID;

	get_id(const char8 *ID) : ID(ID) { }

	bool operator()(std::unique_ptr<load_file> &ID)
	{
		return(ID->GetFileID() == this->ID);
	}
};

/**
*	Predicate to get a file by its ID and font size.
*/
struct get_id_fontsize
{
	const char8 *ID;
	uint8 FontSize;

	get_id_fontsize(const char8 *ID, uint8 FontSize) : ID(ID), FontSize(FontSize) { }

	bool operator()(std::unique_ptr<load_file> &ID)
	{
		return((ID->GetFileID() == this->ID) && (ID->GetFontBitmapInfo()->CharacterSize == FontSize));
	}
};