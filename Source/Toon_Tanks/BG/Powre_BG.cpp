// Fill out your copyright notice in the Description page of Project Settings.


#include "Powre_BG.h"
#include "Toon_Tanks/Pawns/PawnTank.h"
#include "Kismet/GamePlayStatics.h"

#include "Components/StaticMeshComponent.h"

// Sets default values
APowre_BG::APowre_BG()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereMesh=CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Mesh"));
	RootComponent = SphereMesh;
	BGMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BG Mesh"));
	BGMesh->SetupAttachment(RootComponent);

	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

// Called when the game starts or when spawned
void APowre_BG::BeginPlay()
{
	Super::BeginPlay();
	
	SphereMesh->OnComponentBeginOverlap.AddDynamic(this, & APowre_BG::OnHit);
}

// Called every frame
void APowre_BG::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void APowre_BG::OnHit(class UPrimitiveComponent* HitComp,class AActor* OtherActor,class  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Error, TEXT("The hit is worker"))
	UE_LOG(LogTemp, Error, TEXT("kkkkkkkkkkkkkkkkkkkkkkkr"))
	if (OtherActor->ActorHasTag("PlayerTank"))
	{
		

		UE_LOG(LogTemp, Error, TEXT("The hit of Other actor Worker"))
			PlayerPawn->SpawnProtectedField();
		Destroy();

	}

	else if (OtherComp->ComponentHasTag("PlayerTank"))
	{
		
		UE_LOG(LogTemp, Error, TEXT("The hit of Other Component Worker"))
		PlayerPawn->SpawnProtectedField();
		Destroy();
	}

}


