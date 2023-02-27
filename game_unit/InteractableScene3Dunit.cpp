// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableScene3Dunit.h"


// Sets default values
AInteractableScene3Dunit::AInteractableScene3Dunit()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AInteractableScene3Dunit::SetUp_current_state_in_game_logic_FromClassFields()
{
	current_state_in_game_logic.is_selectable = is_selectable;
	current_state_in_game_logic.control_is_selectable = control_is_selectable;
	current_state_in_game_logic.communication_is_selectable = communication_is_selectable;
	current_state_in_game_logic.abilities_is_it_possible_to_select_a_unit_for_magical_interaction = abilities_is_it_possible_to_select_a_unit_for_magical_interaction;
	current_state_in_game_logic.abilities_is_it_possible_to_select_a_unit_for_physical_interaction = abilities_is_it_possible_to_select_a_unit_for_physical_interaction;
	current_state_in_game_logic.view_its_state_through_the_visualization_layer_is_selectable = view_its_state_through_the_visualization_layer_is_selectable;
	current_state_in_game_logic.navigation_is_selectable = navigation_is_selectable;
	current_state_in_game_logic.is_the_object_geometrically_changeable = is_the_object_geometrically_changeable;
	current_state_in_game_logic.is_capable_of_physical_simulation = is_capable_of_physical_simulation;
}

void AInteractableScene3Dunit::SetUp_current_state_in_game_logic_FromConfigFile(FString path_to_config_)
{
	const auto ptr_to_TCHAR = TCHAR_TO_ANSI(*path_to_config_);
	
}

void AInteractableScene3Dunit::SetUp_current_state_in_game_logic_FromConfigFileByClassField()
{
}

// Called when the game starts or when spawned
void AInteractableScene3Dunit::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractableScene3Dunit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

