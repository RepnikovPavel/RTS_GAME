// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSCamera.h"

#include "Kismet/GameplayStatics.h"

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
	SetUpPlayerController();
	
	Super::BeginPlay();

	SetSpringArmVariables(FVector(0.0f,0.0f,50.0f),FRotator(-30.0f,0.0f,0.0f),
		SpringArmLength,SpringArmLagSpeed);

	// emulation of accepting message with viewport size
	FVector2d new_viewport_size;
	GEngine->GameViewport->GetViewportSize(new_viewport_size);
	AcceptMessageWithCurrentViewPortSize(new_viewport_size);
}

// Called every frame
void ARTSCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector2d current_mouse_pos;
	PC_of_this_client->GetMousePosition(current_mouse_pos.X,current_mouse_pos.Y);
	UpdateCamePos(current_mouse_pos);
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


void ARTSCamera::SetUpPlayerController()
{
	PC_of_this_client = UGameplayStatics::GetPlayerController(GetWorld(),0);
}

void ARTSCamera::UpdateCamePos(FVector2d mouse_pos)
{
	float pos_x = mouse_pos.X;
	float pos_y = mouse_pos.Y;
	float h_x = current_view_port_size.X;
	float h_y = current_view_port_size.Y;

	float div_x = pos_x/h_x;
	float div_y = pos_y/h_y;
	
	float world_delta_seconds= GetWorld()->GetDeltaSeconds();
	float undirectional_offset_2D = world_delta_seconds*CameraSpeed2D;  
	//mouse in left screen area
	if (div_x <= delta_x)
	{
		AddActorWorldOffset(FVector(0.0,-undirectional_offset_2D,0.0));
	}
	//mouse in right screen area
	if (div_x >= (1-delta_x))
	{
		AddActorWorldOffset(FVector(0.0,undirectional_offset_2D,0.0));
	}
	//mouse in top screen area
	if (div_y <= delta_y)
	{
		AddActorWorldOffset(FVector(undirectional_offset_2D,0.0,0.0));
	}
	//mouse in bottom screen area
	if (div_y >= (1-delta_y))
	{
		AddActorWorldOffset(FVector(-undirectional_offset_2D,0.0,0.0));
	}
}

void ARTSCamera::AcceptMessageWithCurrentViewPortSize(FVector2d new_vieport_size)
{
	current_view_port_size = new_vieport_size;
}

