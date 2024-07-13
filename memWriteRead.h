#include <systemc.h>
#include "tlm.h"
#include "tlm_utils\simple_target_socket.h"
#include "tlm_utils\simple_initiator_socket.h"

class memWriterReader : public sc_module{
public:
	tlm_utils::simple_initiator_socket<memWriterReader> memWriterReaderSocket;
	tlm_utils::simple_target_socket<memWriterReader> memWriterReaderSocket2;

	SC_CTOR(memWriterReader) : memWriterReaderSocket("Writer-socket"), memWriterReaderSocket2("receiver-socket"),
								blockWriteRead(0) {
		memWriterReaderSocket2.register_b_transport(this, &memWriterReader::b_transport);
		blockWriteRead = new tlm::tlm_generic_payload;
		/// soket
		//for (int i = 0; i < 4; i++) *(data + i) = i + 192;

		SC_THREAD(memWritingReading);
	}

	void memWritingReading();
	tlm::tlm_generic_payload* blockWriteRead;

	void b_transport(tlm::tlm_generic_payload & trans, sc_time& delay){
		unsigned char* data = trans.get_data_ptr();
		std::cout << "Initiator received data: ";
		for (int i = 0; i < trans.get_data_length(); ++i) {
			std::cout << static_cast<int>(*(data+i)) << " ";
		}
		std::cout << std::endl;
	}

	sc_lv<8> data[104];
};

