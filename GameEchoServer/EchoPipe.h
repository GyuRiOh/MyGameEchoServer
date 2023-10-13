#pragma once

#include "../NetRoot/NetServer/NetPipe.h"
#include "GameEchoClient.h"

namespace server_baby
{
	class PipePlayer;
	class EchoPipe_CS_Stub;
	class EchoPipe_SC_Proxy;

	class EchoPipe final : public NetPipe
	{
	public:
		explicit EchoPipe(NetRoot* server, unsigned int framePerSecond, unsigned int threadNum = 1);
		virtual ~EchoPipe() { delete proxy_; }

		NetUser* OnUserJoin(const NetSessionID sessionID) override;
		void OnUserLeave(NetUser* const user) override;
		void OnUserMoveIn(NetUser* const user) override;
		void OnUserMoveOut(const NetSessionID sessionID) override;
		void OnUserMoveOut(NetUser* const user) override;
		void OnUpdate(NetUser* const user) override;
		void OnMonitor(const LoopInfo* const info) override;
		void OnStart() override;
		void OnStop() override;

	public:
		EchoPipe_SC_Proxy* proxy_;
		int framePerSec_;

	};
}