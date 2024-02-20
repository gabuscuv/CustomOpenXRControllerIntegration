// Copyright 2023 Gabriel Bustillo del Cuvillo

#include "OpenXRController.h"
#include "HAL/IConsoleManager.h" 
#include "Components/TextRenderComponent.h" 
#include "Kismet/KismetSystemLibrary.h"
#include "VRExpansionFunctionLibrary.h"
#include "OpenXRControllerStringsConst.h"

// Sets default values
AOpenXRController::AOpenXRController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// Base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpringArm"));
	StaticMeshController = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base"));

	StaticMeshController->SetStaticMesh((UStaticMesh *)StaticLoadObject(
		UStaticMesh::StaticClass(), nullptr,
		*FOpenXRControllerStringsConst::GetMeshPathString(
			EBPOpenXRControllerDeviceType::DT_OculusTouchController, TEXT("Rift S"), isLeftController),
		nullptr, LOAD_None, nullptr));

	StaticMeshController->SetCollisionProfileName(FName("NoCollision"));

	RootComponent = StaticMeshController;

	HelpTextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("HelpText"));
	if (HelpTextComponent)
	{
		HelpTextComponent->SetupAttachment(StaticMeshController);
		HelpTextComponent->SetRelativeLocationAndRotation(
			FVector(11, -2, 4), 
			FRotator(0.0f, 180.0f, 0.0f)
		);
		HelpTextComponent->SetWorldSize(5.0f);
		HelpTextComponent->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	}
	
}

// Called when the game starts or when spawned
void AOpenXRController::BeginPlay()
{
	Super::BeginPlay();
	if (IConsoleManager::Get().FindConsoleVariable(TEXT("vr.SkipControllerDetection"))->GetBool())
	{
		return;
	}

	DetectController();
}

void AOpenXRController::DetectController()
{
	#if WITH_EDITORONLY_DATA
	if (isSpoffingController && !UKismetSystemLibrary::IsPackagedForDistribution())
	{
		SetMesh();
		return;
	}
else
	if (! UVRExpansionFunctionLibrary::GetIsHMDConnected())
	{
		UE_LOG(LogTemp, Verbose, TEXT("OPENXRCONTROLLER: It doesn't detect a HMD Connected"));
		return;
	}
#endif

		// if (Result == EBPXRResultSwitch::OnFailed){/*Delay*/}
	UOpenXRExpansionFunctionLibrary::GetXRMotionControllerType(TrackingSystemName, DeviceType, Result);

	if (Result != EBPXRResultSwitch::OnSucceeded)
	{
		UE_LOG(LogTemp, Error, TEXT("OPENXRCONTROLLER: ERROR, It doesn't Found OpenXRController"))
		#if !(DisableRetryDetection)
		counter++;
		if (counter < attempts)
		{
			WaitTimerDelegate = FTimerDelegate::CreateUObject(this, &AOpenXRController::DetectController);
			GetWorld()->GetTimerManager().SetTimer(WaitTimerHandle, WaitTimerDelegate, HeldTimerDuration, false);
		}
		#endif
		return;
	}
	SetMesh();
}
void AOpenXRController::SetMesh()
{
	StaticMeshController->SetStaticMesh((UStaticMesh *)StaticLoadObject(UStaticMesh::StaticClass(), nullptr,
																		*FOpenXRControllerStringsConst::GetMeshPathString(
																			DeviceType, TrackingSystemName, isLeftController),
																		nullptr, LOAD_None, nullptr));

	StaticMeshController->CreateDynamicMaterialInstance(0, (UMaterialInstance *)StaticLoadObject(
															   UMaterialInstance::StaticClass(), nullptr,
															   *FOpenXRControllerStringsConst::GetMaterialInstancePathString(
																   DeviceType, TrackingSystemName, isLeftController),
															   nullptr, LOAD_None, nullptr));
}

void AOpenXRController::HighlightButtons_Implementation(EButton button, bool state, bool AddOffset)
{
	StaticMeshController->SetScalarParameterValueOnMaterials(GetEnumName(button), (float)(!state));
}

void AOpenXRController::ClearAllHighlightButtons_Implementation()
{
	for (auto Button : TEnumRange<EButton>())
	{
		StaticMeshController->SetScalarParameterValueOnMaterials(GetEnumName(Button), (float)(!false));
	}
}


void AOpenXRController::SetText_Implementation(const FText & text)
{
	HelpTextComponent->SetText(text);
}

FName AOpenXRController::GetEnumName(EButton button)
{
	return FName(*UEnum::GetValueAsString<EButton>(button).Replace(TEXT("EButton::"), TEXT("")));
}