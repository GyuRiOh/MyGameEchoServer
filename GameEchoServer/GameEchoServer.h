#pragma once
#include "../NetRoot/NetServer/NetServer.h"
#include "AuthPipe.h"
#include "EchoPipe.h"
#include "../NetRoot/NetServer/PipeManager.h"
#include "GameEchoClient.h"

namespace server_baby
{
	class GameServer final : public NetRoot
	{
    public:
        explicit GameServer() : authPipe_(nullptr), echoPipe_(nullptr)
        {

            //authManager_ = new PipeManager<AuthPipe>(1, 10, this, 1234, 25, false);
            //echoManager_ = new PipeManager<EchoPipe>(1, 10, this, 6789, 25, false);

            //authManager_->Start();
            //echoManager_->Start();

            authPipe_ = new AuthPipe(this, 3);
            echoPipe_ = new EchoPipe(this, 10);

            RegisterPipe(1234, authPipe_);
            RegisterPipe(6789, echoPipe_);
        }

        ~GameServer() 
        {}

    private:
        //==========================
        //가상함수들
        //==========================
        bool OnConnectionRequest(const SOCKADDR_IN* const addr) override; //Accept 직후. return false시 클라이언트 거부, true시 접속 허용
        void OnClientJoin(NetSessionID NetSessionID) override; //Accept 후 접속 처리 완료 후 호출.
        void OnClientLeave(NetSessionID NetSessionID) override; //Release 후 호출
        void OnSend(NetSessionID NetSessionID, int sendSize) override; //패킷 송신 완료 후
        void OnWorkerThreadBegin() override; //워커스레드 GQCS 하단에서 호출
        void OnWorkerThreadEnd() override; //워커스레드 1루프 종료 후
        void OnError(int errCode, WCHAR*) {}
        void OnMonitor(const MonitoringInfo* const info);
        void OnStart() override;

    public:
        GameEchoClient echoClient_;

    private:
        AuthPipe* authPipe_; 
        EchoPipe* echoPipe_;
    };


    inline void server_baby::GameServer::OnClientJoin(NetSessionID sessionID)
    {
        MovePipe(sessionID, authPipe_->GetPipeID().element_.code_);
    }
}