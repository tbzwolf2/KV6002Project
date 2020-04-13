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
	FString name = MeshTarget->GetName();
	GetOwner()->GetComponents(ListOfMeshes);
	if(ListOfMeshes[0])
	{
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
				UE_LOG(LogTemp,Warning, TEXT("Location of mesh is : %f, %f, %f"), NewX, NewY, NewZ);
				//NewY = ListOfMeshes[i]->y + TranslatorY;
				//NewZ = ListOfMeshes[i]->z + TranslatorZ;
				ListOfMeshes[i]->SetRelativeLocation(FVector(NewX, NewY, NewZ));
			}
		}
	} 

	
}


// Called every frame
void UHideFunction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

