// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeBlackBoard/BlackBoardType/PZ_SkillTreeBlackboardTypeObject.h"

#include "PZ_SkillTreeContext.h"


const UPZ_SkillTreeBlackboardTypeObject::FDataType UPZ_SkillTreeBlackboardTypeObject::InvalidValue = UPZ_SkillTreeBlackboardTypeObject::FDataType(0);


UPZ_SkillTreeBlackboardTypeObject::UPZ_SkillTreeBlackboardTypeObject(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ValueSize = sizeof(FWeakObjectPtr);
	BaseClass = UObject::StaticClass();
	SupportedOp = ESkillTreeBlackboardKeyOperation::Basic;
}

UObject* UPZ_SkillTreeBlackboardTypeObject::GetValue(const UPZ_SkillTreeBlackboardTypeObject* KeyOb, const uint8* RawData)
{
	// RawData can be NULL if the key is corrupted by bad data, such as if someone has duplicated a key in a derived
	// blackboard.  We must handle that bad data case gracefully.  It's likely that we need to handle this for
	// all blackboard key types, so possibly GetValueFromMemory should handle the NULL case instead.  But for now I'm
	// just fixing the case I came across.
	if (RawData == NULL)
	{
		return NULL;
	}

	FWeakObjectPtr WeakObjPtr = GetValueFromMemory<FWeakObjectPtr>(RawData);
	return WeakObjPtr.Get();
}

bool UPZ_SkillTreeBlackboardTypeObject::SetValue(UPZ_SkillTreeBlackboardTypeObject* KeyOb, uint8* RawData, UObject* Value)
{
	TWeakObjectPtr<UObject> WeakObjPtr(Value);
	return SetWeakObjectInMemory<UObject>(RawData, WeakObjPtr);
}

ESkillTreeBlackboardCompare::Type UPZ_SkillTreeBlackboardTypeObject::CompareValues(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock,
	const UPZ_SkillTreeBlackboardKeyType* OtherKeyOb, const uint8* OtherMemoryBlock) const
{
	const UObject* MyValue = GetValue(this, MemoryBlock);
	const UObject* OtherValue = GetValue((UPZ_SkillTreeBlackboardTypeObject*)OtherKeyOb, OtherMemoryBlock);

	return (MyValue == OtherValue) ? ESkillTreeBlackboardCompare::Equal : ESkillTreeBlackboardCompare::NotEqual;
}

FString UPZ_SkillTreeBlackboardTypeObject::DescribeValue(const UPZ_SkillTreeContext& OwnerComp, const uint8* RawData) const
{
	return *GetNameSafe(GetValue(this, RawData));
}

FString UPZ_SkillTreeBlackboardTypeObject::DescribeSelf() const
{
	return *GetNameSafe(BaseClass);
}

bool UPZ_SkillTreeBlackboardTypeObject::IsAllowedByFilter(UPZ_SkillTreeBlackboardKeyType* FilterOb) const
{
	UPZ_SkillTreeBlackboardTypeObject* FilterObject = Cast<UPZ_SkillTreeBlackboardTypeObject>(FilterOb);
	return (FilterObject && (FilterObject->BaseClass == BaseClass || BaseClass->IsChildOf(FilterObject->BaseClass)));
}

bool UPZ_SkillTreeBlackboardTypeObject::GetLocation(const UPZ_SkillTreeContext& OwnerComp, const uint8* RawData, FVector& Location) const
{
	AActor* MyActor = Cast<AActor>(GetValue(this, RawData));
	if (MyActor)
	{
		Location = MyActor->GetActorLocation();
		return true;
	}

	return false;
}

bool UPZ_SkillTreeBlackboardTypeObject::GetRotation(const UPZ_SkillTreeContext& OwnerComp, const uint8* RawData, FRotator& Rotation) const
{
	AActor* MyActor = Cast<AActor>(GetValue(this, RawData));
	if (MyActor)
	{
		Rotation = MyActor->GetActorRotation();
		return true;
	}

	return false;
}

bool UPZ_SkillTreeBlackboardTypeObject::TestBasicOperation(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock, ESkillTreeBasicKeyOperation::Type Op) const
{
	if (MemoryBlock == NULL)
	{
		return false;
	}

	FWeakObjectPtr WeakObjPtr = GetValueFromMemory<FWeakObjectPtr>(MemoryBlock);
	return (Op == EBasicKeyOperation::Set) ? WeakObjPtr.IsValid() : !WeakObjPtr.IsValid();
}
