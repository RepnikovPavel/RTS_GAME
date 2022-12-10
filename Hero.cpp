// Fill out your copyright notice in the Description page of Project Settings.


#include "Hero.h"



class UnitState
{

	// health
	float base_HP_regeneration;
	float base_MP_regeneration;
	float base_acceleration_HP_regeneration;
	float base_acceleration_MP_regeneration;
	// attack 
	float base_HP;
	float base_MP;
	float base_DP;
	float base_movespeed;
	float base_attack_speed;
	float base_interval_between_attacks;
	float base_physical_attack;
	float base_physical_accuracy;
	float base_physical_crit;
	float base_physical_crit_damage;
	float base_magic_attack;
	float base_magic_accuracy;
	float base_magic_crit;
	float base_magic_crit_damage;
	float base_power_of_healing;
	// protection
	float base_physical_protection;
	float base_physical_crit_protection;
	float base_physical_dodge;
	float base_magic_protection;
	float base_magic_crit_protection;
	float base_magic_dodge;
	float base_parrying;
	float base_shield_block;
};



// Sets default values
AHero::AHero()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHero::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

