// © 2024 Marco Silva


#include "Tasks/TaskBase.h"
#include "Tasks/TaskManagerComponent.h"

UWorld* UTaskBase::GetWorld() const
{
	return GetOuter()->GetWorld();
}

void UTaskBase::OnTaskBegin(UTaskManagerComponent* InTaskManager)
{
	TaskManager = InTaskManager;
	OnBegin(InTaskManager);
}

void UTaskBase::OnTaskEnd()
{
	OnEnd();
}

void UTaskBase::OnTaskBind()
{
	OnBind();
}

void UTaskBase::OnTaskUnbind()
{
	OnUnbind();
}

void UTaskBase::OnTaskTick(float DeltaTime)
{
	OnTick(DeltaTime);
}

UTaskManagerComponent* UTaskBase::GetTaskManager()
{
	return TaskManager;
}

AActor* UTaskBase::GetOwningActor()
{
	return TaskManager->GetOwner();
}

bool UTaskBase::HasAuthority()
{
	return GetOwningActor()->HasAuthority();
}
