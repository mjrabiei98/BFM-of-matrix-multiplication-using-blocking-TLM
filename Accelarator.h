#include <systemc.h>
#include "tlm.h"
#include "tlm_utils\simple_target_socket.h"
#include "tlm_utils\simple_initiator_socket.h"

SC_MODULE(accelarator){
	tlm_utils::simple_target_socket<accelarator> acc_receive_socket;
	tlm_utils::simple_initiator_socket<accelarator> acc_send_socket;

	int A[8];
	int B[8][12];
	unsigned char C[12]; // result

	SC_CTOR(accelarator) : acc_receive_socket("acc_receive_socket"), acc_send_socket("acc_send_socket"){

		acc_receive_socket.register_b_transport(this, &accelarator::b_transport);
	}
public:
	virtual void b_transport(tlm::tlm_generic_payload&, sc_time&);
	void send_data_thread();
	void calculate_result();
	void extract_data(tlm::tlm_generic_payload& gotThis);
	void MAC(unsigned char &c, int a, int b, sc_time& delayValue);
};