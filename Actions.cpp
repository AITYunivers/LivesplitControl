#include "Common.hpp"

void Extension::LivesplitConnect(int port)
{
	errorIdentifier = _T("");
	if (livesplitSocket != NULL)
		return;

	livesplitSocket = socket(AF_INET, SOCK_STREAM, 0);

	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(port);
	serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

	int code = connect(livesplitSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
	if (code != SOCKET_ERROR)
		Runtime.GenerateEvent(Cnd_OnConnected);
	else
	{
		livesplitSocket = NULL;
		errorIdentifier = _T("SOCKET ERROR: ") + std::to_tstring(WSAGetLastError());
		Runtime.GenerateEvent(Cnd_OnError);
	}
}

void Extension::LivesplitDisconnect()
{
	errorIdentifier = _T("");
	if (livesplitSocket != NULL)
	{
		closesocket(livesplitSocket);
		livesplitSocket = NULL;
		Runtime.GenerateEvent(Cnd_OnDisconnect);
	}
}

void Extension::StartOrSplit()
{
	errorIdentifier = _T("");
	if (livesplitSocket != NULL)
		send(livesplitSocket, "startorsplit\n", 13, 0);
}

void Extension::Split()
{
	errorIdentifier = _T("");
	if (livesplitSocket != NULL)
		send(livesplitSocket, "split\n", 6, 0);
}

void Extension::Unsplit()
{
	errorIdentifier = _T("");
	if (livesplitSocket != NULL)
		send(livesplitSocket, "unsplit\n", 8, 0);
}

void Extension::SkipSplit()
{
	errorIdentifier = _T("");
	if (livesplitSocket != NULL)
		send(livesplitSocket, "skipsplit\n", 10, 0);
}

void Extension::Pause()
{
	errorIdentifier = _T("");
	if (livesplitSocket != NULL)
		send(livesplitSocket, "pause\n", 6, 0);
}

void Extension::Resume()
{
	errorIdentifier = _T("");
	if (livesplitSocket != NULL)
		send(livesplitSocket, "resume\n", 7, 0);
}

void Extension::Reset()
{
	errorIdentifier = _T("");
	if (livesplitSocket != NULL)
		send(livesplitSocket, "reset\n", 6, 0);
}

void Extension::StartTimer()
{
	errorIdentifier = _T("");
	if (livesplitSocket != NULL)
		send(livesplitSocket, "starttimer\n", 11, 0);
}

void Extension::SetGameTime(int time)
{
	errorIdentifier = _T("");
	if (livesplitSocket != NULL)
	{
		std::string cmd = std::string("setgametime ") + format_millis(time) + "\n";
		send(livesplitSocket, cmd.c_str(), cmd.length(), 0);
	}
}

void Extension::SetLoadingTimes(int time)
{
	errorIdentifier = _T("");
	if (livesplitSocket != NULL)
	{
		std::string cmd = std::string("setloadingtimes ") + format_millis(time) + "\n";
		send(livesplitSocket, cmd.c_str(), cmd.length(), 0);
	}
}

void Extension::AddLoadingTimes(int time)
{
	errorIdentifier = _T("");
	if (livesplitSocket != NULL)
	{
		std::string cmd = std::string("addloadingtimes ") + format_millis(time) + "\n";
		send(livesplitSocket, cmd.c_str(), cmd.length(), 0);
	}
}

void Extension::PauseGameTime()
{
	errorIdentifier = _T("");
	if (livesplitSocket != NULL)
		send(livesplitSocket, "pausegametime\n", 14, 0);
}

void Extension::UnpauseGameTime()
{
	errorIdentifier = _T("");
	if (livesplitSocket != NULL)
		send(livesplitSocket, "unpausegametime\n", 16, 0);
}

void Extension::AlwaysPauseGameTime()
{
	errorIdentifier = _T("");
	if (livesplitSocket != NULL)
		send(livesplitSocket, "alwayspausegametime\n", 20, 0);
}

void Extension::SetComparison(const TCHAR* comparison)
{
	errorIdentifier = _T("");
	if (livesplitSocket != NULL)
	{
		std::string cmd = std::string("setcomparison ") + DarkEdif::TStringToANSI(comparison) + "\n";
		send(livesplitSocket, cmd.c_str(), cmd.length(), 0);
	}
}

void Extension::SwitchToRealTime()
{
	errorIdentifier = _T("");
	if (livesplitSocket != NULL)
		send(livesplitSocket, "switchto realtime\n", 18, 0);
}

void Extension::SwitchToGameTime()
{
	errorIdentifier = _T("");
	if (livesplitSocket != NULL)
		send(livesplitSocket, "switchto gametime\n", 18, 0);
}

void Extension::SetSplitName(int index, const TCHAR* name)
{
	errorIdentifier = _T("");
	if (livesplitSocket != NULL)
	{
		std::string cmd = std::string("setsplitname ") + std::to_string(index) + " " + DarkEdif::TStringToANSI(name) + "\n";
		send(livesplitSocket, cmd.c_str(), cmd.length(), 0);
	}
}

void Extension::SetCurrentSplitName(const TCHAR* name)
{
	errorIdentifier = _T("");
	if (livesplitSocket != NULL)
	{
		std::string cmd = std::string("setcurrentsplitname ") + DarkEdif::TStringToANSI(name) + "\n";
		send(livesplitSocket, cmd.c_str(), cmd.length(), 0);
	}
}

void Extension::SetCustomVariableOLD(const TCHAR* json)
{
	errorIdentifier = _T("");
	if (livesplitSocket != NULL)
	{
		std::string cmd = std::string("setcustomvariable ") + DarkEdif::TStringToANSI(json) + "\n";
		send(livesplitSocket, cmd.c_str(), cmd.length(), 0);
	}
}

void Extension::SetCustomVariable(const TCHAR* name, const TCHAR* value)
{
	errorIdentifier = _T("");
	if (livesplitSocket != NULL)
	{
		std::string cmd = std::string("setcustomvariable [\"") + DarkEdif::TStringToANSI(name) + "\", \"" + DarkEdif::TStringToANSI(value) + "\"]\n";
		send(livesplitSocket, cmd.c_str(), cmd.length(), 0);
	}
}
