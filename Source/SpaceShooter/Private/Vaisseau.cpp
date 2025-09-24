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

	check(PlayerInputComponent);
	
    PlayerInputComponent->BindAxis("MoveForward", this, &AVaisseau::MoveForward);
	PlayerInputComponent->BindAxis("MoveBackward", this, &AVaisseau::MoveBackward);
	PlayerInputComponent->BindAxis("MoveLeft", this, &AVaisseau::MoveLeft);
	PlayerInputComponent->BindAxis("MoveRight", this, &AVaisseau::MoveRight);
	PlayerInputComponent->BindAction("MoveRight", IE_Pressed, this, &AVaisseau::OnSpaceKeyPressed);
}

void AVaisseau::MoveForward(float value)
{
	if (value != 0)
	{
		AddMovementInput(GetActorRightVector(), 1.0f);
	}

}void AVaisseau::MoveBackward(float value)
{
	if (value != 0){
		AddMovementInput(GetActorRightVector(), -1.0f);
	}
}
void AVaisseau::MoveLeft(float value)
{
	if (value != 0)
	{
		AddMovementInput(GetActorForwardVector(), 1.0f);
	}
}
void AVaisseau::MoveRight(float value)
{
	if (value != 0)
	{
		AddMovementInput(GetActorForwardVector(), -1.0f);
	}
}
void AVaisseau::OnSpaceKeyPressed()
{
	UE_LOG(LogTemp, Warning, TEXT("Touche Espace pressée - Avancer"));
	SpawnObject();
}


void AVaisseau::SpawnObject()
{
	FVector SpawnLocation = GetActorLocation();
	SpawnLocation.X += 65;
	ATir* SpawnedActor = GetWorld()->SpawnActor<ATir>(ActorToSpawnClass, SpawnLocation, FRotator(0, 0, 0));
	UPrimitiveComponent* SpawnedComponent = Cast<UPrimitiveComponent>(SpawnedActor->GetRootComponent());
	SpawnedComponent->SetSimulatePhysics(true);
}