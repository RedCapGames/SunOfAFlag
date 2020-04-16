// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "SunOfAFlagCharacter.h"
#include "SAFGameMode.generated.h"


/**
 * 
 */
UCLASS()
class SUNOFAFLAG_API ASAFGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	ASAFGameMode();
	bool TryPickFlag(ASunOfAFlagCharacter* character) const;
	void ReleaseFlag(ASunOfAFlagCharacter* character) const;
	virtual void Tick(float DeltaTime) override;
};


