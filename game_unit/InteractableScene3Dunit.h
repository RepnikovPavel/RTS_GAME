// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../MyPaths.h"
#include "UnitState.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableScene3Dunit.generated.h"

UCLASS()
class RTS_API AInteractableScene3Dunit : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInteractableScene3Dunit();

public:
	void SetUp_current_state_in_game_logic_FromClassFields();
	void SetUp_current_state_in_game_logic_FromConfigFile(FString path_to_config_);
	void SetUp_current_state_in_game_logic_FromConfigFileByClassField();
	
private:
	UnitDescriptionForInteractionInGameLogic current_state_in_game_logic;
	UPROPERTY(EditAnywhere,Category="UnitDescriptionForInteractionInGameLogic")
	bool is_selectable;
	UPROPERTY(EditAnywhere,Category="UnitDescriptionForInteractionInGameLogic")
	bool control_is_selectable;
	UPROPERTY(EditAnywhere,Category="UnitDescriptionForInteractionInGameLogic")
	bool communication_is_selectable;
	UPROPERTY(EditAnywhere,Category="UnitDescriptionForInteractionInGameLogic")
	bool abilities_is_it_possible_to_select_a_unit_for_magical_interaction;
	UPROPERTY(EditAnywhere,Category="UnitDescriptionForInteractionInGameLogic")
	bool abilities_is_it_possible_to_select_a_unit_for_physical_interaction;
	UPROPERTY(EditAnywhere,Category="UnitDescriptionForInteractionInGameLogic")
	bool view_its_state_through_the_visualization_layer_is_selectable;
	UPROPERTY(EditAnywhere,Category="UnitDescriptionForInteractionInGameLogic")
	bool navigation_is_selectable;
	UPROPERTY(EditAnywhere,Category="UnitDescriptionForInteractionInGameLogic")
	bool is_the_object_geometrically_changeable;
	UPROPERTY(EditAnywhere,Category="UnitDescriptionForInteractionInGameLogic")
	bool is_capable_of_physical_simulation;
	UPROPERTY(EditAnywhere,Category="UnitDescriptionForInteractionInGameLogic")
	FString path_to_config;
private:
	// void LoadConfig_current_state_in_game_logic();

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	
};
