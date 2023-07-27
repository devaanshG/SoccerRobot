#include "packets.h"
#include "Wire.h"

const uint Slave1Address = 0x23;
const uint Slave2Address = 0x24;

void InitMaster(){
  Wire.begin();
  Wire.setClock(100'000);//100khz, using ' to make numbers look pretty is perfectly valid cpp
}
MasterToSlave1* InitSlave1(){
  Wire.begin(Slave1Address);
  MasterToSlave1 pak = new MasterToSlave1();
  Wire.onRecieve(pak.Recieve());
  return &pak;
}
Slave2ToMaster* InitSlave2();

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

void FlushReadBuffer(){
  while(Wire.available()){
    Wire.read();
  }
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
  Wire.beginTransmission(Slave1Address);
  Wire.write(this.Seal(), sizeof(MasterToSlave1));
  Wire.endTransmission();
}

void MasterToSlave1::Recieve(){
  char* buffer = new char[sizeof(MasterToSlave1)];
  size_t readBytes = Wire.readBytes(&buffer, sizeof(MasterToSlave1));
  if(readBytes != sizeof(MasterToSlave1)){
    throw "read bytes not equal to target bytes";
  }else{
    this = (MasterToSlave1)buffer;
  }
  
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

void Slave2ToMaster::Request(){
  FlushReadBuffer();
  Wire.requestFrom(Slave2Address, sizeof(Slave2ToMaster));

  if(sizeof(Slave2ToMaster) <= Wire.available()){
    char* buffer = new char[sizeof(Slave2ToMaster)];
    size_t readBytes = Wire.readBytes(buffer, sizeof(Slave2ToMaster));
    if(readBytes != sizeof(Slave2ToMaster)){
      throw "read bytes not equal to target bytes";
    }else{
      this = (MasterToSlave2)buffer;
    }
  }
}

void Slave2ToMaster::Respond(){
  Wire.write(this.Seal(), sizeof(MasterToSlave1));
}