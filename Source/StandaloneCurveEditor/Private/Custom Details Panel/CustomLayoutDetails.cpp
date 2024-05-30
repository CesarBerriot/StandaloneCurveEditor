#include "CustomLayoutDetails.h"
#include "DetailWidgetRow.h"
#include "Slate Widgets/RichCurveValueContent/RichCurveValueContent.h"

TSharedRef<IPropertyTypeCustomization> FCustomLayoutDetails::CreateInstance()
{
	return MakeShareable<IPropertyTypeCustomization>(new FCustomLayoutDetails);
}

void FCustomLayoutDetails::CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow & HeaderRow, IPropertyTypeCustomizationUtils & CustomizationUtils)
{
	HeaderRow
	.NameContent()
	[
		PropertyHandle->CreatePropertyNameWidget()
	]
	.ValueContent()
	[
		SNew(SRichCurveValueContent, PropertyHandle)
	];
}

void FCustomLayoutDetails::CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder & ChildBuilder, IPropertyTypeCustomizationUtils & CustomizationUtils) {}
