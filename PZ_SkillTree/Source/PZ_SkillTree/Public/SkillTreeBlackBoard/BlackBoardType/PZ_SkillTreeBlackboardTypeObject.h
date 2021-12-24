// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "SkillTreeBlackBoard/PZ_SkillTreeBlackboardKeyType.h"
#include "PZ_SkillTreeBlackboardTypeObject.generated.h"

class UPZ_SkillTreeContext;

UCLASS(EditInlineNew, meta = (DisplayName = "Object"))
class PZ_SKILLTREE_API UPZ_SkillTreeBlackboardTypeObject : public UPZ_SkillTreeBlackboardKeyType
{
	GENERATED_UCLASS_BODY()


	typedef UObject* FDataType;
	static const FDataType InvalidValue;

	UPROPERTY(Category = Blackboard, EditDefaultsOnly, meta = (AllowAbstract = "1"))
		UClass* BaseClass;


	static UObject* GetValue(const UPZ_SkillTreeBlackboardTypeObject* KeyOb, const uint8* RawData);
	static bool SetValue(UPZ_SkillTreeBlackboardTypeObject* KeyOb, uint8* RawData, UObject* Value);


	virtual ESkillTreeBlackboardCompare::Type CompareValues(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock,
	const UPZ_SkillTreeBlackboardKeyType* OtherKeyOb, const uint8* OtherMemoryBlock) const override;


	virtual FString DescribeSelf() const override;
	virtual bool IsAllowedByFilter(UPZ_SkillTreeBlackboardKeyType* FilterOb) const override;


protected:

	virtual FString DescribeValue(const UPZ_SkillTreeContext& OwnerComp, const uint8* RawData) const override;
	virtual bool GetLocation(const UPZ_SkillTreeContext& OwnerComp, const uint8* RawData, FVector& Location) const override;
	virtual bool GetRotation(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock, FRotator& Rotation) const override;
	virtual bool TestBasicOperation(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock, ESkillTreeBasicKeyOperation::Type Op) const override;

};




