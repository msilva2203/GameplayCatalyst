// © 2024 Marco Silva

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TaskBase.generated.h"

class UTaskManagerComponent;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class CHARACTERCATALYST_API UTaskBase : public UObject
{
	GENERATED_BODY()

public:

	virtual UWorld* GetWorld() const override;
	
public:

	virtual void OnTaskBegin(UTaskManagerComponent* InTaskManager);
	virtual void OnTaskEnd();

	virtual void OnTaskBind();
	virtual void OnTaskUnbind();
	virtual void OnTaskTick(float DeltaTime);

	UFUNCTION(BlueprintImplementableEvent, Category = "Tasks")
	void OnBegin(UTaskManagerComponent* InTaskManager);

	UFUNCTION(BlueprintImplementableEvent, Category = "Tasks")
	void OnEnd();

	UFUNCTION(BlueprintImplementableEvent, Category = "Tasks")
	void OnBind();

	UFUNCTION(BlueprintImplementableEvent, Category = "Tasks")
	void OnUnbind();

	UFUNCTION(BlueprintImplementableEvent, Category = "Tasks")
	void OnTick(float DeltaTime);

public:

	UFUNCTION(BlueprintPure, Category = "Tasks")
	UTaskManagerComponent* GetTaskManager();

	UFUNCTION(BlueprintPure, Category = "Tasks")
	AActor* GetOwningActor();

	UFUNCTION(BlueprintPure, Category = "Tasks")
	bool HasAuthority();

	UPROPERTY(BlueprintReadOnly, Category = "Tasks")
	FName ID;

private:

	UTaskManagerComponent* TaskManager;
};
