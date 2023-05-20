// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <vector>
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "water_test_actor.generated.h"


UCLASS()
class RTS_API Awater_test_actor : public AActor
{
	GENERATED_BODY()

public:

	Awater_test_actor();

public:
	UPROPERTY(EditAnywhere)
	int Nx=1;
	UPROPERTY(EditAnywhere)
	int Ny=1;
	UPROPERTY(EditAnywhere)
	int Nz=1;
	UPROPERTY(EditAnywhere)
	int N_surf=5;
	UPROPERTY(EditAnywhere)
	double ax=-100.0;
	UPROPERTY(EditAnywhere)
	double bx=100.0;
	UPROPERTY(EditAnywhere)
	double ay=-100.0;
	UPROPERTY(EditAnywhere)
	double by=-100.0;
	UPROPERTY(EditAnywhere)
	double az=-100.0;
	UPROPERTY(EditAnywhere)
	double bz=-100.0;
	UPROPERTY(EditAnywhere)
	double ro=1000.0;

	UPROPERTY(EditAnywhere)
	double StartCullDistance=0.0;
	UPROPERTY(EditAnywhere)  
	double EndCullDistance=10000.0;


public:
	UPROPERTY(VisibleAnywhere)
	UInstancedStaticMeshComponent* MeshPtr;
	
protected:

	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	virtual void OnConstruction(const FTransform& Transform) override;

	
private:
	std::vector<std::vector<std::vector<int>>> I;
	void ReserveMemoryForI();
private:
	double Lx;
	double Ly;
	double Lz;
	double hx;
	double hy;
	double hz;
	double V;
	int N;
	double V_kij;
	double m_kij;
};
