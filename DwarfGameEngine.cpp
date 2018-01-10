// Fill out your copyright notice in the Description page of Project Settings.

#include "DwarfGame.h"
#include "DwarfGameEngine.h"
#include "Sprites.h"

UDwarfGameEngine::UDwarfGameEngine( const FObjectInitializer& ObjectInitializer )
	: Super( ObjectInitializer )
{
	Sprites = Sprites::GetInstance();
}

