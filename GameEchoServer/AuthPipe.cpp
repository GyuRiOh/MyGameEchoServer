#include "AuthPipe.h"
#include "AuthPipe_CS_Stub.h"
#include "PipePlayer.h"
#include "../NetRoot/LanServer/LanPacket.h"
#include "../MonitorProtocol.h"
#include "../NetRoot/Common/Parser.h"

using namespace server_baby;

server_baby::AuthPipe::AuthPipe(NetRoot* server, unsigned int framePerSecond, unsigned int threadNum)
	: NetPipe(server, framePerSecond), framePerSec_(0)
{
	RegisterPipeStub(new AuthPipe_CS_Stub(this));
	proxy_ = new AuthPipe_SC_Proxy(this);
}

server_baby::NetUser* server_baby::AuthPipe::OnUserJoin(NetSessionID sessionID)
{
	PipePlayer* player = reinterpret_cast<PipePlayer*>(
		SizedMemoryPool::GetInstance()->Alloc(sizeof(PipePlayer)));

	new (player) PipePlayer(sessionID, GetServer(), GetPipeID());

    return reinterpret_cast<NetUser*>(player);
}

void server_baby::AuthPipe::OnUserLeave(NetUser* user)
{

    PipePlayer* player = reinterpret_cast<PipePlayer*>(user);

    onlineMap_.Release(player->GetAccountNumber());
    player->~PipePlayer();
    SizedMemoryPool::GetInstance()->Free(player);
}

void server_baby::AuthPipe::OnUserMoveIn(NetUser* user)
{

}

void server_baby::AuthPipe::OnUserMoveOut(NetSessionID sessionID)
{ 
    CrashDump::Crash();
}

void server_baby::AuthPipe::OnUserMoveOut(NetUser* user)
{
    PipePlayer* player = reinterpret_cast<PipePlayer*>(user);

    if (!onlineMap_.Release(player->GetAccountNumber()))
        CrashDump::Crash();

}

void server_baby::AuthPipe::OnUpdate(NetUser* user)
{
}

void server_baby::AuthPipe::OnMonitor(const LoopInfo* const info)
{
    wchar_t title[64] = { 0 };
    swprintf_s(title, L"AuthPipe %d", GetCurrentThreadId());
    SystemLogger::GetInstance()->LogText(title, LEVEL_DEBUG, L"Player Num : %d, Frame Count : %d", GetUserSize(), info->frameCountPerSecond_);

    framePerSec_ = info->frameCountPerSecond_;
}

void server_baby::AuthPipe::OnStart()
{

}

void server_baby::AuthPipe::OnStop()
{
    SystemLogger::GetInstance()->Console(L"PipeManager", LEVEL_DEBUG, L"AuthPipe Stopped");

}

