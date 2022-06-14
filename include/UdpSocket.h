#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include<sys/socket.h>
#include<vector>
#include<netinet/in.h>
#include<string>

using byte_t =unsigned char;
using port_t =unsigned short;

namespace Daw{
	struct UdpPacket{
		public:
			std::string host;
			port_t port;
			std::vector<byte_t> payload;
	};

	const int INVALID_SOCKET=-1;

	class UdpSocket{
		public:
			static constexpr size_t DefaultBufferSize=1500;

		private:
			int m_fd;
			sockaddr_in local_addr{};
			sockaddr_in remote_addr{};

		public:
			UdpSocket();

			UdpSocket(const std::string& local_addr,port_t port);

			void connect(const std::string& local_addr,port_t port);

			void bind(const std::string& local_addr,port_t port);

			size_t sendto(const std::vector<byte_t>&buffer,const std::string& remote_addr,const port_t remote_port);

			size_t send(const std::vector<byte_t>&buffer);

			size_t recvfrom(std::vector<byte_t>&buffer,std::string& src_address,port_t& src_port);

			UdpPacket recvfrom(const size_t max_size=DefaultBufferSize);

			void close();
	};
}

#endif
