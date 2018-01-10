#pragma once

#include "GameFramework/Actor.h"
#include "TileSelector.generated.h"

class ADwarfMap;
class ATile;
/**
 * 
 */
UCLASS()
class DWARFGAME_API ATileSelector : public AActor
{
	GENERATED_BODY()

public:
	ATileSelector();

	// Temporary Invert the selection of all tiles in this area.  This is only a temp color.  This will not set the bSelected of ATile.
	void TempInvertAreaTiles( ATile* t1, ATile* t2, ADwarfMap* Map );

	// Temporary Select the selection of all tiles in this area.  This is only a temp color.  This will not set the bSelected of ATile.
	void TempSelectAreaTiles( ATile* t1, ATile* t2, ADwarfMap* Map );

	// Confirm the Area Tiles to be moved from TempAreaSelectedTiles -> SelectedTiles
	void ConfirmAreaTiles();

	// Invert the selection of all tiles in this area.  This will set the bSelected of ATile.
	void InvertSelectAllTiles( ATile* t1, ATile* t2, ADwarfMap* Map );

	// Clear All Selected Tiles
	void ClearAll();

	// Finalize selection -> Returns a copy of the selected Tiles acted upon
	TSet<ATile*> Finalize( );

	// Remove a Selected Tile
	void RemoveTile( ATile* tile );

	//Add a selected Tile
	void AddSelectedTile( ATile* tile );

	void SetSelectionType( ESelectionEnum Selection );

	void RemoveAndRestoreNotContained( ATile* t1, ATile* t2, ADwarfMap* Map );

public:

	TSet<ATile*> TempAreaSelectedTiles;

	TSet<ATile*> SelectedTiles;

	ESelectionEnum SelectionType;
};
