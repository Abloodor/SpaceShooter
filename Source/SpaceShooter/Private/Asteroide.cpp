// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShooter/Public/Asteroide.h"

#include "Components/SphereComponent.h"
#include "SpaceShooter/Public/Tir.h"
#include "SpaceShooter/Public/Vaisseau.h"
#include "GameFramework/FloatingPawnMovement.h"


// Sets default values
AAsteroide::AAsteroide()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxCollision = CreateDefaultSubobject<USphereComponent>("BoxCollision");
	RootComponent = BoxCollision;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(BoxCollision);

	MovementComponent =  CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>("MovementComponent");
	MovementComponent->UpdatedComponent = BoxCollision;
}

// Called when the game starts or when spawned
void AAsteroide::BeginPlay()
{
	Super::BeginPlay();
	VieA = FMath::RandRange(1,5);
	VieMax = VieA;
	/*
	SetActorScale3D(GetActorScale()+VieMax);*/
}
void AAsteroide::OnOverlap(AActor* MyActor, AActor* OtherActor)
{
	if (Cast<AVaisseau>(OtherActor)) {
		Destroy();
		Cast<AVaisseau>(OtherActor)->VieV-=1;
	}
	if (Cast<ATir>(OtherActor)) {
		Cast<ATir>(OtherActor)->Destroy();
		VieA-=1;
	}
}
// Called every frame
void AAsteroide::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	VectorA = FVector(0.0f, -1.0f * (6-VieMax), 0.0f);
	AddActorWorldOffset(VectorA, true);
	if (VieA <= 0)
	{
		Destroy();
	}
	if (GetActorLocation().Y<=-1500)
	{
		Destroy();
	}
}

