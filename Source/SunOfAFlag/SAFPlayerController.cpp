// Fill out your copyright notice in the Description page of Project Settings.


#include "SAFPlayerController.h"

#include "Engine/World.h"
#include "GameFramework/GameModeBase.h"

ASAFPlayerController::ASAFPlayerController()
{
	bAutoManageActiveCameraTarget = false;
}

void ASAFPlayerController::UnFreeze()
{
	if (GetLocalRole() != ROLE_Authority)
	{
		return;
	}
	GetWorld()->GetAuthGameMode()->RestartPlayer(this);
}
