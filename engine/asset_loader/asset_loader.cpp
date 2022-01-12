#include "asset_loader.h"

std::vector<std::unique_ptr<load_file>> *asset_loader::AssetData = new std::vector<std::unique_ptr<load_file>>;

asset_loader::asset_loader() { }

void asset_loader::MainLoader()
{
	// NOTE(fix): Implement read from list of files here.
	AssetData->push_back(std::unique_ptr<load_file>(new load_file_bmp("Source/data/projectiles/StandardLaser.bmp")));

	// NOTE: Player.
	AssetData->push_back(std::unique_ptr<load_file>(new load_file_bmp("Source/data/player/SpaceShip_Idle.bmp")));
	AssetData->push_back(std::unique_ptr<load_file>(new load_file_bmp("Source/data/player/SpaceShip_Down.bmp")));
	AssetData->push_back(std::unique_ptr<load_file>(new load_file_bmp("Source/data/player/SpaceShip_Up.bmp")));
	AssetData->push_back(std::unique_ptr<load_file>(new load_file_bmp("Source/data/player/SpaceShip_Forward.bmp")));
	AssetData->push_back(std::unique_ptr<load_file>(new load_file_bmp("Source/data/player/SpaceShip_Back.bmp")));

	// NOTE: Enemy 1.
	AssetData->push_back(std::unique_ptr<load_file>(new load_file_bmp("Source/data/enemy1/EnemyShip_1_Idle.bmp")));
	AssetData->push_back(std::unique_ptr<load_file>(new load_file_bmp("Source/data/enemy1/EnemyShip_1_Destroyed_1.bmp")));
	AssetData->push_back(std::unique_ptr<load_file>(new load_file_bmp("Source/data/enemy1/EnemyShip_1_Destroyed_2.bmp")));
	AssetData->push_back(std::unique_ptr<load_file>(new load_file_bmp("Source/data/enemy1/EnemyShip_1_Destroyed_3.bmp")));
	AssetData->push_back(std::unique_ptr<load_file>(new load_file_bmp("Source/data/enemy1/EnemyShip_1_Destroyed_4.bmp")));
	AssetData->push_back(std::unique_ptr<load_file>(new load_file_bmp("Source/data/enemy1/EnemyShip_1_Destroyed_5.bmp")));
	AssetData->push_back(std::unique_ptr<load_file>(new load_file_bmp("Source/data/enemy1/EnemyShip_1_Destroyed_6.bmp")));
	AssetData->push_back(std::unique_ptr<load_file>(new load_file_bmp("Source/data/enemy1/EnemyShip_1_Destroyed_7.bmp")));
	AssetData->push_back(std::unique_ptr<load_file>(new load_file_bmp("Source/data/enemy1/EnemyShip_1_Destroyed_8.bmp")));

	// NOTE: Stars.
	AssetData->push_back(std::unique_ptr<load_file>(new load_file_bmp("Source/data/stars/small_star_8x8_1.bmp")));
	AssetData->push_back(std::unique_ptr<load_file>(new load_file_bmp("Source/data/stars/small_star_8x8_2.bmp")));
	AssetData->push_back(std::unique_ptr<load_file>(new load_file_bmp("Source/data/stars/small_star_8x8_3.bmp")));
	AssetData->push_back(std::unique_ptr<load_file>(new load_file_bmp("Source/data/stars/medium_star_24x24.bmp")));
	AssetData->push_back(std::unique_ptr<load_file>(new load_file_bmp("Source/data/stars/big_star_24x24.bmp")));

	// NOTE: Explosion effect.
	AssetData->push_back(std::unique_ptr<load_file>(new load_file_bmp("Source/data/effects/SmallExplosion_0.bmp")));
	AssetData->push_back(std::unique_ptr<load_file>(new load_file_bmp("Source/data/effects/SmallExplosion_1.bmp")));
	AssetData->push_back(std::unique_ptr<load_file>(new load_file_bmp("Source/data/effects/SmallExplosion_2.bmp")));

	// NOTE: Test stuff.
	AssetData->push_back(std::unique_ptr<load_file>(new load_file_bmp("Source/data/testbackground_collision.bmp")));
	AssetData->push_back(std::unique_ptr<load_file>(new load_file_bmp("Source/data/testbackground.bmp")));
	AssetData->push_back(std::unique_ptr<load_file>(new load_file_bmp("Source/data/space.bmp")));

	std::cout << "DEBUG: Main assets successfully loaded.\n";
}

void asset_loader::FontLoader()
{
	for (uint8 FontSize = 12; FontSize < 28; FontSize++)
	{
		AssetData->push_back(std::unique_ptr<load_file>(new load_file_font("Source/data/fonts/manaspc.ttf", FontSize)));
		AssetData->push_back(std::unique_ptr<load_file>(new load_file_font("Source/data/fonts/medieval.ttf", FontSize)));
		AssetData->push_back(std::unique_ptr<load_file>(new load_file_font("Source/data/fonts/debug.ttf", FontSize)));
		AssetData->push_back(std::unique_ptr<load_file>(new load_file_font("Source/data/fonts/dosclassic.ttf", FontSize)));
	}

	std::cout << "DEBUG: Font assets successfully loaded.\n";
}

// NOTE: If the vector returns end iteratior, then we did not get a result.
// Return nullptr instead, and the function that called the asset needs to
// handle that nullptr.
bitmap_info *asset_loader::GetBitmapInfo(const char8 *ID)
{
	bitmap_info *Result = nullptr;
	std::vector<std::unique_ptr<load_file>>::iterator Find = std::find_if(AssetData->begin(), AssetData->end(), get_id(ID));
	if (Find == AssetData->end())
	{
		std::cout << "DEBUG: Error trying to get asset: " << ID << "\n";
	}
	else
	{
		load_file *LoadFile = Find->get();
		Result = LoadFile->GetBitmapInfo();
	}	
	return Result;
}

font_info *asset_loader::GetFontBitmapInfo(const char8 *ID, uint8 FontSize)
{
	font_info *Result = nullptr;
	std::vector<std::unique_ptr<load_file>>::iterator Find = std::find_if(AssetData->begin(), AssetData->end(), get_id_fontsize(ID, FontSize));
	if (Find == AssetData->end())
	{
		std::cout << "DEBUG: Error trying to get asset: " << ID << "\n";
	}
	else
	{
		load_file *LoadFile = Find->get();
		Result = LoadFile->GetFontBitmapInfo();
	}
	return Result;
}