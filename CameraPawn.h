// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "CameraPawn.generated.h"

UCLASS()
class DWARFGAME_API ACameraPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACameraPawn(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	UPROPERTY()
	UCameraComponent* CameraComponent;
	
	void SetDwarf(class ADworf* Dworft);

private:

	void LeftRightMovement(float val);

	UPROPERTY( Replicated )
	class ADworf* Dworf;

	
};
