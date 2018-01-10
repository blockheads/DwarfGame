// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameEngine.h"
#include "DwarfGameEngine.generated.h"

/**
 * 
 */
UCLASS()
class DWARFGAME_API UDwarfGameEngine : public UGameEngine
{
	GENERATED_BODY()
	
public:

	UDwarfGameEngine( const FObjectInitializer& ObjectInitializer );

private:

	// Ref to Sprites so the object doesn't become deconstructed
	class Sprites* Sprites;
	
	
};
