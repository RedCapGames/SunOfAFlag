// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SAFPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class SUNOFAFLAG_API ASAFPlayerState : public APlayerState
{
	GENERATED_BODY()
		UPROPERTY(replicated)
		bool HasFlag;
	UPROPERTY(replicated)
		FTimespan DurationOfFlag;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const override;
public:
	void GetFlag();
	void ReleaseFlag();
	UFUNCTION(BlueprintCallable)
	bool IsPlayerHasFlag() const;
	UFUNCTION(BlueprintCallable)
	FTimespan GetDurationOfFlag() const;
	void AddToDurationOfFlag(FTimespan duration);
};
