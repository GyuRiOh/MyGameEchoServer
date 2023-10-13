#include "../NetRoot/NetServer/NetPacket.h"
#include "../NetRoot/NetServer/NetSessionID.h"
#include "EchoPipe.h"
#include "../CommonProtocol.h"

namespace server_baby
{
	class EchoPipe_SC_Proxy final
	{
	public:
		explicit EchoPipe_SC_Proxy(EchoPipe* const server) : server_(server){}

		void ResEcho(INT64 accountNo, LONGLONG sendTick, NetSessionID NetSessionID)
		{
			NetPacket* msg = NetPacket::Alloc();

			*msg << (unsigned short)en_PACKET_CS_GAME_RES_ECHO;
			*msg << accountNo;
			*msg << sendTick;

			server_->AsyncSendPacket(NetSessionID, msg);
			NetPacket::Free(msg);
		}


	private:
		EchoPipe* server_;
	};
}
