// Fill out your copyright notice in the Description page of Project Settings.


#include "SAFGameMode.h"

#include "Engine/Engine.h"
#include "SunOfAFlagCharacter.h"
#include "SAFGameState.h"
#include "SAFHUD.h"
#include "SAFPlayerController.h"
#include "SAFPlayerState.h"

ASAFGameMode::ASAFGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	DefaultPawnClass = ASunOfAFlagCharacter::StaticClass();
	GameStateClass = ASAFGameState::StaticClass();
	PlayerStateClass = ASAFPlayerState::StaticClass();
	PlayerControllerClass = ASAFPlayerController::StaticClass();
	HUDClass = ASAFHUD::StaticClass();
}

bool ASAFGameMode::TryPickFlag(ASunOfAFlagCharacter* character) const
{
	if(GetGameState<ASAFGameState>()->GetFlagOwner() == nullptr)
	{
		GetGameState<ASAFGameState>()->SetFlagOwner(character);
		return true;
	}
	return false;
}

void ASAFGameMode::ReleaseFlag(ASunOfAFlagCharacter* character) const
{
	GetGameState<ASAFGameState>()->SetFlagOwner(nullptr);
	character->GetPlayerState<ASAFPlayerState>()->ReleaseFlag();
}
void ASAFGameMode::Tick(float DeltaTime)
{
	if (GetGameState<ASAFGameState>()->GetFlagOwner() != nullptr)
	{
		auto playerState = GetGameState<ASAFGameState>()->GetFlagOwner()->GetPlayerState<ASAFPlayerState>();
		if(playerState != nullptr)
			playerState->AddToDurationOfFlag(FTimespan::FromSeconds(static_cast<double>(DeltaTime)));
	}
}
