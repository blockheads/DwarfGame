// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerState.h"
#include "DwarfPlayerState.generated.h"

// forward dec
class ADworf;

/**
 * State of each player in the game
 * This is where all of a players dwarves should be kept, and the state for each one.
 *
 * So,  a giant list of dwarves should be contained here
 */
UCLASS()
class DWARFGAME_API ADwarfPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:

	ADwarfPlayerState( const FObjectInitializer& ObjectInitializer );

	virtual void Tick( float DeltaSeconds ) override;

	virtual void BeginPlay( ) override;

	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	// Register a Dwarf that the current Client should have control over
	void RegisterOwnedDwarf( class ADworf* MyDwarf );

	// Register a Dwarf as being one that the current Client does not have control over
	void RegisterOtherDwarf( class ADworf*  OtherDwarf );

	void RegisterDwarf( class ADworf* Dwarf );

	TArray<class ADworf*>& GetDwarves();
	
private:
	UPROPERTY( Replicated )
	TArray<class ADworf*> Dwarves;
};
