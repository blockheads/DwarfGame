// Fill out your copyright notice in the Description page of Project Settings.

#include "DwarfGame.h"
#include "MousePlayerController.h"
#include "DwarfMap.h"
#include "Tile.h"
#include "DwarfGameState.h"
#include "DwarfBrain.h"
#include "DwarfGameMode.h"
#include "Net/UnrealNetwork.h"

// Static Helper Classes -> These are classes used by the controller for calling functions that interact with the map/world.  This mouse controller is the "state machine" that should decide what to do
// based on what the current inputs have been.  These classes could all be implemented in here but have been made into static helpers in order to reduce clutter.
#include "TileSelector.h"
#include "PathFinder.h"

AMousePlayerController::AMousePlayerController( const FObjectInitializer& ObjectInitializer )
	: Super( ObjectInitializer )
{
	bReplicates = true;
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	this->DefaultMouseCursor = EMouseCursor::Crosshairs;
	ClickedTile = NULL;
	BFSTile = NULL;	
}
void AMousePlayerController::Tick( float DeltaTime )
{
	
	// Handle Keybinds
	HandleKeyPresses();
}
void AMousePlayerController::BeginPlay( )
{
	Super::BeginPlay();

	// Spawn in a brain into the world, should be client side

	TileSelector = (ATileSelector*)( GetWorld( )->SpawnActor( ATileSelector::StaticClass() ) );

	if ( Role == ROLE_Authority )
	{
		Cast<ADwarfGameMode>( GetWorld()->GetAuthGameMode() )->SpawnDwarf( this );
		Brain = (ADwarfBrain*)( GetWorld( )->SpawnActor( ADwarfBrain::StaticClass( ) ) );
		Brain->SetOwner( this );
	}
}

void AMousePlayerController::UpdateMap()
{
}

void AMousePlayerController::RegisterMap( ADwarfMap* Map )
{
	this->Map = Map;
}

void AMousePlayerController::RegisterTile( class ATile* Tile )
{
	Tile->MouseBeginCursorOverDelegate.BindUObject( this, &AMousePlayerController::TileBeginCursorOver );
	Tile->MouseEndCursorOverDelegate.BindUObject( this, &AMousePlayerController::TileEndCursorOver );
	Tile->MouseOnClickedDelegate.BindUObject( this, &AMousePlayerController::TileOnClicked );
	Tile->MouserOnReleasedDelegate.BindUObject( this, &AMousePlayerController::TileOnReleased );
}

// Mouse over the tile
void AMousePlayerController::TileBeginCursorOver( ATile* Tile )
{
	//GEngine->AddOnScreenDebugMessage( -1, 5.f, FColor::Red, FString::Printf( TEXT( "Cursor Over: (%d, %d)" ), Tile->X, Tile->Y ) );
	
	if ( ClickedTile == NULL && !Tile->IsTileSelected() )
	{
		Tile->SetTileColor( FLinearColor( 0.9f, 0.9f, 0.9f, 1.0f ) );
	}

	if ( ClickedTile )
	{
		// Selecting an Area
		TileSelector->TempSelectAreaTiles( ClickedTile, Tile, Map );
	}
	
}

// Mouse end over the tile
void AMousePlayerController::TileEndCursorOver( ATile* Tile )
{
	//GEngine->AddOnScreenDebugMessage( -1, 5.f, FColor::Red, FString::Printf( TEXT( "Cursor End: (%d, %d)" ), Tile->X, Tile->Y ) );

	// if the tile is not the clicked tile, change the color


}

// Mouse clicked on Tile
void AMousePlayerController::TileOnClicked( ATile* Tile )
{
	//GEngine->AddOnScreenDebugMessage( -1, 5.f, FColor::Red, FString::Printf( TEXT( "Cursor Click: (%d, %d)" ), Tile->X, Tile->Y ) );
	ClickedTile = Tile;
}

// Mouse Released on Tile
void AMousePlayerController::TileOnReleased( ATile* Tile )
{
	//GEngine->AddOnScreenDebugMessage( -1, 5.f, FColor::Red, FString::Printf( TEXT( "Cursor Release: (%d, %d)" ), Tile->X, Tile->Y ) );
	if ( ClickedTile == Tile )
	{
		TileSelector->AddSelectedTile( Tile );
	}
	else
	{
		TileSelector->ConfirmAreaTiles();
	}

	for ( ATile* tile : TileSelector->SelectedTiles )
	{
		switch ( SelectionType )
		{
		case ESelectionEnum::SE_NONE:
			break;

		case ESelectionEnum::SE_SELECT:
			tile->SetTileColor( FLinearColor( 0.0f, 1.0f, 0.0f, 1.0f ) );
			break;

		case ESelectionEnum::SE_DESELECT:
			tile->SetTileColor( FLinearColor( 1.0f, 1.0f, 1.0f, 1.0f ) );
			tile->SetTileSelected( false );
			break;
		}
	}

	ClickedTile = NULL;	
}

/*
* Executes the given action based on tiles that are selected.
*/
void AMousePlayerController::ExecuteSelectedAction()
{
	FTileArea area = FTileArea( TileSelector->SelectedTiles.Array() );
	if ( Role != ROLE_Authority )
	{
		GEngine->AddOnScreenDebugMessage( -1, 5.f, FColor::Red, FString::Printf( TEXT( "Executing Action From Client." ) ) );
	}
	else
	{
		GEngine->AddOnScreenDebugMessage( -1, 5.f, FColor::Red, FString::Printf( TEXT( "Executing Action From Server." ) ) );
	}
	Brain->MineArea( area, this );
	GEngine->AddOnScreenDebugMessage( -1, 5.f, FColor::Red, FString::Printf( TEXT( "Executing Action." ) ) );
	TileSelector->ClearAll( );
}

void AMousePlayerController::SetSelectionType( ESelectionEnum SelectionType )
{
	GEngine->AddOnScreenDebugMessage( -1, 5.f, FColor::Red, FString::Printf( TEXT( "Selection Type Changed." )));
	this->SelectionType = SelectionType;
	TileSelector->SetSelectionType( SelectionType );
}

/*
 * List of all possible key interactions
 *
 * Enter -> Execute Current Action
*/
void AMousePlayerController::HandleKeyPresses()
{

	// if enter was pressed, execute current action -> move state machine forward
	if ( this->WasInputKeyJustReleased( EKeys::Enter ) )
	{
		ExecuteSelectedAction();
	}
}
void AMousePlayerController::GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );

	DOREPLIFETIME( AMousePlayerController, Map );
	DOREPLIFETIME( AMousePlayerController, Brain );
}
