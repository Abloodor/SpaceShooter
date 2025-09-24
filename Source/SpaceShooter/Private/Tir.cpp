// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShooter/Public/Tir.h"

#include "Components/BoxComponent.h"


// Sets default values
ATir::ATir()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	RootComponent = BoxCollision;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(BoxCollision);
}

// Called when the game starts or when spawned
void ATir::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATir::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

