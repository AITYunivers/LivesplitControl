#include "Common.hpp"

///
/// EXTENSION CONSTRUCTOR/DESTRUCTOR
///

#ifdef _WIN32
Extension::Extension(RunObject* const _rdPtr, const EDITDATA* const edPtr, const CreateObjectInfo* const cobPtr) :
	rdPtr(_rdPtr), rhPtr(_rdPtr->get_rHo()->get_AdRunHeader()), Runtime(this)
#elif defined(__ANDROID__)
Extension::Extension(const EDITDATA* const edPtr, const jobject javaExtPtr) :
	javaExtPtr(javaExtPtr, "Extension::javaExtPtr from Extension ctor"),
	Runtime(this, this->javaExtPtr), FusionDebugger(this)
#else
Extension::Extension(const EDITDATA* const edPtr, void* const objCExtPtr) :
	objCExtPtr(objCExtPtr), Runtime(this, objCExtPtr), FusionDebugger(this)
#endif
{
	/*
		Link all your action/condition/expression functions to their IDs to match the
		IDs in the JSON here
	*/

	LinkAction(Act_LivesplitConnect, LivesplitConnect);
	LinkAction(Act_LivesplitDisconnect, LivesplitDisconnect);
	LinkAction(Act_StartOrSplit, StartOrSplit);
	LinkAction(Act_Split, Split);
	LinkAction(Act_Unsplit, Unsplit);
	LinkAction(Act_SkipSplit, SkipSplit);
	LinkAction(Act_Pause, Pause);
	LinkAction(Act_Resume, Resume);
	LinkAction(Act_Reset, Reset);
	LinkAction(Act_StartTimer, StartTimer);
	LinkAction(Act_SetGameTime, SetGameTime);
	LinkAction(Act_SetLoadingTimes, SetLoadingTimes);
	LinkAction(Act_AddLoadingTimes, AddLoadingTimes);
	LinkAction(Act_PauseGameTime, PauseGameTime);
	LinkAction(Act_UnpauseGameTime, UnpauseGameTime);
	LinkAction(Act_AlwaysPauseGameTime, AlwaysPauseGameTime);
	LinkAction(Act_SetComparison, SetComparison);
	LinkAction(Act_SwitchToRealTime, SwitchToRealTime);
	LinkAction(Act_SwitchToGameTime, SwitchToGameTime);
	LinkAction(Act_SetSplitName, SetSplitName);
	LinkAction(Act_SetCurrentSplitName, SetCurrentSplitName);
	LinkAction(Act_SetCustomVariable, SetCustomVariable);

	LinkCondition(Cnd_OnError, ImmediateDefault);
	LinkCondition(Cnd_OnConnected, ImmediateDefault);
	LinkCondition(Cnd_OnDisconnect, ImmediateDefault);
	LinkCondition(Cnd_IsConnected, LivesplitConnected);

	LinkExpression(Exp_GetErrorID, GetErrorID);
	LinkExpression(Exp_GetDelta, GetDelta);
	LinkExpression(Exp_GetDeltaC, GetDeltaC);
	LinkExpression(Exp_GetLastSplitTime, GetLastSplitTime);
	LinkExpression(Exp_GetComparisonSplitTime, GetComparisonSplitTime);
	LinkExpression(Exp_GetCurrentRealTime, GetCurrentRealTime);
	LinkExpression(Exp_GetCurrentGameTime, GetCurrentGameTime);
	LinkExpression(Exp_GetCurrentTime, GetCurrentTime_);
	LinkExpression(Exp_GetFinalTime, GetFinalTime);
	LinkExpression(Exp_GetFinalTimeC, GetFinalTimeC);
	LinkExpression(Exp_GetPredictedTime, GetPredictedTime);
	LinkExpression(Exp_GetBestPossibleTime, GetBestPossibleTime);
	LinkExpression(Exp_GetSplitIndex, GetSplitIndex);
	LinkExpression(Exp_GetAttemptCount, GetAttemptCount);
	LinkExpression(Exp_GetCompletedCount, GetCompletedCount);
	LinkExpression(Exp_GetCurrentSplitName, GetCurrentSplitName);
	LinkExpression(Exp_GetPreviousSplitName, GetPreviousSplitName);
	LinkExpression(Exp_GetCurrentTimerPhase, GetCurrentTimerPhase);
	LinkExpression(Exp_GetCustomVariableValue, GetCustomVariableValue);
	LinkExpression(Exp_Ping, Ping);

	/*
		This is where you'd do anything you'd do in CreateRunObject in the original SDK

		It's the only place you'll get access to edPtr at runtime, so you should transfer
		anything from edPtr to the extension class here.

	*/
}

Extension::~Extension()
{

}


REFLAG Extension::Handle()
{
	return REFLAG::ONE_SHOT;
}


REFLAG Extension::Display()
{
	return REFLAG::DISPLAY;
}

short Extension::FusionRuntimePaused()
{

	// Ok
	return 0;
}

short Extension::FusionRuntimeContinued()
{

	// Ok
	return 0;
}

// Written by ChatGPT, sorry gamers
std::string Extension::format_millis(int ms)
{
	using namespace std::chrono;

	bool neg = ms < 0;
	int64_t v = std::llabs(ms);

	auto h = duration_cast<hours>(milliseconds(v));      v -= h.count() * 3600000;
	auto m = duration_cast<minutes>(milliseconds(v));    v -= m.count() * 60000;
	auto s = duration_cast<seconds>(milliseconds(v));    v -= s.count() * 1000;

	std::ostringstream out;
	if (neg) out << '-';
	out << std::setfill('0') << std::setw(2) << h.count() << ':'
		<< std::setw(2) << m.count() << ':'
		<< std::setw(2) << s.count();

	if (v) {
		int frac = (int)v * 10000; // turn ms into up to 7 digits
		std::string f = std::to_string(frac);
		while (!f.empty() && f.back() == '0') f.pop_back();
		out << '.' << f;
	}
	return out.str();
}

// Not written by ChatGPT, don't worry gamers!
std::tstring Extension::handleExpressionSocket(std::string command)
{
	errorIdentifier = _T("");
	if (livesplitSocket != NULL)
	{
		int r = send(livesplitSocket, (command + "\n").c_str(), command.length() + 1, 0);
		if (r == SOCKET_ERROR)
		{
			errorIdentifier = _T("SEND ERROR: ") + std::to_tstring(WSAGetLastError());
			Runtime.GenerateEvent(Cnd_OnError);
			return _T("");
		}

		char buf[512];
		r = 0;
		while (r == 0)
		{
			r = recv(livesplitSocket, buf, (int)sizeof(buf) - 1, 0);

			if (r != SOCKET_ERROR && r != 0)
			{
				buf[r] = '\0';
				return DarkEdif::ANSIToTString(buf);
			}
			else
			{
				errorIdentifier = _T("RECIEVE ERROR: ") + std::to_tstring(WSAGetLastError());
				Runtime.GenerateEvent(Cnd_OnError);
			}
		}
	}
	return _T("");
}

// These are called if there's no function linked to an ID

void Extension::UnlinkedAction(int ID)
{
	DarkEdif::MsgBox::Error(_T("Extension::UnlinkedAction() called"), _T("Running a fallback for action ID %d. Make sure you ran LinkAction()."), ID);
}

long Extension::UnlinkedCondition(int ID)
{
	DarkEdif::MsgBox::Error(_T("Extension::UnlinkedCondition() called"), _T("Running a fallback for condition ID %d. Make sure you ran LinkCondition()."), ID);
	return 0;
}

long Extension::UnlinkedExpression(int ID)
{
	DarkEdif::MsgBox::Error(_T("Extension::UnlinkedExpression() called"), _T("Running a fallback for expression ID %d. Make sure you ran LinkExpression()."), ID);
	// Unlinked A/C/E is fatal error, but try not to return null string and definitely crash it
	if ((size_t)ID < Edif::SDK->ExpressionInfos.size() && Edif::SDK->ExpressionInfos[ID]->Flags.ef == ExpReturnType::String)
		return (long)Runtime.CopyString(_T(""));
	return 0;
}
