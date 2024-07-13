#include "memWriteRead.h"
#include "memoryUnit.h"

SC_MODULE(memWriteRead_TB){
	memWriterReader* MW1;
	memoryUnit* MU1;

	SC_CTOR(memWriteRead_TB){
		MU1 = new memoryUnit("memoryUnit");
		MW1 = new memWriterReader("memoryWriter");
		MW1->memWriterReaderSocket(MU1->memSideSocket);
		MU1->memSideSocket2(MW1->memWriterReaderSocket2);
	}
};



