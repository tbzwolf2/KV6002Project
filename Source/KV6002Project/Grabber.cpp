// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	CheckPhysicsHandle();
	SetupInputComponent();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector()*2000.f;
	GetWorld()->LineTraceSingleByObjectType(
			OUT Hit,
			PlayerViewPointLocation,
			LineTraceEnd,
			FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
			TraceParams
	);
	HitActor = Hit.GetActor();
	if(HitActor)
	{
		//UE_LOG(LogTemp, Warning, TEXT("%s has been hit"),*(HitActor->GetName()));
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab key has been pressed"));
	if(HitActor){
		Hider = HitActor->FindComponentByClass<UHideFunction>();
		//Hider->Tester();
		UE_LOG(LogTemp, Error, TEXT("Hit a thing"));
	}
	if(Hider)
	{
		UE_LOG(LogTemp, Error, TEXT("You've only gone and bloddy did it"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Didnt bloody work"));
	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab key has been released"));
}

void UGrabber::CheckPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(PhysicsHandle)
	{

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Object %s has no Physics Handle Component attached, please attach in order to run the game"), *GetOwner()->GetName())
	}
}

void UGrabber::SetupInputComponent()
{
	InputHandler = GetOwner()->FindComponentByClass<UInputComponent>();
	if(InputHandler)
	{
		UE_LOG(LogTemp, Warning, TEXT("Grabber has detected the input component on %s"), *GetOwner()->GetName());
		InputHandler->BindAction("Hide", IE_Pressed, this, &UGrabber::Grab);
		InputHandler->BindAction("Hide", IE_Released, this, &UGrabber::Release);
	}
}