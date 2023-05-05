// Fill out your copyright notice in the Description page of Project Settings.


#include "TestMathActor.h"
#include "MathLib/Matrix.h"
#include <string>
#include "Containers/UnrealString.h"

// Sets default values
ATestMathActor::ATestMathActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestMathActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATestMathActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	static constexpr int m_ = 10;
	Matrix<double, m_, m_> test_matrix({ .init_value = 1.0 });
	auto value = test_matrix[1][1];
	
	std::ostringstream strs;
	strs << value;
	std::string output_str = strs.str();
	
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString(output_str.c_str()));	

}

