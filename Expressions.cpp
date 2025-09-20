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
