
#include "memoryUnit.h"

void memoryUnit::b_transport(tlm::tlm_generic_payload& gotThis, sc_time& delayValue){

	int A[8];
	int B[8][12];
	unsigned char* data = gotThis.get_data_ptr();
	std::cout << "Target received data: ";
	for (int i = 0; i < gotThis.get_data_length(); ++i) {
		std::cout  << static_cast<int>(data[i]) << " ";
	}
	for (int i = 0; i < 8; i++){
		A[i] = static_cast<int>(data[i]);
	}
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 12; j++){
			B[i][j] = static_cast<int>(data[i*12+j+8]);
		}
	}


	

	for (int i = 0; i < 12; i++) {
		C[i] = 0;
		for (int j = 0; j < 8; j++) {
			C[i] += A[j] * B[j][i];
			wait(300, SC_NS);
		}
	}

	
	std::cout << std::endl;

	send_data_thread();


	wait(10, SC_NS);

	
};

