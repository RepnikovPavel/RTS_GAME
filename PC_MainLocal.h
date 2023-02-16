// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PC_MainLocal.generated.h"

/**
 * 
 */

#define AM

UCLASS()
class RTS_API APC_MainLocal : public APlayerController
{
	GENERATED_BODY()
	
	virtual void SetupInputComponent() override;

public:
	// UFUNCTION(BlueprintCallable)
	// void SendActionToSubscriber_MoveCameraByFollowingToMouse();
	//
	// UFUNCTION(BlueprintCallable)
	// void SendActionToSubscriber_MoveCameraByDraggingByHand();
	
	
};
