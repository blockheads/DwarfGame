// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DwarfExecutive.generated.h"

UCLASS()
class DWARFGAME_API ADwarfExecutive : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADwarfExecutive();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// This will execute a specific action on the server
	//UFUNCTION( Server )
//	void ExecuteAction();

private:

	// Represents all the dwarves in the Game.  This is contained ServerSide.
	UPROPERTY()
	TArray<class ADworf*> AllDwarves;
	
	
};
