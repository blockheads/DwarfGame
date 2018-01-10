// Fill out your copyright notice in the Description page of Project Settings.

#include "DwarfGame.h"
#include "DwarfBrain.h"
#include "Dworf.h"
#include "DwarfPlayerState.h"
#include "DwarfGameState.h"
#include "Pathfinder.h"
#include "DwarfMap.h"
#include "DwarfController.h"
#include "MousePlayerController.h"


// Sets default values
ADwarfBrain::ADwarfBrain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	bAlwaysRelevant = true;

}

// Called when the game starts or when spawned
void ADwarfBrain::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADwarfBrain::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

bool ADwarfBrain::MineArea_Validate( FTileArea Area, AMousePlayerController* Controller )
{
	return true;
}
//So, what do we do when we want to mine an area of tiles?
//
// Steps:
//
//	1 - Selects All Mining Dwarves
//	2 - Sends them off to mine
void ADwarfBrain::MineArea_Implementation( FTileArea Area, AMousePlayerController* Controller )
{
	GEngine->AddOnScreenDebugMessage( -1, 5.f, FColor::Red, FString::Printf( TEXT( "EXECUTING THE MINING!!!!!" ) ) );
	ADwarfMap* Map = ( (ADwarfGameState*)( GetWorld()->GetGameState<ADwarfGameState>() ) )->GetMap();
	
	TArray<ADworf*> dwarves;
	FTilePath Path;
	//Get all the dwarves CHANGE THIS LATER TO PROFESSION MINE
	for ( ADworf* dwarf : ( (ADwarfPlayerState*)( Controller->PlayerState ) )->GetDwarves() )
	{
		if ( !dwarf->bMoving && Pathfinder::FindPathToArea( dwarf->GetDwarfLocation(), &Area, Map, &Path ) )
		{
			//execute mine on this dwarf
			(Cast<ADwarfController>(dwarf->GetController()))->SetPath( Path );
			return;
		}
	}

}