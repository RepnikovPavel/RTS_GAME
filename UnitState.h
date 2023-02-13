// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"



struct UnitTypeInGameLogic
{
	bool is_selectable;
	bool control_is_selectable;
	bool communication_is_selectable;
	bool abilities_is_it_possible_to_select_a_unit_for_magical_interaction;
	bool abilities_is_it_possible_to_select_a_unit_for_physical_interaction;
	bool view_its_state_through_the_visualization_layer_is_selectable;
	bool navigation_is_selectable;
	bool is_the_object_geometrically_changeable;
	bool is_capable_of_physical_simulation;
};

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
struct PHYSICAL_ATTACK_MODIFIER_attack
{
	float physical_attack;					// add
};

struct PHYSICAL_PROTECTION_MODIFIER_crit
{
	float physical_crit_protection;			// add
};
struct PHYSICAL_PROTECTION_MODIFIER_dodge
{
	float measure_physical_dodge;			// add
};
struct PHYSICAL_PROTECTION_MODIFIER_measure_physical_protection
{
	float measure_physical_protection;		// add
};

struct MAGIC_ATTACK_MODIFIER_crit
{
	float magic_crit_mul;					// ag
	float magic_crit_pr;					// ag
};
struct MAGIC_ATTACK_MODIFIER_attack
{
	float magic_attack;						// add
};

struct MAGIC_PROTECTION_MODIFIER_measure_physical_protection
{
	float measure_magic_protection;			// add
};
struct MAGIC_PROTECTION_MODIFIER_crit
{
	float magic_crit_protection;			// add
};
struct MAGIC_PROTECTION_MODIFIER_dodge
{
	float measure_magic_dodge;				// add
};

struct MODIFIER_HP_abs_value
{
	float HP;								// add
};
struct MODIFIER_HP_mul_value
{
	float HP_mul;							// add
};

struct MODIFIER_MP_abs_value
{
	float MP;								// add
};
struct MODIFIER_MP_mul_value
{
	float MP_mul;							// add
};
struct MODIFIER_DP_abs_value
{
	float DP;								// add
};
struct MODIFIER_DPP_mul_value
{
	float DP_mul;							// add
};


struct MOVE_MODIFIER_move_speed_abs_value
{
	float move_speed;						// ag
};
struct MOVE_MODIFIER_move_speed_mul_value
{
	float move_speed_mul;					// ag
};

struct MOVE_MODIFIER_flight_speed_abs_value
{
	float flight_speed;						// ag
};
struct MOVE_MODIFIER_flight_speed_mul_value
{
	float flight_speed_mul;					// ag
};

struct MOVE_MODIFIER_soaring_speed_abs_value
{
	float soaring_speed;					// ag
};
struct MOVE_MODIFIER_soaring_speed_mul_value
{
	float soaring_speed_mul;				// ag
};

struct HEALING_MODIFIER_power_of_healing
{
	float power_of_healing;					// add
};
struct HEALING_MODIFIER_healing_mul
{
	float healing_mul;						// ag
};

struct HEALING_MODIFIER_power_of_regeneration
{
	float power_of_regeneration;			// add
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
	
	void SendAttack()
	{
		
	};
	void AcceptAttack()
	{};
};
