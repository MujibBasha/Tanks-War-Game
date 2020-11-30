// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealtyComponent.generated.h"

class ATankGameModeBase;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOON_TANKS_API UHealtyComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealtyComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
   
	UFUNCTION()
	void TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

private:

    UPROPERTY(EditAnywhere,BlueprintReadOnly,category="Health",meta=(AllowPrivateAccess="true"))
	float DefaultHealth = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Health", meta = (AllowPrivateAccess = "true"))
	float Health = 0.0f;

	AActor* Owner;

	ATankGameModeBase* GameModeRef;


	
};
