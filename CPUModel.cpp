#include "CPUModel.h"

void CPU_model::send_data(){
	sc_time blockedTime = sc_time(13, SC_NS);
	sc_time pauseTime = sc_time(15, SC_NS);


	tlm::tlm_generic_payload trans;
	sc_time delay = SC_ZERO_TIME;

	unsigned char data[104];
	unsigned char A[8] = { 1,1,1,1,1,1,1,1 };
	unsigned char B[96] = { 1, 0, 3, 2, 1, 5, 8, 3, 4, 5, 6, 3,
		1, 0, 3, 2, 1, 5, 8, 3, 4, 5, 6, 3, 
		1, 0, 3, 2, 1, 5, 8, 3, 4, 5, 6, 3, 
		1, 0, 3, 2, 1, 5, 8, 3, 4, 5, 6, 3, 
		1, 0, 3, 2, 1, 5, 8, 3, 4, 5, 6, 3, 
		1, 0, 3, 2, 1, 5, 8, 3, 4, 5, 6, 3,
		1, 0, 3, 2, 1, 5, 8, 3, 4, 5, 6, 3,
		1, 0, 3, 2, 1, 5, 8, 3, 4, 5, 6, 3};



	for (int i = 0; i < 104; i++){
		if (i < 8)
			data[i] = A[i];
		else
			data[i] = B[i-8];

	}

	trans.set_command(tlm::TLM_WRITE_COMMAND);
	trans.set_data_ptr(data);
	trans.set_data_length(104);

	cpu_send_socket->b_transport(trans, delay);


}


void CPU_model::b_transport(tlm::tlm_generic_payload & trans, sc_time& delay){
	unsigned char* data = trans.get_data_ptr();
	std::cout << "Initiator received data: ";
	for (int i = 0; i < trans.get_data_length(); ++i) {
		std::cout << static_cast<int>(*(data + i)) << " ";
	}
	std::cout << std::endl;
}