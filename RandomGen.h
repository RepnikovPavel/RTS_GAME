// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <array>
#include "CoreMinimal.h"


class RandomEventGenerator
{
	int N = 100;
	int current_pos = 0;
	std::array<float,100> mixed_numbers{79, 78, 46, 17, 60, 80, 42, 38, 93, 26, 4, 100, 99, 71, 86, 15, 39, 9, 76, 88,
		94, 7, 16, 25, 37, 35, 14, 36, 2, 73, 74, 33, 41, 64, 61, 75, 30, 27, 45, 47, 48, 21, 50, 68, 63, 51, 24, 22,
		10, 40, 19, 70, 87, 5, 23, 1, 34, 29, 81, 49, 32, 95, 56, 11, 67, 28, 52, 91, 58, 98, 20, 77, 83, 43, 66, 96,
		18, 84, 6, 72, 82, 97, 65, 57, 69, 54, 44, 13, 55, 53, 31, 12, 89, 62, 59, 8, 90, 92, 3, 85}; 
	float probability_of_an_event_as_a_percentage_;
	void SetUpGenerator(float probability_of_an_event_as_a_percentage)
	{
		probability_of_an_event_as_a_percentage_ = probability_of_an_event_as_a_percentage;
	}
	int GetNext()
	{
		int pos = current_pos;
		if (current_pos!=(N-1))
		{
			current_pos+=1;
		}
		else
		{
			current_pos=0;
		}
		return mixed_numbers[pos];
	};
public:
	bool Try_to_generate_a_random_event()
	{
		if ( GetNext() >= probability_of_an_event_as_a_percentage_ )
		{
			return false;
		}
		else
		{
			return true;
		}
	}
};


class RTS_API RandomGen
{
public:
	RandomGen();
	~RandomGen();
};
