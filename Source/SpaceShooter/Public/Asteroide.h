// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Asteroide.generated.h"


UCLASS()
class SPACESHOOTER_API AAsteroide : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere)
	class USphereComponent* BoxCollision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(Category = Pawn, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPawnMovementComponent* MovementComponent;
	
	UFUNCTION()
	void OnOverlap(AActor* MyActor, AActor* OtherActor);

	TArray<AActor*> Vaisseaux;
	int VieA;
	int VieMax;
	FVector VectorA;

	
public:
	// Sets default values for this actor's properties
	AAsteroide();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
