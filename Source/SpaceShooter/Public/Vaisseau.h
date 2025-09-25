// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tir.h"
#include "GameFramework/Pawn.h"
#include "Vaisseau.generated.h"

UCLASS()
class SPACESHOOTER_API AVaisseau : public APawn
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere)
	class USphereComponent* BoxCollision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(Category = Pawn, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPawnMovementComponent* MovementComponent;

	FVector NextPosition;
	int MaxY;
	int MinY;
	int MaxX;
	int MinX;
	

public:
	// Sets default values for this pawn's properties
	AVaisseau();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int VieV;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Score;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	TSubclassOf<ATir> ActorToSpawnClass;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void MoveForward(float value);
	void MoveBackward(float value);
	void MoveLeft(float value);
	void MoveRight(float value);
	void OnSpaceKeyPressed();
	void SpawnObject();
};
