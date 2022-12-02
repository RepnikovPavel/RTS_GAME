// Fill out your copyright notice in the Description page of Project Settings.


#include "WallSpline.h"
#include "Components/SplineComponent.h"
#include "Components/StaticMeshComponent.h"
#include <fstream>
#include <chrono>
#include <time.h>
#include <ThirdParty/Imath/Deploy/Imath-3.1.3/include/Imath/ImathQuat.h>

#include "TableOfContents.h"
#include "LoggingSystem.h"
#include "SupportFunctionality.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/SkeletalMesh.h"


// Sets default values
AWallSpline::AWallSpline()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	spline_ptr = CreateDefaultSubobject<USplineComponent>("spline");
	spline_ptr->SetupAttachment(GetRootComponent());
	
	// loading assets
	number_of_walls=14;
	paths_to_walls =
	{
		{0,"/Game/landscape/walls/style1/w11/w11"},
		{1,"/Game/landscape/walls/style1/w12/w12"},
		{2,"/Game/landscape/walls/style1/w13/w13"},
		{3,"/Game/landscape/walls/style1/w14/w14"},
		{4,"/Game/landscape/walls/style1/w15/w15"},
		{5,"/Game/landscape/walls/style1/w16/w16"},
		{6,"/Game/landscape/walls/style1/w17/w17"},
		{7,"/Game/landscape/walls/style1/w18/w18"},
		{8,"/Game/landscape/walls/style1/w19/w19"},
		{9,"/Game/landscape/walls/style1/w110/w110"},
		{10,"/Game/landscape/walls/style1/w111/w111"},
		{11,"/Game/landscape/walls/style1/w112/w112"},
		{12,"/Game/landscape/walls/style1/w113/w113"},
		{13,"/Game/landscape/walls/style1/w114/w114"}
	};
	linear_sizes_of_walls =
	{
		{0,FVector(49,504,263)},
		{1,FVector(49,160,262)},
		{2,FVector(102,102,379)},
		{3,FVector(203,212,746)},
		{4,FVector(61,650,262)},
		{5,FVector(61,650,262)},
		{6,FVector(61,325,262)},
		{7,FVector(61,82,262)},
		{8,FVector(61,244,262)},
		{9,FVector(61,82,262)},
		{10,FVector(137,569,672)},
		{11,FVector(180,651,672)},
		{12,FVector(180,408,672)},
		{13,FVector(180,193,672)}
	};
	// column. column for turning. wall. types
	types_of_walls =
	{
		{0,"wall_for_turning"},
		{1,"wall_for_turning"},
		{2,"column"},
		{3,"column"},
		{4,"wall"},
		{5,"wall"},
		{6,"wall"},
		{7,"wall"},
		{8,"wall"},
		{9,"wall"},
		{10,"wall_for_turning"},
		{11,"part_of_wall"},
		{12,"end_of_wall"},
		{13,"end_of_wall"}
	};
	for (int i=0;i<number_of_walls;i++)
	{
		Loader<UStaticMesh> Loader(paths_to_walls[i]);
		preloaded_walls.insert(std::pair(i,Loader.GetDataPtr()));
	}

	for(auto it = types_of_walls.cbegin(); it != types_of_walls.cend(); it++)
	{
		walls_indicies[it->second].push_back(it->first);
	}
	
	number_of_ribbons=16;
	paths_to_ribbons=
	{
		{0,"/Game/landscape/walls/style1/r11/r11"},
		{1,"/Game/landscape/walls/style1/r12/r12"},
		{2,"/Game/landscape/walls/style1/r13/r13"},
		{3,"/Game/landscape/walls/style1/r14/r14"},
		{4,"/Game/landscape/walls/style1/r15/r15"},
		{5,"/Game/landscape/walls/style1/r16/r16"},
		{6,"/Game/landscape/walls/style1/r17/r17"},
		{7,"/Game/landscape/walls/style1/r18/r18"},
		{8,"/Game/landscape/walls/style1/r19/r19"},
		{9,"/Game/landscape/walls/style1/r110/r110"},
		{10,"/Game/landscape/walls/style1/r111/r111"},
		{11,"/Game/landscape/walls/style1/r112/r112"},
		{12,"/Game/landscape/walls/style1/r113/r113"},
		{13,"/Game/landscape/walls/style1/r114/r114"},
		{14,"/Game/landscape/walls/style1/r115/r115"},
		{15,"/Game/landscape/walls/style1/r116/r116"}
	};
	linear_sizes_of_ribbons =
	{
		{0,FVector(104,461,274)},
		{1,FVector(101,122,262)},
		{2,FVector(97,174,262)},
		{3,FVector(104,461,262)},
		{4,FVector(104,461,262)},
		{5,FVector(80,280,262)},
		{6,FVector(96,150,262)},
		{7,FVector(97,140,261)},
		{8,FVector(110,493,262)},
		{9,FVector(104,493,262)},
		{10,FVector(86,386,262)},
		{11,FVector(97,675,262)},
		{12,FVector(68,606,262)},
		{13,FVector(96,675,262)},
		{14,FVector(96,212,262)},
		{15,FVector(91,268,262)},
	};
	
	for (int i=0;i<number_of_ribbons;i++)
	{
		Loader<UStaticMesh> Loader(paths_to_ribbons[i]);
		preloaded_ribbons.insert(std::pair(i,Loader.GetDataPtr()));
	}
	
}

// Called when the game starts or when spawned
void AWallSpline::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWallSpline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWallSpline::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	std::vector<FVector> spline_local_points(spline_ptr->GetNumberOfSplinePoints());
	for (int i =0 ; i < spline_local_points.size(); i++)
	{
		spline_local_points[i] = spline_ptr->GetLocationAtSplinePoint(i,ESplineCoordinateSpace::Local);
	}

	gen_for_walls_selection = std::mt19937(rd_for_walls_selection());
	for(auto it = walls_indicies.cbegin();it!=walls_indicies.cend();it++)
	{
		distrs_for_walls_selection.insert(std::pair(it->first,std::uniform_int_distribution<>(0,it->second.size())));
	}

	for (int i=0; i < (spline_local_points.size()-1);i++)
	{
		UStaticMeshComponent* static_mesh1 =  NewObject<UStaticMeshComponent>(this,UStaticMeshComponent::StaticClass());
		static_mesh1->RegisterComponentWithWorld(GetWorld());
		static_mesh1->AttachToComponent(spline_ptr,FAttachmentTransformRules::KeepRelativeTransform);

		FVector direction = spline_local_points[i+1]-spline_local_points[i];
		float norm = direction.Size();
		direction = direction/norm;
		
		
		int index_of_column = select_random_wall_by_type("column");
		if (preloaded_walls[index_of_column])
		{
			static_mesh1->SetStaticMesh(preloaded_walls[index_of_column]);
		}
		static_mesh1->SetRelativeLocation(spline_local_points[i]);
		static_mesh1->SetRelativeRotation(FRotator(0,0,0));

		UStaticMeshComponent* static_mesh2 =  NewObject<UStaticMeshComponent>(this,UStaticMeshComponent::StaticClass());
		static_mesh2->RegisterComponentWithWorld(GetWorld());
		static_mesh2->AttachToComponent(spline_ptr,FAttachmentTransformRules::KeepRelativeTransform);
		int index_of_wall = select_random_wall_by_type("wall");
		if (preloaded_walls[index_of_wall])
		{
			static_mesh2->SetStaticMesh(preloaded_walls[index_of_wall]);
		}
		static_mesh2->SetRelativeLocation(spline_local_points[i]);
		static_mesh2->SetRelativeRotation(FRotator(0,0,0));
		
		
	}
	
}

int AWallSpline::select_random_wall_by_type(std::string type)
{
	int random_index = distrs_for_walls_selection[type](gen_for_walls_selection);
	int index_of_wall =  walls_indicies[type][random_index];
	return index_of_wall;
}
