// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class DWARFGAME_API WorldGenerator
{
public:
	WorldGenerator();
	~WorldGenerator();

	void SetWorld( UWorld* World );

	bool GenerateTiles( int Row, int Col, int Level = 0 );

private:

	class UWorld* World;

	//TArray<class ATile*> Tiles;

	TArray<TArray<TArray<class ATile*> > > Tiles;
};
