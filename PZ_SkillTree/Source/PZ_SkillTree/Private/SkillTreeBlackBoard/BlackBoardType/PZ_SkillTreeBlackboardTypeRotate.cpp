// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeBlackBoard/BlackBoardType/PZ_SkillTreeBlackboardTypeRotate.h"

#include "PZ_SkillTreeContext.h"


const UPZ_SkillTreeBlackboardTypeRotate::FDataType UPZ_SkillTreeBlackboardTypeRotate::InvalidValue = FRotator();


UPZ_SkillTreeBlackboardTypeRotate::UPZ_SkillTreeBlackboardTypeRotate(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ValueSize = sizeof(FRotator);
	SupportedOp = ESkillTreeBlackboardKeyOperation::Basic;
}

FRotator UPZ_SkillTreeBlackboardTypeRotate::GetValue(const UPZ_SkillTreeBlackboardTypeRotate* KeyOb, const uint8* RawData)
{
	return GetValueFromMemory<FRotator>(RawData);
}

bool UPZ_SkillTreeBlackboardTypeRotate::SetValue(UPZ_SkillTreeBlackboardTypeRotate* KeyOb, uint8* RawData, const FRotator& Value)
{
	return SetValueInMemory<FRotator>(RawData, Value);
}

ESkillTreeBlackboardCompare::Type UPZ_SkillTreeBlackboardTypeRotate::CompareValues(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock,
	const UPZ_SkillTreeBlackboardKeyType* OtherKeyOb, const uint8* OtherMemoryBlock) const
{
	const FRotator MyValue = GetValue(this, MemoryBlock);
	const FRotator OtherValue = GetValue((UPZ_SkillTreeBlackboardTypeRotate*)OtherKeyOb, OtherMemoryBlock);

	return MyValue.Equals(OtherValue) ? ESkillTreeBlackboardCompare::Equal : ESkillTreeBlackboardCompare::NotEqual;
}

void UPZ_SkillTreeBlackboardTypeRotate::Clear(UPZ_SkillTreeContext& OwnerComp, uint8* RawData)
{
	SetValueInMemory<FRotator>(RawData, FRotator());
}

bool UPZ_SkillTreeBlackboardTypeRotate::IsEmpty(const UPZ_SkillTreeContext& OwnerComp, const uint8* RawData) const
{
	const FRotator Rotation = GetValue(this, RawData);
	return Rotation.IsZero();
}

FString UPZ_SkillTreeBlackboardTypeRotate::DescribeValue(const UPZ_SkillTreeContext& OwnerComp, const uint8* RawData) const
{
	const FRotator Rotation = GetValue(this, RawData);
	return !Rotation.IsZero() ? Rotation.ToString() : TEXT("(invalid)");
}

bool UPZ_SkillTreeBlackboardTypeRotate::GetRotation(const UPZ_SkillTreeContext& OwnerComp, const uint8* RawData, FRotator& Rotation) const
{
	Rotation = GetValue(this, RawData);
	return Rotation.IsZero();
}

void UPZ_SkillTreeBlackboardTypeRotate::InitializeMemory(UPZ_SkillTreeContext& OwnerComp, uint8* RawData)
{
	SetValue(this, RawData, FRotator());
}

bool UPZ_SkillTreeBlackboardTypeRotate::TestBasicOperation(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock, ESkillTreeBasicKeyOperation::Type Op) const
{
	const FRotator Rotation = GetValue(this, MemoryBlock);
	return (Op == EBasicKeyOperation::Set) ? Rotation.IsZero() : !Rotation.IsZero();
}
