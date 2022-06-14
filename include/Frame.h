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
			///数据帧：序列号 响应号 数据载体
			uint32_t seq;
			uint32_t ack;
			FrameType type;
			///crc sections checksum
			Payload* payload=nullptr;
			///todo：是否加上校验

		public:
			Frame()=default;

			Frame(seq_t seq,seq_t ack,FrameType type);

			///put a section on the back of thre frame
			void mount(Payload* payload);
			
			//序列化
			std::vector<uint8_t> get(void)const;

			static Frame put(std::vector<uint8_t>& frame);

			bool operator==(const Frame& other)const;
	};

	uint32_t cal_crc32(const std::vector<uint8_t>&content);
}

#endif
