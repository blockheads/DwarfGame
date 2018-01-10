// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Enemy.generated.h"

UCLASS()
class DWARFGAME_API AEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditDefaultsOnly)
	class UPaperSpriteComponent* EnemySprite;
private:

	float GetHealth();

	//properties enemies exhibit ~
	float Health;
	float MaxHealth;
	float Attack;
	float Defense;
	float Range; 
	float AttackRate;

	//dealing damage to dwarves
	UFUNCTION(Reliable, Server, WithValidation)
	void DealDamage();
	void DealDamage_Implementation();
	bool DealDamage_Validate();

	//our dworf
	class ADworf* Dworf;
	//setting our dworf
	void SetDworf();

	void MoveRandom();
	FVector Location;

	//movement funcs

	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();

	UFUNCTION(Reliable, Server, WithValidation)
	void SeverTimer();
	void SeverTimer_Implementation();
	bool SeverTimer_Validate();
	
	bool CanInteractWithDwarf();


	FTimerHandle TimeHandler;
	FTimerHandle TimeHandlert;
};
