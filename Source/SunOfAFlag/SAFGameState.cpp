// Fill out your copyright notice in the Description page of Project Settings.


#include "SAFGameState.h"

#include "Net/UnrealNetwork.h"

ASunOfAFlagCharacter* ASAFGameState::GetFlagOwner() const
{
	return FlagOwner;
}

void ASAFGameState::SetFlagOwner(ASunOfAFlagCharacter* flagOwner)
{
	FlagOwner = flagOwner;
}
void ASAFGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASAFGameState, FlagOwner);
}