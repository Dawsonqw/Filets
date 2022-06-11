#ifndef RECVRESPONSE_H
#define RECVRESPONSE_H

#include"Payload.h"
#include<vector>
#include<string>

namespace Daw{
	class RecvResponse final:public Payload{
		public:
			bool response;

		public:
			std::vector<uint8_t>serialize(void)override;

			void serialize_append(std::vector<uint8_t>&out)override;

			static void deserialize(std::vector<uint8_t>&buffer,RecvResponse** parsed_section);

			bool operator==(const Payload* other)const override;

			bool operator==(const Payload& other)const override;
	};
}

#endif
