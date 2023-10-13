#pragma once

#include "../NetRoot/NetServer/NetPipe.h"
#include "../Player/PlayerMap.h"
#include "GameEchoClient.h"

namespace server_baby
{
	class AuthPipe_CS_Stub;
	class AuthPipe_SC_Proxy;
	class PipePlayer;

	class AuthPipe final : public NetPipe
	{
	public:
		explicit AuthPipe(NetRoot* server, unsigned int framePerSecond, unsigned int threadNum = 1);
		virtual ~AuthPipe() { delete proxy_; }

		NetUser* OnUserJoin(NetSessionID NetSessionID) override;
		void OnUserLeave(NetUser* const user) override;
		void OnUserMoveIn(NetUser* const user) override;
		void OnUserMoveOut(NetSessionID NetSessionID) override;
		void OnUserMoveOut(NetUser* const user) override;
		void OnUpdate(NetUser* const user) override;
		void OnMonitor(const LoopInfo* const info) override;
		void OnStart() override;
		void OnStop() override;


		bool DisconnectAbnormalPlayer(NetSessionID ID){ return Disconnect(ID);}

	public:
		AuthPipe_SC_Proxy* proxy_;
		UserMap<NetSessionID> onlineMap_;
		int framePerSec_;

	};
}