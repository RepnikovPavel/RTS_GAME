// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"



struct CoreState
{
	float physical_attack;					// add
	float magic_attack;						// add
	float measure_physical_protection;		// add
	float measure_magic_protection;			// add
	
	float measure_magic_accuracy;			// add
	float measure_physical_accuracy;		// add
	
	float measure_physical_dodge;			// add
	float measure_magic_dodge;				// add
	
	float HP;								// ag
	float MP;								// ag
	float DP;								// ag
	float speed_HP_regeneration;			// ag
	float speed_MP_regeneration;			// ag
	
	float move_speed;						// ag
	float flight_speed;						// ag
	float soaring_speed;					// ag

	float healing_mul;						// ag
	float power_of_healing;					// add
	float power_of_regeneration;			// add
	
};

struct PHYSICAL_ATTACK_MODIFIER_crit
{
	float physical_crit_mul;				// ag
	float physical_crit_pr;					// ag
};
struct STATIC_PHYSICAL_ATTACK_MODIFIER_attack
{
	float physical_attack;					// add
};

struct STATIC_PHYSICAL_PROTECTION_MODIFIER_crit
{
	float physical_crit_protection;			// add
};
struct PHYSICAL_PROTECTION_MODIFIER_dodge
{
	float measure_physical_dodge;			// add
};
struct STATIC_PHYSICAL_PROTECTION_MODIFIER_measure_physical_protection
{
	float measure_physical_protection;		// add
};

struct MAGIC_ATTACK_MODIFIER_crit
{
	float magic_crit_mul;					// ag
	float magic_crit_pr;					// ag
};
struct STATIC_MAGIC_ATTACK_MODIFIER_attack
{
	float magic_attack;					// add
};

struct STATIC_MAGIC_PROTECTION_MODIFIER_measure_physical_protection
{
	float measure_magic_protection;		// add
};
struct STATIC_MAGIC_PROTECTION_MODIFIER_crit
{
	float magic_crit_protection;			// add
};
struct MAGIC_PROTECTION_MODIFIER_dodge
{
	float measure_magic_dodge;			// add
};


class RTS_API UnitState
{
public:
	UnitState();
	~UnitState();
	CoreState WhiteState;
	CoreState GreenState;
	CoreState CurrentState;
	// items vector
	// abilities vector
	// auras vector
	//
	
	
	void SendAttack()
	{
		
	};
	void AcceptAttack()
	{};
};
