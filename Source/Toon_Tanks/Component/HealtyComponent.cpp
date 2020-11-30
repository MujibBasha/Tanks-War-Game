// Fill out your copyright notice in the Description page of Project Settings.


#include "HealtyComponent.h"
#include "Toon_Tanks/GameModes/TankGameModeBase.h"
#include "Kismet/GamePlayStatics.h"
#include "Components/WidgetComponent.h"
#include "Engine/World.h"
#include "Toon_Tanks/Turret_HealthBar.h"

// Sets default values for this component's properties
UHealtyComponent::UHealtyComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	
}


// Called when the game starts
void UHealtyComponent::BeginPlay()
{
	Super::BeginPlay();
	Health = DefaultHealth;

	GameModeRef = Cast<ATankGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));


	Owner = GetOwner();

	if (Owner)
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealtyComponent::TakeDamage);

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Health Component has no reference to the Woner"));
	}

	
}





void UHealtyComponent::TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{

	if (Damage == 0)
	{
		return;
	}

	Health = FMath::Clamp(Health - Damage, 0.0f, DefaultHealth);

	
	UE_LOG(LogTemp, Warning, TEXT("Health = %f"), Health)


	
	if (Health <= 0)
	{

		if (GameModeRef)
		{
			GameModeRef->ActorDied(Owner);
		}

		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Health Component Has no refrance To the TankGameMode"));
		}
	}


}