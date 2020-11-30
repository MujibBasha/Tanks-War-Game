// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Powre_BG.generated.h"
class APawnTank;

UCLASS()
class TOON_TANKS_API APowre_BG : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowre_BG();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sphere Mesh", meta = (AllowPrivateAccess = "true"))
	USphereComponent*  SphereMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BG", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BGMesh;


	
	void OnHit(class UPrimitiveComponent* HitComp,class AActor* OtherActor,class  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,bool bFromSweep, const FHitResult& SweepResult);

	   

	APawnTank* PlayerPawn;
};
