// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WorkflowOrientedApp/WorkflowCentricApplication.h"
#include "WorkflowOrientedApp/WorkflowTabManager.h"
#include "SGraphPanel.h"



class UPZ_SkillTree_Editor;
class UPZ_SkillTreeEdGraph;
class UPZ_SkillTreeUIPositionEdGraph;



class FPZ_SkillTreeGraph : public FWorkflowCentricApplication, public FNotifyHook, public FEditorUndoClient
{
	friend class FPZ_SkillTreeStructureEditorMode;
	friend class FPZ_SkillTreeUIPositionEditorMode;


public:

	FPZ_SkillTreeGraph();
	virtual ~FPZ_SkillTreeGraph();



public:

	void InitSkillTreeGraph(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UPZ_SkillTree_Editor* Editor);

private:

	void CreateCommandList();
	void BindCommands();
	void CreateStructureEdGraph();
	void CreateUIPositionEdGraph();
	void CreateInternalWidgets();

	void CreateToolbarTab();
	void CreatePropertiesWidget();



public:

	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;


	// FAssetEditorToolkit
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FText GetToolkitName() const override;
	virtual FText GetToolkitToolTipText() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FString GetDocumentationLink() const override;
	virtual bool OnRequestClose() override;

	bool virtual CanSaveAsset() const override;
	void virtual SaveAsset_Execute() override;
	bool virtual CanSaveAssetAs() const override;
	void virtual SaveAssetAs_Execute() override;
	// End of FAssetEditorToolkit

	//FEditorUndoClient Interface///
	virtual void PostUndo(bool bSuccess) override;
	virtual void PostRedo(bool bSuccess) override;


	bool GetSelectedNodesBounds(FSlateRect& Bounds, float Padding);

	TSharedPtr<SGraphEditor> GetViewportWidget();
	TSharedRef<SWidget> GetPropertyWidget();


protected:

	void FillToolbar(FToolBarBuilder& ToolbarBuilder);
	void FillStructureGraphToolbar(FToolBarBuilder& ToolbarBuilder);
	void FillUIPositionGraphToolbar(FToolBarBuilder& ToolbarBuilder);
	TSharedRef<SGraphEditor> CreateStructureGraphEditorWidget();
	TSharedRef<SGraphEditor> CreateUIPositionGraphEditorWidget();



private:
	//paste support
	inline void PasteNode_CalcAvaragePosition(UEdGraphNode* PastedNode, FVector2D& AvarageValue, int& AvarageCounter);
	inline void PasteNode(TSharedPtr<SGraphEditor> InViewportWidget, UEdGraphNode* PastedNode, const FVector2D& AvgNodePosition, const FVector2D& PasteLocation);


	// Delegates for graph editor commands
	void SelectAllNodes();
	bool CanSelectAllNodes();
	void DeleteSelectedNodes();
	bool CanDeleteNodes();
	void CutSelectedNodes();
	bool CanCutNodes();
	void CopySelectedNodes();
	bool CanCopyNodes();
	void PasteNodes();
	bool CanPasteNodes();
	void DuplicateNodes();
	bool CanDuplicateNodes();
	void OnRenameNode();
	bool CanRenameNodes();
	void CreateComment();
	bool CanCreateComment();
	void OnCommandUndoGraphAction();
	void OnCommandRedoGraphAction();

	void RebuildSkillTree();
	bool CanRebuildSkillTree();



	void CompileUIGraph();
	bool CanCompileUIGraph();


	void SetTreeStructureMode();
	bool CanSetTreeStructureMode();
	bool IsTreeStructureMode();

	void SetUIPositionMode();
	bool CanSetUIPositionMode();
	bool IsUIPositionMode();

	


	// graph editor event
	void OnSelectedNodesChanged(const TSet<class UObject*>& NewSelection);
	void OnNodeDoubleClicked(UEdGraphNode* Node);
	void OnNodeTitleCommitted(const FText& NewText, ETextCommit::Type CommitInfo, UEdGraphNode* NodeBeingChanged);
	void OnFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent);
	void OnPackageSaved(const FString& PackageFileName, UObject* Outer);
	



	void Refresh();
	void RefreshViewport();
	void RefreshDetailsView();




private:

	UPZ_SkillTree_Editor* SkillTree = nullptr;
	UPZ_SkillTreeEdGraph* StructureEdGraph = nullptr;
	UPZ_SkillTreeUIPositionEdGraph* UIPositionEdGraph = nullptr;


	TSharedPtr<SGraphEditor> ViewportWidget;
	TSharedPtr<class IDetailsView> PropertyWidget;
	TSharedPtr<FExtender> ToolbarExtender;


	FDelegateHandle OnPackageSavedDelegateHandle;


	/* The command list for this editor */
	TSharedPtr<FUICommandList> GraphEditorCommands;

};
