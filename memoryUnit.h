#include <systemc.h>
#include "tlm.h"
#include "tlm_utils\simple_target_socket.h"
#include "tlm_utils\simple_initiator_socket.h"

SC_MODULE(memoryUnit){
	tlm_utils::simple_target_socket<memoryUnit> memSideSocket;
	tlm_utils::simple_initiator_socket<memoryUnit> memSideSocket2;

	unsigned char C[12];

	SC_CTOR(memoryUnit) : memSideSocket("memorySideSocket"), memSideSocket2("memorySideSocket2"){

		memSideSocket.register_b_transport(this, &memoryUnit::b_transport);
	}
public:
	virtual void b_transport(tlm::tlm_generic_payload&, sc_time&);
	void send_data_thread() {

			// Create a transaction to send data to the initiator
			tlm::tlm_generic_payload trans;
			sc_time delay = SC_ZERO_TIME;
			trans.set_command(tlm::TLM_WRITE_COMMAND);
			trans.set_data_ptr((unsigned char*)C);
			trans.set_data_length(12);

			// Send the transaction to the initiator
			memSideSocket2->b_transport(trans, delay);

	}
};