// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include <map>
#include <random>
#include "Components/SplineMeshComponent.h"
#include "WallSpline.generated.h"

UCLASS()
class RTS_API AWallSpline : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWallSpline();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	std::map<int, FString> paths_to_walls;
	std::map<int, FVector> linear_sizes_of_walls;
	std::map<int, std::string> types_of_walls;
	std::map<std::string,std::vector<int>> walls_indicies;

	std::random_device rd_for_walls_selection;
	std::mt19937 gen_for_walls_selection;
	std::map<std::string,std::uniform_int_distribution<>> distrs_for_walls_selection;
	int select_random_wall_by_type(std::string type);
	
	int number_of_walls;
	std::map<int, FString> paths_to_ribbons;
	std::map<int, FVector> linear_sizes_of_ribbons;
	int number_of_ribbons;
	
public:
	UPROPERTY(EditAnywhere)
	USplineComponent* spline_ptr;

	UPROPERTY(EditAnywhere,Category="meshes")
	TMap<int, UStaticMesh*> map_with_walls;

	UPROPERTY(EditAnywhere,Category="meshes")
	TMap<int, UStaticMesh*> map_with_ribbons;

public:
	virtual void OnConstruction(const FTransform& Transform) override;
	
};


