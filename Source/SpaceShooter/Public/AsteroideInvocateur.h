// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Asteroide.h"
#include "GameFramework/Actor.h"
#include "AsteroideInvocateur.generated.h"

UCLASS()
class SPACESHOOTER_API AAsteroideInvocateur : public AActor
{
	GENERATED_BODY()

	int MaxX = 1840;
	int MinX = -1730;
	int Y = 1500;
	int Z = 182;
	float Timer;

public:
	// Sets default values for this actor's properties
	AAsteroideInvocateur();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	TSubclassOf<AAsteroide> ActorToSpawnClass;
	void SpawnObject(FVector Spawn);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
