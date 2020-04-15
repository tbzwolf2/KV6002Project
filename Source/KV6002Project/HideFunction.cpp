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

	
	
}


// Called every frame
void UHideFunction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FVector StartViewPoint;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT StartViewPoint, OUT PlayerViewPointRotation);
	
	FVector EndPoint = StartViewPoint + PlayerViewPointRotation.Vector()*500.f;
	UE_LOG(LogTemp, Warning, TEXT("Player view point is x:%f , y:%f , z:%f "), EndPoint.X,EndPoint.Y,EndPoint.Z);
	
	
	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	DrawDebugLine(GetWorld(), StartViewPoint, EndPoint, FColor(0,255,0), false, 0.0f,0,5.f);
	GetWorld()->LineTraceSingleByObjectType(
			OUT Hit,
			StartViewPoint,
			EndPoint,
			FCollisionObjectQueryParams(ECollisionChannel::ECC_Visibility),
			TraceParams
	);
	UActorComponent* HitActor = Hit.GetComponent();
	if(HitActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Nothing has been hit right now"));
	}
	

}

//FString name = MeshTarget->GetName();
	//CollisionBox=GetOwner()->GetAttachActor();
	//GetOwner()->GetComponents(ListOfMeshes);
	//GetOwner()->GetComponents(ListOfBoxes);
	/*for(int i = 0;i<ListOfMeshes.Num();i++)
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
	*/

/*if(CollisionBox->IsOverlappingActor(ActorThatOpens))
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Overlapping"));
	}
	*/