#include<functional>
#include<fstream>
#include<string>
#include<string_view>
#include"RequestPayload.h"
#include"UdpSocket.h"
#include"ReadBuffer.h"
#include"Utils.h"
namespace Daw{
	
	/**
	class TransferProcess{
		public:
		size_t total_size;
		size_t completed_size;
	};
	**/
	
	class FiletsClient{
		protected:
			UdpSocket socket_;
			ReadBuffer buffer_;
			std::ifstream* in_;
			size_t file_size_;
			std::string file_path_;

			TransferProcess status_;

		protected:
			static std::string_view parse_file_name(const std::string& file);

			RequestPayload* prepare_send_request();

		public:
			FiletsClient(const std::string& path);

			void connect(const std::string& host,const port_t port);

			bool try_send(void);

			void send(const std::function<bool(TransferProcess)>&callback);

			void close(void);

	};
}
