#include <stdio.h>
#include "suma.h"
typedef unsigned long long Bcd;

Bcd sumaBcd(Bcd x, Bcd y) {
   Bcd mask = 0xF;
   int resto = 0;
   Bcd resultado = 0;
  for(int i = 0; i< 16 ; i++){

    Bcd mask_i = (mask << (i<<2)) ;  // i<<2 equivale a i*4
    Bcd x_i =(x & mask_i) >> (i<<2) ; //4 últimos bits de x
    Bcd y_i =( y & mask_i ) >> (i<<2) ; //4 últimos bits de y
    Bcd sum = x_i + y_i + resto;

    if( sum >= 10 ){
      sum -= 10;  
      resto = 1;
    } else{
      resto = 0;
    }
    if( i==15 && resto == 1){
      return 0xffffffffffffffff ;
    }

    resultado += (sum << (i << 2));

    }
  return resultado;

}

