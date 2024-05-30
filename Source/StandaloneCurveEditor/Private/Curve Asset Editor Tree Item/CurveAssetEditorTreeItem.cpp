#include "CurveAssetEditorTreeItem.h"

#include "Tree/SCurveEditorTreePin.h"
#include "Tree/SCurveEditorTreeSelect.h"
#include "Widgets/Layout/SScaleBox.h"

FCurveAssetEditorTreeItem::FCurveAssetEditorTreeItem(FRichCurve * Curve, FText TreeItemText, FText EditorTopRightText)
: Curve(Curve), TreeItemText(TreeItemText), EditorTopRightText(EditorTopRightText) {}

TSharedPtr<SWidget> FCurveAssetEditorTreeItem::GenerateCurveEditorTreeWidget(FName const & InColumnName, TWeakPtr<FCurveEditor> InCurveEditor, FCurveEditorTreeItemID InTreeItemID, TSharedRef<ITableRow> const & InTableRow)
{
	if(InColumnName == ColumnNames.Label)
		return SNew(STextBlock).Text(TreeItemText);
	else if(InColumnName == ColumnNames.SelectHeader)
		return SNew(SCurveEditorTreeSelect, InCurveEditor, InTreeItemID, InTableRow);
	else if(InColumnName == ColumnNames.PinHeader)
		return SNew(SCurveEditorTreePin, InCurveEditor, InTreeItemID, InTableRow);
	else
	{
		checkNoEntry();
		throw;
	}
}

void FCurveAssetEditorTreeItem::CreateCurveModels(TArray<TUniquePtr<FCurveModel>> & OutCurveModels)
{
	TUniquePtr<FRichCurveEditorModelRaw> NewCurve = MakeUnique<FRichCurveEditorModelRaw>(Curve, GWorld);
	NewCurve->SetShortDisplayName(EditorTopRightText);
	OutCurveModels.Add(MoveTemp(NewCurve));
}
