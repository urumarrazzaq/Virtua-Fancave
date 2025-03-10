// Fill out your copyright notice in the Description page of Project Settings.

#include "FileDownloader.h"
#include "TviLobby.h"
#include "PlatformFilemanager.h"

UFileDownloader::UFileDownloader() :
	FileUrl(TEXT(""))
	, FileSavePath(TEXT(""))
{
}

UFileDownloader::~UFileDownloader()
{
}

UFileDownloader* UFileDownloader::MakeDownloader()
{
	UFileDownloader* Downloader = NewObject<UFileDownloader>();
	return Downloader;
}

UFileDownloader* UFileDownloader::DownloadFile(const FString& Url, FString SavePath)
{
	FileUrl = Url;
	FileSavePath = SavePath; // ../../../DLCTestMain/Saved/DLCPack.pak

							 //FileSavePath = FPaths::EngineContentDir() + "DLCPak.pak";
							 //FileSavePath = FPaths::ProjectUserDir() + "/DLCPak.pak";
							 //FileSavePath = FPaths::ConvertRelativePathToFull(FileSavePath);

							 /*
							 if (FileSavePath.IsEmpty())
							 {
							 UE_LOG(LogTemp, Warning, TEXT("EMPTY"));
							 }*/

							 //UE_LOG(LogTemp, Warning, TEXT("PATH: %s"), *FileSavePath);

							 //GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, SavePath);
							 //GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FileSavePath);

	TSharedRef< IHttpRequest > HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetVerb("GET");
	HttpRequest->SetURL(Url);
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &UFileDownloader::OnReady);
	HttpRequest->OnRequestProgress().BindUObject(this, &UFileDownloader::OnProgress_Internal);

	// Execute the request
	HttpRequest->ProcessRequest();
	AddToRoot();

	return this;
}

void UFileDownloader::OnReady(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	RemoveFromRoot();
	Request->OnProcessRequestComplete().Unbind();

	if (Response.IsValid() && EHttpResponseCodes::IsOk(Response->GetResponseCode()))
	{
		// SAVE FILE
		IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

		// create save directory if not existent
		FString Path, Filename, Extension;
		FPaths::Split(FileSavePath, Path, Filename, Extension);
		if (!PlatformFile.DirectoryExists(*Path))
		{
			if (!PlatformFile.CreateDirectoryTree(*Path))
			{
				OnResult.Broadcast(EDownloadResult::DirectoryCreationFailed);
				return;
			}
		}

		// open/create the file
		IFileHandle* FileHandle = PlatformFile.OpenWrite(*FileSavePath);
		if (FileHandle)
		{
			// write the file
			FileHandle->Write(Response->GetContent().GetData(), Response->GetContentLength());
			// Close the file
			delete FileHandle;
			
			OnResult.Broadcast(EDownloadResult::Success);
		}
		else
		{
			OnResult.Broadcast(EDownloadResult::SaveFailed);
		}
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("Response Code: %d", Response->GetResponseCode())
		UE_LOG(LogTemp, Warning, TEXT("WAS SUCCESSFUL: %s"), (bWasSuccessful ? TEXT("True") : TEXT("False")));

		OnResult.Broadcast(EDownloadResult::DownloadFailed);
	}
}

void UFileDownloader::OnProgress_Internal(FHttpRequestPtr Request, int32 BytesSent, int32 BytesReceived)
{
	FHttpResponsePtr HttpResponse = Request->GetResponse();
	int32 FullSize;

	if (HttpResponse.IsValid())
	{
		FullSize = HttpResponse->GetContentLength();
	}

	OnProgress.Broadcast(BytesSent, BytesReceived, FullSize);
}