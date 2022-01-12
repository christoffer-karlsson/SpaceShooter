#pragma once

#include "load_file.h"

struct shift_up;

class load_file_font : public load_file
{
	private:
	font_info *FontInfo;
	uint8 CharacterSize;
	const char8 RangeStart = 33;
	const char8 RangeEnd = 126;

	public:
	load_file_font(const char8 *ID, uint8 CharacterSize);
	void Read() override;
	font_info *GetFontBitmapInfo() const override;
	uint8 GetCharacterSize() const;
	char8 GetRangeStart() const;
	char8 GetRangeEnd() const;
};

struct shift_up
{
	uint32 operator()(uint8 Source)
	{
		return ((uint32)(Source << 24));
	}
};