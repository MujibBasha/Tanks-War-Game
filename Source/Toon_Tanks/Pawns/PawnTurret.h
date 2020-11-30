// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/World.h"
#include "Components/WidgetComponent.h"
#include "PawnTurret.generated.h"
\
class APawnTank;
class AProjectileBase;
class UHealtyComponent;
UCLASS()
class TOON_TANKS_API APawnTurret : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APawnTurret();
	
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UCapsuleComponent* CapsuleComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		USceneComponent* ProjectileSpawnPoint;


	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health Bar")
	//UWidgetComponent* TurretHealthBar;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame

	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:

	FTimerHandle FireRateTimerHandle;

	void ChekFireCondition();
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category= "Components", meta = (AllowPrivateAccess = "true"))
	float FireRate = 2.5f;


	APawnTank* PlayerPawn;


	float RoturnDistanceToPlayer();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	float FireRange = 500.f;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Spawn Class", meta = (ALLowPrivateAccess = "true"))
		TSubclassOf<AProjectileBase> ProjectileClass;





	void RotateTurrent(FVector LookAtTarget);
	void Fire();
	
	

protected:
	virtual void HandleDestruction();

	
public:
	void PawnDestroyed();

	//virtual void HandleDestruction() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UHealtyComponent* HealthComponent_Turret;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Particale Type", meta = (ALLowPrivateAccess = "true"))
		//TSubclassOf<AProjectileBase>  ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Particale Asset for Turret", meta = (ALLowPrivateAccess = "true"))
		UParticleSystem* DeathParticle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Death Turret Sound Effect", meta = (ALLowPrivateAccess = "true"))
		USoundBase* DeathSound;



};
