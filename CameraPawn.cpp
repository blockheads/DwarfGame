// Fill out your copyright notice in the Description page of Project Settings.

#include "DwarfGame.h"
#include "CameraPawn.h"
#include "Dworf.h"
#include "Net/UnrealNetwork.h"


// Sets default values
ACameraPawn::ACameraPawn(const FObjectInitializer& ObjectInitializer)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("CameraComponent"));

	RootComponent = CameraComponent;
	CameraComponent->ProjectionMode = ECameraProjectionMode::Orthographic;
	CameraComponent->OrthoWidth = 3600.0f;

}

// Called when the game starts or when spawned
void ACameraPawn::BeginPlay()
{
	Super::BeginPlay();
	CameraComponent->SetRelativeLocation( FVector( 600.0f, 100.0f, 0.0f ) );
	
}

// Called every frame
void ACameraPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ACameraPawn::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis("LeftRightMovement", this, &ACameraPawn::LeftRightMovement);

	if (Dworf == NULL)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("null"));
	else
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("not null"));
	this->InputComponent = InputComponent;


}

void ACameraPawn::LeftRightMovement(float val){

	SetActorLocation(FVector(GetActorLocation().X + val * 10, GetActorLocation().Y, GetActorLocation().Z));

}

void ACameraPawn::SetDwarf(ADworf* Dworft){

	Dworf = Dworft;

	if (InputComponent == NULL)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("null"));
	else
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("not null"));

	if (InputComponent)
	{
		Dworf->SetupPlayerInputComponent(InputComponent);
	}

	
}

void ACameraPawn::GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const
{
	DOREPLIFETIME( ACameraPawn, Dworf );
}