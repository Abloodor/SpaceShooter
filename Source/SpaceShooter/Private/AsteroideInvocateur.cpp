// Fill out your copyright notice in the Description page of Project Settings.


#include "AsteroideInvocateur.h"

#include "Components/BoxComponent.h"


// Sets default values
AAsteroideInvocateur::AAsteroideInvocateur()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ConstructorHelpers::FClassFinder<AActor> ActorToSpawn (TEXT("/Game/Jeu/BP_Asteroide"));
	if (ActorToSpawn.Succeeded())
	{
		ActorToSpawnClass = ActorToSpawn.Class;
	}
}

// Called when the game starts or when spawned
void AAsteroideInvocateur::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAsteroideInvocateur::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	Timer += DeltaTime;
	if (Timer>=2.0f)
	{
		Invoc = FMath::RandRange(0,2);
		if (Invoc==0)
		{
			FVector SpawnLocation = FVector(MinX,FMath::RandRange(MinY, MaxY),Z);
			SpawnObject(SpawnLocation);
			Timer = 0.0f;
		}
		if (Invoc==1)
		{
			FVector SpawnLocation = FVector(FMath::RandRange(MinX, MaxX),MaxY,Z);
			SpawnObject(SpawnLocation);
			Timer = 0.0f;
		}
		if (Invoc==2)
		{
			FVector SpawnLocation = FVector(MaxX,FMath::RandRange(MinY, MaxY),Z);
			SpawnObject(SpawnLocation);
			Timer = 0.0f;
		}
	}
}
void AAsteroideInvocateur::SpawnObject(FVector Spawn)
{
	AAsteroide* SpawnedActor = GetWorld()->SpawnActor<AAsteroide>(ActorToSpawnClass, Spawn, FRotator(0, 0, 0));
	UPrimitiveComponent* SpawnedComponent = Cast<UPrimitiveComponent>(SpawnedActor->GetRootComponent());
	SpawnedComponent->SetSimulatePhysics(true);
}
