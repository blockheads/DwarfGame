// Fill out your copyright notice in the Description page of Project Settings.

#include "DwarfGame.h"
#include "Dworf.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"
#include "Tile.h"
#include "DwarfPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "DwarfController.h"

ADworf::ADworf(const FObjectInitializer& ObjectInitializer)
{

	bReplicates = true;
	bAlwaysRelevant = true;

	AIControllerClass = ADwarfController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	static ConstructorHelpers::FObjectFinder<UPaperSprite> LeftSpritet(TEXT("PaperSprite'/Game/Sprites/Character/left_dwarf_Sprite_0'"));
	static ConstructorHelpers::FObjectFinder<UPaperSprite> RightSpritet(TEXT("PaperSprite'/Game/Sprites/Character/right_dwarf_Sprite_0'"));

	LeftSprite = LeftSpritet.Object;
	RightSprite = RightSpritet.Object;

	PaperSpriteComponent = ObjectInitializer.CreateDefaultSubobject<UPaperSpriteComponent> (this, TEXT("PaperSpriteComponent"));
	PaperSpriteComponent->SetSprite(RightSprite);

	RootComponent = PaperSpriteComponent;

	bMoving = false;
	IsAlive = true;

	Health = 100.0f;

}

void ADworf::SetupPlayerInputComponent(UInputComponent* InputComponent){

}

void ADworf::BeginPlay()
{
	Super::BeginPlay();
}

bool ADworf::MoveToAdjacentTile_Validate( ATile* Tile )
{
	return true;
}

void ADworf::MoveToAdjacentTile_Implementation( ATile* Tile )
{
	this->DwarfLocation = Tile;
	FVector Loc = Tile->GetActorLocation();
	Loc.Y = 1.0f;
	PaperSpriteComponent->SetWorldLocation( Loc );
	//broadcast a moving animation of the Dwarf to all clients that can see it move
}

void ADworf::OnRep_UpdateLocation( )
{
	//ok, should probably move
	GEngine->AddOnScreenDebugMessage( -1, 5.f, FColor::Red, DwarfLocation->GetActorLocation( ).ToString( ) );
	FVector Loc = DwarfLocation->GetActorLocation();
	Loc.Y = 1.0f;
	PaperSpriteComponent->SetWorldLocation( Loc );
}


void ADworf::SetDwarfLocation(ATile* DwarfLocationt)
{
	DwarfLocation = DwarfLocationt;
}

ATile* ADworf::GetDwarfLocation(){ return DwarfLocation; }

void ADworf::GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );

	DOREPLIFETIME( ADworf, DwarfLocation );
}

float ADworf::GetHealth(){

	return Health;
}

void ADworf::TestTakeingDamage(float val){

	Health -= val;

}