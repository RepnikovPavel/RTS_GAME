// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSCamera.h"

#include <fstream>
#include <chrono>
#include "ActionAndAxisMappings.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ARTSCamera::ARTSCamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UserInputState= RTSCameraState::the_player_cannot_control;
	CameraMovementLogicState = RTSCameraMovementLogicState::following_the_cursor;
	
	SpringArmComponentPtr = CreateDefaultSubobject<USpringArmComponent>("SpringArm",true);
	SpringArmComponentPtr->SetupAttachment(GetRootComponent());

	CameraComponentPtr= CreateDefaultSubobject<UCameraComponent>("Camera",true);
	CameraComponentPtr->SetupAttachment(SpringArmComponentPtr);

	SpringArmComponentPtr->bDoCollisionTest = false;
}

// Called when the game starts or when spawned
void ARTSCamera::BeginPlay()
{
	// SetUpLog();
	
	Super::BeginPlay();

	SetSpringArmVariables(FVector(0.0f,0.0f,50.0f),FRotator(-CameraAngle,0.0f,0.0f),
		SpringArmLength,SpringArmLagSpeed);

	// emulation of accepting message with viewport size
	FVector2d new_viewport_size;
	// GEngine->GameViewport->GetViewportSize(new_viewport_size);
	new_viewport_size.X = GSystemResolution.ResX;
	new_viewport_size.Y = GSystemResolution.ResY;
	AcceptMessageWithCurrentViewPortSize(new_viewport_size);
	
}

// Called every frame
void ARTSCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// FString printed_string;
	// GEngine->AddOnScreenDebugMessage(-1,GetWorld()->DeltaTimeSeconds,FColor::Green,printed_string);
	if (UserInputState==RTSCameraState::the_player_can_control)
	{
		FVector2d current_mouse_pos;
		PC_of_this_client->GetMousePosition(current_mouse_pos.X,current_mouse_pos.Y);
		UpdateCurrent_actor_forward_vetor_XY_projection();
		if (CameraMovementLogicState==RTSCameraMovementLogicState::following_the_cursor)
		{
			UpdateCamePos_following_the_cursor(current_mouse_pos);	
		}
		else if (CameraMovementLogicState==RTSCameraMovementLogicState::dragging_by_hand)
		{
			FVector2d delta_mouse_pos = current_mouse_pos - last_pos_of_mouse_cursor_in_screen;
			UpdateCamePos_dragging_by_hand(delta_mouse_pos,current_mouse_pos);
			last_pos_of_mouse_cursor_in_screen = current_mouse_pos;
		}
		
	}
	
}

// Called to bind functionality to input
void ARTSCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction(M_ACM_MoveCameraByHand,EInputEvent::IE_Pressed,this,&ARTSCamera::Switch_CameraMovementStateTo_dragging_by_hand);
	PlayerInputComponent->BindAction(M_ACM_MoveCameraByHand,EInputEvent::IE_Released,this,&ARTSCamera::Switch_CameraMovementStateTo_following_the_cursor);
	
}

void ARTSCamera::SetSpringArmVariables(const FVector& LocalLocation, const FRotator& LocalRotation, const float ArmLength,
	const float CameraLagSpeed)
{
	SpringArmComponentPtr->AddLocalRotation(LocalRotation);
	SpringArmComponentPtr->AddLocalOffset(LocalLocation);
	SpringArmComponentPtr->TargetArmLength = ArmLength;
	if (CameraLagSpeed != 0.0)
	{
		SpringArmComponentPtr->bEnableCameraLag = true;
		SpringArmComponentPtr->CameraLagSpeed= CameraLagSpeed;
	}
	
}

void ARTSCamera::SetPlayerController(APlayerController* new_pc)
{
	PC_of_this_client = new_pc;
}

void ARTSCamera::UpdateCurrent_actor_forward_vetor_XY_projection()
{
	FVector current_root_fv = GetActorForwardVector();
	n_actor_forward_vetor_XY_projection_word_coords.X = current_root_fv.X;
	n_actor_forward_vetor_XY_projection_word_coords.Y = current_root_fv.Y;
}

void ARTSCamera::UpdateCamePos_following_the_cursor(FVector2d mouse_pos)
{
	float pos_x = mouse_pos.X;
	float pos_y = mouse_pos.Y;
	float h_x = current_view_port_size.X;
	float h_y = current_view_port_size.Y;

	if (h_x==0.0 || h_y ==0.0)
	{
		return;
	}
	
	if ((pos_x < 0.0 || pos_x > h_x) || ( pos_y < 0.0 || pos_y > h_y))
	{
		return;
	}
	
	float div_x = pos_x/h_x;
	float div_y = pos_y/h_y;
	
	float world_delta_seconds= GetWorld()->GetDeltaSeconds();
	float undirectional_offset_2D = world_delta_seconds*CameraSpeed2D;
	
	FVector2d dir = n_actor_forward_vetor_XY_projection_word_coords;
	dir*=undirectional_offset_2D;
	//mouse in left screen area
	if (div_x <= delta_x)
	{
		FVector2d target_dir = dir.GetRotated(270.0);
		AddActorWorldOffset(FVector(target_dir.X,target_dir.Y,0.0));
	}
	//mouse in right screen area
	if (div_x >= (1-delta_x))
	{
		FVector2d target_dir = dir.GetRotated(90.0);
		AddActorWorldOffset(FVector(target_dir.X,target_dir.Y,0.0));
	}
	//mouse in top screen area
	if (div_y <= delta_y)
	{
		AddActorWorldOffset(FVector(dir.X,dir.Y,0.0));
	}
	//mouse in bottom screen area
	if (div_y >= (1-delta_y))
	{
		FVector2d target_dir = dir.GetRotated(180.0);
		AddActorWorldOffset(FVector(target_dir.X,target_dir.Y,0.0));
	}
}

void ARTSCamera::UpdateCamePos_dragging_by_hand(FVector2d delta_mouse_pos,FVector2d mouse_pos)
{
	float pos_x = mouse_pos.X;
	float pos_y = mouse_pos.Y;

	float h_x = current_view_port_size.X;
	float h_y = current_view_port_size.Y;
	if ((pos_x < 0.0 || pos_x > h_x) || ( pos_y < 0.0 || pos_y > h_y))
	{
		return;
	}
	
	if (h_x==0.0 || h_y ==0.0)
	{
		return;
	}

	float step_x = delta_mouse_pos.X;
	float step_y = delta_mouse_pos.Y;
	
	float div_x = step_x/h_x;
	float div_y = step_y/h_y;

	float output_delta_along_per_to_forward_dir = -div_x*dragging_by_hand_step_multiplier;
	float output_delta_along_forward_dir = div_y*dragging_by_hand_step_multiplier;
	
	FVector2d dir = n_actor_forward_vetor_XY_projection_word_coords;
	FVector2d dir_per = dir.GetRotated(90.0);
	dir*=output_delta_along_forward_dir;
	dir_per*=output_delta_along_per_to_forward_dir;
	FVector2d final_step_of_actor_XY = dir+dir_per;
	FVector3d final_step_of_actor(final_step_of_actor_XY.X,final_step_of_actor_XY.Y,0.0);
	AddActorWorldOffset(final_step_of_actor);
}

void ARTSCamera::AcceptMessageWithCurrentViewPortSize(FVector2d new_viewport_size)
{
	current_view_port_size = new_viewport_size;
}

void ARTSCamera::SetUpLog()
{
	LogPath = std::string(M_LOG_PATH_RTS_CAMERA_CLASS);
	auto start_time = std::chrono::system_clock::now();
	std::time_t time_to_log_file = std::chrono::system_clock::to_time_t(start_time);
	std::ofstream _EventLog(LogPath,std::ios_base::trunc);
	char time_str[26];
	ctime_s(time_str,sizeof(time_str),&time_to_log_file);
	_EventLog << time_str << std::endl;
	_EventLog.close();
}

void ARTSCamera::WriteToLog(std::string message_to_log)
{
	std::ofstream _EventLog(LogPath,std::ios_base::app);
	_EventLog << message_to_log << std::endl;
	_EventLog.close();
}

void ARTSCamera::SwitchTo_the_player_can_control_camera()
{
	UserInputState = RTSCameraState::the_player_can_control;
}

void ARTSCamera::SwitchTo_the_player_cannot_control_camera()
{
	UserInputState = RTSCameraState::the_player_cannot_control;
}

void ARTSCamera::Switch_CameraMovementStateTo_following_the_cursor()
{
	CameraMovementLogicState = RTSCameraMovementLogicState::following_the_cursor;
}

void ARTSCamera::Switch_CameraMovementStateTo_dragging_by_hand()
{
	CameraMovementLogicState = RTSCameraMovementLogicState::dragging_by_hand;
	PC_of_this_client->GetMousePosition(last_pos_of_mouse_cursor_in_screen.X,last_pos_of_mouse_cursor_in_screen.Y);
}


