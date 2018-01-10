// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameState.h"
#include "DwarfGameState.generated.h"

/**
 * 
 */
UCLASS()
class DWARFGAME_API ADwarfGameState : public AGameState
{
	GENERATED_BODY()
	
	
public:

	ADwarfGameState();

	virtual void Tick( float DeltaSeconds ) override;

	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	void SetMap( class ADwarfMap* DwarfMap );

	UFUNCTION()
	void UpdateMap();

	class ADwarfMap* GetMap();

private:
	UPROPERTY( ReplicatedUsing=UpdateMap )
	class ADwarfMap* Map;
	
};
