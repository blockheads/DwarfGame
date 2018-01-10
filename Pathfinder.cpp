// Fill out your copyright notice in the Description page of Project Settings.

#include "DwarfGame.h"
#include "Pathfinder.h"
#include "DwarfMap.h"
#include "Tile.h"

namespace
{
	uint8 mUp = 0x1;
	uint8 mDown = 0x2;
	uint8 mLeft = 0x4;
	uint8 mRight = 0x8;
}

Pathfinder::Pathfinder()
{
}

Pathfinder::~Pathfinder()
{
}

bool Pathfinder::FindPathToArea( ATile* StartingTile, FTileArea* Destination, ADwarfMap* Map, FTilePath* Path )
{
	for ( ATile* tile : Destination->Tiles )
	{
		if ( FindPath( StartingTile, tile, Map, Path ) )
		{
			return true;
		}
	}
	return false;
}

bool Pathfinder::FindPath( ATile* t1, ATile* t2, ADwarfMap* Map, FTilePath* Path )
{
	TArray<ATile*> path = BFS( t1, t2, Map );
	if ( Path && path.Num() > 0 )
	{
		Path->Path = path;
		Path->StartingTile = t1;
		Path->EndingTile = t2;
	}
	
	if ( path.Num() > 0 )
	{
		return true;
	}

	return false;
}

/*
 * Start at a Tile, add it to stack
 * 
 * Pop Stack
 * if Goal tile -> Return
 * else add adjacent tiles to stack
 * repeat till path is found
*/
TArray<ATile*> Pathfinder::BFS( ATile* t1, ATile* t2, ADwarfMap* Map )
{
	TArray<ATile*> emptyPath;

	//Container for all possible paths
	TArray<TArray<ATile*>> paths;

	//array for tiles that have been reached
	TArray<ATile*> reachedTiles;

	TArray<ATile*> start;
	start.Add( t1 );

	paths.Add( start );
	reachedTiles.Add( t1 );
	while ( paths.Num() > 0 )
	{
		TArray<ATile*> path = paths[0];
		paths.RemoveAt( 0 );
		
		if ( path.Last() == t2 )
		{
			return path;
		}

		ATile* up = CanMoveUp( path.Last(), Map );
		ATile* down = CanMoveDown( path.Last(), Map );
		ATile* left = CanMoveLeft( path.Last(), Map );
		ATile* right = CanMoveRight( path.Last(), Map );



		/* Begin Add adjacent Tiles*/
		if ( up && !reachedTiles.Contains(up) )
		{
			TArray<ATile*> newPath = path;
			newPath.Add( up );
			paths.Add( newPath );
			reachedTiles.Add( up );
		}
		if ( down && !reachedTiles.Contains( down ) )
		{
			TArray<ATile*> newPath = path;
			newPath.Add( down );
			paths.Add( newPath );
			reachedTiles.Add( down );
		}
		if ( left && !reachedTiles.Contains( left ) )
		{
			TArray<ATile*> newPath = path;
			newPath.Add( left );
			paths.Add( newPath );
			reachedTiles.Add( left );
		}
		if ( right && !reachedTiles.Contains( right ) )
		{
			TArray<ATile*> newPath = path;
			newPath.Add( right );
			paths.Add( newPath );
			reachedTiles.Add( right );
		}
		/* End Add Adjacent Tiles*/
	}

	return emptyPath;
}

ATile* Pathfinder::CanMoveLeft( ATile* tile, ADwarfMap* Map )
{
	ATile* adjTile = Map->GetTileLeft( tile );
	if ( adjTile )
	{
		if ( adjTile->GetCollisionData() & mRight || tile->GetCollisionData() & mLeft )
		{
			adjTile = NULL;
		}
	}
	return adjTile;
}

ATile* Pathfinder::CanMoveRight( ATile* tile, ADwarfMap* Map )
{
	ATile* adjTile = Map->GetTileRight( tile );
	if ( adjTile )
	{
		if ( adjTile->GetCollisionData( ) & mLeft || tile->GetCollisionData( ) & mRight )
		{
			adjTile = NULL;
		}
	}
	return adjTile;
}

ATile* Pathfinder::CanMoveUp( ATile* tile, ADwarfMap* Map )
{
	ATile* adjTile = Map->GetTileAbove( tile );
	if ( adjTile )
	{
		if ( adjTile->GetCollisionData( ) & mDown || tile->GetCollisionData( ) & mUp )
		{
			adjTile = NULL;
		}
	}
	return adjTile;
}

ATile* Pathfinder::CanMoveDown( ATile* tile, ADwarfMap* Map )
{
	ATile* adjTile = Map->GetTileBelow( tile );
	if ( adjTile )
	{
		if ( adjTile->GetCollisionData( ) & mUp || tile->GetCollisionData( ) & mDown )
		{
			adjTile = NULL;
		}
	}
	return adjTile;
}

bool Pathfinder::CanMoveBetweenAdjacentTiles( ATile* t1, ATile* t2, ADwarfMap* Map )
{
	ATile* canMoveTile = NULL;

	if ( Map && Map->ValidateTile( t1 ) && Map->ValidateTile( t2 ) )
	{
		if ( t1->X == t2->X )
		{
			if ( t1->Y > t2->Y )
			{
				canMoveTile = CanMoveDown( t1, Map );
			}
			else
			{
				canMoveTile = CanMoveUp( t1, Map );
			}
		}

		if ( t1->Y == t2->Y )
		{
			if ( t1->X > t2->X )
			{
				canMoveTile = CanMoveLeft( t1, Map );
			}
			else
			{
				canMoveTile = CanMoveRight( t1, Map );
			}
		}
	}

	return ( canMoveTile != NULL );
}