// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "DwarfMap.generated.h"

/*Bounds that represent the bounds of the tile*/
USTRUCT()
struct FBounds
{
	GENERATED_USTRUCT_BODY()

	//Mins / maxes -> can create helpers later
	UPROPERTY()
	int32 minX;

	UPROPERTY()
	int32 minY;

	UPROPERTY()
	int32 maxX;

	UPROPERTY()
	int32 maxY;


	UPROPERTY()
	int32 RowSize;
	UPROPERTY()
	int32 ColSize;
};

/**
 * Container for all the Tiles in the Game
 * Might need to add some networking stuff in here later
 */
UCLASS()
class DWARFGAME_API ADwarfMap : public AActor
{
	GENERATED_BODY()

public:

	ADwarfMap( const FObjectInitializer& ObjectInitializer );

	bool GenerateTiles( int Row, int Col, int Level = 0 );

	void SetWorld( UWorld* World );

	TArray<class ATile*>* GetAllTiles();

	void GetTileArea( class ATile* t1, class ATile* t2, TSet<ATile*>& Tiles );

	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	ATile* GetTile( int32 X, int32 Y );

	//Helper Functions to get tiles based on direction (left, right, up, down, in) from a tile -> not doing in yet.  Levels will be implemented later
	//Returns NULL if no such tile exists
	ATile* GetTileLeft( ATile* tile );
	ATile* GetTileRight( ATile* tile );
	ATile* GetTileAbove( ATile* tile );
	ATile* GetTileBelow( ATile* tile );

	// Validate a coordinate pair so that it is guaranteed to be in the map
	bool ValidateCoords( int32 X, int32 Y );
	bool ValidateTile( ATile* tile );
	
private:
	UPROPERTY( Replicated )
	TArray<class ATile*> Tiles;

	// doesn't need to be replicated
	UWorld* World;

	UPROPERTY( Replicated )
	FBounds MapBounds;
};
