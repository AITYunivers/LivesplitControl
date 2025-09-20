#include "Common.hpp"

bool Extension::ImmediateDefault()
{
	return true;
}

bool Extension::LivesplitConnected()
{
	return livesplitSocket != NULL;
}
