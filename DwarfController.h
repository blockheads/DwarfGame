// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "DwarfController.generated.h"

/**
 * 
 */
UCLASS()
class DWARFGAME_API ADwarfController : public AAIController
{
	GENERATED_BODY()

public:
	ADwarfController( const FObjectInitializer& ObjectInitializer );

	virtual void Tick( float DeltaTime ) override;

	void MineTile(ATile* Tile);

	/* Move on a Path, returns true if complete*/
	bool MoveOnPath();

	/* Move to a tile, returns true if can, false if can't*/
	bool MoveToTile( ATile* Tile );

	void SetPath( FTilePath TilePath );

	virtual void Possess( class APawn* InPawn ) override;

private:

	FTilePath Path;

	UPROPERTY()
	float TimeCounter;

	UPROPERTY()
	class ADworf* Dwarf;

};
