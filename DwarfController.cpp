// Fill out your copyright notice in the Description page of Project Settings.

#include "DwarfGame.h"
#include "DwarfController.h"
#include "Pathfinder.h"
#include "Tile.h"
#include "Dworf.h"
#include "DwarfGameState.h"

ADwarfController::ADwarfController( const FObjectInitializer& ObjectInitializer )
	: Super( ObjectInitializer )
{
	PrimaryActorTick.bCanEverTick = true;
	TimeCounter = 0.0f;
}


void ADwarfController::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	//currently just updating the movement of the dwarf in the controller
	if ( Dwarf && Dwarf->bMoving )
	{
		//if the dwarf is scheduled to move
		TimeCounter += DeltaTime;
		if ( TimeCounter > 1.0f )
		{
			//move the dwarf
			if ( !MoveOnPath() )
			{
				Dwarf->bMoving = false;
			}

			TimeCounter = 0.0f;
		}
	}
}

void ADwarfController::MineTile(ATile* Tile)
{

	

}

void ADwarfController::SetPath( FTilePath TilePath )
{
	if ( Dwarf && !Dwarf->bMoving )
	{
		Path = TilePath;
		Dwarf->bMoving = true;
	}
}

bool ADwarfController::MoveOnPath()
{
	ATile* NextTile = Path.GetNextTile();
	if ( NextTile )
	{
		return MoveToTile( NextTile );
	}
	return false;
}

bool ADwarfController::MoveToTile( ATile* Tile )
{
	if ( Dwarf && Pathfinder::CanMoveBetweenAdjacentTiles( Tile, Dwarf->GetDwarfLocation( ), GetWorld( )->GetGameState<ADwarfGameState>( )->GetMap( ) ) )
	{
		//execute move
		Dwarf->MoveToAdjacentTile( Tile );
		return true;
	}
	return false;
}

void  ADwarfController::Possess( APawn* InPawn )
{
	Super::Possess( InPawn );
	Dwarf = (ADworf*)InPawn;
}
