#include "CPUModel.h"
#include "Accelarator.h"

SC_MODULE(testbench){
	CPU_model* MW1;
	accelarator *MU1;

	SC_CTOR(testbench){
		MU1 = new accelarator("memoryUnit");
		MW1 = new CPU_model("memoryWriter");
		MW1->cpu_send_socket(MU1->acc_send_socket);
		MU1->acc_receive_socket(MW1->cpu_receive_socket);
	}
};



