// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "PZ_SkillTreeNodesInfo.h"

#include "SkillTreeBlackBoard/SkillTreeBlackboardData.h"

#include "PZ_SkillTreeContext.generated.h"




class UPZ_SkillTree_Editor;
class UPZ_SkillTreeRBaseTreeElement;
class UPZ_SkillTreeRBaseNode;
class UPZ_SkillTreeREventNode;
class UPZ_SkillTreeRUINode;
class UPZ_SkillTreeBlackboardKeyType;
class UPZ_SkillTreeComponent;



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnIsOpenChangeBind, int, SkillIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLvlChangeBind, int, SkillIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCanBeOpenChangeBind, int, SkillIndex);

USTRUCT(BlueprintType)
struct PZ_SKILLTREE_API FContextNodeInfo
{

	GENERATED_USTRUCT_BODY()

	FContextNodeInfo() {};
	FContextNodeInfo(UPZ_SkillTreeRBaseTreeElement* InRNode, UPZ_SkillTreeContext* InOwnerContext) :
		RNode(InRNode),
		OwnerContext(InOwnerContext) 
	{};


private:

	UPZ_SkillTreeRBaseTreeElement* RNode;
	UPZ_SkillTreeContext* OwnerContext;

public:


	int CurrentSkillLvl = 0;

	bool IsOpen = false;

	bool CanBeOpen = false;
	
	int SwichNodeCount = 0;


	////////////Этот блок тут как попытка запретить редактирование RNode (но их отсутствие делает невозможным создание деревьев до создания контекста)/////////////// 
	//////Вероятно, нужно будет удалить
	UPZ_SkillTreeRBaseTreeElement const * GetRNode() const { return RNode; } ;
	UPZ_SkillTreeRUINode const* GetRUINode() const;

	void GetNextNodesInfo(TArray<FContextNodeInfo>& NodeInfoArray);
	void GetPrevNodesInfo(TArray<FContextNodeInfo>& NodeInfoArray);

	void GetNextNodesInfo_WithUI(TArray<FContextNodeInfo>& NodeInfoArray);
	void GetPrevNodesInfo_WithUI(TArray<FContextNodeInfo>& NodeInfoArray);
	//////////////////////////////


	bool operator == (const FContextNodeInfo& TargetContextNodeInfo) const
	{
		return (RNode == TargetContextNodeInfo.RNode);
	}

	bool operator != (const FContextNodeInfo& TargetContextNodeInfo) const
	{
		return (RNode != TargetContextNodeInfo.RNode);
	}
};







UCLASS(BlueprintType)
class PZ_SKILLTREE_API UPZ_SkillTreeContext : public UObject
{
	GENERATED_BODY()


//constructor
public:

	UPZ_SkillTreeContext() {}
	UPZ_SkillTreeContext(UPZ_SkillTree_Editor* SkillTree, AActor* PlayerCharacter, UPZ_SkillTreeComponent* InSTComponent);

	void InitContext(UPZ_SkillTree_Editor* SkillTree, AActor* PlayerCharacter, UPZ_SkillTreeComponent* InSTComponent);



	/** setup component for using given blackboard asset, returns true if blackboard is properly initialized for specified blackboard data */
	bool InitializeBlackboard();








//c++ public methods:
public:
	// TODO тут часть нужно унести в pivat/protected
	///////////////////////////// Execute For Nodes /////////////////////////////

	void ExecuteEvents(const TArray<class UPZ_SkillTreeEvent*>& Events);

	bool ExecuteCondition(const TArray<class UPZ_SkillTreeCondition*>& Conditions);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



	void UpdateNextNodes(UPZ_SkillTreeRBaseTreeElement* AnchorNode);
	//void UpdateNextNode();
	void UpdatePreviousNodes(UPZ_SkillTreeRBaseTreeElement* AnchorNode);
	//void UpdatePreviousNode();



	void ExecuteNode(UPZ_SkillTreeRBaseTreeElement* SkillNode);


	bool CanExecuteEvent(UPZ_SkillTreeREventNode* EventNode);


	void GetRootNodeInfos(TArray<FContextNodeInfo>& NodeInfoArray);
	const FContextNodeInfo& GetRootUINodeInfo();


//c++ protected methods
protected:

	virtual void BeginDestroy() override;



	TArray<UPZ_SkillTreeRBaseTreeElement*> GetNextNodes(UPZ_SkillTreeRBaseTreeElement* AnchorNode);

	TArray<UPZ_SkillTreeRBaseTreeElement*> GetPreviousNodes(UPZ_SkillTreeRBaseTreeElement* AnchorNode);


	void GetNextNodesToUpdate(UPZ_SkillTreeRBaseTreeElement* AnchorNode, TArray<UPZ_SkillTreeRBaseTreeElement*>& NextNodesArray);
	void GetPrevNodesToUpdate(UPZ_SkillTreeRBaseTreeElement* AnchorNode, TArray<UPZ_SkillTreeRBaseTreeElement*>& PrevNodesArray);

	bool IsHavePrevSkillNode(UPZ_SkillTreeRSkillNode* InSkillNode);

//Blueprint methods
public:


	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SkillTree | SkillTreeContext")
		UPZ_SkillTree_Editor* GetImplementedSkillTree() const;

	UFUNCTION(BlueprintCallable, Category = "SkillTree|Context|Events")
		bool CanExecuteEventByName(const FName& EventName);

	UFUNCTION(BlueprintCallable, Category = "SkillTree|Context|Events")
		bool ExecudeEventNode(FName EventNodeName);

	UFUNCTION(BlueprintCallable, Category = "SkillTree|Context|Events")
		bool CanExecuteSkillNode(UPZ_SkillTreeRSkillNode* InSkillNode);

	UFUNCTION(BlueprintCallable, Category = "SkillTree|Context|UI_POS")
		FVector2D GetNodeUILocationByIndex(int NodeIndex);





//Blueprint Values
public:
	UPROPERTY(BlueprintReadOnly, Category = "SkillTree | SkillTreeContext")
		UPZ_SkillTreeComponent* STComponent = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "SkillTree | SkillTreeContext")
		UPZ_SkillTreeRBaseTreeElement* CurrentNode = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "SkillTree | SkillTreeContext")
		UPZ_SkillTree_Editor* ImplementSkillTree = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "SkillTree | SkillTreeContext")
		AActor* Player = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "SkillTree | SkillTreeContext")
		TMap<int, FContextNodeInfo> ContextNodeInfo;




	FOnIsOpenChangeBind OnIsOpenChangeBind;
	FOnLvlChangeBind OnLvlChangeBind;
	FOnCanBeOpenChangeBind OnCanBeOpenChangeBind;





/////////////////////////////////////////////// BlackBoard methods ///////////////////////////////////////////////



//c++ private methods:
private:

	/** @return key ID from name */
	FBlackboard::FKey GetKeyID(const FName& KeyName) const;


	/** Uninitialize BlackBoard */
	void DestroyValues();

	template<class TDataClass>
	bool IsKeyOfType(FBlackboard::FKey KeyID) const;

	template<class TDataClass>
	bool SetValue(const FName& KeyName, typename TDataClass::FDataType Value);

	template<class TDataClass>
	bool SetValue(FBlackboard::FKey KeyID, typename TDataClass::FDataType Value);

	template<class TDataClass>
	typename TDataClass::FDataType GetValue(const FName& KeyName) const;

	template<class TDataClass>
	typename TDataClass::FDataType GetValue(FBlackboard::FKey KeyID) const;


	




	
//Blueprint public methods:
public:

	UFUNCTION(BlueprintCallable, Category = "SkillTree|Context|Blackboard")
		UObject* GetValueAsObject(const FName& KeyName) const;

	UFUNCTION(BlueprintCallable, Category = "SkillTree|Context|Blackboard")
		UClass* GetValueAsClass(const FName& KeyName) const;

	UFUNCTION(BlueprintCallable, Category = "SkillTree|Context|Blackboard")
		uint8 GetValueAsEnum(const FName& KeyName) const;

	UFUNCTION(BlueprintCallable, Category = "SkillTree|Context|Blackboard")
		int32 GetValueAsInt(const FName& KeyName) const;

	UFUNCTION(BlueprintCallable, Category = "SkillTree|Context|Blackboard")
		float GetValueAsFloat(const FName& KeyName) const;

	UFUNCTION(BlueprintCallable, Category = "SkillTree|Context|Blackboard")
		bool GetValueAsBool(const FName& KeyName) const;

	UFUNCTION(BlueprintCallable, Category = "SkillTree|Context|Blackboard")
		FString GetValueAsString(const FName& KeyName) const;

	UFUNCTION(BlueprintCallable, Category = "SkillTree|Context|Blackboard")
		FName GetValueAsName(const FName& KeyName) const;

	UFUNCTION(BlueprintCallable, Category = "SkillTree|Context|Blackboard")
		FVector GetValueAsVector(const FName& KeyName) const;

	UFUNCTION(BlueprintCallable, Category = "SkillTree|Context|Blackboard")
		FRotator GetValueAsRotator(const FName& KeyName) const;

	UFUNCTION(BlueprintCallable, Category = "SkillTree|Context|Blackboard")
		void SetValueAsObject(const FName& KeyName, UObject* ObjectValue);

	UFUNCTION(BlueprintCallable, Category = "SkillTree|Context|Blackboard")
		void SetValueAsClass(const FName& KeyName, UClass* ClassValue);

	UFUNCTION(BlueprintCallable, Category = "SkillTree|Context|Blackboard")
		void SetValueAsEnum(const FName& KeyName, uint8 EnumValue);

	UFUNCTION(BlueprintCallable, Category = "SkillTree|Context|Blackboard")
		void SetValueAsInt(const FName& KeyName, int32 IntValue);

	UFUNCTION(BlueprintCallable, Category = "SkillTree|Context|Blackboard")
		void SetValueAsFloat(const FName& KeyName, float FloatValue);

	UFUNCTION(BlueprintCallable, Category = "SkillTree|Context|Blackboard")
		void SetValueAsBool(const FName& KeyName, bool BoolValue);

	UFUNCTION(BlueprintCallable, Category = "SkillTree|Context|Blackboard")
		void SetValueAsString(const FName& KeyName, FString StringValue);

	UFUNCTION(BlueprintCallable, Category = "SkillTree|Context|Blackboard")
		void SetValueAsName(const FName& KeyName, FName NameValue);

	UFUNCTION(BlueprintCallable, Category = "SkillTree|Context|Blackboard")
		void SetValueAsVector(const FName& KeyName, FVector VectorValue);

	UFUNCTION(BlueprintCallable, Category = "SkillTree|Context|Blackboard")
		void SetValueAsRotator(const FName& KeyName, FRotator VectorValue);



	/** get pointer to raw data for given key */
	FORCEINLINE uint8* GetKeyRawData(const FName& KeyName) { return GetKeyRawData(GetKeyID(KeyName)); }
	FORCEINLINE uint8* GetKeyRawData(FBlackboard::FKey KeyID) { return ValueMemory.Num() && ValueOffsets.IsValidIndex(KeyID) ? (ValueMemory.GetData() + ValueOffsets[KeyID]) : NULL; }

	FORCEINLINE const uint8* GetKeyRawData(const FName& KeyName) const { return GetKeyRawData(GetKeyID(KeyName)); }

	FORCEINLINE const uint8* GetKeyRawData(FBlackboard::FKey KeyID) const { return ValueMemory.Num() && ValueOffsets.IsValidIndex(KeyID) ? (ValueMemory.GetData() + ValueOffsets[KeyID]) : NULL; }



//c++ public Values
public:

	/** instanced keys with custom data allocations */
	UPROPERTY(transient)
		TArray<UPZ_SkillTreeBlackboardKeyType*> KeyInstances;

//c++ private Values
private:

	/** memory block holding all values */
	TArray<uint8> ValueMemory;

	/** offsets in ValueMemory for each key */
	TArray<uint16> ValueOffsets;

	TArray<FSkillTreeBlackboardEntry> BlackBoardValues;

	UPZ_SkillTreeComponent* SkillTreeComponent;



};
