// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Http.h"

#include "Runtime/Core/Public/Misc/Paths.h"
#include "Runtime/Core/Public/GenericPlatform/GenericPlatformFile.h"

#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>

#include "FileDownloader.generated.h"

/**
* Possible results from a download request.
*/
UENUM(BlueprintType, Category = "Fozi")
enum class EDownloadResult : uint8
{
	Success,
	DownloadFailed,
	SaveFailed,
	DirectoryCreationFailed
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnResult, const EDownloadResult, Result);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnProgress, const int32, BytesSent, const int32, BytesReceived, const int32, ContentLength);

/**
* Download a file from a URL and save it locally.
*/
UCLASS(BlueprintType, Category = "Fozi")
class TVILOBBY_API UFileDownloader : public UObject
{
	GENERATED_BODY()

public:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Fozi)
	//int32 downloadID;

	/**
	* Bind to know when the download is complete (even if it fails).
	*/
	UPROPERTY(BlueprintAssignable, Category = "Fozi")
		FOnResult OnResult;
	/**
	* Bind to know when the download is complete (even if it fails).
	*/
	UPROPERTY(BlueprintAssignable, Category = "Fozi")
		FOnProgress OnProgress;

	/**
	* The URL used to start this download.
	*/
	UPROPERTY(BlueprintReadOnly, Category = "Fozi")
		FString FileUrl;
	/**
	* The path set to save the downloaded file.
	*/
	UPROPERTY(BlueprintReadOnly, Category = "Fozi")
		FString FileSavePath;

	UFileDownloader();
	~UFileDownloader();

	/**
	* Instantiates a FileDownloader object, starts downloading and saves it when done.
	*
	* @return The FileDownloader object. Bind to it's OnResult event to know when it's done downloading.
	*/
	UFUNCTION(BlueprintCallable, Meta = (DisplayName = "Create Downloader"), Category = "Fozi")
		static UFileDownloader* MakeDownloader();

	/**
	* Starts downloading a file and saves it when done. Bind to the OnResult
	* event to know when the download is done (preferrably, before calling this function).
	*
	* @param Url		The file Url to be downloaded.
	* @param SavePath	The absolute path and file name to save the downloaded file.
	* @return Returns itself.
	*/
	UFUNCTION(BlueprintCallable, Category = "Fozi")
		UFileDownloader* DownloadFile(const FString& Url, FString SavePath);

private:

	void OnReady(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void OnProgress_Internal(FHttpRequestPtr Request, int32 BytesSent, int32 BytesReceived);
};
