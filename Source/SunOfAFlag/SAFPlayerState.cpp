// Fill out your copyright notice in the Description page of Project Settings.


#include "SAFPlayerState.h"

#include "Net/UnrealNetwork.h"

void ASAFPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASAFPlayerState, HasFlag);
	DOREPLIFETIME(ASAFPlayerState, DurationOfFlag);

}

void ASAFPlayerState::GetFlag()
{
	HasFlag = true;
}

void ASAFPlayerState::ReleaseFlag()
{
	HasFlag = false;
}

bool ASAFPlayerState::IsPlayerHasFlag() const
{
	return HasFlag;
}

FTimespan ASAFPlayerState::GetDurationOfFlag() const
{
	return DurationOfFlag;
}

void ASAFPlayerState::AddToDurationOfFlag(FTimespan duration)
{
	DurationOfFlag += duration;
}
