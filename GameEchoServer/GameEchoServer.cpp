#include "GameEchoServer.h"
#include "../NetRoot/Common/PDHMonitor.h"
#include "../NetRoot/Common/Parser.h"
#include "../MonitorProtocol.h"

bool server_baby::GameEchoServer::OnConnectionRequest(const SOCKADDR_IN* const addr)
{
    return true;
}

void server_baby::GameEchoServer::OnClientLeave(NetSessionID NetSessionID)
{

}

void server_baby::GameEchoServer::OnSend(NetSessionID NetSessionID, int sendSize)
{

}

void server_baby::GameEchoServer::OnWorkerThreadBegin()
{

}

void server_baby::GameEchoServer::OnWorkerThreadEnd()
{

}

void server_baby::GameEchoServer::OnMonitor(const MonitoringInfo* const info)
{
    HardwareMonitor::CpuUsageForProcessor::GetInstance()->UpdateCpuTime();
    ProcessMonitor::CpuUsageForProcess::GetInstance()->UpdateCpuTime();
    ProcessMonitor::MemoryForProcess::GetInstance()->Update();

    time_t timer;
    timer = time(NULL);

    LanPacket* packet = LanPacket::Alloc();

    *packet << static_cast<WORD>(en_PACKET_SS_MONITOR_DATA_UPDATE);
    *packet << static_cast<BYTE>(dfMONITOR_DATA_TYPE_GAME_SERVER_RUN);
    *packet << static_cast<int>(true);
    *packet << static_cast<int>(timer);

    echoClient_.SendPacket(packet);
    packet->Clear();

    *packet << static_cast<WORD>(en_PACKET_SS_MONITOR_DATA_UPDATE);
    *packet << static_cast<BYTE>(dfMONITOR_DATA_TYPE_GAME_SERVER_CPU);
    *packet << static_cast<int>(ProcessMonitor::CpuUsageForProcess::GetInstance()->ProcessTotal());
    *packet << static_cast<int>(timer);

    echoClient_.SendPacket(packet);
    packet->Clear();

    *packet << static_cast<WORD>(en_PACKET_SS_MONITOR_DATA_UPDATE);
    *packet << static_cast<BYTE>(dfMONITOR_DATA_TYPE_GAME_SERVER_MEM);
    *packet << static_cast<int>(ProcessMonitor::MemoryForProcess::GetInstance()->GetPrivateBytes(L"GameEchoServer") / eMEGA_BYTE);
    *packet << static_cast<int>(timer);

    echoClient_.SendPacket(packet);
    packet->Clear();

    *packet << static_cast<WORD>(en_PACKET_SS_MONITOR_DATA_UPDATE);
    *packet << static_cast<BYTE>(dfMONITOR_DATA_TYPE_GAME_SESSION);
    *packet << static_cast<int>(info->sessionCount_);
    *packet << static_cast<int>(timer);

    echoClient_.SendPacket(packet);
    packet->Clear();

    *packet << static_cast<WORD>(en_PACKET_SS_MONITOR_DATA_UPDATE);
    *packet << static_cast<BYTE>(dfMONITOR_DATA_TYPE_GAME_ACCEPT_TPS);
    *packet << static_cast<int>(info->acceptTPS_);
    *packet << static_cast<int>(timer);

    echoClient_.SendPacket(packet);
    packet->Clear();

    *packet << static_cast<WORD>(en_PACKET_SS_MONITOR_DATA_UPDATE);
    *packet << static_cast<BYTE>(dfMONITOR_DATA_TYPE_GAME_PACKET_POOL);
    *packet << static_cast<int>(info->packetCount_);
    *packet << static_cast<int>(timer);

    echoClient_.SendPacket(packet);
    packet->Clear();

    *packet << static_cast<WORD>(en_PACKET_SS_MONITOR_DATA_UPDATE);
    *packet << static_cast<BYTE>(dfMONITOR_DATA_TYPE_MONITOR_CPU_TOTAL);
    *packet << static_cast<int>(HardwareMonitor::CpuUsageForProcessor::GetInstance()->ProcessorTotal());
    *packet << static_cast<int>(timer);

    echoClient_.SendPacket(packet);
    packet->Clear();

    *packet << static_cast<WORD>(en_PACKET_SS_MONITOR_DATA_UPDATE);
    *packet << static_cast<BYTE>(dfMONITOR_DATA_TYPE_MONITOR_NONPAGED_MEMORY);
    *packet << static_cast<int>(ProcessMonitor::MemoryForProcess::GetInstance()->GetNonPagedByte() / eMEGA_BYTE);
    *packet << static_cast<int>(timer);

    echoClient_.SendPacket(packet);
    packet->Clear();

    *packet << static_cast<WORD>(en_PACKET_SS_MONITOR_DATA_UPDATE);
    *packet << static_cast<BYTE>(dfMONITOR_DATA_TYPE_MONITOR_NETWORK_RECV);
    *packet << static_cast<int>(ProcessMonitor::MemoryForProcess::GetInstance()->GetTotalRecvBytes() / eKILO_BYTE);
    *packet << static_cast<int>(timer);

    echoClient_.SendPacket(packet);
    packet->Clear();

    *packet << static_cast<WORD>(en_PACKET_SS_MONITOR_DATA_UPDATE);
    *packet << static_cast<BYTE>(dfMONITOR_DATA_TYPE_MONITOR_NETWORK_SEND);
    *packet << static_cast<int>(ProcessMonitor::MemoryForProcess::GetInstance()->GetTotalSendBytes() / eKILO_BYTE);
    *packet << static_cast<int>(timer);

    echoClient_.SendPacket(packet);
    packet->Clear();

    *packet << static_cast<WORD>(en_PACKET_SS_MONITOR_DATA_UPDATE);
    *packet << static_cast<BYTE>(dfMONITOR_DATA_TYPE_MONITOR_AVAILABLE_MEMORY);
    *packet << static_cast<int>(ProcessMonitor::MemoryForProcess::GetInstance()->GetAvailableBytes());
    *packet << static_cast<int>(timer);

    echoClient_.SendPacket(packet);
    packet->Clear();

    *packet << static_cast<WORD>(en_PACKET_SS_MONITOR_DATA_UPDATE);
    *packet << static_cast<BYTE>(dfMONITOR_DATA_TYPE_GAME_PACKET_RECV_TPS);
    *packet << static_cast<int>(info->recvTPS_);
    *packet << static_cast<int>(timer);

    echoClient_.SendPacket(packet);
    packet->Clear();

    *packet << static_cast<WORD>(en_PACKET_SS_MONITOR_DATA_UPDATE);
    *packet << static_cast<BYTE>(dfMONITOR_DATA_TYPE_GAME_PACKET_SEND_TPS);
    *packet << static_cast<int>(info->sendTPS_);
    *packet << static_cast<int>(timer);

    echoClient_.SendPacket(packet);
    packet->Clear();

    *packet << static_cast<WORD>(en_PACKET_SS_MONITOR_DATA_UPDATE);
    *packet << static_cast<BYTE>(dfMONITOR_DATA_TYPE_LOGIN_PACKET_POOL);
    *packet << static_cast<int>(info->recvTPS_ / 10000);
    *packet << static_cast<int>(timer);

    echoClient_.SendPacket(packet);
    packet->Clear();

    *packet << static_cast<WORD>(en_PACKET_SS_MONITOR_DATA_UPDATE);
    *packet << static_cast<BYTE>(dfMONITOR_DATA_TYPE_CHAT_PACKET_POOL);
    *packet << static_cast<int>(info->sendTPS_ / 10000);
    *packet << static_cast<int>(timer);

    echoClient_.SendPacket(packet);
    packet->Clear();

    *packet << static_cast<WORD>(en_PACKET_SS_MONITOR_DATA_UPDATE);
    *packet << static_cast<BYTE>(dfMONITOR_DATA_TYPE_GAME_GAME_PLAYER);
    *packet << static_cast<int>(echoPipe_->GetUserSize());
    *packet << static_cast<int>(timer);

    echoClient_.SendPacket(packet);
    packet->Clear();

    *packet << static_cast<WORD>(en_PACKET_SS_MONITOR_DATA_UPDATE);
    *packet << static_cast<BYTE>(dfMONITOR_DATA_TYPE_GAME_GAME_THREAD_FPS);
    *packet << static_cast<int>(echoPipe_->framePerSec_);
    *packet << static_cast<int>(timer);

    echoClient_.SendPacket(packet);
    packet->Clear();

    *packet << static_cast<WORD>(en_PACKET_SS_MONITOR_DATA_UPDATE);
    *packet << static_cast<BYTE>(dfMONITOR_DATA_TYPE_GAME_AUTH_PLAYER);
    *packet << static_cast<int>(authPipe_->GetUserSize());
    *packet << static_cast<int>(timer);

    echoClient_.SendPacket(packet);
    packet->Clear();

    *packet << static_cast<WORD>(en_PACKET_SS_MONITOR_DATA_UPDATE);
    *packet << static_cast<BYTE>(dfMONITOR_DATA_TYPE_GAME_AUTH_THREAD_FPS);
    *packet << static_cast<int>(authPipe_->framePerSec_);
    *packet << static_cast<int>(timer);

    echoClient_.SendPacket(packet);

    LanPacket::Free(packet);

    ProcessMonitor::MemoryForProcess::GetInstance()->ZeroEthernetValue();  
    SystemLogger::GetInstance()->Console(L"GameEchoServer", LEVEL_DEBUG, L"Recv TPS : %d", info->recvTPS_);
    SystemLogger::GetInstance()->Console(L"GameEchoServer", LEVEL_DEBUG, L"Send TPS : %d", info->sendTPS_);

  
}

void server_baby::GameEchoServer::OnStart()
{
    int relayPort = 0;
    Parser::GetInstance()->GetValue("RelayServerPort", (int*)&relayPort);
    SystemLogger::GetInstance()->Console(L"NetServer", LEVEL_DEBUG, L"Relay Server Port : %d", relayPort);

    char IP[16] = "127.0.0.1";
    echoClient_.Start(IP, relayPort);

}
