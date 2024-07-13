#include <systemc.h>
#include "tlm.h"
#include "tlm_utils\simple_target_socket.h"
#include "tlm_utils\simple_initiator_socket.h"

class CPU_model : public sc_module{
public:
	tlm_utils::simple_initiator_socket<CPU_model> cpu_send_socket;
	tlm_utils::simple_target_socket<CPU_model> cpu_receive_socket;

	SC_CTOR(CPU_model) : cpu_send_socket("cpu_send_socket"), cpu_receive_socket("cpu_receiver_socket"),
		AB_payload(0) {
		cpu_receive_socket.register_b_transport(this, &CPU_model::b_transport);
		AB_payload = new tlm::tlm_generic_payload;

		SC_THREAD(send_data);
	}

	void send_data();
	tlm::tlm_generic_payload* AB_payload;

	void b_transport(tlm::tlm_generic_payload & trans, sc_time& delay);

	sc_lv<8> data[104];
};

