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
        //�����Լ���
        //==========================
        bool OnConnectionRequest(const SOCKADDR_IN* const addr) override; //Accept ����. return false�� Ŭ���̾�Ʈ �ź�, true�� ���� ���
        void OnClientJoin(NetSessionID NetSessionID) override; //Accept �� ���� ó�� �Ϸ� �� ȣ��.
        void OnClientLeave(NetSessionID NetSessionID) override; //Release �� ȣ��
        void OnSend(NetSessionID NetSessionID, int sendSize) override; //��Ŷ �۽� �Ϸ� ��
        void OnWorkerThreadBegin() override; //��Ŀ������ GQCS �ϴܿ��� ȣ��
        void OnWorkerThreadEnd() override; //��Ŀ������ 1���� ���� ��
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