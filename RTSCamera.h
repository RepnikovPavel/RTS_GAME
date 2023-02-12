// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "LoggingSystem.h"
#include "MyPaths.h"
#include "ActionAndAxisMappings.h"
#include "RTSCamera.generated.h"

enum RTSCameraState
{
	the_player_can_control,
	the_player_cannot_control
};
enum RTSCameraMovementLogicState
{
	following_the_cursor,
	dragging_by_hand
};

UCLASS()
class RTS_API ARTSCamera : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARTSCamera();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComponentPtr;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponentPtr; 

	void SetSpringArmVariables(const FVector& LocalLocation,const FRotator& LocalRotation,
		const float ArmLength, const float CameraLagSpeed);
	
public:
	UPROPERTY(EditAnywhere)
	float SpringArmLength=1000.0f;

	UPROPERTY(EditAnywhere)
	float CameraAngle=60.0f;

	UPROPERTY(EditAnywhere)
	float CameraSpeed2D=500.0f;
	
	UPROPERTY(EditAnywhere)
	float SpringArmLagSpeed=10.0f;

	//the_area_of_sensitivity_to_camera_displacement
	UPROPERTY(EditAnywhere)
	float delta_x=0.02;

	UPROPERTY(EditAnywhere)
	float delta_y=0.02;
public:
	UFUNCTION(BlueprintCallable)
	void SetPlayerController(APlayerController* new_pc);
private:
	APlayerController* PC_of_this_client;

private:
	void UpdateCamePos_following_the_cursor(FVector2d mouse_pos);

	
	void UpdateCamePos_dragging_by_hand(FVector2d delta_mouse_pos,FVector2d mouse_pos);
	FVector2d last_pos_of_mouse_cursor_in_screen;
	FVector2d n_actor_forward_vetor_XY_projection_word_coords;
	void UpdateCurrent_actor_forward_vetor_XY_projection();
public:
	UPROPERTY(BlueprintReadWrite)
	float dragging_by_hand_step_multiplier=1550.0f;


	
public:
	UPROPERTY(BlueprintReadWrite)
	float camera_movement_mul_dragging_by_hand = 10.0f;
	
public:
	void AcceptMessageWithCurrentViewPortSize(FVector2d new_viewport_size);
private:
	FVector2d current_view_port_size;
private:
	void SetUpLog();
	void WriteToLog(std::string message_to_log);
	std::string LogPath;
private:
	
	RTSCameraState UserInputState;

	// state switches of the user input state machine
public:
	UFUNCTION(BlueprintCallable)
	void SwitchTo_the_player_can_control_camera();
	
	UFUNCTION(BlueprintCallable)
	void SwitchTo_the_player_cannot_control_camera();

private:
	RTSCameraMovementLogicState CameraMovementLogicState;

	void Switch_CameraMovementStateTo_following_the_cursor();
	void Switch_CameraMovementStateTo_dragging_by_hand();
	
};




