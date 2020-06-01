// https://code.kx.com/q/interfaces/using-c-functions/
#include"k.h" // k.h in https://github.com/KxSystems/kdb/
#ifdef __cplusplus
extern "C"{
#endif

K add(K x,K y)
{
  if(x->t!=-KJ||y->t!=-KJ)
    return krr("type");
  return kj(x->j+y->j);
}

#ifdef __cplusplus
}
#endif
