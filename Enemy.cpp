// Fill out your copyright notice in the Description page of Project Settings.

#include "DwarfGame.h"
#include "Enemy.h"
#include "DwarfGameState.h"
#include "Tile.h"
#include "PaperSpriteComponent.h"
#include "Engine.h"
#include "Dworf.h"

// Sets default values
AEnemy::AEnemy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EnemySprite = ObjectInitializer.CreateDefaultSubobject<UPaperSpriteComponent>(this, "EnemySprite");
	
	//seting maxhealth and health to 100 to start out...
	Health = MaxHealth;

	//For Testing Purposes
	Range = 2;
	Attack = 10;
	//multiplied by tile size
	Range *= 64;


}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	if (Role == ROLE_Authority){
		SeverTimer();
	}
	

}

// Called every frame
void AEnemy::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	SetDworf();
	if (Role == ROLE_Authority){
		if (CanInteractWithDwarf()){
			
			DealDamage();

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::SanitizeFloat(Dworf->GetHealth()));
		}
	}
}

float AEnemy::GetHealth(){

	return Health;
}


void AEnemy::DealDamage_Implementation(){
	
	//NEED TO BE ABLE TO GET DWARVES DEFENSE
	float DeltaAttackDefense = Attack;

	//timer to deal damage
	UWorld* World = GetWorld();
	if (World){
		World->GetTimerManager().SetTimer(TimeHandlert, this, &AEnemy::MoveRandom, AttackRate, true);
		Dworf->TestTakeingDamage(DeltaAttackDefense);
	}

}
bool AEnemy::DealDamage_Validate(){ return true; }


void AEnemy::SetDworf(){
	
	
	//sets Dworf = nearest dworf
	for (TActorIterator<ADworf> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (Dworf == NULL || ActorItr->GetDistanceTo(this) < Dworf->GetDistanceTo(this)){
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Found dwarf!"));
			Dworf = *ActorItr;
		}
		
	}
	

}

void AEnemy::MoveRandom(){

	int32 seed = FMath::RandRange(1, 4);

	if (seed == 1){
		
		MoveLeft();

	}
	else if (seed == 2){
		
		MoveDown();

	}
	else if (seed == 3){
	
		MoveUp();

	}
	else if (seed == 4){
		
		MoveRight();

	}
}

void AEnemy::MoveLeft(){

	EnemySprite->SetWorldLocation(FVector(EnemySprite->GetComponentLocation().X - 64, EnemySprite->GetComponentLocation().Y, EnemySprite->GetComponentLocation().Z));
	
}

void AEnemy::MoveRight(){

	EnemySprite->SetWorldLocation(FVector(EnemySprite->GetComponentLocation().X + 64, EnemySprite->GetComponentLocation().Y, EnemySprite->GetComponentLocation().Z));
	
}

void AEnemy::MoveUp(){

	EnemySprite->SetWorldLocation(FVector(EnemySprite->GetComponentLocation().X, EnemySprite->GetComponentLocation().Y, EnemySprite->GetComponentLocation().Z + 64));

}

void AEnemy::MoveDown(){

	EnemySprite->SetWorldLocation(FVector(EnemySprite->GetComponentLocation().X, EnemySprite->GetComponentLocation().Y, EnemySprite->GetComponentLocation().Z - 64));

}


void AEnemy::SeverTimer_Implementation(){
	
	UWorld* World = GetWorld();
	if (World){

		World->GetTimerManager().SetTimer(TimeHandler, this, &AEnemy::MoveRandom, 1.0f, true);

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Executed on server	"));
	}
}

bool AEnemy::SeverTimer_Validate(){
	return true; 
}

bool AEnemy::CanInteractWithDwarf(){

	if (Dworf->GetDistanceTo(this) <= Range){
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Can interact"));
		return true;

	}
	return false;

}
