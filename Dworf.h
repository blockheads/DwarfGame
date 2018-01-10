// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperCharacter.h"
#include "Dworf.generated.h"

/**
 * 
 */
UCLASS()
class DWARFGAME_API ADworf : public APaperCharacter
{
	GENERATED_BODY()


	
public:

	ADworf(const FObjectInitializer& ObjectInitializer);

	void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	virtual void BeginPlay() override;

	UPROPERTY()
	class UPaperSpriteComponent* PaperSpriteComponent;

	void SetDwarfLocation(class ATile* DwarfLocationt);

	ATile* GetDwarfLocation();

	/* Sends a command to the server to move the Dwarf to a tile */
	UFUNCTION( Server, WithValidation, Reliable )
	void MoveToAdjacentTile( ATile* Tile );

	/* This function is called by all clients when a Dwarfs location has been updated*/
	UFUNCTION()
	void OnRep_UpdateLocation();

	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	UFUNCTION()
	float GetHealth();



	bool bInteracting;
	bool bMoving;

	void TestTakeingDamage(float val);

private:

	bool IsAlive;
	
	class UPaperSprite* LeftSprite;

	class UPaperSprite* RightSprite;
	FTimerHandle TimeHandler;

	UPROPERTY( ReplicatedUsing = OnRep_UpdateLocation )
	class ATile* DwarfLocation;

	UPROPERTY()
	float Health;


	/* Represents the current state of the Dwarf*/
	UPROPERTY()
	FDwarfState State;

	
	
};
