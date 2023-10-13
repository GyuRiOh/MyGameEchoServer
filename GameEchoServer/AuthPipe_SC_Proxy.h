#include "../NetRoot/NetServer/NetPacket.h"
#include "../NetRoot/NetServer/NetSessionID.h"
#include "AuthPipe.h"
#include "../CommonProtocol.h"

namespace server_baby
{
	class AuthPipe_SC_Proxy final
	{
	public:
		explicit AuthPipe_SC_Proxy(AuthPipe* server) : server_(server){}

		void ResLogin(BYTE status, INT64 accountNo, NetSessionID NetSessionID)
		{
			//���� �Լ� ȣ���� ��û�ϴ� Proxy�� ���, 
			//�ƹ��͵� ���� �ʾƵ�
			//�ڵ����� �Լ� �ڵ� ��ü�� ���������.

			NetPacket* msg = NetPacket::Alloc();

			*msg << (unsigned short)en_PACKET_CS_GAME_RES_LOGIN;
			*msg << status;
			*msg << accountNo;

			server_->AsyncSendPacket(NetSessionID, msg);
			NetPacket::Free(msg);
		}

	private:
		AuthPipe* server_;
	};
}
