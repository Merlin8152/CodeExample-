// Fill out your copyright notice in the Description page of Project Settings.


#include "PZ_SkillTreeGraphEditor.h"

#include "PZ_SkillTree_Editor.h"

#include "StructureGraph/Graph/PZ_SkillTreeStructureEdGraph.h"
#include "StructureGraph/Graph/PZ_SkillTreeStructureEdGraphSchema.h"
#include "UIPositionGraph/Graph/PZ_SkillTreeUIPositionEdGraph.h"
#include "UIPositionGraph/Graph/PZ_SkillTreeUIPositionEdGraphSchema.h"

#include "PZ_SkillTreeEditor/Private/SkillTreeModes/PZ_SkillTreeEditorModes.h"
#include "PZ_SkillTreeEditor/Private/SkillTreeModes/PZ_SkillTreeStructureEditorMode.h"
#include "PZ_SkillTreeEditor/Private/SkillTreeModes/PZ_SkillTreeUIPositionMode.h"

#include "SkillTreeTabsFactories/PZ_SkillTreeEditorTabs.h"
#include "PZ_SkillTreeGraphEditorCommands.h"
#include "PZ_SkillTreeEditorStyle.h"

#include "StructureGraph/Nodes/PZ_SkillTreeNodeInterface.h"
#include "StructureGraph/Nodes/EdgePoint/PZ_SkillTreeEdNode_Edge.h"
#include "StructureGraph/Nodes/BaseNode/PZ_SkillTreeEdNode_Base.h"

#include "UIPositionGraph/Nodes/BaseNode/PZ_SkillTreeUIPositionEdNode_Base.h"

#include "Nodes/UINode/PZ_SkillTreeRUINode.h"

#include "Toolkits/AssetEditorManager.h"
#include "Toolkits/AssetEditorToolkit.h"

#include "Framework/Commands/GenericCommands.h"
#include "Framework/Docking/TabManager.h"

#include "GraphEditorActions.h"
#include "EdGraphUtilities.h"

#include "Editor/UnrealEd/Public/Kismet2/BlueprintEditorUtils.h"
#include "HAL/PlatformApplicationMisc.h"





const FName SkillTreeGraphEditorAppName = FName(TEXT("SkillTreeGraphEditorAppName"));





FPZ_SkillTreeGraph::FPZ_SkillTreeGraph()
{
	GEditor->RegisterForUndo(this);

	OnPackageSavedDelegateHandle = UPackage::PackageSavedEvent.AddRaw(this, &FPZ_SkillTreeGraph::OnPackageSaved);
}

FPZ_SkillTreeGraph::~FPZ_SkillTreeGraph()
{
	UPackage::PackageSavedEvent.Remove(OnPackageSavedDelegateHandle);

	GEditor->UnregisterForUndo(this);
}






void FPZ_SkillTreeGraph::InitSkillTreeGraph(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UPZ_SkillTree_Editor* Editor)
{
	FGenericCommands::Register();
	FGraphEditorCommands::Register();
	FPZ_SkillTreeGraphCommands::Register();

	SkillTree = Editor;


	CreateStructureEdGraph();
	CreateUIPositionEdGraph();
	CreateCommandList();
	BindCommands();
	CreateInternalWidgets();


	const TSharedRef<FTabManager::FLayout> DummyLayout = FTabManager::NewLayout("NullLayout")->AddArea(FTabManager::NewPrimaryArea());

	const bool bCreateDefaultStandaloneMenu = true;
	const bool bCreateDefaultToolbar = true;
	FAssetEditorToolkit::InitAssetEditor(Mode, InitToolkitHost, SkillTreeGraphEditorAppName, DummyLayout, bCreateDefaultStandaloneMenu, bCreateDefaultToolbar, SkillTree, false);


	AddApplicationMode
	(
		FPZ_SkillTreeGraphEditor_Modes::StructureEditMode,
		MakeShareable(new FPZ_SkillTreeStructureEditorMode(SharedThis(this)))
	);

	AddApplicationMode
	(
		FPZ_SkillTreeGraphEditor_Modes::UIPositionMode,
		MakeShareable(new FPZ_SkillTreeUIPositionEditorMode(SharedThis(this)))
	);

	SetCurrentMode(FPZ_SkillTreeGraphEditor_Modes::StructureEditMode);



	RegenerateMenusAndToolbars();
}


void FPZ_SkillTreeGraph::CreateCommandList()
{

	if (GraphEditorCommands.IsValid()) return;


	GraphEditorCommands = MakeShareable(new FUICommandList);



	GraphEditorCommands->MapAction(FGenericCommands::Get().SelectAll,
		FExecuteAction::CreateRaw(this, &FPZ_SkillTreeGraph::SelectAllNodes),
		FCanExecuteAction::CreateRaw(this, &FPZ_SkillTreeGraph::CanSelectAllNodes)
	);

	GraphEditorCommands->MapAction(FGenericCommands::Get().Delete,
		FExecuteAction::CreateRaw(this, &FPZ_SkillTreeGraph::DeleteSelectedNodes),
		FCanExecuteAction::CreateRaw(this, &FPZ_SkillTreeGraph::CanDeleteNodes)
	);

	GraphEditorCommands->MapAction(FGenericCommands::Get().Copy,
		FExecuteAction::CreateRaw(this, &FPZ_SkillTreeGraph::CopySelectedNodes),
		FCanExecuteAction::CreateRaw(this, &FPZ_SkillTreeGraph::CanCopyNodes)
	);

	GraphEditorCommands->MapAction(FGenericCommands::Get().Cut,
		FExecuteAction::CreateRaw(this, &FPZ_SkillTreeGraph::CutSelectedNodes),
		FCanExecuteAction::CreateRaw(this, &FPZ_SkillTreeGraph::CanCutNodes)
	);

	GraphEditorCommands->MapAction(FGenericCommands::Get().Paste,
		FExecuteAction::CreateRaw(this, &FPZ_SkillTreeGraph::PasteNodes),
		FCanExecuteAction::CreateRaw(this, &FPZ_SkillTreeGraph::CanPasteNodes)
	);

	GraphEditorCommands->MapAction(FGenericCommands::Get().Duplicate,
		FExecuteAction::CreateRaw(this, &FPZ_SkillTreeGraph::DuplicateNodes),
		FCanExecuteAction::CreateRaw(this, &FPZ_SkillTreeGraph::CanDuplicateNodes)
	);

	GraphEditorCommands->MapAction(FGenericCommands::Get().Rename,
		FExecuteAction::CreateSP(this, &FPZ_SkillTreeGraph::OnRenameNode),
		FCanExecuteAction::CreateSP(this, &FPZ_SkillTreeGraph::CanRenameNodes)
	);

	GraphEditorCommands->MapAction(FGraphEditorCommands::Get().CreateComment,
		FExecuteAction::CreateSP(this, &FPZ_SkillTreeGraph::CreateComment),
		FCanExecuteAction::CreateSP(this, &FPZ_SkillTreeGraph::CanCreateComment)
	);

}

void FPZ_SkillTreeGraph::BindCommands()
{

	ToolkitCommands->MapAction(
		FGenericCommands::Get().Undo,
		FExecuteAction::CreateSP(this, &FPZ_SkillTreeGraph::OnCommandUndoGraphAction)
	);

	ToolkitCommands->MapAction(
		FGenericCommands::Get().Redo,
		FExecuteAction::CreateSP(this, &FPZ_SkillTreeGraph::OnCommandRedoGraphAction)
	);



	ToolkitCommands->MapAction(FPZ_SkillTreeGraphCommands::Get().RebuildSkillTree,
		FExecuteAction::CreateSP(this, &FPZ_SkillTreeGraph::RebuildSkillTree),
		FCanExecuteAction::CreateSP(this, &FPZ_SkillTreeGraph::CanRebuildSkillTree)
	);

	ToolkitCommands->MapAction(FPZ_SkillTreeGraphCommands::Get().CompileUI,
		FExecuteAction::CreateSP(this, &FPZ_SkillTreeGraph::CompileUIGraph),
		FCanExecuteAction::CreateSP(this, &FPZ_SkillTreeGraph::CanCompileUIGraph)
	);

	ToolkitCommands->MapAction(FPZ_SkillTreeGraphCommands::Get().SetTreeStructureMode,
		FExecuteAction::CreateSP(this, &FPZ_SkillTreeGraph::SetTreeStructureMode),
		FCanExecuteAction::CreateSP(this, &FPZ_SkillTreeGraph::CanSetTreeStructureMode),
		FIsActionChecked::CreateSP(this, &FPZ_SkillTreeGraph::IsTreeStructureMode)
	);

	ToolkitCommands->MapAction(FPZ_SkillTreeGraphCommands::Get().SetUIPositionMode,
		FExecuteAction::CreateSP(this, &FPZ_SkillTreeGraph::SetUIPositionMode),
		FCanExecuteAction::CreateSP(this, &FPZ_SkillTreeGraph::CanSetUIPositionMode),
		FIsActionChecked::CreateSP(this, &FPZ_SkillTreeGraph::IsUIPositionMode)
	);

}




void FPZ_SkillTreeGraph::CreateStructureEdGraph()
{
	if (!IsValid(SkillTree->StructureEdGraph))
	{
		StructureEdGraph = CastChecked<UPZ_SkillTreeEdGraph>(FBlueprintEditorUtils::CreateNewGraph(SkillTree, NAME_None, UPZ_SkillTreeEdGraph::StaticClass(), UPZ_SkillTreeEdGraphSchema::StaticClass()));

		SkillTree->StructureEdGraph = StructureEdGraph;
		
		// Give the schema a chance to fill out any required nodes (like the results node)
		const UEdGraphSchema* StructureGraphSchema = StructureEdGraph->GetSchema();
		StructureGraphSchema->CreateDefaultNodesForGraph(*StructureEdGraph);
	}
	else
	{
		StructureEdGraph = Cast<UPZ_SkillTreeEdGraph>(SkillTree->StructureEdGraph);
	}
	

	StructureEdGraph->SkillTreeGraph = this;
	StructureEdGraph->SkillTree = SkillTree;
	StructureEdGraph->bAllowDeletion = false;
}

void FPZ_SkillTreeGraph::CreateUIPositionEdGraph()
{
	if (!IsValid(SkillTree->UIPositionEdGraph))
	{
		UIPositionEdGraph = CastChecked<UPZ_SkillTreeUIPositionEdGraph>(FBlueprintEditorUtils::CreateNewGraph(SkillTree, NAME_None, UPZ_SkillTreeUIPositionEdGraph::StaticClass(), UPZ_SkillTreeUIPositionEdGraphSchema::StaticClass()));

		SkillTree->UIPositionEdGraph = UIPositionEdGraph;

		const UEdGraphSchema* UIPositionSchema = UIPositionEdGraph->GetSchema();
		UIPositionSchema->CreateDefaultNodesForGraph(*UIPositionEdGraph);
		
	}
	else
	{
		UIPositionEdGraph = Cast<UPZ_SkillTreeUIPositionEdGraph>(SkillTree->UIPositionEdGraph);
	}
	

	UIPositionEdGraph->SkillTreeGraph = this;
	UIPositionEdGraph->SkillTree = SkillTree;
	UIPositionEdGraph->bAllowDeletion = false;
}




void FPZ_SkillTreeGraph::CreateInternalWidgets()
{
	//ViewportWidget created at tabs
	CreateToolbarTab();
	CreatePropertiesWidget();
}

void FPZ_SkillTreeGraph::CreateToolbarTab()
{
	if (!ToolbarExtender.IsValid())
	{
		ToolbarExtender = MakeShareable(new FExtender);
	}

	ToolbarExtender->AddToolBarExtension("Asset", EExtensionHook::After, GetToolkitCommands(), FToolBarExtensionDelegate::CreateSP(this, &FPZ_SkillTreeGraph::FillToolbar));
	AddToolbarExtender(ToolbarExtender);

}


void FPZ_SkillTreeGraph::CreatePropertiesWidget()
{
	FDetailsViewArgs Args;
	Args.bHideSelectionTip = true;
	Args.NotifyHook = this;


	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyWidget = PropertyModule.CreateDetailView(Args);
	PropertyWidget->SetObject(SkillTree);
	PropertyWidget->OnFinishedChangingProperties().AddSP(this, &FPZ_SkillTreeGraph::OnFinishedChangingProperties);
}






void FPZ_SkillTreeGraph::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);
}

void FPZ_SkillTreeGraph::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);
}







FName FPZ_SkillTreeGraph::GetToolkitFName() const
{
	return FName("FSkillTreeEditor");
}

FText FPZ_SkillTreeGraph::GetBaseToolkitName() const
{
	return FText::FromString("SkillTree Editor");
}

FText FPZ_SkillTreeGraph::GetToolkitName() const
{
	return FText::FromString(SkillTree->GetName());
}

FText FPZ_SkillTreeGraph::GetToolkitToolTipText() const
{
	return FAssetEditorToolkit::GetToolTipTextForObject(SkillTree);
}

FLinearColor FPZ_SkillTreeGraph::GetWorldCentricTabColorScale() const
{
	return FLinearColor::White;
}

FString FPZ_SkillTreeGraph::GetWorldCentricTabPrefix() const
{
	return FString("SkillTreeEditor");
}

FString FPZ_SkillTreeGraph::GetDocumentationLink() const
{
	return FString("");
}

bool FPZ_SkillTreeGraph::OnRequestClose()
{
	//TODO

	return FAssetEditorToolkit::OnRequestClose();
}





bool FPZ_SkillTreeGraph::CanSaveAsset() const
{
	return true;
}

void FPZ_SkillTreeGraph::SaveAsset_Execute()
{
	//TODO

	FAssetEditorToolkit::SaveAsset_Execute();
}

bool FPZ_SkillTreeGraph::CanSaveAssetAs() const
{
	return true;
}

void FPZ_SkillTreeGraph::SaveAssetAs_Execute()
{
	//TODO

	FAssetEditorToolkit::SaveAssetAs_Execute();
}





void FPZ_SkillTreeGraph::PostUndo(bool bSuccess)
{
	if (bSuccess)
	{
		Refresh();

		SkillTree->NeedToRebuild = true;
		RegenerateMenusAndToolbars();
	}
}

void FPZ_SkillTreeGraph::PostRedo(bool bSuccess)
{
	if (bSuccess)
	{
		Refresh();

		SkillTree->NeedToRebuild = true;
		RegenerateMenusAndToolbars();
	}
}





bool FPZ_SkillTreeGraph::GetSelectedNodesBounds(FSlateRect& Bounds, float Padding)
{
	return ViewportWidget->GetBoundsForSelectedNodes(Bounds, Padding);
}



TSharedPtr<SGraphEditor> FPZ_SkillTreeGraph::GetViewportWidget()
{
	return ViewportWidget;
}

TSharedRef<SWidget> FPZ_SkillTreeGraph::GetPropertyWidget()
{
	return PropertyWidget.ToSharedRef();
}














TSharedRef<SGraphEditor> FPZ_SkillTreeGraph::CreateStructureGraphEditorWidget()
{
	PropertyWidget->SetObject(SkillTree);
	FGraphAppearanceInfo AppearanceInfo;
	AppearanceInfo.CornerText = FText::FromString("SkillTree Graph");

	SGraphEditor::FGraphEditorEvents InEvents;
	InEvents.OnSelectionChanged = SGraphEditor::FOnSelectionChanged::CreateSP(this, &FPZ_SkillTreeGraph::OnSelectedNodesChanged);
	InEvents.OnNodeDoubleClicked = FSingleNodeEvent::CreateSP(this, &FPZ_SkillTreeGraph::OnNodeDoubleClicked);
	InEvents.OnTextCommitted = FOnNodeTextCommitted::CreateSP(this, &FPZ_SkillTreeGraph::OnNodeTitleCommitted);
	SAssignNew(ViewportWidget, SGraphEditor)
		.AdditionalCommands(GraphEditorCommands)
		.IsEditable(true)
		.Appearance(AppearanceInfo)
		.GraphToEdit(StructureEdGraph)
		.GraphEvents(InEvents)
		.AutoExpandActionMenu(true)
		.ShowGraphStateOverlay(false)
		;


	return ViewportWidget.ToSharedRef();
}

TSharedRef<SGraphEditor> FPZ_SkillTreeGraph::CreateUIPositionGraphEditorWidget()
{
	PropertyWidget->SetObject(nullptr);
	UIPositionEdGraph->RebuildGraph(/*SkillTree->GetCompiledSkillNodesLink()*/);

	FGraphAppearanceInfo AppearanceInfo;
	AppearanceInfo.CornerText = FText::FromString("SkillTree Graph");

	SGraphEditor::FGraphEditorEvents InEvents;
	InEvents.OnSelectionChanged = SGraphEditor::FOnSelectionChanged::CreateSP(this, &FPZ_SkillTreeGraph::OnSelectedNodesChanged);

	return SAssignNew(ViewportWidget, SGraphEditor)
		.IsEditable(true)
		.Appearance(AppearanceInfo)
		.GraphToEdit(UIPositionEdGraph)
		.GraphEvents(InEvents)
		.AutoExpandActionMenu(true)
		.ShowGraphStateOverlay(false)
		;

}


void FPZ_SkillTreeGraph::FillToolbar(FToolBarBuilder& ToolbarBuilder)
{
	ToolbarBuilder.BeginSection("Mode Selection");
	{
		ToolbarBuilder.AddToolBarButton
		(
			FPZ_SkillTreeGraphCommands::Get().SetTreeStructureMode,
			NAME_None,
			FText::FromString("Structure Mode"),
			FText::FromString("Structure Mode"),
			FSlateIcon(FPZ_SkillTreeEditorStyle::GetStyleSetName(), "SkillTreeEditor.NeedRebuildSkillTree")
		);
		ToolbarBuilder.AddToolBarButton
		(
			FPZ_SkillTreeGraphCommands::Get().SetUIPositionMode,
			NAME_None,
			FText::FromString("UIPosition Mode"),
			FText::FromString("UIPosition Mode"),
			FSlateIcon(FPZ_SkillTreeEditorStyle::GetStyleSetName(), "SkillTreeEditor.NeedRebuildSkillTree")
		);
	}
	ToolbarBuilder.EndSection();
}

void FPZ_SkillTreeGraph::FillStructureGraphToolbar(FToolBarBuilder& ToolbarBuilder)
{
	ToolbarBuilder.BeginSection("StructureGraph");
	{
		ToolbarBuilder.AddToolBarButton
		(
			FPZ_SkillTreeGraphCommands::Get().RebuildSkillTree,
			NAME_None,
			FText::FromString("Rebuild"),
			FText::FromString("Rebuild"),
			(SkillTree->NeedToRebuild) ? FSlateIcon(FPZ_SkillTreeEditorStyle::GetStyleSetName(), "SkillTreeEditor.NeedRebuildSkillTree") : FSlateIcon(FPZ_SkillTreeEditorStyle::GetStyleSetName(), "SkillTreeEditor.RebuildSkillTree")

		);

	}
	ToolbarBuilder.EndSection();
}

void FPZ_SkillTreeGraph::FillUIPositionGraphToolbar(FToolBarBuilder& ToolbarBuilder)
{
	ToolbarBuilder.BeginSection("StructureGraph");
	{
		ToolbarBuilder.AddToolBarButton
		(
			FPZ_SkillTreeGraphCommands::Get().CompileUI,
			NAME_None,
			FText::FromString("Compile"),
			FText::FromString("Compile"),
			(SkillTree->NeedCompileUI) ? FSlateIcon(FPZ_SkillTreeEditorStyle::GetStyleSetName(), "SkillTreeEditor.NeedRebuildSkillTree") : FSlateIcon(FPZ_SkillTreeEditorStyle::GetStyleSetName(), "SkillTreeEditor.RebuildSkillTree")

		);

	}
	ToolbarBuilder.EndSection();
}










void FPZ_SkillTreeGraph::PasteNode_CalcAvaragePosition(UEdGraphNode* PastedNode, FVector2D& AvarageValue, int& AvarageCounter)
{
	AvarageValue.X += PastedNode->NodePosX;
	AvarageValue.Y += PastedNode->NodePosY;
	++AvarageCounter;
}









void FPZ_SkillTreeGraph::PasteNode(TSharedPtr<SGraphEditor> InViewportWidget, UEdGraphNode* PastedNode, const FVector2D& AvgNodePosition, const FVector2D& PasteLocation)
{
	ViewportWidget->SetNodeSelection(PastedNode, true);

	PastedNode->NodePosX = (PastedNode->NodePosX - AvgNodePosition.X) + PasteLocation.X;
	PastedNode->NodePosY = (PastedNode->NodePosY - AvgNodePosition.Y) + PasteLocation.Y;


	// Give new node a different Guid from the old one
	PastedNode->CreateNewGuid();

}

void FPZ_SkillTreeGraph::SelectAllNodes()
{
	ViewportWidget->SelectAllNodes();
}

bool FPZ_SkillTreeGraph::CanSelectAllNodes()
{
	return true;
}
//.......................................//


void FPZ_SkillTreeGraph::DeleteSelectedNodes()
{

	const FScopedTransaction Transaction(FGenericCommands::Get().Delete->GetDescription());

	ViewportWidget->GetCurrentGraph()->Modify();

	const FGraphPanelSelectionSet SelectedNodes = ViewportWidget->GetSelectedNodes();
	ViewportWidget->ClearSelectionSet();

	for (auto& DeletingNode : SelectedNodes)
	{
		UEdGraphNode* EdNode = Cast<UEdGraphNode>(DeletingNode);
		if (EdNode == nullptr || !EdNode->CanUserDeleteNode())	continue;

		EdNode->GetSchema()->BreakNodeLinks(*EdNode);
		EdNode->Modify();
		EdNode->DestroyNode();
		
	}

	SkillTree->NeedToRebuild = true;
	RegenerateMenusAndToolbars();
}

bool FPZ_SkillTreeGraph::CanDeleteNodes()
{
	const FGraphPanelSelectionSet SelectedNodes = ViewportWidget->GetSelectedNodes();
	for (const auto& SelectedNode : SelectedNodes)
	{
		UEdGraphNode* Node = Cast<UEdGraphNode>(SelectedNode);
		if (Node && Node->CanUserDeleteNode())
		{
			return true;
		}
	}

	return false;
}
//.......................................//


void FPZ_SkillTreeGraph::CutSelectedNodes()
{
	CopySelectedNodes();
	DeleteSelectedNodes();
}

bool FPZ_SkillTreeGraph::CanCutNodes()
{
	return CanCopyNodes() && CanDeleteNodes();
}
//.......................................//


void FPZ_SkillTreeGraph::CopySelectedNodes()
{
	
	FGraphPanelSelectionSet SelectedNodes = ViewportWidget->GetSelectedNodes();
	TArray<UPZ_SkillTreeEdNode_Base*> SubNodes;

	int32 CopySubNodeIndex = 0;

	for (FGraphPanelSelectionSet::TIterator SelectedIter(SelectedNodes); SelectedIter; ++SelectedIter)
	{
		UEdGraphNode* Node = Cast<UEdGraphNode>(*SelectedIter);
		if (Node == nullptr)
		{
			SelectedIter.RemoveCurrent();
			continue;
		}

		if (UPZ_SkillTreeEdNode_Edge* EdNode_Edge = Cast<UPZ_SkillTreeEdNode_Edge>(*SelectedIter))
		{
			UEdGraphNode* StartNode = EdNode_Edge->GetStartNode();
			UEdGraphNode* EndNode = EdNode_Edge->GetEndNode();

			if (!SelectedNodes.Contains(StartNode) || !SelectedNodes.Contains(EndNode))
			{
				SelectedIter.RemoveCurrent();
				continue;
			}
		}
		Node->PrepareForCopying();


		UPZ_SkillTreeEdNode_Base* SkillTree_Node = Cast<UPZ_SkillTreeEdNode_Base>(Node);
		if (SkillTree_Node)
		{

			SkillTree_Node->CopySubNodeIndex = CopySubNodeIndex;

			// append all subnodes for selection
			for (int32 Idx = 0; Idx < SkillTree_Node->SubNodes.Num(); ++Idx)
			{
				SkillTree_Node->SubNodes[Idx]->CopySubNodeIndex = CopySubNodeIndex;
				SubNodes.Add(SkillTree_Node->SubNodes[Idx]);
			}

			++CopySubNodeIndex;

		}

	}

	for (int32 Idx = 0; Idx < SubNodes.Num(); ++Idx)
	{
		SelectedNodes.Add(SubNodes[Idx]);
		SubNodes[Idx]->PrepareForCopying();
	}


	FString ExportedText;
	FEdGraphUtilities::ExportNodesToText(SelectedNodes, ExportedText);
	FPlatformApplicationMisc::ClipboardCopy(*ExportedText);

}

bool FPZ_SkillTreeGraph::CanCopyNodes()
{
	
	const FGraphPanelSelectionSet SelectedNodes = ViewportWidget->GetSelectedNodes();
	for (const auto& SelectedNode : SelectedNodes)
	{
		UEdGraphNode* Node = Cast<UEdGraphNode>(SelectedNode);

		if (Node && Node->CanDuplicateNode())
		{
			return true;
		}
		
	}

	return false;
}
//.......................................//


void FPZ_SkillTreeGraph::PasteNodes()
{
	FVector2D PasteLocation = ViewportWidget->GetPasteLocation();

	UEdGraph* LGraph = ViewportWidget->GetCurrentGraph();


	const FScopedTransaction Transaction(FGenericCommands::Get().Paste->GetDescription());
	LGraph->Modify();


	UPZ_SkillTreeEdNode_Base* SelectedParent = NULL;
	bool bHasMultipleNodesSelected = false;

	const FGraphPanelSelectionSet SelectedNodes = ViewportWidget->GetSelectedNodes();
	for (FGraphPanelSelectionSet::TConstIterator SelectedIter(SelectedNodes); SelectedIter; ++SelectedIter)
	{
		UPZ_SkillTreeEdNode_Base* STNode = Cast<UPZ_SkillTreeEdNode_Base>(*SelectedIter);
		if (STNode && STNode->IsSubNode())
		{
			STNode = STNode->ParentNode;
		}

		if (STNode)
		{
			if (SelectedParent == nullptr)
			{
				SelectedParent = STNode;
			}
			else
			{
				bHasMultipleNodesSelected = true;
				break;
			}
		}
	}

	ViewportWidget->ClearSelectionSet();



	FString TextToImport;
	FPlatformApplicationMisc::ClipboardPaste(TextToImport);

	TSet<UEdGraphNode*> PastedNodes;
	FEdGraphUtilities::ImportNodesFromText(LGraph, TextToImport, PastedNodes);


		

	FVector2D AvgNodePosition(0.0f, 0.0f);
	int AvgNodesCount = 0;
	for (const auto&  PastedNode : PastedNodes)
	{
		UPZ_SkillTreeEdNode_Base* STPastedNode = Cast<UPZ_SkillTreeEdNode_Base>(PastedNode);
		if (STPastedNode)
		{
			if (!STPastedNode->IsSubNode())
			{
				PasteNode_CalcAvaragePosition(PastedNode, AvgNodePosition, AvgNodesCount);
			}
		}
		else
		{
			PasteNode_CalcAvaragePosition(PastedNode, AvgNodePosition, AvgNodesCount);
		}
	}

	float InvNumNodes = 1.f;
	if (AvgNodesCount != 0)	InvNumNodes = 1.0f / float(AvgNodesCount); 

	AvgNodePosition.X *= InvNumNodes;
	AvgNodePosition.Y *= InvNumNodes;

	bool bPastedParentNode = false;


	TMap<int32, UPZ_SkillTreeEdNode_Base*> ParentMap;
	for (const auto& PastedNode : PastedNodes)
	{
		UPZ_SkillTreeEdNode_Base* PastedSTNode = Cast<UPZ_SkillTreeEdNode_Base>(PastedNode);

		if (PastedSTNode)
		{
			if (!PastedSTNode->IsSubNode())
			{
				bPastedParentNode = true;

				PasteNode(ViewportWidget, PastedNode, AvgNodePosition, PasteLocation);

				if (PastedSTNode)
				{
					PastedSTNode->RemoveAllSubNodes();
					ParentMap.Add(PastedSTNode->CopySubNodeIndex, PastedSTNode);
				}
			}
		}
		else
		{
			PasteNode(ViewportWidget, PastedNode, AvgNodePosition, PasteLocation);
		}
	}

	for (const auto& PastedNode : PastedNodes)
	{
		UPZ_SkillTreeEdNode_Base* PastedSTNode = Cast<UPZ_SkillTreeEdNode_Base>(PastedNode);
		if (PastedSTNode && PastedSTNode->IsSubNode())
		{
			PastedSTNode->NodePosX = 0;
			PastedSTNode->NodePosY = 0;

			// remove subnode from graph, it will be referenced from parent node
			PastedSTNode->DestroyNode();

			PastedSTNode->ParentNode = ParentMap.FindRef(PastedSTNode->CopySubNodeIndex);
			if (PastedSTNode->ParentNode)
			{
				PastedSTNode->ParentNode->AddSubNode(PastedSTNode, LGraph);
			}
			else if (!bHasMultipleNodesSelected && !bPastedParentNode && SelectedParent)
			{
				SelectedParent->AddSubNode(PastedSTNode, LGraph);
			}
		}
	}

	RefreshViewport();
	SkillTree->PostEditChange();
	SkillTree->MarkPackageDirty();

	SkillTree->NeedToRebuild = true;
	RegenerateMenusAndToolbars();
}


bool FPZ_SkillTreeGraph::CanPasteNodes()
{
	FString ClipboardContent;
	FPlatformApplicationMisc::ClipboardPaste(ClipboardContent);

	return FEdGraphUtilities::CanImportNodesFromText(ViewportWidget->GetCurrentGraph(), ClipboardContent);
}
//.......................................//


void FPZ_SkillTreeGraph::DuplicateNodes()
{
	CopySelectedNodes();
	PasteNodes();
}

bool FPZ_SkillTreeGraph::CanDuplicateNodes()
{
	return CanCopyNodes();
}
//.......................................//


void FPZ_SkillTreeGraph::OnRenameNode()
{
	
	const FGraphPanelSelectionSet SelectedNodes = ViewportWidget->GetSelectedNodes();
	for (const auto& SelectedNode : SelectedNodes)//get first
	{
		UEdGraphNode* LSelectedNode = Cast<UEdGraphNode>(SelectedNode);
		ViewportWidget->IsNodeTitleVisible(LSelectedNode, true);
		break;
	}
	
}

bool FPZ_SkillTreeGraph::CanRenameNodes()
{
	const FGraphPanelSelectionSet SelectedNodes = ViewportWidget->GetSelectedNodes();
	bool CanRenameNode = false;
	for (const auto& SelectedNode : SelectedNodes)//get first
	{
		UEdGraphNode* LSelectedNode = Cast<UEdGraphNode>(SelectedNode);
		CanRenameNode = LSelectedNode->bCanRenameNode;
		break;
	}

	return SelectedNodes.Num() == 1 && CanRenameNode;
}
//.......................................//


void FPZ_SkillTreeGraph::CreateComment()
{
	FNewComment_SkillTreeGraphSchemaAction CommentAction;
	CommentAction.PerformAction(StructureEdGraph, nullptr, ViewportWidget->GetPasteLocation());
}

bool FPZ_SkillTreeGraph::CanCreateComment()
{
	return true;
}
//.......................................//



void FPZ_SkillTreeGraph::OnCommandUndoGraphAction()
{
	GEditor->UndoTransaction(true);

}

void FPZ_SkillTreeGraph::OnCommandRedoGraphAction()
{
	ViewportWidget->ClearSelectionSet();
	GEditor->RedoTransaction();

}
//.......................................//




//.....................................................................................//


void FPZ_SkillTreeGraph::RebuildSkillTree()
{
	StructureEdGraph->RebuildGraph();
	SaveAsset_Execute();
	RegenerateMenusAndToolbars();
}

bool FPZ_SkillTreeGraph::CanRebuildSkillTree()
{
	return true;
}



void FPZ_SkillTreeGraph::CompileUIGraph()
{
	UIPositionEdGraph->CompileGraph();
	SaveAsset_Execute();
	RegenerateMenusAndToolbars();
}

bool FPZ_SkillTreeGraph::CanCompileUIGraph()
{
	return true;
}


void FPZ_SkillTreeGraph::SetTreeStructureMode()
{
	SetCurrentMode(FPZ_SkillTreeGraphEditor_Modes::StructureEditMode);
}

bool FPZ_SkillTreeGraph::CanSetTreeStructureMode()
{
	return GetCurrentMode() != FPZ_SkillTreeGraphEditor_Modes::StructureEditMode;
}

bool FPZ_SkillTreeGraph::IsTreeStructureMode()
{
	return GetCurrentMode() == FPZ_SkillTreeGraphEditor_Modes::StructureEditMode;
}



void FPZ_SkillTreeGraph::SetUIPositionMode()
{
	SetCurrentMode(FPZ_SkillTreeGraphEditor_Modes::UIPositionMode);
}

bool FPZ_SkillTreeGraph::CanSetUIPositionMode()
{
	return GetCurrentMode() != FPZ_SkillTreeGraphEditor_Modes::UIPositionMode;
}

bool FPZ_SkillTreeGraph::IsUIPositionMode()
{
	return GetCurrentMode() == FPZ_SkillTreeGraphEditor_Modes::UIPositionMode;
}



//.....................................................................................//






void FPZ_SkillTreeGraph::OnSelectedNodesChanged(const TSet<class UObject*>& NewSelection)
{
	if (NewSelection.Num() > 0)
	{

		TArray<UObject*> ViewSelection;
		for (UObject* Selected : NewSelection)
		{
			if (IsUIPositionMode())
			{
				if (UPZ_SkillTreeUIPositionEdNode_Base* UIPNode = Cast<UPZ_SkillTreeUIPositionEdNode_Base>(Selected))
				{
					ViewSelection.Add(UIPNode->RUINode);
				}
				else
				{
					ViewSelection.Add(Selected);
				}

			}
			else
			{
				ViewSelection.Add(Selected);
			}
		}

		PropertyWidget->SetObjects(ViewSelection, true);

	}
	else
	{
		if (IsUIPositionMode())
		{
			PropertyWidget->SetObject(nullptr);
		}
		else
		{
			PropertyWidget->SetObject(SkillTree);
		}

	}
}

void FPZ_SkillTreeGraph::OnNodeDoubleClicked(UEdGraphNode* Node)
{
	if (IPZ_SkillTreeNodeInterface* LSkillTreeNode = Cast<IPZ_SkillTreeNodeInterface>(Node))
	{
		LSkillTreeNode->OnNodeDoubleClicked();
	}
}

void FPZ_SkillTreeGraph::OnNodeTitleCommitted(const FText& NewText, ETextCommit::Type CommitInfo, UEdGraphNode* NodeBeingChanged)
{
	if (NodeBeingChanged)
	{
		NodeBeingChanged->Modify();
		NodeBeingChanged->OnRenameNode(NewText.ToString());
	}
}

void FPZ_SkillTreeGraph::OnFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent)
{
	if (IsTreeStructureMode())
	{
		for (auto LNode : StructureEdGraph->Nodes)
		{
			if (IPZ_SkillTreeNodeInterface* LSkillTreeNode = Cast<IPZ_SkillTreeNodeInterface>(LNode))
			{
				LSkillTreeNode->OnChangedProperties(PropertyChangedEvent.GetPropertyName());
			}

		}

	SkillTree->NeedToRebuild = true;
	}

	if (IsUIPositionMode())
	{
		SkillTree->NeedCompileUI = true;
	}

	RegenerateMenusAndToolbars();
}

void FPZ_SkillTreeGraph::OnPackageSaved(const FString& PackageFileName, UObject* Outer)
{
	//TODO
}






void FPZ_SkillTreeGraph::Refresh()
{
	ViewportWidget->ClearSelectionSet();
	RefreshViewport();
	RefreshDetailsView();
	FSlateApplication::Get().DismissAllMenus();
}

void FPZ_SkillTreeGraph::RefreshViewport()
{
	ViewportWidget->NotifyGraphChanged();
}

void FPZ_SkillTreeGraph::RefreshDetailsView()
{
	PropertyWidget->SetObject(SkillTree);
	PropertyWidget->ClearSearch();
}





