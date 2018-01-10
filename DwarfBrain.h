// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DwarfGlobals.h"
#include "GameFramework/Actor.h"
#include "DwarfBrain.generated.h"

/*
 * The Dwarf Brain is what is going to decide if you can execute a specific action/etc...
 * If you can do the action, it is fired off to the server 
*/
UCLASS()
class DWARFGAME_API ADwarfBrain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADwarfBrain();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Mine this area
	UFUNCTION( Server, WithValidation, Reliable )
	void MineArea( FTileArea Area, class AMousePlayerController* Controller );

private:

	// Gets all the dwarves of a specific profession
	// TArray<class ADworf*> GetAllDwarvesOfType( DwarfProfessions );
	
	
};
