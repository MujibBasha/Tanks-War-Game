// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include "Toon_Tanks/Pawns/PawnTank.h"
#include "Toon_Tanks/Pawns/PawnTurret.h"
#include "Kismet/GamePlayStatics.h"
#include "Toon_Tanks/PlayerControllers/PlayerControllerBase.h"
#include "TimerManager.h"


void ATankGameModeBase::BeginPlay()
{


	TargetTurrets = GetTargetTurretCount();


	PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));

	PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

	HandleGameStart();

	Super::BeginPlay();

}

int32 ATankGameModeBase::GetTargetTurretCount()
{
	TSubclassOf<APawnTurret> ClassToFind;
	ClassToFind = APawnTurret::StaticClass();

	TArray<AActor*> TurretActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ClassToFind, TurretActors);
	return 	  TurretActors.Num();;

}

void ATankGameModeBase::ActorDied(AActor* DeadActor)
{

	if (DeadActor == PlayerTank)
	{
		if (PlayerControllerRef) {
			PlayerControllerRef->setPlayerEnableState(false);

		}
		PlayerTank->PawnDestroyed();
		HandleGameOver(false);

		
	}

	else if (APawnTurret* DestroyTurret = Cast<APawnTurret>(DeadActor))
	{

		DestroyTurret->PawnDestroyed();

		TargetTurrets--;

		if (TargetTurrets == 0)
		{
			HandleGameOver(true);
		}
	}
}



void ATankGameModeBase::HandleGameStart()
{

	GameStart();
	if (PlayerControllerRef) {
		PlayerControllerRef->setPlayerEnableState(false);
	
		FTimerHandle PlayerEnableHandle;
		FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef, &APlayerControllerBase::setPlayerEnableState,true);
		GetWorldTimerManager().SetTimer(PlayerEnableHandle,PlayerEnableDelegate,StartDelay,false);
	}
	
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon)
{
	GameOver(PlayerWon);
}

