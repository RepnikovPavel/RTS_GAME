// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */


struct CoreState
{
	float HP;
	float MP;
	float DP;
	float HP_regeneration;
	float MP_regeneration;
	float speed_HP_regeneration;
	float speed_MP_regeneration;
	
	float move_speed;
	float flight_speed;
	float soaring_speed;
	
	float attack_speed;
	float interval_between_attacks;
	float physical_attack;
	float physical_accuracy;
	float physical_crit_pr;
	float physical_crit_mul;
	float magic_attack;
	float magic_accuracy;
	float magic_crit;
	float magic_crit_damage;
	float power_of_healing;
	
	float physical_protection;
	float physical_crit_protection;
	float physical_dodge;
	float magic_protection;
	float magic_crit_protection;
	float magic_dodge;
};

class RTS_API UnitState
{
public:
	UnitState();
	~UnitState();
	CoreState WhiteState;
	CoreState GreenState;
	CoreState CurrentState;
};
