#include "Common.hpp"

const TCHAR * Extension::GetErrorID()
{
	return Runtime.CopyString(errorIdentifier.c_str());
}

const TCHAR * Extension::GetDelta()
{
	return Runtime.CopyString(handleExpressionSocket("getdelta").c_str());
}

const TCHAR * Extension::GetDeltaC(const TCHAR* comparison)
{
	return Runtime.CopyString(handleExpressionSocket("getdelta " + DarkEdif::TStringToANSI(comparison)).c_str());
}

const TCHAR * Extension::GetLastSplitTime()
{
	return Runtime.CopyString(handleExpressionSocket("getlastsplittime").c_str());
}

const TCHAR * Extension::GetComparisonSplitTime()
{
	return Runtime.CopyString(handleExpressionSocket("getcomparisonsplittime").c_str());
}

const TCHAR * Extension::GetCurrentRealTime()
{
	return Runtime.CopyString(handleExpressionSocket("getcurrentrealtime").c_str());
}

const TCHAR * Extension::GetCurrentGameTime()
{
	return Runtime.CopyString(handleExpressionSocket("getcurrentgametime").c_str());
}

const TCHAR * Extension::GetCurrentTime_()
{
	return Runtime.CopyString(handleExpressionSocket("getcurrenttime").c_str());
}

const TCHAR * Extension::GetFinalTime()
{
	return Runtime.CopyString(handleExpressionSocket("getfinaltime").c_str());
}

const TCHAR * Extension::GetFinalTimeC(const TCHAR* comparison)
{
	return Runtime.CopyString(handleExpressionSocket("getfinaltime " + DarkEdif::TStringToANSI(comparison)).c_str());
}

const TCHAR * Extension::GetPredictedTime(const TCHAR* comparison)
{
	return Runtime.CopyString(handleExpressionSocket("getpredictedtime " + DarkEdif::TStringToANSI(comparison)).c_str());
}

const TCHAR * Extension::GetBestPossibleTime()
{
	return Runtime.CopyString(handleExpressionSocket("getbestpossibletime").c_str());
}

int Extension::GetSplitIndex()
{
	return std::stoi(handleExpressionSocket("getsplitindex"));
}

int Extension::GetAttemptCount()
{
	return std::stoi(handleExpressionSocket("getattemptcount"));
}

int Extension::GetCompletedCount()
{
	return std::stoi(handleExpressionSocket("getcompletedcount"));
}

const TCHAR * Extension::GetCurrentSplitName()
{
	return Runtime.CopyString(handleExpressionSocket("getcurrentsplitname").c_str());
}

const TCHAR * Extension::GetPreviousSplitName()
{
	return Runtime.CopyString(handleExpressionSocket("getprevioussplitname").c_str());
}

const TCHAR * Extension::GetCurrentTimerPhase()
{
	return Runtime.CopyString(handleExpressionSocket("getcurrenttimerphase").c_str());
}

const TCHAR* Extension::GetCustomVariableValue(const TCHAR* varName)
{
	return Runtime.CopyString(handleExpressionSocket("getcustomvariablevalue " + DarkEdif::TStringToANSI(varName)).c_str());
}

const TCHAR * Extension::Ping()
{
	return Runtime.CopyString(handleExpressionSocket("ping").c_str());
}

const TCHAR* Extension::GetComparisonSplitTimeC(const TCHAR* comparison)
{
	return Runtime.CopyString(handleExpressionSocket("getcomparisonsplittime " + DarkEdif::TStringToANSI(comparison)).c_str());
}

const TCHAR* Extension::GetPausedRealTime()
{
	return Runtime.CopyString(handleExpressionSocket("getpausedrealtime").c_str());
}

const TCHAR* Extension::GetPausedGameTime()
{
	return Runtime.CopyString(handleExpressionSocket("getpausedgametime").c_str());
}

const TCHAR* Extension::GetOffset()
{
	return Runtime.CopyString(handleExpressionSocket("getoffset").c_str());
}

int Extension::GetSplitCount()
{
	return std::stoi(handleExpressionSocket("getsplitcount"));
}

const TCHAR* Extension::GetSplitName(int index)
{
	return Runtime.CopyString(handleExpressionSocket("getsplitname " + std::to_string(index)).c_str());
}

const TCHAR* Extension::GetUpcomingSplitName()
{
	return Runtime.CopyString(handleExpressionSocket("getupcomingsplitname").c_str());
}

const TCHAR* Extension::GetGameName()
{
	return Runtime.CopyString(handleExpressionSocket("getgamename").c_str());
}

const TCHAR* Extension::GetCategoryName()
{
	return Runtime.CopyString(handleExpressionSocket("getcategoryname").c_str());
}

const TCHAR* Extension::GetComparisonName()
{
	return Runtime.CopyString(handleExpressionSocket("getcomparisonname").c_str());
}

const TCHAR* Extension::GetTimingMethod()
{
	return Runtime.CopyString(handleExpressionSocket("gettimingmethod").c_str());
}

const TCHAR* Extension::GetLayoutPath()
{
	return Runtime.CopyString(handleExpressionSocket("getlayoutpath").c_str());
}

const TCHAR* Extension::GetSplitsPath()
{
	return Runtime.CopyString(handleExpressionSocket("getsplitspath").c_str());
}

const TCHAR* Extension::GetHotkeyProfile()
{
	return Runtime.CopyString(handleExpressionSocket("gethotkeyprofile").c_str());
}

const TCHAR* Extension::GetLivesplitVersion()
{
	return Runtime.CopyString(handleExpressionSocket("getlivesplitversion").c_str());
}

const TCHAR* Extension::GetLivesplitPath()
{
	return Runtime.CopyString(handleExpressionSocket("getlivesplitpath").c_str());
}

const TCHAR* Extension::GetServerType()
{
	return Runtime.CopyString(handleExpressionSocket("getservertype").c_str());
}

const TCHAR* Extension::GetCategoryRegion()
{
	std::tstring jsonData = handleExpressionSocket("getcategoryvariables");
	nlohmann::json j = getJson(jsonData.c_str());

	if (!j.contains("region"))
		return Runtime.CopyString(_T(""));

	std::string region;
	j["region"].get_to(region);

	return Runtime.CopyString(DarkEdif::UTF8ToTString(region).c_str());
}

const TCHAR* Extension::GetCategoryPlatform()
{
	std::tstring jsonData = handleExpressionSocket("getcategoryvariables");
	nlohmann::json j = getJson(jsonData.c_str());

	if (!j.contains("platform"))
		return Runtime.CopyString(_T(""));

	std::string platform;
	j["platform"].get_to(platform);

	return Runtime.CopyString(DarkEdif::UTF8ToTString(platform).c_str());
}

const TCHAR* Extension::GetCategoryUsesEmulator()
{
	std::tstring jsonData = handleExpressionSocket("getcategoryvariables");
	nlohmann::json j = getJson(jsonData.c_str());

	if (!j.contains("usesEmulator"))
		return Runtime.CopyString(_T(""));

	bool usesEmulator;
	j["usesEmulator"].get_to(usesEmulator);

	return usesEmulator ? Runtime.CopyString(_T("true")) : Runtime.CopyString(_T("false"));
}

int Extension::GetCategoryVariableCount()
{
	std::tstring jsonData = handleExpressionSocket("getcategoryvariables");
	nlohmann::json j = getJson(jsonData.c_str());

	if (!j.contains("variables"))
		return 0;

	return j["variables"].size();
}

const TCHAR* Extension::GetCategoryVariableName(int varIndex)
{
	std::tstring jsonData = handleExpressionSocket("getcategoryvariables");
	nlohmann::json j = getJson(jsonData.c_str());

	if (!j.contains("variables"))
		return Runtime.CopyString(_T(""));

	auto it = j["variables"].begin();
	std::advance(it, varIndex);
	return Runtime.CopyString(DarkEdif::UTF8ToTString(it.key()).c_str());
}

const TCHAR* Extension::GetCategoryVariable(const TCHAR* varName)
{
	std::tstring jsonData = handleExpressionSocket("getcategoryvariables");
	nlohmann::json j = getJson(jsonData.c_str());

	std::string varNameA = DarkEdif::TStringToUTF8(varName);
	if (!j.contains("variables") || !j["variables"].contains(varNameA))
		return Runtime.CopyString(_T(""));

	std::string variable;
	j["variables"][varNameA].get_to(variable);

	return Runtime.CopyString(DarkEdif::UTF8ToTString(variable).c_str());
}
