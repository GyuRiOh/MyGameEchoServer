#include "EchoPipe.h"
#include "EchoPipe_CS_Stub.h"
#include "PipePlayer.h"
#include "../NetRoot/LanServer/LanPacket.h"
#include "../MonitorProtocol.h"
#include "../NetRoot/Common/Parser.h"


server_baby::EchoPipe::EchoPipe(NetRoot* server, unsigned int framePerSecond, unsigned int threadNum)
	: NetPipe(server, framePerSecond), framePerSec_(0)
{
    RegisterPipeStub(new EchoPipe_CS_Stub(this));
	proxy_ = new EchoPipe_SC_Proxy(this);
}

server_baby::NetUser* server_baby::EchoPipe::OnUserJoin(NetSessionID sessionID)
{
    CrashDump::Crash();
    return nullptr;
}

void server_baby::EchoPipe::OnUserLeave(NetUser* user)
{
    PipePlayer* player = reinterpret_cast<PipePlayer*>(user);

    player->~PipePlayer();
    SizedMemoryPool::GetInstance()->Free(player);
}

void server_baby::EchoPipe::OnUserMoveIn(NetUser* user)
{

}

void server_baby::EchoPipe::OnUserMoveOut(NetSessionID sessionID)
{
    CrashDump::Crash();
}

void server_baby::EchoPipe::OnUserMoveOut(NetUser* user)
{
    CrashDump::Crash();
}

void server_baby::EchoPipe::OnUpdate(NetUser* user)
{

}

void server_baby::EchoPipe::OnMonitor(const LoopInfo* const info)
{
    wchar_t title[64] = { 0 };
    swprintf_s(title, L"EchoPipe %d", GetCurrentThreadId());
    SystemLogger::GetInstance()->LogText(title, LEVEL_DEBUG, L"Player Num : %d, Frame Count : %d", GetUserSize(), info->frameCountPerSecond_);
   
    framePerSec_ = info->frameCountPerSecond_;
}

void server_baby::EchoPipe::OnStart()
{
    HANDLE thread = GetCurrentThread();
    DWORD dwThreadPri = GetThreadPriority(thread);
    SystemLogger::GetInstance()->Console(L"Priority", LEVEL_DEBUG, L"Logic Thread - 0x%x", dwThreadPri);
    SetThreadPriority(thread, THREAD_PRIORITY_ABOVE_NORMAL);

    dwThreadPri = GetThreadPriority(thread);
    SystemLogger::GetInstance()->Console(L"Priority", LEVEL_DEBUG, L"Logic Thread - 0x%x", dwThreadPri);

    CloseHandle(thread);
    
    SystemLogger::GetInstance()->Console(L"PipeManager", LEVEL_DEBUG, L"EchoPipe Started");

}

void server_baby::EchoPipe::OnStop()
{
    SystemLogger::GetInstance()->Console(L"PipeManager", LEVEL_DEBUG, L"EchoPipe Stopped");

}
