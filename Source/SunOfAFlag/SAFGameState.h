// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "SunOfAFlagCharacter.h"
#include "SAFGameState.generated.h"
/**
 *
 */
UCLASS()
class SUNOFAFLAG_API ASAFGameState : public AGameState
{
	GENERATED_BODY()

		UPROPERTY(replicated)
		ASunOfAFlagCharacter* FlagOwner;
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const override;
public:
	ASunOfAFlagCharacter* GetFlagOwner() const;
	void SetFlagOwner(ASunOfAFlagCharacter* flagOwner);
};
