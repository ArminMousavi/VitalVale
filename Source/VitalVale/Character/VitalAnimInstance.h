// Copyright @ 2023 By Seyed Armin Mousavi, All rights are reserved.Using this code isn't allowed in anywhere.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "VitalAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class VITALVALE_API UVitalAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;

private:
	UPROPERTY(BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	class AVitalCharacter* VitalCharacter;

	UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float Speed;

	UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool bIsInAir;

	UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool bIsAccelerating;
};
