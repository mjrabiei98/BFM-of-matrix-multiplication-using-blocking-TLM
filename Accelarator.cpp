
#include "Accelarator.h"

void accelarator::b_transport(tlm::tlm_generic_payload& gotThis, sc_time& delayValue){

	extract_data(gotThis);
	calculate_result();
	send_data_thread();

};


void accelarator::send_data_thread() {

	wait(100, SC_NS);

	tlm::tlm_generic_payload trans;
	sc_time delay = SC_ZERO_TIME;
	trans.set_command(tlm::TLM_WRITE_COMMAND);
	trans.set_data_ptr((unsigned char*)C);
	trans.set_data_length(12);

	acc_send_socket->b_transport(trans, delay);

}


void accelarator::MAC(unsigned char &c, int a, int b, sc_time& delayValue){
	c += a * b;
	wait(delayValue);
}


void accelarator::calculate_result(){
	std::cout << "starting calculation" << endl;
	std::cout << "result : \n";
	for (int i = 0; i < 12; i++) {
		C[i] = 0;
		for (int j = 0; j < 8; j++) {
			MAC(C[i], A[j], B[j][i], sc_time(300, SC_NS));

		}
		std::cout << static_cast<int>(C[i]) << " ";
	}
	std::cout << "\ncalculation end at " << sc_time_stamp() << endl;
}


void accelarator::extract_data(tlm::tlm_generic_payload& gotThis){
	unsigned char* data = gotThis.get_data_ptr();
	std::cout << "acc received data at " << sc_time_stamp() << endl;
	std::cout << "extracting data .. " << endl;
	std::cout << "A: \n";
	for (int i = 0; i < 8; i++){
		A[i] = static_cast<int>(data[i]);
		std::cout << static_cast<int>(data[i]) << " ";
	}
	std::cout << "\nB: \n";
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 12; j++){
			B[i][j] = static_cast<int>(data[i * 12 + j + 8]);
			std::cout << static_cast<int>(B[i][j]) << " ";
		}
		std::cout << "\n";
	}
}