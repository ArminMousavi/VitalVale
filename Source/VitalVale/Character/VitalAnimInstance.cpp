// Copyright @ 2023 By Seyed Armin Mousavi, All rights are reserved. Using this code isn't allowed in anywhere.


#include "VitalAnimInstance.h"
#include "VitalCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UVitalAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	VitalCharacter = Cast<AVitalCharacter>(TryGetPawnOwner());
}

void UVitalAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (VitalCharacter == nullptr)
	{
		VitalCharacter = Cast<AVitalCharacter>(TryGetPawnOwner());
	}
	if (VitalCharacter == nullptr) return;

	FVector Velocity = VitalCharacter->GetVelocity();
	Velocity.Z = 0.f;
	Speed = Velocity.Size();

	bIsInAir = VitalCharacter->GetCharacterMovement()->IsFalling();

	bIsAccelerating = VitalCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f ? true : false;
}
