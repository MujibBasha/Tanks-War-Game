// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTank.h"
#include "Components/StaticMeshComponent.h"
#include "Components/Inputcomponent.h"
#include "Kismet/KismetMathLibrary.h"	

#include "GameFramework/PlayerController.h"
#include "Toon_Tanks/Actors/ProjectileBase.h"
#include "Toon_Tanks/Component/HealtyComponent.h"
#include "Kismet/GamePlayStatics.h"
#include "Components/WidgetComponent.h"
#include "Toon_Tanks/Field_Projectle.h"


// Sets default values
APawnTank::APawnTank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(BaseMesh);
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Prijectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);


	HealthComponent_Tank = CreateDefaultSubobject<UHealtyComponent>(TEXT("Health Component"));



	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm,USpringArmComponent::SocketName);


	//TArray<AField_Projectle*> ProjectileFieldRef;
	//TSubclassOf<AField_Projectle> ProjectileFieldType;
	//ProjectileFieldType = AField_Projectle::StaticClass();

    //UGameplayStatics::GetAllActorsOfClass(GetWorld(), ProjectileFieldType, ProjectileFieldRef);

		

}

// Called when the game starts or when spawned
void APawnTank::BeginPlay()
{
	Super::BeginPlay();

	
	PlayerControllerRef = Cast<APlayerController>(GetController());

	

	if (TankBar) 
	{
		
		PlayerITankBar = CreateWidget(GetWorld(), TankBar);
		PlayerITankBar->AddToViewport();
	}
	
}

// Called every frame
void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Rotate();
		Move();

		if (PlayerControllerRef)
		{
			PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			
			FVector HitLocation = TraceHitResult.ImpactPoint;
			RotateTurrent(HitLocation);

		}

}

// Called to bind functionality to input
void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank::CalculateMoveInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawnTank::CalculateRotateInput);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APawnTank::Fire);
}

void APawnTank::CalculateMoveInput(float Value)
{
	MoveDirection = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds,0,0);

}

void APawnTank::CalculateRotateInput(float Value)
{

	FRotator Rotation = FRotator(0, Value * RotateSpeed * GetWorld()->DeltaTimeSeconds,0);
	RotationDirection = FQuat(Rotation);


}

void APawnTank::Move()
{
	AddActorLocalOffset(MoveDirection,true);       //!!!!

}

void APawnTank::Rotate()
{
	AddActorLocalRotation(RotationDirection,true);
}



void APawnTank::RotateTurrent(FVector LookAtTarget)
{
	//Update TurretMesh rotation to face towards the   LookAtTarget passed in from the child Class.
	 //TurretMesh->SetWorldRotation()...

	FVector StartLocation = TurretMesh->GetComponentLocation();
	
	FRotator TurretRotation = UKismetMathLibrary::FindLookAtRotation(StartLocation, FVector(LookAtTarget.X, LookAtTarget.Y, TurretMesh->GetComponentLocation().Z));

	TurretMesh->SetWorldRotation(TurretRotation);
}
void APawnTank::Fire()
{
	//Get ProjectileSpawnPoint Location && Rotation  -> Spawn Projectile class at Location towards Rotation

	if (ProjectileClass)
	{
		FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
		FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();

		AProjectileBase* TempProjectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, SpawnLocation, SpawnRotation);

		//TempProjectile->SetOwner(this);
	}

}

void APawnTank::HandleDestruction()
{
	
	

		//Universel Functionslitry


	//ParticleSysytem Effect when the Tank Death
	UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetActorLocation(), FRotator::ZeroRotator);


   //Play death particls, sound and camera shake
	if (DeathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	}
	if (DeathShake)
	{
		GetWorld()->GetFirstPlayerController()->PlayerCameraManager->PlayCameraShake(DeathShake,1);
	}

//--PawntTank--	 Inform GameMode turret Died -> Then Hide () All Component && stop Movement Input.
	SetActorHiddenInGame(true);

	SetActorTickEnabled(false);
			  
	


}

void APawnTank::PawnDestroyed()
{

	HandleDestruction();
	bAlive = false;

}

bool APawnTank::GetPlayerAlive()
{

	return bAlive;

}


void  APawnTank::SpawnProtectedField()
{
	FVector Lo = CapsuleComp->GetComponentLocation();
	
	
	

	AField_Projectle* ProField=GetWorld()->SpawnActor<AField_Projectle>(ProtectedField,Lo, FRotator(0));
	//ProField->AttachToActor(this);


}

