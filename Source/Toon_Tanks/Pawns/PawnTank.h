
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "Camera/CameraShake.h"
#include "GameFramework/SpringArmComponent.h"
#include "PawnTank.generated.h"



class AProjectileBase;
class UHealtyComponent;
class AField_Projectle;

UCLASS()
class TOON_TANKS_API APawnTank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APawnTank();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UCapsuleComponent* CapsuleComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		USceneComponent* ProjectileSpawnPoint;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UCameraComponent* Camera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* SpringArm;

	FVector MoveDirection;
	FQuat RotationDirection;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Movement", meta = (ALLowPrivateAccess = "true"))
		float MoveSpeed = 10.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Movement", meta = (ALLowPrivateAccess = "true"))
		float RotateSpeed = 10.f;

	void CalculateMoveInput(float Value);
	void CalculateRotateInput(float Value);


	void Move();
	void Rotate();

	void RotateTurrent(FVector LookAtTarget);
	void Fire();
	FHitResult TraceHitResult;

	APlayerController* PlayerControllerRef;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Spawn Class", meta = (ALLowPrivateAccess = "true"))
	TSubclassOf<AProjectileBase> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Tank Healthy Bar", meta = (ALLowPrivateAccess = "true"))
		TSubclassOf<UUserWidget> TankBar;

	UUserWidget* PlayerITankBar;
	

protected:

	virtual void HandleDestruction();

	bool bAlive=true;

public:
	void PawnDestroyed();
	bool GetPlayerAlive();


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UHealtyComponent* HealthComponent_Tank;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Particale Asset for Tank", meta = (ALLowPrivateAccess = "true"))

	UParticleSystem* DeathParticle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Death Tank Sound Effect", meta = (ALLowPrivateAccess = "true"))
		USoundBase* DeathSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Death Tank Camera Shake", meta = (ALLowPrivateAccess = "true"))
		TSubclassOf<UCameraShake> DeathShake;



	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn Field", meta = (ALLowPrivateAccess = "true"))
		TSubclassOf<AField_Projectle> ProtectedField;

	UFUNCTION()
	void SpawnProtectedField();
	


	
};
