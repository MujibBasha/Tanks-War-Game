#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameModeBase.generated.h"

class APlayerControllerBase;

class APawnTank;
class APawnTurret;
UCLASS()
class TOON_TANKS_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;


public:
	void ActorDied(AActor* DeadActor);

	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool PlayerWon);



private:

	void HandleGameStart();
	void HandleGameOver(bool PlayerWon);


	int32 TargetTurrets = 0;
	int32 GetTargetTurretCount();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player", meta = (AllowPrivateAccess = "true"))
		APawnTank* PlayerTank;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Game Loop", meta = (AllowPrivateAccess = "true"))
	int start_Delay_2 = 3;


	APlayerControllerBase* PlayerControllerRef;
	float StartDelay = 4.f;


	
};
