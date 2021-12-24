// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeBlackBoard/BlackBoardType/PZ_SkillTreeBlackboardType_class.h"

#include "UObject/WeakObjectPtr.h"
#include "Templates/Casts.h"

#include "PZ_SkillTreeContext.h"


const UPZ_SkillTreeBlackboardType_class::FDataType UPZ_SkillTreeBlackboardType_class::InvalidValue = nullptr;





UPZ_SkillTreeBlackboardType_class::UPZ_SkillTreeBlackboardType_class(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ValueSize = sizeof(TWeakObjectPtr<UClass>);
	BaseClass = UObject::StaticClass();
	SupportedOp = ESkillTreeBlackboardKeyOperation::Basic;
}

UClass* UPZ_SkillTreeBlackboardType_class::GetValue(const UPZ_SkillTreeBlackboardType_class* KeyOb, const uint8* RawData)
{
	TWeakObjectPtr<UClass> WeakObjPtr = GetValueFromMemory< TWeakObjectPtr<UClass> >(RawData);
	return WeakObjPtr.Get();
}

bool UPZ_SkillTreeBlackboardType_class::SetValue(UPZ_SkillTreeBlackboardType_class* KeyOb, uint8* RawData, UClass* Value)
{
	TWeakObjectPtr<UClass> WeakObjPtr(Value);
	return SetWeakObjectInMemory<UClass>(RawData, WeakObjPtr);
}

ESkillTreeBlackboardCompare::Type UPZ_SkillTreeBlackboardType_class::CompareValues(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock,
	const UPZ_SkillTreeBlackboardKeyType* OtherKeyOb, const uint8* OtherMemoryBlock) const
{
	const UClass* MyValue = GetValue(this, MemoryBlock);
	const UClass* OtherValue = GetValue((UPZ_SkillTreeBlackboardType_class*)OtherKeyOb, OtherMemoryBlock);

	return (MyValue == OtherValue) ? ESkillTreeBlackboardCompare::Equal : ESkillTreeBlackboardCompare::NotEqual;
}

FString UPZ_SkillTreeBlackboardType_class::DescribeValue(const UPZ_SkillTreeContext& OwnerComp, const uint8* RawData) const
{
	return *GetNameSafe(GetValue(this, RawData));
}

FString UPZ_SkillTreeBlackboardType_class::DescribeSelf() const
{
	return *GetNameSafe(BaseClass);
}

bool UPZ_SkillTreeBlackboardType_class::IsAllowedByFilter(UPZ_SkillTreeBlackboardKeyType* FilterOb) const
{
	UPZ_SkillTreeBlackboardType_class* FilterClass = Cast<UPZ_SkillTreeBlackboardType_class>(FilterOb);
	return (FilterClass && (FilterClass->BaseClass == BaseClass || BaseClass->IsChildOf(FilterClass->BaseClass)));
}

bool UPZ_SkillTreeBlackboardType_class::TestBasicOperation(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock, ESkillTreeBasicKeyOperation::Type Op) const
{
	TWeakObjectPtr<UClass> WeakObjPtr = GetValueFromMemory< TWeakObjectPtr<UClass> >(MemoryBlock);
	return (Op == ESkillTreeBasicKeyOperation::Set) ? WeakObjPtr.IsValid() : !WeakObjPtr.IsValid();
}
