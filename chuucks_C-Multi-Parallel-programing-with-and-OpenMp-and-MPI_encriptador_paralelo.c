#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
# include <stdio.h>
  # include <string.h>
  # include <stdlib.h>

  int main(){
          
     FILE *inicializador, *lectura, *encriptado; 
     char llave_hexadecimal[4], llave_binario[16], lectura_caracteres[2], lectura_binario[16];
     char nombre_archivo[13], bufer_inicializador[17], bufer_archivo[2];
     char digitos_binario[3] = "01";
     int i, j, k, n, indice, operando1, operando2, resultado;
     
     inicializador = fopen("inicializador.txt", "r"); 
     if(inicializador == NULL){
         printf("%S de inicializacion no encontrado, favor de validar", nombre_archivo);
     }else{
              
          if(fgets(bufer_inicializador, 30, (FILE*)inicializador) != 0){
                           sscanf(bufer_inicializador, "%s" "%s", nombre_archivo, llave_hexadecimal);
          }else{
                printf("No se pudo leer linea de archivo inicializador, favor de validar existencia de archivo.");
                exit(0);
          }
          
          //En este ciclo se asigna el valor ASCCI de un caracter correspondiente a la letra leida en HEXADECIMAL                    
																			dummyMethod1();
          #pragma omp parallel for private(i)
          for(i=0; i<4; i++){
            switch(llave_hexadecimal[i]){

              case '0':
                llave_hexadecimal[i] = 0;
                break;

              case '1':
                llave_hexadecimal[i] = 1;
                break;

              case '2':
                llave_hexadecimal[i] = 2;
                break;

              case '3':
                llave_hexadecimal[i] = 3;
                break;

              case '4':
                llave_hexadecimal[i] = 4;
                break;

              case '5':
                llave_hexadecimal[i] = 5;
                break;

              case '6':
                llave_hexadecimal[i] = 6;
                break;

              case '7':
                llave_hexadecimal[i] = 7;
                break;

              case '8':
                llave_hexadecimal[i] = 8;
                break;

              case '9':
                llave_hexadecimal[i] = 9;
                break;

              case 'a':
              case 'A':
                llave_hexadecimal[i] = 10;
                break;

              case 'b':
              case 'B':
                llave_hexadecimal[i] = 11;
                break;

              case 'c':
              case 'C':
                llave_hexadecimal[i] = 12;
                break;

              case 'd':
              case 'D':
                llave_hexadecimal[i] = 13;
                break;

              case 'e':
              case 'E':
                llave_hexadecimal[i] = 14;
                break;

              case 'f':
              case 'F':
                llave_hexadecimal[i] = 15;
                break;
            }          
          }
																			dummyMethod2();

          lectura = fopen(nombre_archivo, "r");
          if(lectura == 0){
            printf("No se pudo abrir el archivo a leer, revise permisos.");            
          }else{
        
            encriptado = fopen("chiper.txt", "w+");
            if(encriptado == NULL){
              printf("No se pudo crear el archivo a escribir, revise permisos.");              
            }else{
                        
              while(fgets(bufer_archivo, 2, (FILE*)lectura) != 0){
                
																															dummyMethod3();
                for(i=0; i<2; i++){
                  lectura_caracteres[i] = bufer_archivo[i];
                }
																															dummyMethod4();
                
                //Conversion de caracteres leidos a BINARIO             
																															dummyMethod1();
                #pragma omp parallel for private(k)
                for(k=8; k>0; k--){
                  indice = lectura_caracteres[0] % 2;
                  lectura_caracteres[0] = lectura_caracteres[0] / 2;
                  lectura_binario[k-1] = digitos_binario[indice];                  
                }                
																															dummyMethod2();
																															dummyMethod1();
                #pragma omp parallel for private(k)
                for(k=16; k>8; k--){
                  indice = lectura_caracteres[1] % 2;
                  lectura_caracteres[1] = lectura_caracteres[1] / 2;
                  lectura_binario[k-1] = digitos_binario[indice];               
                }
																															dummyMethod2();

                //Conversion de llave en HEXADECIMAL a BINARIO
																															dummyMethod1();
                #pragma omp parallel for private(i,j)
                for(j=4; j>0; j--){
                  for(k=4; k>0; k--){
                    indice = llave_hexadecimal[j] % 2;
                    llave_hexadecimal[j] = llave_hexadecimal[j] / 2;
                    llave_hexadecimal[(k*j)-1] = digitos_binario[indice];
                    }
                }
																															dummyMethod2();

                //Operacion XOR bit a bit de los 16 bits de las 2 letras leidas con los 16 bits de los 4 caracteres en HEXADECIMAL
                
																															dummyMethod1();
                #pragma omp parallel for private(n)
                for(n=0; n<16; n++){
                  operando1 = lectura_binario[n];
                  operando2 = llave_binario[n];
                  resultado = operando1 ^ operando2;
                  fprintf(encriptado, "%c", resultado);
                }
																															dummyMethod2();
                
                fprintf(encriptado, "\n");
              }
                             
              printf("Se realizo el encriptado del archivo exitosamente!");
              
              fclose(inicializador);
              fclose(lectura);
              fclose(encriptado);
            }
                    
        }
    }
}
int dummyMethod1(){
    return 0;
}
int dummyMethod2(){
    return 0;
}
int dummyMethod3(){
    return 0;
}
int dummyMethod4(){
    return 0;
}