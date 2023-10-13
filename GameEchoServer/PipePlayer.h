#pragma once
#include "../NetRoot/NetServer/NetUser.h"
#include "../NetRoot/NetServer/NetSessionID.h"
#include "../Sector/Sector.h"
#include "../PacketStruct.h"

namespace server_baby
{
	class PipePlayer : public NetUser
	{
	public:
		explicit PipePlayer(NetSessionID ID, NetRoot* server, NetPipeID curPipe) : 
			NetUser(ID, server, curPipe), accountNum_(NULL) 
		{ }
		~PipePlayer() { Destroy(); }

		bool UpdateInfo(PACKET_CS_CHAT_REQ_LOGIN* loginPacket)
		{
			if (accountNum_ != NULL)
				return false;

			accountNum_ = loginPacket->accountNum_;
			return true;
		}

		INT64 GetAccountNumber() const { return accountNum_; }

		void Destroy()
		{
			accountNum_ = NULL;
		}

	public:
		INT64 accountNum_;
	};
}
