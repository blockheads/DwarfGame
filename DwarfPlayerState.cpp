// Fill out your copyright notice in the Description page of Project Settings.

#include "DwarfGame.h"
#include "DwarfPlayerState.h"
#include "Dworf.h"



ADwarfPlayerState::ADwarfPlayerState( const FObjectInitializer& ObjectInitializer )
	: Super( ObjectInitializer )
{
	bReplicates = true;
}


void ADwarfPlayerState::Tick( float DeltaSeconds )
{

}

void ADwarfPlayerState::BeginPlay( )
{

}

void ADwarfPlayerState::GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );
}

// Register a Dwarf that the current Client should have control over
void ADwarfPlayerState::RegisterOwnedDwarf( ADworf* MyDwarf )
{

}

// Register a Dwarf as being one that the current Client does not have control over
void ADwarfPlayerState::RegisterOtherDwarf( ADworf*  OtherDwarf )
{

}

void ADwarfPlayerState::RegisterDwarf( ADworf* Dwarf )
{
	if ( Dwarf )
	{
		Dwarves.AddUnique( Dwarf );
	}
}

TArray<class ADworf*>& ADwarfPlayerState::GetDwarves()
{
	return Dwarves;
}