// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "InputCoreTypes.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "PZ_SkillTreeBlackboardKeyType.generated.h"

namespace ESkillTreeBlackboardCompare
{
	enum Type
	{
		Less = -1,
		Equal = 0,
		Greater = 1,

		NotEqual = 1,	// important, do not change
	};
}

namespace ESkillTreeBlackboardKeyOperation
{
	enum Type
	{
		Basic,
		Arithmetic,
		Text,
	};
}

UENUM()
namespace ESkillTreeBasicKeyOperation
{
	enum Type
	{
		Set				UMETA(DisplayName = "Is Set"),
		NotSet			UMETA(DisplayName = "Is Not Set"),
	};
}

UENUM()
namespace ESkillTreeArithmeticKeyOperation
{
	enum Type
	{
		Equal			UMETA(DisplayName = "Is Equal To"),
		NotEqual		UMETA(DisplayName = "Is Not Equal To"),
		Less			UMETA(DisplayName = "Is Less Than"),
		LessOrEqual		UMETA(DisplayName = "Is Less Than Or Equal To"),
		Greater			UMETA(DisplayName = "Is Greater Than"),
		GreaterOrEqual	UMETA(DisplayName = "Is Greater Than Or Equal To"),
	};
}

UENUM()
namespace ESkillTreeTextKeyOperation
{
	enum Type
	{
		Equal			UMETA(DisplayName = "Is Equal To"),
		NotEqual		UMETA(DisplayName = "Is Not Equal To"),
		Contain			UMETA(DisplayName = "Contains"),
		NotContain		UMETA(DisplayName = "Not Contains"),
	};
}

struct FSkillTreeBlackboardInstancedKeyMemory
{
	/** index of instanced key in UBlackboardComponent::InstancedKeys */
	int32 KeyIdx;
};

class UPZ_SkillTreeContext;


UCLASS(EditInlineNew, Abstract, CollapseCategories)
class PZ_SKILLTREE_API UPZ_SkillTreeBlackboardKeyType : public UObject
{
	GENERATED_UCLASS_BODY()
	


	/** handle dynamic data size */
	virtual void PreInitialize(UPZ_SkillTreeContext& OwnerComp);


	/** handle instancing if needed */
	void InitializeKey(UPZ_SkillTreeContext& OwnerComp, FBlackboard::FKey KeyID);

	/** does it match settings in filter? */
	virtual bool IsAllowedByFilter(UPZ_SkillTreeBlackboardKeyType* FilterOb) const;


	/** extract location from entry, supports instanced keys */
	bool WrappedGetLocation(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock, FVector& Location) const;

	/** extract rotation from entry, supports instanced keys */
	bool WrappedGetRotation(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock, FRotator& Rotation) const;

	/** free value before removing from blackboard, supports instanced keys */
	void WrappedFree(UPZ_SkillTreeContext& OwnerComp, uint8* MemoryBlock);

	/** sets value to the default, supports instanced keys */
	void WrappedClear(const UPZ_SkillTreeContext& OwnerComp, uint8* MemoryBlock) const;

	/** check if key has stored value, supports instanced keys */
	bool WrappedIsEmpty(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock) const;

	/** various value testing, used by decorators, supports instanced keys */
	bool WrappedTestBasicOperation(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock, ESkillTreeBasicKeyOperation::Type Op) const;
	bool WrappedTestArithmeticOperation(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock, ESkillTreeArithmeticKeyOperation::Type Op, int32 OtherIntValue, float OtherFloatValue) const;
	bool WrappedTestTextOperation(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock, ESkillTreeTextKeyOperation::Type Op, const FString& OtherString) const;

	/** describe params of arithmetic test */
	virtual FString DescribeArithmeticParam(int32 IntValue, float FloatValue) const;

	/** convert value to text, supports instanced keys */
	FString WrappedDescribeValue(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock) const;

	/** description of params for property view */
	virtual FString DescribeSelf() const;

	/** create replacement key for deprecated data */
	virtual UPZ_SkillTreeBlackboardKeyType* UpdateDeprecatedKey();

	/** @return key instance if bCreateKeyInstance was set */
	const UPZ_SkillTreeBlackboardKeyType* GetKeyInstance(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock) const;
	UPZ_SkillTreeBlackboardKeyType* GetKeyInstance(UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock) const;

	/** compares two values */
	virtual ESkillTreeBlackboardCompare::Type CompareValues(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock,
		const UPZ_SkillTreeBlackboardKeyType* OtherKeyOb, const uint8* OtherMemoryBlock) const;


	/** @return true if key wants to be instanced */
	bool HasInstance() const;

	/** @return true if this object is instanced key */
	bool IsInstanced() const;

	/** get ValueSize */
	uint16 GetValueSize() const;

	/** get test supported by this type */
	ESkillTreeBlackboardKeyOperation::Type GetTestOperation() const;


protected:

	/** size of value for this type */
	uint16 ValueSize;

	/** decorator operation supported with this type */
	TEnumAsByte<ESkillTreeBlackboardKeyOperation::Type> SupportedOp;

	/** set automatically for node instances */
	uint8 bIsInstanced : 1;

	/** if set, key will be instanced instead of using memory block */
	uint8 bCreateKeyInstance : 1;






	/** helper function for reading typed data from memory block */
	template<typename T>
	static T GetValueFromMemory(const uint8* MemoryBlock)
	{
		return *((T*)MemoryBlock);
	}



	/** helper function for writing typed data to memory block, returns true if value has changed */
	template<typename T>
	static bool SetValueInMemory(uint8* MemoryBlock, const T& Value)
	{
		const bool bChanged = *((T*)MemoryBlock) != Value;
		*((T*)MemoryBlock) = Value;

		return bChanged;
	}



	/** helper function for witting weak object data to memory block, returns true if value has changed */
	template<typename T>
	static bool SetWeakObjectInMemory(uint8* MemoryBlock, const TWeakObjectPtr<T>& Value)
	{
		TWeakObjectPtr<T>* PrevValue = (TWeakObjectPtr<T>*)MemoryBlock;
		const bool bChanged =
			(Value.IsValid(false, true) != PrevValue->IsValid(false, true)) ||
			(Value.IsStale(false, true) != PrevValue->IsStale(false, true)) ||
			(*PrevValue) != Value;

		*((TWeakObjectPtr<T>*)MemoryBlock) = Value;

		return bChanged;
	}

	/** copy value from other key, works directly on provided memory/properties */
	virtual void CopyValues(UPZ_SkillTreeContext& OwnerComp, uint8* MemoryBlock, const UPZ_SkillTreeBlackboardKeyType* SourceKeyOb, const uint8* SourceBlock);

	/** initialize memory, works directly on provided memory/properties */
	virtual void InitializeMemory(UPZ_SkillTreeContext& OwnerComp, uint8* MemoryBlock);

	/** free value before removing from blackboard, works directly on provided memory/properties */
	virtual void FreeMemory(UPZ_SkillTreeContext& OwnerComp, uint8* MemoryBlock);

	/** extract location from entry, works directly on provided memory/properties */
	virtual bool GetLocation(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock, FVector& Location) const;

	/** extract rotation from entry, works directly on provided memory/properties */
	virtual bool GetRotation(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock, FRotator& Rotation) const;

	/** sets value to the default, works directly on provided memory/properties */
	virtual void Clear(UPZ_SkillTreeContext& OwnerComp, uint8* MemoryBlock);

	/** check if key has stored value, works directly on provided memory/properties */
	virtual bool IsEmpty(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock) const;

	/** various value testing, works directly on provided memory/properties */
	virtual bool TestBasicOperation(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock, ESkillTreeBasicKeyOperation::Type Op) const;
	virtual bool TestArithmeticOperation(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock, ESkillTreeArithmeticKeyOperation::Type Op, int32 OtherIntValue, float OtherFloatValue) const;
	virtual bool TestTextOperation(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock, ESkillTreeTextKeyOperation::Type Op, const FString& OtherString) const;

	/** convert value to text, works directly on provided memory/properties */
	virtual FString DescribeValue(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock) const;


};



//////////////////////////////////////////////////////////////////////////
// Inlines

FORCEINLINE uint16 UPZ_SkillTreeBlackboardKeyType::GetValueSize() const
{
	return ValueSize;
}

FORCEINLINE ESkillTreeBlackboardKeyOperation::Type UPZ_SkillTreeBlackboardKeyType::GetTestOperation() const
{
	return SupportedOp;
}

FORCEINLINE bool UPZ_SkillTreeBlackboardKeyType::HasInstance() const
{
	return bCreateKeyInstance;
}

FORCEINLINE bool UPZ_SkillTreeBlackboardKeyType::IsInstanced() const
{
	return bIsInstanced;
}