// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CoreDelegates.h"
#include "TerraHelper.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FIsControllerChangeDelegate, bool, Status);

UCLASS()
class TVILOBBY_API ATerraHelper : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATerraHelper();
	FCoreDelegates* coreDelegate;
	void OnControllerConnection(bool Sucess, FPlatformUserId userid, int32 id);

	UPROPERTY(BlueprintAssignable)
	FIsControllerChangeDelegate isControllerStateChange;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Tvi")
	bool IsGamePadConnected();

	UFUNCTION(BlueprintCallable, Category = "Tvi")
	static void minimizeWindow();

	UFUNCTION(BlueprintCallable, Category = "Tvi")
	static bool loadRsaStringFromFile(FString& Result, FString Filename);
};
