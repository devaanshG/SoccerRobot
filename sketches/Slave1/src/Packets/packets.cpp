#include "packets.h"
#include "Wire.h"

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
    this->parity = (this->parity + 1) % 2;//toggle parity bit
    char* ret = (char*)this;
    return ret;
  }
}

void MasterToSlave1::Send(){
  Wire.beginTransmission(Slave1Address);
  Wire.write(this->Seal(), sizeof(MasterToSlave1));
  Wire.endTransmission();
}

void MasterToSlave1::Recieve(){
  char* buffer = new char[sizeof(MasterToSlave1)];
  size_t readBytes = Wire.readBytes(buffer, sizeof(MasterToSlave1));
  if(readBytes != sizeof(MasterToSlave1)){
    //throw "read bytes not equal to target bytes";, error handling adds 40kb to flash memory requirements, well over the 2kb uno flash size
  }else{
    *this = *reinterpret_cast<MasterToSlave1*>(buffer);
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
    this->parity = (this->parity + 1) % 2;//toggle parity bit
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
      //throw "read bytes not equal to target bytes";, for reason this is commented see other throw
    }else{
      *this = *reinterpret_cast<Slave2ToMaster*>(buffer);
    }
  }
}

void Slave2ToMaster::Respond(int count){
  Wire.write(this->Seal(), sizeof(MasterToSlave1));
}


