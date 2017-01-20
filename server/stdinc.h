#pragma once
#pragma warning(disable : 4996)

#include <stdio.h>
#include <uv.h>
#include <string>
#include <map>

// raknet
#include <MessageIdentifiers.h>
#include <RakPeerInterface.h>
#include <BitStream.h>

// squirrel
#define _SQ64
#include <squirrel.h>

#include <Utils.h>

#include <MessageID.h>
#include <LinearMath.h>
#include <BuildVersion.h>

// #include "Network/Handlers/ServerConnectionHandler.h"
// #include "Network/Handlers/ServerSyncHandler.h"
// #include "Network/Handlers/ServerRakNetHandler.h"

#include "Network/Client.h"
#include "Network/Manager.h"
#include "Network/Handler.h"

#include "Core.h"
