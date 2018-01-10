// Fill out your copyright notice in the Description page of Project Settings.

#include "DwarfGame.h"
#include "DwarfGameState.h"
#include "DwarfMap.h"
#include "MousePlayerController.h"
#include "Net/UnrealNetwork.h"
#include "Tile.h"

ADwarfGameState::ADwarfGameState()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	bAlwaysRelevant = true;

}

void ADwarfGameState::Tick( float DeltaSeconds )
{
	Super::Tick( DeltaSeconds );
}

void ADwarfGameState::BeginPlay( )
{
	Super::BeginPlay();
}

void ADwarfGameState::SetMap( ADwarfMap* DwarfMap )
{
	Map = DwarfMap;
	if ( ( (AMousePlayerController*)GetWorld()->GetFirstPlayerController() ) )
	{
		( (AMousePlayerController*)GetWorld()->GetFirstPlayerController() )->RegisterMap( Map );
	}
}

ADwarfMap* ADwarfGameState::GetMap()
{
	return Map;
}

void ADwarfGameState::GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );
	DOREPLIFETIME( ADwarfGameState, Map );
}

void ADwarfGameState::UpdateMap()
{
	if ( Role != ROLE_Authority )
	{
		( (AMousePlayerController*)GetWorld()->GetFirstPlayerController() )->RegisterMap( Map );
	}

}


