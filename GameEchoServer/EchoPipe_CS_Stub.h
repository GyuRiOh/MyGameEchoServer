
#include <Windows.h>
#include "../NetRoot/NetServer/NetSessionID.h"
#include "../NetRoot/NetServer/NetPacketSet.h"
#include "../NetRoot/NetServer/NetUser.h"
#include "EchoPipe_SC_Proxy.h"
#include "EchoPipe.h"
#include "PipePlayer.h"
#include "../CommonProtocol.h"
#include "../PacketStruct.h"
#include "../NetRoot/NetServer/NetStub.h"

namespace server_baby
{
	class EchoPipe_CS_Stub final : public NetStub
	{
	public:
		explicit EchoPipe_CS_Stub(EchoPipe* server) : server_(server) {}

		bool PacketProc(NetSessionID sessionID, NetDummyPacket* msg) override
		{
			WORD type;
			*msg >> type;
			switch (type)
			{
			case en_PACKET_CS_GAME_REQ_ECHO:
			{
				PACKET_CS_GAME_REQ_ECHO* reqEchoMsg = (PACKET_CS_GAME_REQ_ECHO*)(msg->GetStart());
				PipePlayer* player = (PipePlayer*)server_->FindUser(sessionID);

				if (!player)
					CrashDump::Crash();

				server_->proxy_->ResEcho(
					player->GetAccountNumber(),
					reqEchoMsg->SendTick, 
					sessionID);
			}
				return true;
			}
			return false;
			CrashDump::Crash();
		}

	private:
		EchoPipe* server_;
	};
}
