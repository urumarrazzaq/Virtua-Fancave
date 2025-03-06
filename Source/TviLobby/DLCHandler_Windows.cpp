// Fill out your copyright notice in the Description page of Project Settings.

#include "DLCHandler_Windows.h"
#include "Engine/ObjectLibrary.h"
#include "Engine/BlueprintGeneratedClass.h"

// Sets default values
ADLCHandler_Windows::ADLCHandler_Windows()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADLCHandler_Windows::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ADLCHandler_Windows::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ADLCHandler_Windows::MountPAK(FString SaveDirectory)
{
	FString path = FPaths::ConvertRelativePathToFull(SaveDirectory);
	bool check = false;
	if (FCoreDelegates::OnMountPak.IsBound())
	{
		check = FCoreDelegates::OnMountPak.Execute(SaveDirectory, 0, nullptr);

		FAssetRegistryModule& assetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
		IAssetRegistry& assetRegistry = assetRegistryModule.Get();
		assetRegistry.ScanPathsSynchronous({ TEXT("/Game/") }, true);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Error: OnMountPak is NOT Bound"));
	}
	return check;
}

bool ADLCHandler_Windows::doesFileExist(FString FileDirectory)
{
	return FPaths::FileExists(FileDirectory);
}

// Get UClass from asset in AssetRegistry
TArray<UClass*> ADLCHandler_Windows::GetClassFromAssetData(TArray<FAssetData>& InAssetData)
{
	TArray<UClass*> ClassArrayOut;
	ClassArrayOut.Empty();
	// Iterate over retrieved blueprint assets
	for (FAssetData asset : InAssetData)
	{
		FString ObjPath = asset.ObjectPath.ToString().Append("_C");
		UE_LOG(LogTemp, Warning, TEXT("Object path is : %s"), *ObjPath);
		UE_LOG(LogTemp, Warning, TEXT("Trying to return BPClass!"));

		//Get UClass
		ClassArrayOut.Add(StaticLoadClass(UObject::StaticClass(), NULL, *ObjPath, NULL, LOAD_None, NULL));
	}
	return ClassArrayOut;
}

TArray<UClass*> ADLCHandler_Windows::GetBlueprintsOf(UClass* TypeClass, FString InFolder)
{
	TArray<UClass*> list;
	//helper::GetBlueprintsOf(TypeClass, InFolder, list);

	auto items = UObjectLibrary::CreateLibrary(TypeClass, true, GIsEditor);
	items->AddToRoot();
	items->LoadBlueprintsFromPath(InFolder);

	TArray<UBlueprintGeneratedClass*> classes;
	items->GetObjects<UBlueprintGeneratedClass>(classes);

	for (int32 i = 0; i < classes.Num(); ++i)
	{
		UBlueprintGeneratedClass * item = classes[i];
		FString name = item->GetName();
		FString path = item->GetPathName();

		//skip editor debug stuff...
		if (name.StartsWith(TEXT("SKEL_"))) continue;

		UE_LOG(LogTemp, Warning, TEXT("- found / `%s` / in `%s`"), *name, *path);

		//:note: you can use ContainsByPredicate instead for more nuance
		list.AddUnique(item);
	}
	return list;
}