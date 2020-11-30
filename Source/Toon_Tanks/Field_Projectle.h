// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Field_Projectle.generated.h"



UCLASS()
class TOON_TANKS_API AField_Projectle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AField_Projectle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	USphereComponent * SphereCollision;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* SphereMesh;

	UFUNCTION()
		void Hit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpuct, const FHitResult& Hit);

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Projectile_Field")
	TSubclassOf<AActor> Projectile_Field;

};
