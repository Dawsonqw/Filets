#ifndef FREAME_H
#define FREAME_H

#include<vector>
#include<stdint.h>
namespace Daw{
	enum struct FrameType{
		/// Client send SendRequest to server
		SendRequest=1,
		/// Server send RecvResonse to client
		RecvResponse=2,
		Data=10
	};

	using seq_t=uint32_t;

	struct Payload;

	class Frame{
		public:
			uint32_t seq;
			uint32_t ack;
			FrameType type;
			///crc sections checksum
			Payload* payload=nullptr;

		public:
			Frame()=default;

			Frame(seq_t seq,seq_t ack,FrameType type);

			///put a section on the back of thre frame
			void put(Payload* payload);
			
			//序列化
			std::vector<uint8_t> serialize(void)const;

			static Frame deserialize(std::vector<uint8_t>& frame);

			bool operator==(const Frame& other)const;
	};

	uint32_t cal_crc32(const std::vector<uint8_t>&content);
}

#endif
