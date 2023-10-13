#include <Windows.h>
#include "../NetRoot/NetServer/NetSessionID.h"
#include "AuthPipe_SC_Proxy.h"
#include "AuthPipe.h"
#include "PipePlayer.h"
#include "../CommonProtocol.h"

namespace server_baby
{
	class AuthPipe_CS_Stub final : public NetStub
	{
	public:
		explicit AuthPipe_CS_Stub(AuthPipe* server) : server_(server){}

		bool PacketProc(NetSessionID NetSessionID, NetDummyPacket* msg) override
		{
			WORD type;
			*msg >> type;
			switch (type)
			{
			case en_PACKET_CS_GAME_REQ_LOGIN:
			{
				INT64 accountNo;
				char sessionKey[64] = {0};
				int version = 0;
				*msg >> accountNo;
				msg->DeqData((char*)sessionKey, 64);
				*msg >> version;
				ReqLogin(accountNo, sessionKey, NetSessionID);
			}
				return true;
			}
			return false;
		}

		void ReqLogin(INT64 accountNo, char* sessionKey, NetSessionID sessionID)
		{
			PipePlayer* player = (PipePlayer*)server_->FindUser(sessionID);
			if (!player)
				CrashDump::Crash();

			player->accountNum_ = accountNo;

			//중복로그인 체크 - 온라인 맵
			if (!server_->onlineMap_.Insert(sessionID, player->GetAccountNumber()))
			{
				SystemLogger::GetInstance()->LogText(L"AuthPipe", LEVEL_ERROR,
					L"Login - Duplicated. %d", accountNo);
				CrashDump::Crash();
			}
			
			server_->MovePipe((NetUser*)player, 6789);
			server_->proxy_->ResLogin(true, player->GetAccountNumber(), sessionID);
		}

	private:
		AuthPipe* server_;
	};
}
