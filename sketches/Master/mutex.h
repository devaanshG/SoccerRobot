#ifndef MUTEX_H
#define MUTEX_H

template<class T>

///an implementation of Mutex, NOTE that this WILL NOT
///work with multiple cores waiting on the same Mutex
struct Mutex{
  public:
    volatile T object;
    Mutex(T obj){
      object = obj;
    }

    void GetLock(){
      // return; ///UNCOMMENT to SHORT mutex, this could
                ///cause corruption in data and false readings, 
                ///but thats better than the robot freezing.

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
    volatile bool locked;

    
};
#endif