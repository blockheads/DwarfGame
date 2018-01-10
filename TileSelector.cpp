// Fill out your copyright notice in the Description page of Project Settings.

#include "DwarfGame.h"
#include "TileSelector.h"
#include "Tile.h"
#include "DwarfMap.h"




namespace
{
	FLinearColor TileHighlight = FLinearColor( 0.0f, 1.0f, 0.0f );
	FLinearColor TileBase = FLinearColor( 1.0f, 1.0f, 1.0f );
}

ATileSelector::ATileSelector()
{
}

//Add a selected Tile
void ATileSelector::AddSelectedTile( ATile* tile )
{
	tile->SetTileSelected( true );
	SelectedTiles.Add( tile );	
}

void ATileSelector::SetSelectionType( ESelectionEnum Selection )
{
	SelectionType = Selection;
}

void ATileSelector::ConfirmAreaTiles()
{
	for ( ATile* tile : TempAreaSelectedTiles.Difference( SelectedTiles ) )
	{
		AddSelectedTile( tile );
	}

}

// Invert All TileColors from within t1/t2.  Need to undo all tiles in the temp array that arn't in this inversion
void ATileSelector::TempInvertAreaTiles( ATile* t1, ATile* t2, ADwarfMap* Map )
{
	RemoveAndRestoreNotContained( t1, t2, Map );
	
	for ( ATile* tile : TempAreaSelectedTiles )
	{
		if ( tile->IsTileSelected() )
		{
			tile->SetTileColor( FLinearColor( 1.0f, 1.0f, 1.0f, 1.0f ) );
		}
		else
		{
			tile->SetTileColor( FLinearColor( 0.0f, 0.0f, 1.0f, 1.0f ) );
		}

	}
}

void ATileSelector::TempSelectAreaTiles( ATile* t1, ATile* t2, ADwarfMap* Map )
{
	RemoveAndRestoreNotContained( t1, t2, Map );
	for ( ATile* tile : TempAreaSelectedTiles )
	{
		tile->SetTileColor( FLinearColor( 0.0f, 0.0f, 1.0f, 1.0f ) );
	}

}

TSet<ATile*> ATileSelector::Finalize( )
{
	return SelectedTiles;
}

// Invert the selection of all tiles in this area.  This will set the bSelected of ATile.
void ATileSelector::InvertSelectAllTiles( ATile* t1, ATile* t2, ADwarfMap* Map )
{

}

void ATileSelector::RemoveAndRestoreNotContained( ATile* t1, ATile* t2, ADwarfMap* Map )
{
	TSet<ATile*> area;

	Map->GetTileArea( t1, t2, area );

	TSet<ATile*> deselectedTiles = TempAreaSelectedTiles.Difference( area );

	for ( ATile* tile : deselectedTiles )
	{
		if ( tile )
		{

			if ( tile->IsTileSelected() )
			{
				tile->SetTileColor( TileHighlight );
			}
			else
			{
				tile->SetTileColor( TileBase );
			}
		}
	}

	
	TempAreaSelectedTiles.Empty( area.Num() );
	TempAreaSelectedTiles.Append( area );

}

// Clear All Selected Tiles
void ATileSelector::ClearAll()
{
	for ( ATile* tile : SelectedTiles )
	{
		tile->SetTileColor( FLinearColor( 1.0f, 1.0f, 1.0f, 1.0f ) );
		tile->SetTileSelected( false );
	}

	SelectedTiles.Empty();
	TempAreaSelectedTiles.Empty();
}

// Remove a Selected Tile
void ATileSelector::RemoveTile( ATile* tile )
{

}