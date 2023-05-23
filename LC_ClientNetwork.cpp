// Fill out your copyright notice in the Description page of Project Settings.


#include "LC_ClientNetwork.h"

// Sets default values
ALC_ClientNetwork::ALC_ClientNetwork()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALC_ClientNetwork::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALC_ClientNetwork::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALC_ClientNetwork::MakeConnection(const FString fstring)
{
	NetProxy.OpenChannel(fstring);
}

void ALC_ClientNetwork::SendMessage(const FString message)
{
	NetProxy.WriteToChannel(TCHAR_TO_ANSI(*message));
}

void ALC_ClientNetwork::DestroyConnection()
{
	NetProxy.CloseChannel();
}

