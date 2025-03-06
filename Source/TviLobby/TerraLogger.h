// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TerraLogger.generated.h"

UCLASS()
class TVILOBBY_API ATerraLogger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATerraLogger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Tvi", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext))
	static void printFlow(UObject* WorldContextObject, const FString Log);

	UFUNCTION(BlueprintCallable, Category = "Tvi", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext))
	static void printLog(UObject* WorldContextObject, const FString& Log, const FString& Value);

	UFUNCTION(BlueprintCallable, Category = "Tvi", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext))
	static void printWarning(UObject* WorldContextObject, const FString Log);

	UFUNCTION(BlueprintCallable, Category = "Tvi", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext))
	static void printError(UObject* WorldContextObject, const FString Log);
};
