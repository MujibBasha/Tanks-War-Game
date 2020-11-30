// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GamePlayStatics.h"

#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
	RootComponent = ProjectileMesh;
	
	

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->InitialSpeed = MovementSpeed;
	ProjectileMovement->MaxSpeed=MovementSpeed;
		
	InitialLifeSpan = 30.0f;

	ParticleTrail = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle Component"));
	ParticleTrail->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	if (LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound,GetActorLocation());
	}

	
	
}


void AProjectileBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpuct, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Error, TEXT(")_)ERRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR"))
		
		MyOwner = HitComp->GetOwner();

		UE_LOG(LogTemp, Error, TEXT("0_ERRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR"))
		if (!MyOwner)					 //ERROR   I can not Get
		{
			UE_LOG(LogTemp, Error, TEXT("Inside og IF MyOwner_1"))
				return;
		}
	UE_LOG(LogTemp, Error, TEXT("1_ERRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR"))
	

	if (OtherActor != NULL && OtherActor != this && OtherActor != MyOwner)
	{

		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwner->GetInstigatorController(), this, DamageType);
		if (HitParticale) {
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticale, GetActorLocation(), FRotator::ZeroRotator);
		}

		if (HitSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
		}

		if (HitShake)
		{

			GetWorld()->GetFirstPlayerController()->PlayerCameraManager->PlayCameraShake(HitShake,1);
		}


		this->Destroy();

	}

	UE_LOG(LogTemp,Error,TEXT("ERRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR"))


}

/*UE_LOG(LogTemp, Error, TEXT(")_)ERRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR"))


UE_LOG(LogTemp, Error, TEXT("0_ERRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR"))
if (MyOwner ==NULL)					 //ERROR   I can not Get
{
	UE_LOG(LogTemp, Error, TEXT("Inside og IF"))
	return;
}
UE_LOG(LogTemp, Error, TEXT("1_ERRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR"))*/
