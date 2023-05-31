#include <intrinsics.h>

#pragma svc_number=1
__svc void __svc_1 (unsigned int *);
#pragma svc_number=2
__svc void __svc_2 (unsigned int *);
#pragma svc_number=3
__svc void __svc_3 (unsigned int *);

void __the_actual_svc_1 (unsigned int cp)
{
  __disable_interrupt();
  (*(unsigned int *)cp) += 10;
  __enable_interrupt();
}

void __the_actual_svc_2 (unsigned int cp)
{
  __disable_interrupt();
  (*(unsigned int *)cp) -= 5;
  __enable_interrupt();
}

void __the_actual_svc_3 (unsigned int cp)
{
  __disable_interrupt();
  (*(unsigned int *)cp) -= 1;
  __enable_interrupt();
}

void SVC_Handler_C(unsigned int *svc_args)
{
  unsigned int svc_number;
 /*
  * Stack contains:
  * r0, r1, r2, r3, r12, r14, the return address and xPSR
  * First argument (r0) is svc_args[0]
  */
  svc_number = ( ( char * )svc_args[ 6 ] )[ -2 ] ;
  switch( svc_number )
  {
  case 0:
    while(1); // Generally used by RTOSes for Context-switching
    break;
  case 1:
    __the_actual_svc_1(svc_args[0]);
    break;
  case 2:
    __the_actual_svc_2(svc_args[0]);
    break;
  case 3:
    __the_actual_svc_3(svc_args[0]);
    break;
  default:
    break;
  }
}

unsigned int counter, c = 0;

__noreturn int main()
{
  __enable_interrupt();
  while (1)
  {
    counter++;
    if (counter % 100 == 0)
    {
      __svc_1(&c);
    }
    if (counter % 1000 == 0)
    {
      __svc_2(&c);
    }
    if (counter % 10000 == 0)
    {
      __svc_3(&c);
    }
  }
}
