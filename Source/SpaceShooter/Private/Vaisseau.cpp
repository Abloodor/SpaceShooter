// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShooter/Public/Vaisseau.h"

#include "Components/SphereComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"


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

	ConstructorHelpers::FClassFinder<AActor> ActorToSpawn (TEXT("/Game/Jeu/BP_Tir"));
	if (ActorToSpawn.Succeeded())
	{
		ActorToSpawnClass = ActorToSpawn.Class;
	}
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
	Timer += DeltaTime;
	if (VieV <= 0)
	{
		Restart();
	}
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
	PlayerInputComponent->BindAction("Tirer", IE_Pressed, this, &AVaisseau::OnSpaceKeyPressed);
}

void AVaisseau::MoveForward(float value)
{
	if (value != 0)
	{
		if (GetActorLocation().Y<=MaxY)
		{
			AddActorWorldOffset(FVector(0.0f, 10.0f, 0.0f), true);
		}
	}

}void AVaisseau::MoveBackward(float value)
{
	if (value != 0){
		if (GetActorLocation().Y>=MinY)
		{
			AddActorWorldOffset(FVector(0.0f, -10.0f, 0.0f), true);
		}
	}
}
void AVaisseau::MoveLeft(float value)
{
	if (value != 0)
	{
		if (GetActorLocation().X<=MaxX)
		{
			AddActorWorldOffset(FVector(10.0f, 0.0f, 0.0f), true);
		}
	}
}
void AVaisseau::MoveRight(float value)
{
	if (value != 0)
	{
		if (GetActorLocation().X>=MinX)
		{
			AddActorWorldOffset(FVector(-10.0f,0.0f, 0.0f), true);
		}
	}
}
void AVaisseau::OnSpaceKeyPressed()
{
	/*if (NS_Tir)
	{
		FVector SpawnLocation = GetActorLocation();
		SpawnLocation.Y += 65;
	}
	if (SB_Tir)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), SB_Tir, GetActorLocation());
	}*/
	if (Timer>=1.0f)
	{
		SpawnObject();
	}
}


void AVaisseau::SpawnObject()
{
	FVector SpawnLocation = GetActorLocation();
	SpawnLocation.Y += 65;
	ATir* SpawnedActor = GetWorld()->SpawnActor<ATir>(ActorToSpawnClass, SpawnLocation, FRotator(0, 0, 0));
	UPrimitiveComponent* SpawnedComponent = Cast<UPrimitiveComponent>(SpawnedActor->GetRootComponent());
	SpawnedComponent->SetSimulatePhysics(true);
}