#ifndef MUTEX_H
#define MUTEX_H

template<class T>

///an implementation of Mutex, NOTE that this WILL NOT
///work with multiple cores waiting on the same Mutex
typedef struct Mutex{
  
  public:
    T object;
    Mutex(T obj){
      object = obj;
    }

    void GetLock(){
      while(locked);//block until unlocked
      locked = true;//lock again
      return;
    }
    void ReleaseLock(){
      locked = false;
    }
    bool IsLocked(){
      return locked;
    }
  private:
    bool locked;

    
};
#endif