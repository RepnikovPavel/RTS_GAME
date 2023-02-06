// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "LoggingSystem.h"
#include "MyPaths.h"
#include "RTSCamera.generated.h"

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

	void SetSpringArmVariables(const FVector& RelLocation,const FRotator& RelRotation,
		const float ArmLength, const float CameraLagSpeed);
	
public:
	UPROPERTY(EditAnywhere)
	float SpringArmLength=1000.0f;

	UPROPERTY(EditAnywhere)
	float CameraAngle=60.0f;

	UPROPERTY(EditAnywhere)
	float CameraSpeed2D=100.0f;
	
	UPROPERTY(EditAnywhere)
	float SpringArmLagSpeed=10.0f;

	//the_area_of_sensitivity_to_camera_displacement
	UPROPERTY(EditAnywhere)
	float delta_x=0.02;

	UPROPERTY(EditAnywhere)
	float delta_y=0.02;
private:
	void SetUpPlayerController();
	APlayerController* PC_of_this_client;
private:

	void UpdateCamePos(FVector2d mouse_pos);
public:
	void AcceptMessageWithCurrentViewPortSize(FVector2d new_viewport_size);
private:
	FVector2d current_view_port_size;
private:
	void SetUpLog();
	void WriteToLog(std::string message_to_log);
	std::string LogPath;
};
