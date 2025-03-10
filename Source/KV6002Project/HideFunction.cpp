// Fill out your copyright notice in the Description page of Project Settings.


#include "HideFunction.h"

// Sets default values for this component's properties
UHideFunction::UHideFunction()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHideFunction::BeginPlay()
{
	Super::BeginPlay();
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	InitialiseObject();
	
	
}


// Called every frame
void UHideFunction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(CollisionBox->IsOverlappingActor(ActorThatOpens) && InUse == false)
	{
		//Hide(DeltaTime);
		InUse=true;
	}

}

void UHideFunction::InitialiseObject()
{
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	InUse = false;

	GetOwner()->GetComponents(ListOfMeshes);
	GetOwner()->GetComponents(ListOfBoxes);

	if(MeshTarget)
	{
		FString name = MeshTarget->GetName();
	}

	for(int i = 0;i<ListOfMeshes.Num();i++)
	{
		FString MeshName = ListOfMeshes[i]->GetName();
		UE_LOG(LogTemp, Warning, TEXT("List of meshes include: %s"), *(MeshName));
	}

	for(int i = 0;i<ListOfBoxes.Num();i++)
	{
		FString SceneName = ListOfBoxes[i]->GetName();
		UE_LOG(LogTemp, Warning, TEXT("List of meshes include: %s"), *(SceneName));
		if(SceneName==FString("Box"))
		{
			CollisionBox=ListOfBoxes[i];
		}
	}
}

void UHideFunction::Hide(float DeltaTime)
{
	if(MeshTarget&&ListOfMeshes[0])
	{
		FString name = MeshTarget->GetName();
		for(int i = 0;i<2;i++)
		{
			name = ListOfMeshes[i]->GetStaticMesh()->GetName();
			FString ComparisonName = MeshTarget->GetName();
			if(name==ComparisonName)
			{
				UE_LOG(LogTemp,Warning, TEXT("This has attached %s"), *name);
				InitialLocation = ListOfMeshes[i]->GetRelativeLocation();
				NewX = InitialLocation.X + TranslatorX;
				NewY = InitialLocation.Y + TranslatorY;
				NewZ = InitialLocation.Z + TranslatorZ;
				FVector TargetLocation(NewX, NewY, NewZ);;
				UE_LOG(LogTemp,Warning, TEXT("Location of mesh is : %f, %f, %f"), NewX, NewY, NewZ);
	
				ListOfMeshes[i]->SetRelativeLocation(TargetLocation);
			}
		}
	} 
}
/*if(CollisionBox->IsOverlappingActor(ActorThatOpens))
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Overlapping"));
	}
	*/