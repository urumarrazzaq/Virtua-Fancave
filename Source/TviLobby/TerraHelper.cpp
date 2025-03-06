// Fill out your copyright notice in the Description page of Project Settings.

#include "TerraHelper.h"
#include "Engine/GameEngine.h"
#include "EngineGlobals.h"
#include "SlateCore.h"

// Sets default values
ATerraHelper::ATerraHelper()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATerraHelper::OnControllerConnection(bool Sucess, FPlatformUserId userid, int32 id)
{
	isControllerStateChange.Broadcast(Sucess);
}


// Called when the game starts or when spawned
void ATerraHelper::BeginPlay()
{
	Super::BeginPlay();
	FCoreDelegates::OnControllerConnectionChange.AddUObject(this, &ATerraHelper::OnControllerConnection);
}

// Called every frame
void ATerraHelper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ATerraHelper::IsGamePadConnected()
{
	auto genericApplication = FSlateApplication::Get().GetPlatformApplication();
	if (genericApplication.Get() != nullptr && genericApplication->IsGamepadAttached())
	{
		return true;
	}
	return false;
}

void ATerraHelper::minimizeWindow()
{
#if !WITH_EDITOR

	UGameEngine* gameEngine = Cast<UGameEngine>(GEngine);

	if (gameEngine)
	{
		TSharedPtr<SWindow> windowPtr = gameEngine->GameViewportWindow.Pin();
		SWindow *window = windowPtr.Get();

		if (window)
		{
			window->Minimize();
		}
	}

#endif // !WITH_EDITOR
}

bool ATerraHelper::loadRsaStringFromFile(FString& Result, FString Filename)
{
	FString myFilePath = FPaths::Combine(FPaths::ProjectContentDir(), TEXT("Dist"));
	myFilePath = FPaths::Combine(myFilePath, Filename);
	UE_LOG(LogTemp, Warning, TEXT("FILE PATH: %s"), *myFilePath);
	return FFileHelper::LoadFileToString(Result, *myFilePath);
}

