// Fill out your copyright notice in the Description page of Project Settings.

#include "water_test_actor.h"

#include "../../../../../Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.33.31629/INCLUDE/string"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"


Awater_test_actor::Awater_test_actor()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled=true;
	MeshPtr = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("MeshPtr"));
	SetRootComponent(MeshPtr);
	MeshPtr->SetMobility(EComponentMobility::Static);
	MeshPtr->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	MeshPtr->SetGenerateOverlapEvents(false);
}


void Awater_test_actor::BeginPlay()
{
	Super::BeginPlay();
	
}

void Awater_test_actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto num_of_instances = MeshPtr->GetInstanceCount();
	
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString(std::to_string(num_of_instances).c_str()));	
	
}

void Awater_test_actor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	Lx = bx-ax;
	Ly=by-ay;
	Lz=bz-az;
	V = Lx*Ly*Lz;
	N = Nx*Ny*Nz;
	hx = Lx/((double)Nx);
	hy = Lx/((double)Ny);
	hz = Lx/((double)Nz);
	V_kij=V/((double)N);
	m_kij = ro*V_kij;

	ReserveMemoryForI();
	
	for(int k=0;k<Nz;k++)
	{
		for(int i=0;i<Nx;i++)
		{
			for(int j=0;j<Ny;j++)
			{
				I[k][i][j] = MeshPtr->AddInstance(FTransform(FVector(ax+i*hx,ay+j*hy,az+k*hz)));
			}
		}
	}
	
}

void Awater_test_actor::ReserveMemoryForI()
{
	I.resize(Nz);
	for (int k=0;k<Nz;k++)
	{
		I[k].resize(Nx);
		for (int i=0;i<Nx;i++)
		{
			I[k][i].resize(Ny);
		}
	}
}