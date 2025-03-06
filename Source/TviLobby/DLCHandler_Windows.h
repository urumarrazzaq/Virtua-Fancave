// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Runtime/Core/Public/HAL/PlatformFilemanager.h"
#include "Net/UnrealNetwork.h"
#include "Runtime/PakFile/Public/IPlatformFilePak.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Core/Public/Serialization/Archive.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Runtime/Engine/Classes/Engine/StreamableManager.h"

#include "Runtime/Engine/Classes/Engine/SkeletalMesh.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"

#include "Runtime/AssetRegistry/Public/AssetRegistryModule.h"

#include "Runtime/Core/Public/Misc/CoreDelegates.h"
#include "Runtime/Core/Public/Misc/Paths.h"

#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>

//GetClassFromAssetData
#include "Runtime/AssetRegistry/Public/AssetData.h"


#include "GameFramework/Actor.h"
#include "DLCHandler_Windows.generated.h"

class FPakPlatformFile;

UCLASS()
class TVILOBBY_API ADLCHandler_Windows : public AActor
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	ADLCHandler_Windows();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Fozi")
		static bool MountPAK(FString SaveDirectory);

	UFUNCTION(BlueprintCallable, Category = "Fozi")
		static bool doesFileExist(FString FileDirectory);

	/**
	* Get UClass from assets found with AssetManager (Purple Class node)
	* Use this to get Assets by Path, Class Type ect.
	* Use GET ASSET REGISTRY node -> GET ASSETS node -> as your input to this
	* Using correct class checking and casting, this can be used for spawning actors, getting class defaults, using textures, sounds ect.
	* COOKED BUILDS: : Make sure your assets/folders are manually added to cooked build if they are not used directly in Editor.
	* On-the-fly asset list creation or add DLC content, no lookup tables!
	*/
	UFUNCTION(BlueprintCallable, Category = "Fozi")
	static TArray<UClass*> GetClassFromAssetData(UPARAM(ref) TArray<FAssetData>& InAssetData);

	/** Returns a list of Class references to blueprint assets from a given project path. */
	UFUNCTION(BlueprintCallable, Category = "Helpers")
	static TArray<UClass*> GetBlueprintsOf(UClass* TypeClass, FString InFolder);

};
