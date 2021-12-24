// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeBlackBoard/BlackBoardType/PZ_SkillTreeBlackboardType_Enum.h"

#include "UObject/Package.h"
#include "UObject/UnrealType.h"

#include "PZ_SkillTreeContext.h"

const UPZ_SkillTreeBlackboardType_Enum::FDataType UPZ_SkillTreeBlackboardType_Enum::InvalidValue = UPZ_SkillTreeBlackboardType_Enum::FDataType(0);


UPZ_SkillTreeBlackboardType_Enum::UPZ_SkillTreeBlackboardType_Enum(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ValueSize = sizeof(uint8);
	SupportedOp = ESkillTreeBlackboardKeyOperation::Arithmetic;
}

uint8 UPZ_SkillTreeBlackboardType_Enum::GetValue(const UPZ_SkillTreeBlackboardType_Enum* KeyOb, const uint8* RawData)
{
	return GetValueFromMemory<uint8>(RawData);
}

bool UPZ_SkillTreeBlackboardType_Enum::SetValue(UPZ_SkillTreeBlackboardType_Enum* KeyOb, uint8* RawData, uint8 Value)
{
	return SetValueInMemory<uint8>(RawData, Value);
}

ESkillTreeBlackboardCompare::Type UPZ_SkillTreeBlackboardType_Enum::CompareValues(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock,
	const UPZ_SkillTreeBlackboardKeyType* OtherKeyOb, const uint8* OtherMemoryBlock) const
{
	const uint8 MyValue = GetValue(this, MemoryBlock);
	const uint8 OtherValue = GetValue((UPZ_SkillTreeBlackboardType_Enum*)OtherKeyOb, OtherMemoryBlock);

	return (MyValue > OtherValue) ? ESkillTreeBlackboardCompare::Greater :
		(MyValue < OtherValue) ? ESkillTreeBlackboardCompare::Less :
		ESkillTreeBlackboardCompare::Equal;
}

FString UPZ_SkillTreeBlackboardType_Enum::DescribeValue(const UPZ_SkillTreeContext& OwnerComp, const uint8* RawData) const
{
	return EnumType ? EnumType->GetDisplayNameTextByValue(GetValue(this, RawData)).ToString() : FString("UNKNOWN!");
}

FString UPZ_SkillTreeBlackboardType_Enum::DescribeSelf() const
{
	return *GetNameSafe(EnumType);
}

bool UPZ_SkillTreeBlackboardType_Enum::IsAllowedByFilter(UPZ_SkillTreeBlackboardKeyType* FilterOb) const
{
	UPZ_SkillTreeBlackboardType_Enum* FilterEnum = Cast<UPZ_SkillTreeBlackboardType_Enum>(FilterOb);
	return (FilterEnum && FilterEnum->EnumType == EnumType);
}

bool UPZ_SkillTreeBlackboardType_Enum::TestArithmeticOperation(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock, ESkillTreeArithmeticKeyOperation::Type Op, int32 OtherIntValue, float OtherFloatValue) const
{
	const uint8 Value = GetValue(this, MemoryBlock);
	switch (Op)
	{
	case EArithmeticKeyOperation::Equal:			return (Value == OtherIntValue);
	case EArithmeticKeyOperation::NotEqual:			return (Value != OtherIntValue);
	case EArithmeticKeyOperation::Less:				return (Value < OtherIntValue);
	case EArithmeticKeyOperation::LessOrEqual:		return (Value <= OtherIntValue);
	case EArithmeticKeyOperation::Greater:			return (Value > OtherIntValue);
	case EArithmeticKeyOperation::GreaterOrEqual:	return (Value >= OtherIntValue);
	default: break;
	}

	return false;
}

FString UPZ_SkillTreeBlackboardType_Enum::DescribeArithmeticParam(int32 IntValue, float FloatValue) const
{
	return EnumType ? EnumType->GetDisplayNameTextByValue(IntValue).ToString() : FString("UNKNOWN!");
}

#if WITH_EDITOR
void UPZ_SkillTreeBlackboardType_Enum::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.Property &&
		PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(UPZ_SkillTreeBlackboardType_Enum, EnumName))
	{
		EnumType = FindObject<UEnum>(ANY_PACKAGE, *EnumName, true);
	}

	bIsEnumNameValid = EnumType && !EnumName.IsEmpty();
}
#endif
