#pragma once

#include "Editor/UnrealEd/Public/Toolkits/AssetEditorToolkit.h"
#include "Editor/UnrealEd/Public/Kismet2/CompilerResultsLog.h"
#include "Developer/MessageLog/Public/IMessageLogListing.h"
#include "Developer/MessageLog/Public/MessageLogModule.h"
#include "Runtime/CoreUObject/Public/Misc/NotifyHook.h"
#include "GraphEditor.h"
#include "IDetailsView.h"
#include "DialogAsset.h"
#include "SlateBasics.h"
#include "Commands.h"
#include "EditorStyle.h"
#include "Runtime/Core/Public/Logging/TokenizedMessage.h"
#include "Widgets/Views/STableViewBase.h"
#include "Widgets/Views/STableRow.h"
#include "DialogEditorNodes.h"

struct DIALOGSYSTEMEDITOR_API FDialogAssetEditorTabs
{
	static const FName DetailsID;
	static const FName CompilerResultsID;
	static const FName GraphEditorID;
	
private:
	FDialogAssetEditorTabs() {}
};

struct DIALOGSYSTEMEDITOR_API FDialogCommands : public TCommands<FDialogCommands>
{
	TSharedPtr<FUICommandInfo> Compile;
	TSharedPtr<FUICommandInfo> Find;
	TSharedPtr<FUICommandInfo> Import;
	TSharedPtr<FUICommandInfo> Export;

	FDialogCommands()
		: TCommands<FDialogCommands>(TEXT("Dialog Graph Commands"), FText::FromString("Dialog Graph Commands"), NAME_None, FEditorStyle::GetStyleSetName())
	{
	}

	virtual void RegisterCommands() override;
};

class UEdGraph;
class UEdGraphNode;
class SGraphEditor;

class UDialogPhraseNode;
class UDdialogEdGraphNode;
class UDialogRootEdGraphNode;

class DIALOGSYSTEMEDITOR_API FDialogAssetEditor : public FAssetEditorToolkit, public FNotifyHook
{
public:

	~FDialogAssetEditor();

	// IToolkit interface
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	// FAssetEditorToolkit

	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	void InitDialogAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, UDialogAsset* Object);

private:

	TSharedPtr<class IMessageLogListing> CompilerResultsListing;
	TSharedPtr<SGraphEditor> GraphEditor;
	TSharedPtr<FUICommandList> GraphEditorCommands;
	TSharedPtr<IDetailsView> PropertyEditor;
	TSharedPtr<FUICommandList> MyToolBarCommands;
	TSharedPtr<FExtender> ToolbarExtender;
	TSharedPtr<SDockTab> CompilerResultsTab;
	TSharedPtr<SDockTab> KeysTab;
	TSharedPtr<SDockTab> KeyManagerTab;
	UDialogAsset* EditedAsset;
	FDelegateHandle OnGraphChangedDelegateHandle;
	FDelegateHandle OnPropertyChangedDelegateHandle;
	FCompilerResultsLog CompileLogResults;
	bool bGraphStateChanged;

	TSharedRef<SGraphEditor> CreateGraphEditorWidget(UEdGraph* InGraph);
	TSharedRef<SDockTab> SpawnTab_Viewport(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnTab_CompilerResults(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnTab_Details(const FSpawnTabArgs& Args);

	UEdGraph* CreateGraphFromAsset();
	UDialogRootEdGraphNode* GetRootNode();

	void OnGraphChanged(const FEdGraphEditAction& Action);
	void OnPropertyChanged(const FPropertyChangedEvent& Event);
	void BuildToolbar(FToolBarBuilder &builder);
	void SelectAllNodes();
	bool CanSelectAllNodes() const;
	void DeleteSelectedNodes();
	bool CanDeleteNode(UEdGraphNode* Node);
	bool CanDeleteNodes() const;
	void DeleteNodes(const TArray<UEdGraphNode*>& NodesToDelete);
	void CopySelectedNodes();
	bool CanCopyNodes() const;
	void PasteNodes();
	void PasteNodesHere(const FVector2D& Location);
	bool CanPasteNodes() const;
	void CutSelectedNodes();
	bool CanCutNodes() const;
	void DuplicateNodes();
	bool CanDuplicateNodes() const;
	void DeleteSelectedDuplicatableNodes();

	void OnSelectedNodesChanged(const TSet<UObject*>& NewSelection);
	void OnNodeDoubleClicked(UEdGraphNode* Node);

	void OpenFindWindow();
	void ImportExecute();
	void ExportExecute();
	void CompileExecute();

	void ResetCompilePhrase(UDdialogEdGraphNode* Node);
	UDialogNode* Compile(UDdialogEdGraphNode* Node);
};