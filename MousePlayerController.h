// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "MousePlayerController.generated.h"

UENUM()
enum class EInputStatesEnum : uint8
{
	IE_MOUSEOVER_TILE,
	IE_MOUSEOFF_TILE,
	IE_MOUSECLICK_TILE,
	IE_MOUSERELEASE_TILE,
	IE_MOUSEOVER_NONE,
	IE_KEYPRESS
};

/**
* This is the main input controller
* Handling of all mouse inputs should be here.
* Delegating commands to AIControllers should happen here.
*/
UCLASS()
class DWARFGAME_API AMousePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	AMousePlayerController( const FObjectInitializer& ObjectInitializer );
	
	// Main function called to Register a map for this player
	// This will enable the player to have click events with every tile in the game
	// This function must be called after a player controller has been created
	void RegisterMap( class ADwarfMap* Map );

	void RegisterTile( class ATile* Tile );

	virtual void Tick( float DeltaTime ) override;

	// Mouse over the tile
	void TileBeginCursorOver( class ATile* Tile );

	// Mouse end over the tile
	void TileEndCursorOver( class ATile* Tile );

	// Mouse clicked on Tile
	void TileOnClicked( class ATile* Tile );

	// Mouse Released on Tile
	void TileOnReleased( class ATile* Tile );

	void UpdateMap();

	virtual void BeginPlay() override;

	// Set the Selection Type.  This will be called via blueprints from some UI components.  Possibly called from some keybinds later on
	UFUNCTION( BlueprintCallable, Category = "ControllerSelection" )
	void SetSelectionType( ESelectionEnum SelectionType );

	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

private:

	void ExecuteSelectedAction();

	// this function will handle all the key presses
	void HandleKeyPresses();

	// Update the state of input
	void UpdateState();

	// Execute Current State
	void ExecuteState();

private:
	UPROPERTY( Replicated )
	class ADwarfMap* Map;

	UPROPERTY( Replicated )
	class ADwarfBrain* Brain;

	UPROPERTY()
	class ATileSelector* TileSelector;

	class ATile* ClickedTile;

	class ATile* ReleasedTile;

	class ATile* BFSTile;

	ESelectionEnum SelectionType;
};
