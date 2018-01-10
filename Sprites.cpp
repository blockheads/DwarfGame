// Fill out your copyright notice in the Description page of Project Settings.

#include "DwarfGame.h"
#include "Sprites.h"
#include "PaperSprite.h"


Sprites* Sprites::SpritesRef = 0;


Sprites::Sprites()
{
	for ( int32 i = 0; i <= 39; i++ )
	{
		//FString str2 = FString( TEXT( "PaperSprite'/Game/Sprites/Tiles/basic_ground_tiles_Sprite_" ) );
		//str2.AppendInt( i );
		//str2.AppendChars( TEXT( "'" ), 1 );
		
		//GroundSprites.Add( i, ConstructorHelpers::FObjectFinder<UPaperSprite>( *str2 ).Object );
	}
	FString grassTile = FString( TEXT( "PaperSprite'/Game/Sprites/Tiles/dirt_tile_Sprite_0'" ) );
	FString groundTile = FString( TEXT( "PaperSprite'/Game/Sprites/Tiles/ground_Sprite_0.ground_Sprite_0'" ) );
	SpriteMap.Add( ESpriteTypes::ST_GROUND_0, ConstructorHelpers::FObjectFinder<UPaperSprite>( *groundTile ).Object );
	SpriteMap.Add( ESpriteTypes::ST_GRASS_0, ConstructorHelpers::FObjectFinder<UPaperSprite>( *grassTile ).Object );
}

Sprites::~Sprites()
{
}

// Get the Ground sprite at this num
UPaperSprite* Sprites::GetGroundSprite( ESpriteTypes SpriteType )
{
	return SpriteMap[SpriteType];
}

UPaperSprite* Sprites::GetGrassSprite( ESpriteTypes SpriteType )
{
	return SpriteMap[SpriteType];
}

// Get a random Ground Sprite
UPaperSprite* Sprites::GetRandomGroundSprite()
{
	return GetGroundSprite(ESpriteTypes::ST_GROUND_0);
}

Sprites* Sprites::GetInstance()
{
	if ( !SpritesRef )
	{
		SpritesRef = new Sprites();
	}
	return SpritesRef;
}

UPaperSprite* Sprites::GetSprite( ESpriteTypes SpriteType )
{
	return SpriteMap[SpriteType];
}