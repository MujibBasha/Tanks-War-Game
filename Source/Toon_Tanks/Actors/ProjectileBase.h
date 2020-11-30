// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"


class UProjectileMovementComponent;

UCLASS()
class TOON_TANKS_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float MovementSpeed =2500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (AllowPrivateAccess = "true"))
	float Damage =10.0f;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpuct, const FHitResult& Hit);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MYOWner")
	AActor* MyOwner;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Particale Asset Projectile Hit", meta = (ALLowPrivateAccess = "true"))
	UParticleSystem* HitParticale;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Particale Asset Projectile Hit")
	UParticleSystemComponent* ParticleTrail ;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile Sound Effect", meta = (ALLowPrivateAccess = "true"))
	USoundBase* HitSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile Sound Effect", meta = (ALLowPrivateAccess = "true"))
	USoundBase* LaunchSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hit Projectile Camera Shake", meta = (ALLowPrivateAccess = "true"))
	TSubclassOf<UCameraShake> HitShake;
	
};
