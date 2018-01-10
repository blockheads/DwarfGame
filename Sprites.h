// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "DwarfGlobals.h"
/**
 * A Singleton for accessing all of the Sprites
 */
class DWARFGAME_API Sprites
{
public:



	// Get the singleton instance
	static Sprites* GetInstance();

	// Get the Ground sprite at index
	class UPaperSprite* GetGroundSprite( ESpriteTypes SpriteType );

	// Get the Grass sprite at index
	class UPaperSprite* GetGrassSprite( ESpriteTypes SpriteType );

	// Get a random Ground Sprite
	class UPaperSprite* GetRandomGroundSprite();

	// Get a sprite
	class UPaperSprite* GetSprite( ESpriteTypes SpriteType );


protected:

	static Sprites* SpritesRef;

private:

	Sprites();
	~Sprites();

	TMap<ESpriteTypes, UPaperSprite*> SpriteMap;



};
