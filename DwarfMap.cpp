// Fill out your copyright notice in the Description page of Project Settings.

#include "DwarfGame.h"
#include "DwarfMap.h"
#include "Tile.h"
#include "Engine.h"
#include "Net/UnrealNetwork.h"


ADwarfMap::ADwarfMap( const FObjectInitializer& ObjectInitializer )
	: Super( ObjectInitializer )
{
	bReplicates = true;
	bAlwaysRelevant = true;
}

void ADwarfMap::SetWorld( UWorld* World )
{
	this->World = World;
}

TArray<ATile*>* ADwarfMap::GetAllTiles( )
{
	return &Tiles;
}

bool ADwarfMap::GenerateTiles( int Row, int Col, int Level )
{
	if ( Role == ROLE_Authority )
	{
		GEngine->AddOnScreenDebugMessage( -1, 5.f, FColor::Red, FString::Printf( TEXT( "SERVER GENERATING TILES" )) );
	}
	else
	{
		GEngine->AddOnScreenDebugMessage( -1, 5.f, FColor::Red, FString::Printf( TEXT( "CLIENT GENERATING TILES" )) );
	}

	if ( !World )
	{
		return false;
	}

	//Each tile is 128x128
	int X = 0.0f;
	int Y = 0.0f;

	MapBounds.minX = 0;
	MapBounds.minY = 0;
	MapBounds.maxX = Row - 1;
	MapBounds.maxY = Col - 1;
	MapBounds.RowSize = Row;
	MapBounds.ColSize = Col;

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
			Tiles.Add( tile );

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

void ADwarfMap::GetTileArea( class ATile* t1, class ATile* t2, TSet<ATile*>& Tiles )
{
	int32 xDelta = t2->X - t1->X;
	int32 yDelta = t2->Y - t1->Y;
	int32 xIncrement = FMath::Sign<int32>( xDelta == 0 ? 1 : xDelta ) * 1;
	int32 yIncrement = FMath::Sign<int32>( yDelta == 0 ? 1 : yDelta ) * 1;

	for ( int x = t1->X; x != t1->X + xDelta + xIncrement; x += xIncrement )
	{
		for ( int y = t1->Y; y != t1->Y + yDelta + yIncrement; y += yIncrement )
		{
			ATile* tile = GetTile( x, y );
			if ( tile )
			{
				Tiles.Add( tile );
			}
		}
	}
}

/*
So, Tiles contains all the tiles
In order to access the tile via X,Y.  Treat X as row, and Y as col
*/
ATile* ADwarfMap::GetTile( int32 X, int32 Y )
{
	ATile* tile = NULL;
	int index = X * MapBounds.RowSize + Y;
	if ( ValidateCoords( X, Y ) && Tiles.Num() > index )
	{
		tile = Tiles[index];
	}

	return tile;
}

bool ADwarfMap::ValidateCoords( int32 X, int32 Y )
{
	return ( X >= MapBounds.minX && Y >= MapBounds.minY && X <= MapBounds.maxX && Y <= MapBounds.maxY );
}

bool ADwarfMap::ValidateTile( ATile* tile )
{
	return ValidateCoords( tile->X, tile->Y );
}

/* Tile Direction Helper Functions Start */
ATile* ADwarfMap::GetTileLeft( ATile* tile )
{
	return GetTile( tile->X - 1, tile->Y );
}
ATile* ADwarfMap::GetTileRight( ATile* tile )
{
	return GetTile( tile->X + 1, tile->Y );
}
ATile* ADwarfMap::GetTileAbove( ATile* tile )
{
	return GetTile( tile->X, tile->Y + 1 );
}
ATile* ADwarfMap::GetTileBelow( ATile* tile )
{
	return GetTile( tile->X, tile->Y - 1 );
}
/* Tile Direction Helper Functions End */

void ADwarfMap::GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );
	DOREPLIFETIME( ADwarfMap, Tiles );
	DOREPLIFETIME( ADwarfMap, MapBounds );
}