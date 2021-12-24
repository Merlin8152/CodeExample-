// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "SkillTreeBlackBoard/PZ_SkillTreeBlackboardKeyType.h"
#include "PZ_SkillTreeBlackboardType_Enum.generated.h"




class UPZ_SkillTreeContext;

UCLASS(EditInlineNew, meta = (DisplayName = "Enum"))
class PZ_SKILLTREE_API UPZ_SkillTreeBlackboardType_Enum : public UPZ_SkillTreeBlackboardKeyType
{
	GENERATED_UCLASS_BODY()

	typedef uint8 FDataType;
	static const FDataType InvalidValue;

	UPROPERTY(Category = Blackboard, EditDefaultsOnly)
		UEnum* EnumType;

	/** name of enum defined in c++ code, will take priority over asset from EnumType property */
	UPROPERTY(Category = Blackboard, EditDefaultsOnly)
		FString EnumName;

	/** set when EnumName override is valid and active */
	UPROPERTY(Category = Blackboard, VisibleDefaultsOnly)
		uint32 bIsEnumNameValid : 1;


	static uint8 GetValue(const UPZ_SkillTreeBlackboardType_Enum* KeyOb, const uint8* RawData);
	static bool SetValue(UPZ_SkillTreeBlackboardType_Enum* KeyOb, uint8* RawData, uint8 Value);

	virtual ESkillTreeBlackboardCompare::Type CompareValues(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock,
		const UPZ_SkillTreeBlackboardKeyType* OtherKeyOb, const uint8* OtherMemoryBlock) const override;

	virtual FString DescribeSelf() const override;
	virtual FString DescribeArithmeticParam(int32 IntValue, float FloatValue) const override;
	virtual bool IsAllowedByFilter(UPZ_SkillTreeBlackboardKeyType* FilterOb) const override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

protected:
	virtual FString DescribeValue(const UPZ_SkillTreeContext& OwnerComp, const uint8* RawData) const override;
	virtual bool TestArithmeticOperation(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock, ESkillTreeArithmeticKeyOperation::Type Op, int32 OtherIntValue, float OtherFloatValue) const override;

	
};
