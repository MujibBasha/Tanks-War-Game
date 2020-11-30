// Fill out your copyright notice in the Description page of Project Settings.


#include "Field_Projectle.h"

// Sets default values
AField_Projectle::AField_Projectle()

{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollision =CreateDefaultSubobject<USphereComponent>(TEXT("ShereCollistion"));
	//SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &APawnTank::OnHit);
	RootComponent= SphereCollision;
	
	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere Mesh"));
		
	SphereMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AField_Projectle::BeginPlay()
{
	Super::BeginPlay();
	SphereMesh->OnComponentHit.AddDynamic(this, &AField_Projectle::Hit);
	
}

// Called every frame
void AField_Projectle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AField_Projectle::Hit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpuct, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Error, TEXT("insid eof Hit"))
	if (OtherActor->ActorHasTag("Tank_Turret_Projectile"))
	{
		UE_LOG(LogTemp, Error, TEXT("FGADfsDFSDFD"))
		FVector Loc = OtherActor->GetActorLocation();
		
		float Angle = FMath::RandRange(0, 90);

		AActor* FieldProjectile = GetWorld()->SpawnActor<AActor>(Projectile_Field, Loc, FRotator(5, Angle,0));
	}

}

