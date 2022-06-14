#ifndef REQUESTPAYLOAD_H
#define REQUESTPAYLOAD_H

#include<string>
#include"Payload.h"

namespace Daw{
	class RequestPayload final:public Payload{
		public:
			std::string client_name;
			std::string file_name;
			uint32_t file_id=0x00;
			uint32_t file_size;
			uint16_t block_size=1024;

		public:
			std::vector<uint8_t>get(void)override;

			void get_append(std::vector<uint8_t>&out)override;

			static void put(std::vector<uint8_t>&content,RequestPayload** parsed_section);

			bool operator==(const Payload* other)const override;

			bool operator==(const Payload& other)const override;
	};
}

#endif
