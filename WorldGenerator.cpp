// Fill out your copyright notice in the Description page of Project Settings.

#include "DwarfGame.h"
#include "WorldGenerator.h"
#include "Tile.h"

namespace
{
	int Z = 0.0f;
}

WorldGenerator::WorldGenerator()
{
}

WorldGenerator::~WorldGenerator()
{
}

void WorldGenerator::SetWorld( UWorld* World )
{
	this->World = World;
}

bool WorldGenerator::GenerateTiles( int Row, int Col, int Level )
{
	if ( !World )
	{
		return false;
	}

	//Each tile is 128x128
	int X = 0.0f;
	int Y = 0.0f;

	for ( int row = 0; row < Row; row++ )
	{
		for ( int col = 0; col < Col; col++ )
		{
			ATile* tile = World->SpawnActor<ATile>( ATile::StaticClass( ) );
			tile->SetPosition( FVector( row, col, Level ) );
			if ( col == 0 )
			{
				//first row is for grass, create the grass here
				tile->SetTileSprite( ESpriteTypes::ST_GRASS_0 );
			}
			else
			{
				tile->SetTileSprite( ESpriteTypes::ST_GROUND_0 );
			}

			
		}
	}

	// CREATE WORLD IN GLOBAL FILE
	// WORLD WILL CONTAIN ALL THE TILES IN THE GAME
	// SHOULD BE ABLE TO GRAB A STATIC REF TO IT AND USE!
	// PUT IT INTO THE DWARFGAMEENGINE.H!!!
	// CREATE SELECTOR CLASS WHICH WILL SELECT TILES THAT I WANT
	// EZ
	return true;
}