// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "DwarfGlobals.generated.h"

//Forward Declarations
class ATile;

UENUM()
enum class EActionEnum : uint8
{
	AE_MINE,
	AE_BUILD,
	AE_GATHER,
	AE_MOVE,
	AE_ATTACK,
	AE_IDLE,
	AE_NONE
};

UENUM()
enum class ESpriteTypes : uint8
{
	ST_GROUND_0,
	ST_GRASS_0
};

/* Enumeration for the different mouse selection types */
UENUM( BlueprintType )
enum class ESelectionEnum : uint8
{
	SE_SELECT		UMETA( DisplayName = "Select" ),
	SE_DESELECT		UMETA( DisplayName = "DeSelect" ),
	SE_NONE			UMETA( DisplayName = "None" )
};

//Dwarf action enums

UENUM()
enum class EDwarfActions : uint8
{

	Mining,
	Walking

};

UENUM()
enum class EDwarfProfressions : uint8
{

	Peasant,
	Gatherer,
	Miner

};


/* Structure representing an Action to be taken
 * This should contain the following:
 * 
 * 1 - Type of Action
 * 2 - Tiles taking place in the action
 * 3 - SourcePawns taking place in the action
 * 4 - InteractingPawns taking place in the action (Incase of interacting with other pawns -> e.x. SourcePawns AE_ATTACK Interacting Pawns) Things like this
 *
 * This may not need to be replicated, most likely will be, will get to this later
 */
USTRUCT()
struct FAction
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	EActionEnum Action;

	UPROPERTY()
	TArray<ATile*> Tiles;

	UPROPERTY()
	TArray<APawn*> SourcePawns;

	UPROPERTY()
	TArray<APawn*> InteractingPawns;
};

/* Stats for a Character 
 * These represent values for a character that are their max -> Changing of these values should happen in the State
*/
USTRUCT()
struct FDWarfStats
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	uint32 Attack;

	UPROPERTY()
	uint32 Defense;

	UPROPERTY()
	uint32 Health;

};

/* Structure representing the dwarf state
 * Can add things here as more stuff is acquired that needs to be known about a dwarf at any instance
 * These Represent the current state of a character
*/
USTRUCT()
struct FDwarfState
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	uint32 Health;

	UPROPERTY()
	uint32 Happiness;

	//UPROPERTY()
	//TArray<class Equipment*> Gear;

	UPROPERTY()
	uint32 Age;

	UPROPERTY()
	uint8 Gender;

	UPROPERTY()
	FString Description;

	UPROPERTY()
	EActionEnum CurrentAction;

	UPROPERTY()
	FString Name;
};

/* A container for managing tiles (this is just a wrapper around a TSet of Tiles.  I do this to make it easier to read what I am doing)
 * When I work with a bunch of tiles, using a tilecontainer will keep the syntax nice and clean compared to using TSet functions
 * This could be a whole bunch of tiles, a single tile, or even 0 tiles
 * 
 * This will represent an area of tiles
*/
USTRUCT()
struct FTileArea
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	TArray<ATile*> Tiles;

	FTileArea( TArray<ATile*> ATiles )
	{
		Tiles = ATiles;
	}

	FTileArea()
	{

	}

	void RemoveTile( ATile* tile )
	{
		Tiles.Remove( tile );
	}

	uint32 NumTiles()
	{
		return Tiles.Num();
	}

	void AddTile( ATile* tile )
	{
		Tiles.Add( tile );
	}

	bool Contains( ATile* tile )
	{
		return Tiles.Contains( tile );
	}


};
/* FTilePath wrapper
 * A struct for managing a tile path -> ending is single tile, will create an area ending later
 */
USTRUCT()
struct FTilePath
{
	GENERATED_USTRUCT_BODY()

	FTilePath()
	{
		loc = 0;
	}

	ATile* GetNextTile()
	{
		if ( loc >= Path.Num() )
		{
			return NULL;
		}

		ATile* tile = Path[loc];
		loc++;
		return tile;		
	}

	UPROPERTY()
	ATile* StartingTile;

	UPROPERTY()
	ATile* EndingTile;

	UPROPERTY()
	ATile* CurrentTile;

	UPROPERTY()
	TArray<ATile*> Path;

	UPROPERTY()
	uint8 loc;
};
