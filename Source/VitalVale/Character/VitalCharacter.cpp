#include "VitalCharacter.h"

#include <flatbuffers/flexbuffers.h>

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../Network/NetworkManager.h"
#include "../VitalValeInstance.h"
#include "../Network/Packets/Outbound/PlayOutPosRot.h"
#include "Math/Vector.h"
#include "Math/Rotator.h"


AVitalCharacter::AVitalCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetMesh());
	CameraBoom->TargetArmLength = 300.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}


void AVitalCharacter::BeginPlay()
{
	Super::BeginPlay();

	AVitalCharacter* NewActor = GetWorld()->SpawnActor<
		AVitalCharacter>(FVector(1000, 1000, 500), FRotator::ZeroRotator);
}

void AVitalCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AVitalCharacter::Jump);

	PlayerInputComponent->BindAxis("MoveForward", this, &AVitalCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AVitalCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AVitalCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AVitalCharacter::LookUp);
}


void AVitalCharacter::MoveForward(float Value)
{
	if (Controller != nullptr && Value != 0.f)
	{
		const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
		const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X));
		AddMovementInput(Direction, Value);
	}
}

void AVitalCharacter::MoveRight(float Value)
{
	if (Controller != nullptr && Value != 0.f)
	{
		const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
		const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y));
		AddMovementInput(Direction, Value);
	}
}

void AVitalCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void AVitalCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}


void AVitalCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// if (this->GetActorLocation() != oldPosition)
	// {
	// 	UVitalValeInstance* GameInstance = Cast<UVitalValeInstance>(GetGameInstance());
	// 	if (GameInstance)
	// 	{
	// 		if (GameInstance->GetNetworkMg() != nullptr)
	// 		{
	// 			flexbuffers::Builder fbb;
	// 			fbb.Vector([&]()
	// 			{
	// 				fbb.Int()
	// 			});
	// 		}
	// 	}
	// }
	/*	if (this->GetActorLocation() != oldPosition)
		{
			UE_LOG(LogTemp, Warning, TEXT("position changed"));
			UVitalValeInstance* GameInstance = Cast<UVitalValeInstance>(GetGameInstance());
			if (GameInstance)
			{
				UPlayOutPosRot* PlayOutPosRot = new UPlayOutPosRot();
				PlayOutPosRot->ConstructPacket(this->GetActorLocation().X, this->GetActorLocation().Y, this->GetActorLocation().Z, this->GetActorRotation().Roll, this->GetActorRotation().Pitch, this->GetActorRotation().Yaw);
	
				if (GameInstance->GetNetworkMg() != nullptr)
				{
					UE_LOG(LogTemp, Warning, TEXT("Packet sent: %s"), *PlayOutPosRot->JSerialize());
					GameInstance->GetNetworkMg()->SendPacket(PlayOutPosRot->JSerialize());
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("PosRot NetworkMg is nullptr"));
				}
	
				delete PlayOutPosRot;
	
				UE_LOG(LogTemp, Warning, TEXT("PosRot Sent to Server."));
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("PosRot GameInstance is nullptr"));
			}
			
		}*/
	oldPosition = this->GetActorLocation();
}
