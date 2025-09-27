// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShooter/Public/Asteroide.h"

#include "AsteroideInvocateur.h"
#include "Components/SphereComponent.h"
#include "SpaceShooter/Public/Tir.h"
#include "SpaceShooter/Public/Vaisseau.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"



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
	this->OnActorBeginOverlap.AddDynamic(this, &AAsteroide::OnOverlap);
	SetActorScale3D(GetActorScale()+VieMax);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AVaisseau::StaticClass(), Vaisseaux);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAsteroideInvocateur::StaticClass(), Invocateurs);
	if (Cast<AAsteroideInvocateur>(Invocateurs[0])->Invoc==0)
	{
		VectorA = FVector(1.0f * (6-VieMax), 0.0f, 0.0f);
	}
	if (Cast<AAsteroideInvocateur>(Invocateurs[0])->Invoc==1)
	{
		VectorA = FVector(0.0f, -1.0f * (6-VieMax), 0.0f);
	}
	if (Cast<AAsteroideInvocateur>(Invocateurs[0])->Invoc==2)
	{
		VectorA = FVector(-1.0f * (6-VieMax), 0.0f, 0.0f);
	}
}

void AAsteroide::PlayDestructionParticles()
{
	if (DestructionParticles)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(),
			DestructionParticles,
			GetActorLocation(),
			FRotator::ZeroRotator
			);
	}
	Destroy();
}

void AAsteroide::OnOverlap(AActor* MyActor, AActor* OtherActor)
{
	if (Cast<AVaisseau>(OtherActor)) {
		PlayDestructionParticles();
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
	AddActorWorldOffset(VectorA, true);
	if (VieA <= 0)
	{
		Cast<AVaisseau>(Vaisseaux[0])->Score+=VieMax*100;
		PlayDestructionParticles();
	}
	if (GetActorLocation().Y<=-1500 or GetActorLocation().Y>=1800 or GetActorLocation().X>=2000 or GetActorLocation().X<=-1900)
	{
		PlayDestructionParticles();
	}
}