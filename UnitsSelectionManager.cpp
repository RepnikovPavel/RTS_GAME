// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitsSelectionManager.h"
#include "ActionAndAxisMappings.h"

// Sets default values for this component's properties
UUnitsSelectionManager::UUnitsSelectionManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UUnitsSelectionManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UUnitsSelectionManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UUnitsSelectionManager::Select_all_the_selected_units_in_the_rectangle(FVector2d mouse_start_pos,
	FVector2d mouse_end_pos)
{
	
}

