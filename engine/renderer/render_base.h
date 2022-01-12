#pragma once

#include <string>
#include "..\buffer\offscreen_buffer.h"
#include "..\asset_loader\asset_loader.h"
#include "..\renderer\render_mkrenderable.h"

// NOTE: This struct is meant to refer the pixel grid, so this
// is not handling any float values by design.
struct coord_xy
{
	int32 X, Y;
};

/**
*	Handles the actual rendering to the pixel buffer in memory. This class has
*	some generic tools to draw pixels and shapes. It also draws bitmap files and
*	font to the buffer.
*/
class render_base
{
	private:
	offscreen_buffer Buffer;
	asset_loader Asset;

	protected:
	bool PixelIsTransparent(uint32 Color);																						//!< Check if pixel is transparent before draw.
	void Pixel(coord_xy Point, uint32 Color);																					//!< Sets the pixel at given position, with given color.
	void PixelAlphaBlend(uint32 *Source, uint32 *Dest);																			//!< Checks alpha channel on source and destination pixel and blends them. (Currently not used because it is too slow). \todo { Fixa a usable alpha blend. }
	void Line(coord_xy PointA, coord_xy PointB, uint32 Color);																	//!< Render a line.
	void Rectangle(coord_xy Point, int32 Size, uint32 Color);																	//!< Render a rectangle.
	void Font(coord_xy Point, font_info::bitmap_info *Bitmap, uint32 Color);													//!< Render a character to the buffer.
	void Bitmap(coord_xy Point, bitmap_info *BitmapAsset, uint32 *NewBitmap);													//!< Render bitmap to the buffer.
	int32 ConvertCoordinateToMemoryLocation(coord_xy Point);																	//!< Convert the pixel buffer memory adresses, to X,Y coordinates.

	public:
	void DrawBitmap(renderable_object *RenderObject);																			//!< Gathers information about a bitmap, and calls Bitmap() which will render it. @param *RenderableObject Pointer to a renderable_object.
	void DrawBitmapText(std::string Text, real32 PositionX, real32 PositionY, uint32 Color, const char8 *ID, uint8 FontSize);	//!< Gathers information about a text string, and calls Font() which will render it.
	void FillScreen(uint32 Color);																								//!< Fills screen with given color. @param Color #FFXXXXXX value. \todo { Alpha value not used. }

	public:
	render_base();
};