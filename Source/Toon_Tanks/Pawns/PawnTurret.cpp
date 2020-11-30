// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "Components/StaticMeshComponent.h"
#include "Components/Inputcomponent.h"
#include "Kismet/GamePlayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "PawnTank.h"
#include "Toon_Tanks/Actors/ProjectileBase.h"
#include "Toon_Tanks/Component/HealtyComponent.h"

// Sets default values
APawnTurret::APawnTurret()
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

	//HealthComponent_Turret=CreateDefaultSubobject<UHealtyComponent>(TEXT("Health Component"));

	//TurretHealthBar=CreateDefaultSubobject<UWidgetComponent>(TEXT("HEalth Bar"));

	//TurretHealthBar->SetupAttachment(RootComponent);
	
	
}

// Called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
	Super::BeginPlay();	 


	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::ChekFireCondition, FireRate, true,false);
	
	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!PlayerPawn || RoturnDistanceToPlayer() >FireRange)
	{ 
	
		return;
	}


	RotateTurrent(PlayerPawn->GetActorLocation());

}

// Called to bind functionality to input
void APawnTurret::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void APawnTurret::ChekFireCondition()
{

	//if Player === null  ||  is Dead Then Bail
	if (!PlayerPawn || !PlayerPawn->GetPlayerAlive())
	{
		return;
	}

	//if Player Player in range Then Fire
	if (RoturnDistanceToPlayer() <= FireRange)
	{
		//Fire
		Fire();
		
	}
}


float APawnTurret::RoturnDistanceToPlayer()
{
	if (!PlayerPawn)
	{
		return 0.0;
	}

	float Distance = (PlayerPawn->GetActorLocation() - GetActorLocation()).Size();

	return Distance;



}



void APawnTurret::RotateTurrent(FVector LookAtTarget)
{
   //Update TurretMesh rotation to face towards the   LookAtTarget passed in from the child Class.
	//TurretMesh->SetWorldRotation()...

	FVector StartLocation = TurretMesh->GetComponentLocation();
	FRotator TurretRotation = UKismetMathLibrary::FindLookAtRotation(StartLocation, FVector(LookAtTarget.X, LookAtTarget.Y,TurretMesh->GetComponentLocation().Z));

	TurretMesh->SetWorldRotation(TurretRotation);
}
void APawnTurret::Fire()
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

void APawnTurret::HandleDestruction()
{
	

		//Universel Functionslitry


   //.... Then do unique shild override

   //--pawnTurret-- Inform GameMode turret Died -> Then Destroy()  self.
	UGameplayStatics::SpawnEmitterAtLocation(this,DeathParticle,GetActorLocation(),FRotator::ZeroRotator );

	//Play death particls, sound and camera shake
	if (DeathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	}


	Destroy();

	//--PawntTank--	 Inform GameMode turret Died -> Then Hide () All Component && stop Movement Input.
}




void APawnTurret:: PawnDestroyed()
{

	HandleDestruction();

}