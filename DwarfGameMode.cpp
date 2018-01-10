// Fill out your copyright notice in the Description page of Project Settings.

#include "DwarfGame.h"
#include "DwarfGameMode.h"
#include "DwarfMap.h"
#include "MousePlayerController.h"
#include "DwarfGameState.h"
#include "Dworf.h"
#include "CameraPawn.h"
#include "DwarfPlayerState.h"
#include "Enemy.h"

ADwarfGameMode::ADwarfGameMode( const FObjectInitializer& ObjectInitializer )
: Super ( ObjectInitializer )
{
	PlayerControllerClass = AMousePlayerController::StaticClass();

	HUDClass = ConstructorHelpers::FClassFinder<AHUD>(TEXT("Blueprint'/Game/DwarfHUD/BP_DwarvenHud.BP_DwarvenHud_c'")).Class;
	DefaultPawnClass = ConstructorHelpers::FClassFinder<APawn>( TEXT( "Class'/Script/DwarfGame.CameraPawn'" ) ).Class;

	GameStateClass = ADwarfGameState::StaticClass();
	PlayerStateClass = ADwarfPlayerState::StaticClass();

	
}

void ADwarfGameMode::StartPlay( )
{

	UWorld* World = GetWorld();

	if ( World )
	{
		Map = World->SpawnActor<ADwarfMap>( ADwarfMap::StaticClass( ) );
		Map->SetWorld( World );
		Map->GenerateTiles( 21, 21 );

		GetGameState<ADwarfGameState>( )->SetMap( Map );
	}

	Super::StartPlay( );
}

void ADwarfGameMode::PostLogin( APlayerController* NewPlayer )
{
	Super::PostLogin( NewPlayer );
}

void ADwarfGameMode::SpawnDwarf( APlayerController*  Controller )
{
	//spawn a dwarf
	ADworf* Dworf = GetWorld()->SpawnActor<ADworf>( ADworf::StaticClass( ) );
	Dworf->SetOwner( Controller );
	( (ADwarfPlayerState*)Controller->PlayerState )->RegisterDwarf( Dworf );
	Dworf->SetDwarfLocation( Map->GetTile( 0, 0 ) );
}