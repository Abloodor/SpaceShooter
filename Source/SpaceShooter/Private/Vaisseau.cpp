// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShooter/Public/Vaisseau.h"

#include "Components/SphereComponent.h"
#include "GameFramework/FloatingPawnMovement.h"


// Sets default values
AVaisseau::AVaisseau()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxCollision = CreateDefaultSubobject<USphereComponent>("BoxCollision");
	RootComponent = BoxCollision;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(BoxCollision);

	MovementComponent =  CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>("MovementComponent");
	MovementComponent->UpdatedComponent = BoxCollision;
}

// Called when the game starts or when spawned
void AVaisseau::BeginPlay()
{
	Super::BeginPlay();
	VieV = 3;
	
}

// Called every frame
void AVaisseau::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AVaisseau::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

