// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SAFPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SUNOFAFLAG_API ASAFPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ASAFPlayerController();
	void UnFreeze()override;
};
