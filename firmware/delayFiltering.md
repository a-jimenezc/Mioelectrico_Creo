La función *delay_filtering* permite leer pulsos enviados por el músculo. Además, permite adaptar en tiempo real el threshold de activación del motor según las amplitud de la señal.


Matemáticamente, la función juega con el delay intrínseco del filtro *moving average* para ser sensible únicamente a los cambios bruscos en la señal. Esto permite que el motor pueda ser controlado con pulsos del músculo, a la vez que se evita el ruido.


''' 

void delayFiltering(int milliseconds){
  int milliseconds_2 = (1000/sample_interval)*milliseconds; //float to int
  for(int i=0; i < milliseconds_2; i++){//delay filtrando
       int Value= analogRead(SensorEmgInputPin);
       int DataAfterFilter = myFilter.update(Value);
       unsigned  long envlope = sq(DataAfterFilter);
       unsigned  long mov_avg = movAvg_myo.reading(envlope);

       if(Threshold < 60){Threshold = aux_trh.reading(trsh_60);} //treshold dinámico
       else if(Threshold < prim_int ){Threshold = aux_trh.reading(mov_avg*(1+(funParametro_1-pow(Threshold,1/30))));}
       else if(Threshold < seg_int ){Threshold = aux_trh.reading(mov_avg*(1+(funParametro_2-pow(Threshold,1/30))));} 
       else{Threshold = aux_trh.reading(mov_avg*(1+(1.2-pow(Threshold,1/30))));}

       Serial.print("absuared Data: ");
       Serial.println(mov_avg);
       Serial.print("threshold: ");
       Serial.println(Threshold);
       delayMicroseconds(sample_interval);//debe coincidir con SAMPLE_FREQ
  }   
}

'''


Descripción:

La función "delayFiltering" realiza el filtrado de las señales EMG y la actualización del umbral dinámico de manera retardada durante un tiempo especificado en milisegundos. A continuación se describen los pasos principales del proceso:

Conversión de milisegundos a muestras: Se calcula el número de muestras necesarias para el retardo, multiplicando el tiempo en milisegundos por la frecuencia de muestreo inversa en segundos (1000/sample_interval), donde "sample_interval" es el intervalo de muestreo de las señales EMG en microsegundos.

Bucle de filtrado: Se inicia un bucle que se ejecuta tantas veces como el número de muestras calculado en el paso anterior. Dentro del bucle, se realiza lo siguiente:
a. Lectura del valor del sensor EMG: Se lee el valor analógico del pin del sensor EMG utilizando la función "analogRead" y se almacena en la variable "Value".
b. Filtrado de la señal EMG: Se aplica el filtro de EMG previamente configurado utilizando la función "update" de la instancia "myFilter" y se obtiene el valor filtrado en la variable "DataAfterFilter".
c. Cálculo del valor del umbral dinámico: Se calcula el valor del umbral dinámico en función de los parámetros de control y el valor filtrado de la señal EMG. Dependiendo del valor actual del umbral, se utilizan diferentes ecuaciones para calcular el nuevo valor del umbral. Los cálculos se realizan utilizando las funciones "reading" de las instancias "aux_trh", "movAvg_myo" y las operaciones matemáticas como potenciación y raíz. El resultado se almacena en la variable "Threshold".
d. Impresión de valores: Se imprimen en el Monitor Serie los valores del valor absoluto del promedio móvil de la señal EMG (mov_avg) y el umbral dinámico calculado (Threshold) para fines de depuración.
e. Retardo: Se espera un tiempo equivalente al intervalo de muestreo (sample_interval) utilizando la función "delayMicroseconds".

Finalización del bucle: Una vez que se completan todas las iteraciones del bucle, la función "delayFiltering" finaliza.

Es importante tener en cuenta que el valor del umbral dinámico se actualiza en función de los parámetros de control y los valores filtrados de la señal EMG durante el retardo especificado, lo que permite adaptar el umbral a los cambios en la señal EMG en tiempo real.
