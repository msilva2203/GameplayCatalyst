// © 2024 Marco Silva

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TaskBase.h"
#include "TaskManagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CHARACTERCATALYST_API UTaskManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTaskManagerComponent();

protected:
	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Tasks")
	void Setup();

	UFUNCTION(BlueprintCallable, Category = "Tasks")
	bool BindTask(const FName TaskID);

	UFUNCTION(BlueprintCallable, Category = "Tasks")
	bool UnbindTask();

	UFUNCTION(BlueprintCallable, Category = "Tasks")
	bool AddTask(const FName TaskID, TSubclassOf<UTaskBase> TaskClass);

	UFUNCTION(BlueprintCallable, Category = "Tasks")
	bool RemoveTask(const FName TaskID);

	UFUNCTION(BlueprintCallable, Category = "Tasks")
	UTaskBase* GetTask(const FName TaskID);

public:

	UFUNCTION(BlueprintPure, Category = "Tasks")
	UTaskBase* GetCurrentTask();

public:

	UPROPERTY(EditDefaultsOnly, Category = "Tasks")
	TMap<FName, TSubclassOf<UTaskBase>> DefaultTasks;

private:

	UPROPERTY()
	TMap<FName, UTaskBase*> Tasks;

	UPROPERTY()
	UTaskBase* CurrentTask;

};
