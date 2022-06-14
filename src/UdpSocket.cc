#include"UdpSocket.h"
#include<vector>
#include<string>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<exception>


namespace Daw{

	UdpSocket::UdpSocket(const std::string& local_addr,port_t port):UdpSocket(){
		this->bind(local_addr,port);
	}

	UdpSocket::UdpSocket(){
		this->m_fd=socket(AF_INET,SOCK_DGRAM,0);
		if(INVALID_SOCKET==this->m_fd)throw std::exception();
	}

	void UdpSocket::bind(const std::string& local_addr,port_t port){
		struct sockaddr_in& cur_local_addr=this->local_addr;

		cur_local_addr.sin_family=AF_INET;
		cur_local_addr.sin_port=htons(port);
		inet_pton(AF_INET,local_addr.c_str(),&cur_local_addr.sin_addr);

		if(::bind(this->m_fd,(struct sockaddr*)&cur_local_addr,sizeof(sockaddr_in))){
			throw std::exception();
		}
	}

	size_t UdpSocket::sendto(const std::vector<byte_t>&buffer,const std::string& remote_addr,const port_t remote_port){
		struct sockaddr_in dst_addr;

		dst_addr.sin_family=AF_INET;
		dst_addr.sin_port=htons(remote_port);
		inet_pton(AF_INET,remote_addr.c_str(),&dst_addr.sin_addr);

		int send_size=::sendto(this->m_fd,reinterpret_cast<const char*>(&buffer[0]),buffer.size(),0,(struct sockaddr*)&dst_addr,sizeof(dst_addr));
		
		if(send_size==-1)throw std::exception();
		return send_size;
	}

	size_t UdpSocket::send(const std::vector<byte_t>& buffer){
		int send_size=::sendto(this->m_fd,reinterpret_cast<const char*>(&buffer[0]),buffer.size(),0,(struct sockaddr*)&(this->remote_addr),sizeof(sockaddr_in));
		
		if(send_size==-1)throw std::exception();

		return send_size;
	}

	void UdpSocket::connect(const std::string& remote_addr,port_t remote_port){
		struct sockaddr_in& dst_addr=this->remote_addr;
		dst_addr.sin_family=AF_INET;
		dst_addr.sin_port=htons(remote_port);
		inet_pton(AF_INET,remote_addr.c_str(),&dst_addr.sin_addr);
		///todo?没写完吧。。。
		if(::connect(this->m_fd,(struct sockaddr*)&dst_addr,sizeof(dst_addr)))
			throw std::exception();
	}


	size_t UdpSocket::recvfrom(std::vector<byte_t>&buffer,std::string& src_addr,port_t& src_port){
		struct sockaddr_in cur_addr{};
		socklen_t cur_len=sizeof(cur_addr);

		int recv_size=::recvfrom(this->m_fd,reinterpret_cast<char*>(&buffer[0]),buffer.capacity(),0,(struct sockaddr*)&cur_addr,&cur_len);

		if(recv_size<0)throw std::exception();
		///传出 port和addr
		src_addr=inet_ntoa(cur_addr.sin_addr);
		src_port=htons(cur_addr.sin_port);
		return recv_size;
	}

	UdpPacket UdpSocket::recvfrom(const size_t max_size){
		std::string address;
		port_t port;
		std::vector<byte_t>buffer(max_size);

		int recv_size=this->recvfrom(buffer,address,port);
		buffer.resize(recv_size);
		return UdpPacket{address,port,std::move(buffer)};
	}

	void UdpSocket::close(){
		shutdown(this->m_fd,2);
		m_fd=INVALID_SOCKET;
	}

}
