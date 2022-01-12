#include "render_base.h"

render_base::render_base() { }

int32 render_base::ConvertCoordinateToMemoryLocation(coord_xy Point)
{
	// NOTE: This will convert the memory access so we can talk about x, y-coordinates instead.
	int32 Result = 0;

	if (Point.X > Buffer.GetWidth())	{ int32 X = Buffer.GetWidth(); }
	else if (Point.X < 0)				{ int32 X = 0; }

	if (Point.Y > Buffer.GetHeight())	{ int32 Y = Buffer.GetHeight(); }
	else if (Point.Y < 0)				{ int32 Y = 0; }

	if (Point.Y < 0)					{ Result = Point.X; }
	else								{ Result = (Point.Y * Buffer.GetWidth()) + Point.X; }

	return Result;
}

void render_base::FillScreen(uint32 Color)
{
	for (int32 Y = 0; Y < Buffer.GetHeight(); Y++)
	{
		for (int32 X = 0; X < Buffer.GetWidth(); X++)
		{
			Pixel({ X, Y }, Color);
		}
	}
}

void render_base::Pixel(coord_xy Point, uint32 Color)
{
	offscreen_buffer Buffer;
	if (!((Point.Y > Buffer.GetHeight() - 1) || (Point.Y < 0)) 
		&& !((Point.X > Buffer.GetWidth() - 1) || (Point.X < 0)))
	{
		uint32 *BufferPointer = Buffer.GetMemoryBegin();
		if (!PixelIsTransparent(Color))
		{
			BufferPointer[ConvertCoordinateToMemoryLocation({ Point.X, Point.Y })] = Color;
			// NOTE: See info in PixelAlphaBlend() about this blending.
			/*uint32 *Source = &Color;
			uint32 *Dest = &BufferPointer[ConvertCoordinateToMemoryLocation({ Point.X, Point.Y })];
			PixelAlphaBlend(Source, Dest);*/
		}
	}
}

void render_base::PixelAlphaBlend(uint32 *Source, uint32 *Dest)
{
	// NOTE: Linear alpha blend formula used: (1 - t)A + tB
	// This is way too slow, might need to move to OpenGL to handle things like alpha,
	// or find a better method. Around 7 fps in release mode with this!!
	real32 SA = (real32)((*Source >> 24) & 0xFF) / 255.0f;
	real32 SR = (real32)((*Source >> 16) & 0xFF);
	real32 SG = (real32)((*Source >> 8) & 0xFF);
	real32 SB = (real32)((*Source >> 0) & 0xFF);
	real32 DR = (real32)((*Dest >> 16) & 0xFF);
	real32 DG = (real32)((*Dest >> 8) & 0xFF);
	real32 DB = (real32)((*Dest >> 0) & 0xFF);

	real32 R = (1.0f - SA) * DR + SA * SR;
	real32 G = (1.0f - SA) * DG + SA * SG;
	real32 B = (1.0f - SA) * DB + SA * SB;

	*Dest = (((uint32)(R + 0.5f) << 16) | ((uint32)(G + 0.5f) << 8) | ((uint32)(B + 0.5f) << 0));
}

void render_base::Line(coord_xy PointA, coord_xy PointB, uint32 Color)
{
	// NOTE: This does not work when slope is declining!!
	real32 Y = 0;
	real32 Coefficient = 1;

	real32 DeltaX = PointB.X - PointA.X;
	real32 DeltaY = PointB.Y - PointA.Y;

	if (!(DeltaX == 0) && !(DeltaX == DeltaY))
	{
		Coefficient = DeltaY / DeltaX;
	}

	for (int32 X = PointA.X; X < PointB.X; X++)
	{
		Y = Coefficient * X;
		Pixel({ (int32)X, (int32)Y }, Color);
	}
}

void render_base::Rectangle(coord_xy Point, int32 Size, uint32 Color)
{
	int32 StartX = Point.X - (Size / 2);
	int32 StartY = Point.Y - (Size / 2);

	for (int32 Y = StartY; Y < (StartY + Size); Y++)
	{
		for (int32 X = StartX; X < (StartX + Size); X++)
		{
			Pixel({ X, Y }, Color);
		}
	}
}

void render_base::Font(coord_xy Point, font_info::bitmap_info *BitmapInfo, uint32 Color)
{
	// NOTE: This does not work as intended atm. If alpha channel is inputted,
	// the font will dissapear. No blending is done yet!
	uint32 *SourcePixel = BitmapInfo->Bitmap;
	for (int32 Y = BitmapInfo->Height + Point.Y; Y > Point.Y; Y--)
	{
		for (int32 X = Point.X; X < BitmapInfo->Width + Point.X; X++)
		{
			*SourcePixel = (*SourcePixel | Color);
			Pixel({ X, Y }, *SourcePixel);
			SourcePixel++;
		}
	}
}

void render_base::Bitmap(coord_xy Point, bitmap_info *Bitmap, uint32 *NewBitmap)
{
	if (!(Bitmap == nullptr))
	{
		// NOTE: Offset so that the bitmap is centered around the point.
		int32 MidPointXOffset = Bitmap->Width / 2;
		int32 MidPointYOffset = Bitmap->Height / 2;
		uint32 *SourcePixel = NewBitmap;
		for (int32 Y = Point.Y - MidPointYOffset; Y < Bitmap->Height + Point.Y - MidPointYOffset; Y++)
		{
			for (int32 X = Point.X - MidPointXOffset; X < Bitmap->Width + Point.X - MidPointXOffset; X++)
			{
				Pixel({ X, Y }, *SourcePixel);
				SourcePixel++;
			}
		}
	}
}

bool render_base::PixelIsTransparent(uint32 Color)
{
	// Checking in format: 0x A8 R8 G8 B8.
	// NOTE: Alpha blending need to be implemented here!!
	bool Result = 0;
	uint32 AlphaBits = (Color >> 24);
	if (AlphaBits < 128)
	{
		Result = 1;
	}
	return Result;
}

void render_base::DrawBitmap(renderable_object *RenderObject)
{
	bitmap_info *BitmapAsset = Asset.GetBitmapInfo(RenderObject->GetAssetID());

	// Do a copy of source bitmap before operation.
	uint32 SourceSize = BitmapAsset->BufferSize;
	uint32 *SourceBitmap = BitmapAsset->PixelPointer;
	uint32 *DestBitmap = new uint32[BitmapAsset->Width * BitmapAsset->Height];
	std::copy(SourceBitmap, SourceBitmap + SourceSize, DestBitmap);

	// NOTE(fix): Implement rotation/scaling on DestBitmap in future here!!

	// Normalazie the position.
	coord_xy PixelPoint;
	PixelPoint.X = (uint32)(RenderObject->GetPositionX() * Buffer.GetWidth());
	PixelPoint.Y = (uint32)(RenderObject->GetPositionY() * Buffer.GetHeight());

	// Call the actuall draw.
	Bitmap(PixelPoint, BitmapAsset, DestBitmap);

	// NOTE: Delete the copied bitmap after it is drawn.
	delete[] DestBitmap;
}

void render_base::DrawBitmapText(std::string Text, real32 PositionX, real32 PositionY, uint32 Color, const char8 *ID, uint8 FontSize)
{
	font_info *FontAsset = Asset.GetFontBitmapInfo(ID, FontSize);

	// Normalazie the position.
	coord_xy Point;
	Point.X = (uint32)(PositionX * Buffer.GetWidth());
	Point.Y = (uint32)(PositionY * Buffer.GetHeight());

	// NOTE: Some temporary y-offsets, since I have not found any way to
	// do it more efficient from the library.
	char8 YOffsets[255] = {};
	YOffsets[39] =	 8;	// ´
	YOffsets[44] =	-4;	// ,
	YOffsets[45] =	 5;	// -
	YOffsets[103] = -5;	// g
	YOffsets[106] = -7;	// j
	YOffsets[112] = -5;	// p
	YOffsets[113] = -5;	// q
	YOffsets[121] = -5;	// y

	if (!(FontAsset == nullptr))
	{
		font_info::bitmap_info *BitmapInfo = FontAsset->BitmapInfo;

		int16 YOffset = 0;
		int16 TotalXOffset = 0;
		char8 Character = 0;
		std::string::iterator TextPointer = Text.begin();
		while (TextPointer != Text.end())
		{
			// If there is a valid character in the range, draw it and adjust XOffset based on that
			// character. If not, we assume there is a space and the offset then represent the space
			// character.
			Character = *TextPointer;
			if ((Character >= FontAsset->RangeStart) && (Character < FontAsset->RangeEnd))
			{
				if (YOffsets[Character] != 0)
				{
					YOffset = YOffsets[Character];
				}
				Font({ (Point.X + TotalXOffset), (Point.Y + YOffset) }, (BitmapInfo + Character), Color);
				TotalXOffset += (BitmapInfo + Character)->XOffset + (BitmapInfo + Character)->Width + 2;
				YOffset = 0;
			}
			else
			{
				TotalXOffset += FontAsset->CharacterSize - 13.0;
			}
			TextPointer++;
		}
	}
}