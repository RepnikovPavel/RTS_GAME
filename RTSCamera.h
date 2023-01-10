// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
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
	float SpringArmLength=500.0f;

	UPROPERTY(EditAnywhere)
	float CameraAngle=60.0f;

	UPROPERTY(EditAnywhere)
	float CameraSpeed=10.0f;
	
	UPROPERTY(EditAnywhere)
	float SpringArmLagSpeed=10.0f;

	//the_area_of_sensitivity_to_camera_displacement
	UPROPERTY(EditAnywhere)
	float delta_x=0.02;

	UPROPERTY(EditAnywhere)
	float delta_y=0.02;
private:
	void UpdateCamePos(FVector2d mouse_pos,FVector2d viewport_size);

};
