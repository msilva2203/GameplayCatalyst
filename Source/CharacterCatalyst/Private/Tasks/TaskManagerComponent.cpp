// © 2024 Marco Silva


#include "Tasks/TaskManagerComponent.h"

UTaskManagerComponent::UTaskManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UTaskManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Setup();
}

void UTaskManagerComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	for (auto TaskPair : Tasks)
	{
		RemoveTask(TaskPair.Key);
	}
}

void UTaskManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentTask)
	{
		CurrentTask->OnTaskTick(DeltaTime);
	}
}

void UTaskManagerComponent::Setup()
{
	for (auto TaskPair : DefaultTasks)
	{
		AddTask(TaskPair.Key, TaskPair.Value);
	}
}

bool UTaskManagerComponent::BindTask(const FName TaskID)
{
	UTaskBase** TaskSearch = Tasks.Find(TaskID);
	if (TaskSearch)
	{
		UTaskBase* Task = *TaskSearch;
		UnbindTask();
		Task->OnTaskBind();
		CurrentTask = Task;
		return true;
	}
	return false;
}

bool UTaskManagerComponent::UnbindTask()
{
	if (CurrentTask)
	{
		CurrentTask->OnTaskUnbind();
		CurrentTask = nullptr;
		return true;
	}
	return false;
}

bool UTaskManagerComponent::AddTask(const FName TaskID, TSubclassOf<UTaskBase> TaskClass)
{
	UTaskBase** TaskSearch = Tasks.Find(TaskID);
	if (!TaskSearch)
	{
		UTaskBase* NewTask = NewObject<UTaskBase>(this, TaskClass);
		Tasks.Add(TaskID, NewTask);
		NewTask->ID = TaskID;
		NewTask->OnTaskBegin(this);
		return true;
	}
	return false;
}

bool UTaskManagerComponent::RemoveTask(const FName TaskID)
{
	UTaskBase** TaskSearch = Tasks.Find(TaskID);
	if (TaskSearch)
	{
		UTaskBase* Task = *TaskSearch;
		Tasks.Remove(TaskID);
		Task->OnTaskEnd();
		return true;
	}
	return false;
}

UTaskBase* UTaskManagerComponent::GetTask(const FName TaskID)
{
	UTaskBase* Task = nullptr;
	UTaskBase** TaskSearch = Tasks.Find(TaskID);
	if (TaskSearch)
	{
		Task = *TaskSearch;
	}
	return Task;
}

UTaskBase* UTaskManagerComponent::GetCurrentTask()
{
	return CurrentTask;
}

