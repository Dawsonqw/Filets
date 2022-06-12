#ifndef FILETSSERVER_H
#define FILETSSERVER_H

#include<functional>
#include<string>
#include<string_view>
#include"RequestPayload.h"
#include"UdpSocket.h"
#include"WriteBuffer.h"
#include"Utils.h"

namespace Daw{
	//保留发送信息 其实可以分成两个部分放到Server中
	/**
	class TransferProcess{
		public:
		size_t total_size;
		size_t completed_size;	
	};
	**/

	class FiletsServer{
		protected:
			UdpSocket socket_;
			
			///文件流
			std::ofstream* out_=nullptr;
			///发送缓冲区
			WriteBuffer* buffer_;	
			///发送文件大小
			size_t file_size_;
			///发送文件路径
			std::string file_path_;
			///保留发送文件信息 主要已经发送大小 和 总大小
			TransferProcess status_;

		public:
			FiletsServer(const std::string& path);

			void listen(const std::string& host,const port_t port);

			RequestPayload wait();

			void accept();

			void decline();

			void write(const std::function<bool(TransferProcess)>& callback);

			void close();
	};
}

#endif
