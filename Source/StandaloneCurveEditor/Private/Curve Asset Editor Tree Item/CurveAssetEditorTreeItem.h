#pragma once
#include "CurveEditor.h"
#include "RichCurveEditorModel.h"
#include "Tree/ICurveEditorTreeItem.h"

struct FCurveAssetEditorTreeItem final : ICurveEditorTreeItem
{
private:
	FRichCurve * Curve;
	FText TreeItemText;
	FText EditorTopRightText;
public:
	FCurveAssetEditorTreeItem(FRichCurve * Curve, FText TreeItemText, FText EditorTopRightText);
	virtual TSharedPtr<SWidget> GenerateCurveEditorTreeWidget(FName const & InColumnName, TWeakPtr<FCurveEditor> InCurveEditor, FCurveEditorTreeItemID InTreeItemID, TSharedRef<ITableRow> const & InTableRow) override;
	virtual void CreateCurveModels(TArray<TUniquePtr<FCurveModel>> & OutCurveModels) override;
};
