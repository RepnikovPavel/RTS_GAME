// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSCamera.h"

#define M_AXM_MoveCameraX			"MoveCameraX"
#define M_AXM_MoveCameraY			"MoveCameraY"


// Sets default values
ARTSCamera::ARTSCamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	SpringArmComponentPtr = CreateDefaultSubobject<USpringArmComponent>("SpringArm",true);
	SpringArmComponentPtr->SetupAttachment(GetRootComponent());

	CameraComponentPtr= CreateDefaultSubobject<UCameraComponent>("Camera",true);
	CameraComponentPtr->SetupAttachment(SpringArmComponentPtr);
	
}

// Called when the game starts or when spawned
void ARTSCamera::BeginPlay()
{
	Super::BeginPlay();

	SetSpringArmVariables(FVector(0.0f,0.0f,50.0f),FRotator(-30.0f,0.0f,0.0f),
		SpringArmLength,SpringArmLagSpeed);
	
}

// Called every frame
void ARTSCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARTSCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ARTSCamera::SetSpringArmVariables(const FVector& RelLocation, const FRotator& RelRotation, const float ArmLength,
	const float CameraLagSpeed)
{
	SpringArmComponentPtr->SetRelativeLocationAndRotation(RelLocation,RelRotation);
	SpringArmComponentPtr->TargetArmLength = ArmLength;
	if (CameraLagSpeed != 0.0)
	{
		SpringArmComponentPtr->bEnableCameraLag = true;
		SpringArmComponentPtr->CameraLagSpeed= CameraLagSpeed;
	}
}


void ARTSCamera::UpdateCamePos(FVector2d mouse_pos, FVector2d viewport_size)
{
	float pos_x = mouse_pos.X;
	float pos_y = mouse_pos.Y;
	float h_x = viewport_size.X;
	float h_y = viewport_size.Y;

	float div_x = pos_x/h_x;
	float div_y = pos_y/h_y;

	//mouse in left screen area
	if (div_x <= delta_x)
	{
		
	}
	//mouse in right screen area
	if (div_x >= (1-delta_x))
	{
		
	}
	//mouse in top screen area
	if (div_y <= delta_y)
	{
		
	}
	//mouse in bottom screen area
	if (div_y >= (1-delta_y))
	{
		
	}
	
	
	
	
}

