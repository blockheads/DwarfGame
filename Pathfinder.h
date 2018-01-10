// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class ATile;
class ADwarfMap;

/**
 * Pathfinder is a Helper class used to find paths between tiles
 * This will be useful for say anytime that it is desired to know if you can reach tile Y from tile X
 * This is not exclusive to reaching a single tile, areas can be specified aswell
 */
class DWARFGAME_API Pathfinder
{
public:

	Pathfinder();
	~Pathfinder();

	/* Finds a path from tile 1 to tile 2
	 * Returns true if path was found
	 * Fills out the Path structure if True AND the structure is not NULL
	*/
	static bool FindPath( ATile* t1, ATile* t2, ADwarfMap* Map, FTilePath* Path );

	/* Functions to Check if you can move in a direction from a tile
	 * Returns ATile if possible, NULL if not
	*/
	static ATile* CanMoveLeft( ATile* tile, ADwarfMap* Map );
	static ATile* CanMoveRight( ATile* tile, ADwarfMap* Map );
	static ATile* CanMoveUp( ATile* tile, ADwarfMap* Map );
	static ATile* CanMoveDown( ATile* tile, ADwarfMap* Map );

	/* Function to quickly check if movement is possible from t1 to t2
	 * where these tiles are guaranteed to be adjacent to each other
	*/
	static bool CanMoveBetweenAdjacentTiles( ATile* t1, ATile* t2, ADwarfMap* Map );

	/*
	* if can move to area, return a path, otherwise no
	*/
	static bool FindPathToArea( ATile* StartingTile, FTileArea* Destination, ADwarfMap* Map, FTilePath* Path );

private:

	// Helper functions

	/*
	 * Perform a Breadth First Search from Tile t1 to Tile t2 on the given Map
	 * Returns an Array of tiles for the path found, will be empty if there is no path
	*/
	static TArray<ATile*> BFS( ATile* t1, ATile* t2, ADwarfMap* Map );
};
