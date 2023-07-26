#include "packets.h"
#include "Wire.h"

const uint Slave1Address = 0x23;
const uint Slave2Address = 0x24;

bool GetParity(char* input){
  bool ret = false;
  for(int i = 0; i < sizeof(input); i++){
    if(GetParity(input[i])){
      ret = !ret;
    }
  }
  return ret;
}

bool GetParity(char input){
  char ret;
  for(; input > 0; input >> 1){
    ret ^= input;
  }
  return ret % 2 == 0;
}

bool MasterToSlave1::Verify(){
  char* test = (char*)this;
  return GetParity(test);
}

char* MasterToSlave1::Seal(){
  char* test = (char*)this;
  bool parity = GetParity(test);

  if(parity){
    return test;
  }else{
    this.parity = (this.parity + 1) % 2;//toggle parity bit
    char* ret = (char*)this;
    return ret;
  }
}

void MasterToSlave1::Send(){
  Wire.BeginTransmission(Slave1Address)
}

bool Slave2ToMaster::Verify(){
  char* test = (char*)this;
  return GetParity(test);
}

char* Slave2ToMaster::Seal(){
  char* test = (char*)this;
  bool parity = GetParity(test);

  if(parity){
    return test;
  }else{
    this.parity = (this.parity + 1) % 2;//toggle parity bit
    char* ret = (char*)this;
    return ret;
  }
}

