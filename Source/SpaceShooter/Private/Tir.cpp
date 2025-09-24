// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShooter/Public/Tir.h"

#include "NetworkReplayStreaming.h"
#include "Components/BoxComponent.h"
#include "GameFramework/FloatingPawnMovement.h"


// Sets default values
ATir::ATir()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	RootComponent = BoxCollision;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(BoxCollision);

	MovementComponent =  CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>("MovementComponent");
	MovementComponent->UpdatedComponent = BoxCollision;
}

FVector ATir::Seek(FVector TargetLocation)
{
	FVector vDesiredLocation = TargetLocation - GetActorLocation();
	vDesiredLocation.Normalize();
	vDesiredLocation*= MovementComponent->GetMaxSpeed();
	FVector vSterring = MovementComponent->Velocity;

	vSterring = vSterring.GetClampedToMaxSize(MovementComponent->GetMaxSpeed());

	return vSterring;
}

// Called when the game starts or when spawned
void ATir::BeginPlay()
{
	Super::BeginPlay();
	DesiredLocation = GetActorLocation();
	DesiredLocation.Y = 1111;
	MovementComponent->AddInputVector(DesiredLocation);
}

// Called every frame
void ATir::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

