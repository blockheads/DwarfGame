// Fill out your copyright notice in the Description page of Project Settings.

#include "DwarfGame.h"
#include "Tile.h"
#include "PaperSpriteComponent.h"
#include "MousePlayerController.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ATile::ATile( const FObjectInitializer& ObjectInitializer )
: Super( ObjectInitializer )
{
	bReplicates = true;
	bAlwaysRelevant = true;
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	UPaperSprite* BasicGround = Sprites::GetInstance()->GetRandomGroundSprite();
	TileVisual = ObjectInitializer.CreateDefaultSubobject<UPaperSpriteComponent>( this, "TileComp" );

	TileVisual->SetSprite( BasicGround );

	RootComponent = TileVisual;

	TDelta = 0.0f;
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	( (AMousePlayerController*)GetWorld()->GetFirstPlayerController() )->RegisterTile( this );
	
}

// Called every frame
void ATile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	TDelta += DeltaTime;
	if ( TDelta > 1.5f )
	{
		TDelta = 0.0f;
		//RandomizeGround();
		
	}

}

// Set the Position of the Tile
// x -> x position
// y -> z position
// z -> contains the level
void ATile::SetPosition( FVector Position )
{
	FVector relativePosition = FVector( Position.X * 64.0f, -1.0f, Position.Y * -64.0f );
	X = Position.X;
	Y = Position.Y;
	Level = Position.Z;
	
	TileVisual->SetRelativeLocation( relativePosition );
	TileVisual->SetRelativeRotation( FQuat( FRotator( 0.0f, 0.0f, 0.0f ) ) );
}

// Set the Scale of the Tiles
void ATile::SetScale( FVector Scale )
{
	TileVisual->SetRelativeScale3D( Scale );
}

void ATile::RandomizeGround()
{
	UPaperSprite* rSprite = Sprites::GetInstance()->GetRandomGroundSprite();
	if ( rSprite )
	{
		TileVisual->SetSprite( rSprite );
	}
	
}

// Mouse begin over the tile
void ATile::NotifyActorBeginCursorOver()
{
	MouseBeginCursorOverDelegate.ExecuteIfBound( this );
}

// Mouse end over the tile
void ATile::NotifyActorEndCursorOver()
{
	MouseEndCursorOverDelegate.ExecuteIfBound( this );
}

// Mouse clicked on Tile
void ATile::NotifyActorOnClicked()
{
	MouseOnClickedDelegate.ExecuteIfBound( this );
	//TileVisual->SetSpriteColor( FLinearColor( 0.f, 200.f, 200.0f, 0.75f ) );
}

// Mouse Released on Tile
void ATile::NotifyActorOnReleased()
{
	MouserOnReleasedDelegate.ExecuteIfBound( this );
}

void ATile::SetTileLocation( int32 x, int32 y, int32 z, int32 level )
{
	X = x;
	Y = y;
	Z = z;
	Level = level;
}

void ATile::SetTileSprite_Implementation( ESpriteTypes SpriteType )
{
	TileVisual->SetSprite( Sprites::GetInstance()->GetSprite( SpriteType ) );
	this->SpriteType = SpriteType;
}

bool ATile::SetTileSprite_Validate( ESpriteTypes SpriteType )
{
	return true;
}

void ATile::SetTileColor( FLinearColor Color )
{
	TileVisual->SetSpriteColor( Color );
}

// Set the Tile to Selected.  This will update the color of the tile to selected/unselected colors
void ATile::SetTileSelected( bool bSelected )
{
	this->bSelected = bSelected;
}

// Is this tile currently selected?
bool ATile::IsTileSelected()
{
	return bSelected;
}

void ATile::SetCollisionData( uint8 CollisionData )
{
	this->CollisionMask = CollisionData;
}

uint8 ATile::GetCollisionData()
{
	return CollisionMask;
}

void ATile::GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );

	DOREPLIFETIME( ATile, TDelta );
	DOREPLIFETIME( ATile, X );
	DOREPLIFETIME( ATile, Y );
	DOREPLIFETIME( ATile, Z );
	DOREPLIFETIME( ATile, Level );
	DOREPLIFETIME( ATile, CollisionMask );
	DOREPLIFETIME( ATile, SpriteType );
}

void ATile::UpdateSprite()
{
	TileVisual->SetSprite( Sprites::GetInstance( )->GetSprite( SpriteType ) );
}