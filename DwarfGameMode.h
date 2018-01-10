// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "DwarfGameMode.generated.h"

/**
 * 
 */
UCLASS()
class DWARFGAME_API ADwarfGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:

	ADwarfGameMode( const FObjectInitializer& ObjectInitializer );

	virtual void StartPlay() override;

	virtual void PostLogin( APlayerController* NewPlayer ) override;
	
	void SpawnDwarf( class APlayerController* Controller );

private:

	UPROPERTY()
	class ADwarfMap* Map;
};
