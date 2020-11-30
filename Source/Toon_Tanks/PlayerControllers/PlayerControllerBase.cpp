// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerBase.h"
#include "GameFramework/Controller.h"



void APlayerControllerBase::setPlayerEnableState(bool setPlayerEnabled)
{
	if (setPlayerEnabled== true)
	{
		APlayerControllerBase::bShowMouseCursor = true;
		GetPawn()->EnableInput(this);
		
		


     }
	else
	{
		GetPawn()-> DisableInput(this);

		APlayerControllerBase::bShowMouseCursor=false;
	}
}