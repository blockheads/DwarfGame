// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Tile.generated.h"

DECLARE_DELEGATE_OneParam( FTileDelegate, class ATile* );

UCLASS()
class DWARFGAME_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile( const FObjectInitializer& ObjectInitializer );

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Set the Position of the Tile
	void SetPosition( FVector Position );

	// Set the Scale of the Tiles
	void SetScale( FVector Scale );

	// Randomize the Ground Tiles to any of them
	void RandomizeGround();

	// Mouse over the tile
	virtual void NotifyActorBeginCursorOver() override;

	// Mouse end over the tile
	virtual void NotifyActorEndCursorOver() override;

	// Mouse clicked on Tile
	virtual void NotifyActorOnClicked() override;

	// Mouse Released on Tile
	virtual void NotifyActorOnReleased() override;

	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	// Set the tile location -- This must be called after creating a new Tile!
	// x -> x location in the world
	// y -> y location in the world
	// z -> the z value so as to set render priority for the block
	// level -> the level of the block.  0 -> ground level
	void SetTileLocation( int32 x, int32 y, int32 z, int32 level );

	// Set the type of sprite
	UFUNCTION( Server, Reliable, WithValidation )
	void SetTileSprite( ESpriteTypes SpriteType );

	// Set the Color of the Tile
	void SetTileColor( FLinearColor Color );

	// Set the Tile to Selected
	void SetTileSelected( bool bSelected );

	// Is this tile currently selected?
	bool IsTileSelected();

	// Sets the collision data, default is 0000 -> reachable from all tiles
	void SetCollisionData( uint8 CollisionData );

	UFUNCTION()
	void UpdateSprite();

	// Get the collision data for this tile
	uint8 GetCollisionData();

public:

	FTileDelegate MouseBeginCursorOverDelegate;
	FTileDelegate MouseEndCursorOverDelegate;
	FTileDelegate MouseOnClickedDelegate;
	FTileDelegate MouserOnReleasedDelegate;
	
protected:

	// Visual Representation of the sprite
	class UPaperSpriteComponent* TileVisual;
	
public:
	UPROPERTY( Replicated )
	float TDelta;

	// X location of the tile
	UPROPERTY( Replicated )
	int32 X;

	// Y location of the tile
	UPROPERTY( Replicated )
	int32 Y;

	// Z location of the tile
	UPROPERTY( Replicated )
	int32 Z;

	// level the tile exists in
	UPROPERTY( Replicated )
	int32 Level;

private:
	bool bSelected;

	//Mask representing what this tile can collide with
	// 1000 -> UP
	// 0100 -> DOWN
	// 0010 -> LEFT
	// 0001 -> RIGHT
	// Tile with 1111 is UNREACHABLE
	UPROPERTY( Replicated )
	uint8 CollisionMask;

	UPROPERTY( ReplicatedUsing=UpdateSprite )
	ESpriteTypes SpriteType;
	
};
