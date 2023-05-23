// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Network/ClientNetProxy.h"
#include "LC_ClientNetwork.generated.h"

UCLASS()
class RTS_API ALC_ClientNetwork : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALC_ClientNetwork();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
private:
	ClientNetProxy NetProxy;
public:
	UFUNCTION(BlueprintCallable)
	void MakeConnection(const FString fstring);

	UFUNCTION(BlueprintCallable)
	void SendMessage(const FString message);

	UFUNCTION(BlueprintCallable)
	void DestroyConnection();
	
};
