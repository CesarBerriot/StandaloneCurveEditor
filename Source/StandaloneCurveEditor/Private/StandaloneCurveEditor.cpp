#include "StandaloneCurveEditor.h"

#define LOCTEXT_NAMESPACE "FStandaloneCurveEditorModule"

void FStandaloneCurveEditorModule::StartupModule()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomPropertyTypeLayout(FRichCurve::StaticStruct()->GetFName(), FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FCustomLayoutDetails::CreateInstance));
}

void FStandaloneCurveEditorModule::ShutdownModule()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.UnregisterCustomPropertyTypeLayout(NAME_StructProperty);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FStandaloneCurveEditorModule, StandaloneCurveEditor)