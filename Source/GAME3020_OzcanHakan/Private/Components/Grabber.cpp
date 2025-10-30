#include "Components/Grabber.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UGrabber::BeginPlay()
{
    Super::BeginPlay();
}

void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    UPhysicsHandleComponent* PhysicsHandler = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    if (PhysicsHandler != nullptr)
    {
        if (PhysicsHandler->GetGrabbedComponent() != nullptr)
        {
            FVector TargetLocation = GetComponentLocation() + GetForwardVector() * holdDistance;
            PhysicsHandler->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
        }
    }
}

void UGrabber::Grab()
{
    UPhysicsHandleComponent* PhysicsHandler = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    if (PhysicsHandler == nullptr)
        return;

    FHitResult HitResult;
    bool HasHit = GetGrabbableInReach(HitResult);

    if (HasHit)
    {
        PhysicsHandler->GrabComponentAtLocationWithRotation(
            HitResult.GetComponent(),
            NAME_None,
            HitResult.ImpactPoint,
            GetComponentRotation()
        );
    }
}

void UGrabber::Release()
{
    UPhysicsHandleComponent* PhysicsHandler = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    if (PhysicsHandler == nullptr)
        return;

    if (PhysicsHandler->GetGrabbedComponent() != nullptr)
    {
        PhysicsHandler->ReleaseComponent();
    }
}

bool UGrabber::GetGrabbableInReach(FHitResult& OutHitResult)
{
    FVector Start = GetComponentLocation();
    FVector End = Start + GetForwardVector() * maxGrabDistance;

    FCollisionShape Sphere = FCollisionShape::MakeSphere(grabRadius);
    return GetWorld()->SweepSingleByChannel(
        OutHitResult,
        Start,
        End,
        FQuat::Identity,
        ECC_GameTraceChannel2,
        Sphere
    );
}
