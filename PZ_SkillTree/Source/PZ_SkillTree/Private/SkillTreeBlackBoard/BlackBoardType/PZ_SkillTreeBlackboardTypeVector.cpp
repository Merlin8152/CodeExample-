// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeBlackBoard/BlackBoardType/PZ_SkillTreeBlackboardTypeVector.h"

#include "PZ_SkillTreeContext.h"

const UPZ_SkillTreeBlackboardTypeVector::FDataType UPZ_SkillTreeBlackboardTypeVector::InvalidValue = UPZ_SkillTreeBlackboardTypeVector::FDataType(0);

UPZ_SkillTreeBlackboardTypeVector::UPZ_SkillTreeBlackboardTypeVector(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ValueSize = sizeof(FVector);
	SupportedOp = ESkillTreeBlackboardKeyOperation::Basic;
}

FVector UPZ_SkillTreeBlackboardTypeVector::GetValue(const UPZ_SkillTreeBlackboardTypeVector* KeyOb, const uint8* RawData)
{
	return GetValueFromMemory<FVector>(RawData);
}

bool UPZ_SkillTreeBlackboardTypeVector::SetValue(UPZ_SkillTreeBlackboardTypeVector* KeyOb, uint8* RawData, const FVector& Value)
{
	return SetValueInMemory<FVector>(RawData, Value);
}

ESkillTreeBlackboardCompare::Type UPZ_SkillTreeBlackboardTypeVector::CompareValues(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock,
	const UPZ_SkillTreeBlackboardKeyType* OtherKeyOb, const uint8* OtherMemoryBlock) const
{
	const FVector MyValue = GetValue(this, MemoryBlock);
	const FVector OtherValue = GetValue((UPZ_SkillTreeBlackboardTypeVector*)OtherKeyOb, OtherMemoryBlock);

	return MyValue.Equals(OtherValue) ? ESkillTreeBlackboardCompare::Equal : ESkillTreeBlackboardCompare::NotEqual;
}

void UPZ_SkillTreeBlackboardTypeVector::Clear(UPZ_SkillTreeContext& OwnerComp, uint8* RawData)
{
	SetValueInMemory<FVector>(RawData,FVector());
}

bool UPZ_SkillTreeBlackboardTypeVector::IsEmpty(const UPZ_SkillTreeContext& OwnerComp, const uint8* RawData) const
{
	const FVector Location = GetValue(this, RawData);
	return !Location.IsZero();
}

FString UPZ_SkillTreeBlackboardTypeVector::DescribeValue(const UPZ_SkillTreeContext& OwnerComp, const uint8* RawData) const
{
	const FVector Location = GetValue(this, RawData);
	return !Location.IsZero() ? Location.ToString() : TEXT("(invalid)");
}

bool UPZ_SkillTreeBlackboardTypeVector::GetLocation(const UPZ_SkillTreeContext& OwnerComp, const uint8* RawData, FVector& Location) const
{
	Location = GetValue(this, RawData);
	return !Location.IsZero();
}

void UPZ_SkillTreeBlackboardTypeVector::InitializeMemory(UPZ_SkillTreeContext& OwnerComp, uint8* RawData)
{
	SetValue(this, RawData,FVector());
}

