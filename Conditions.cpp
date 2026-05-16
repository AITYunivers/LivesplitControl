#include "Common.hpp"

bool Extension::ImmediateDefault()
{
	return true;
}

bool Extension::LivesplitConnected()
{
	return livesplitSocket != NULL;
}

bool Extension::GlobalHotkeysEnabled()
{
	return handleExpressionSocket("globalhotkeysenabled") == _T("True");
}

bool Extension::SaveLayouts()
{
	return handleExpressionSocket("savelayout") == _T("True");
}

bool Extension::SaveSplits()
{
	return handleExpressionSocket("savesplits") == _T("True");
}

bool Extension::SaveLayoutsSelector(const TCHAR* file)
{
	return handleExpressionSocket("savelayoutas " + DarkEdif::TStringToANSI(file)) == _T("True");
}

bool Extension::SaveSplitsSelector(const TCHAR* file)
{
	return handleExpressionSocket("savesplitsas " + DarkEdif::TStringToANSI(file)) == _T("True");
}

bool Extension::SwitchLayout(const TCHAR* file)
{
	return handleExpressionSocket("switchlayout " + DarkEdif::TStringToANSI(file)) == _T("True");
}

bool Extension::SwitchSplits(const TCHAR* file)
{
	return handleExpressionSocket("switchsplits " + DarkEdif::TStringToANSI(file)) == _T("True");
}

bool Extension::SaveSplitsScreenshot(const TCHAR* file)
{
	return handleExpressionSocket("savesplitsscreenshot " + DarkEdif::TStringToANSI(file)) == _T("True");
}

bool Extension::CategoryUsesEmulator()
{
	std::tstring jsonData = handleExpressionSocket("getcategoryvariables");
	nlohmann::json j = getJson(jsonData.c_str());

	if (!j.contains("usesEmulator"))
		return false;

	bool usesEmulator;
	j["usesEmulator"].get_to(usesEmulator);

	return usesEmulator;
}
