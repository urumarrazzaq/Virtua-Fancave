// Fill out your copyright notice in the Description page of Project Settings.

#include "TerraLogger.h"
#include "TviLobby.h"

// Sets default values
ATerraLogger::ATerraLogger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATerraLogger::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATerraLogger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATerraLogger::printFlow(UObject * WorldContextObject, const FString Log)
{
	const FString SourceObjectPrefix = FString::Printf(TEXT("[%s] "), *GetNameSafe(WorldContextObject));
	FString FinalLogString = SourceObjectPrefix + Log;

	//SET_WARN_COLOR(COLOR_CYAN);
	UE_LOG(TviFlow, Log, TEXT("%s"), *FinalLogString);
	//CLEAR_WARN_COLOR();
}

void ATerraLogger::printLog(UObject* WorldContextObject, const FString& Log, const FString& Value)
{
	const FString SourceObjectPrefix = FString::Printf(TEXT("[%s] "), *GetNameSafe(WorldContextObject));
	FString FinalLogString = SourceObjectPrefix + Log + TEXT(": ") + Value;

	//SET_WARN_COLOR(COLOR_CYAN);
	UE_LOG(TviLog, Log, TEXT("%s"), *FinalLogString);
	//CLEAR_WARN_COLOR();
}

void ATerraLogger::printWarning(UObject* WorldContextObject, const FString Log)
{
	const FString SourceObjectPrefix = FString::Printf(TEXT("[%s] "), *GetNameSafe(WorldContextObject));
	FString FinalLogString = SourceObjectPrefix + Log;

	//SET_WARN_COLOR(COLOR_CYAN);
	UE_LOG(TviWarning, Warning, TEXT("%s"), *FinalLogString);
	//CLEAR_WARN_COLOR();
}

void ATerraLogger::printError(UObject* WorldContextObject, const FString Log)
{
	const FString SourceObjectPrefix = FString::Printf(TEXT("[%s] "), *GetNameSafe(WorldContextObject));
	FString FinalLogString = SourceObjectPrefix + Log;

	//SET_WARN_COLOR(COLOR_CYAN);
	UE_LOG(TviError, Error, TEXT("%s"), *FinalLogString);
	//CLEAR_WARN_COLOR();
}

