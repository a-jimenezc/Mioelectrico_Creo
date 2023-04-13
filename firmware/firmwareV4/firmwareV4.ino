/*promediar sensor myo y el threshold, libreria movingAvg
    docuentación: https://www.arduino.cc/reference/en/libraries/movingavg/ 
 *Para mas información sobre el codigo del sensor myo ir a 
 *  https://wiki.dfrobot.com/Analog_EMG_Sensor_by_OYMotion_SKU_SEN0240 */

#include <movingAvg.h> 
#include "Arduino.h"
#include "EMGFilters.h"

#define SensorEmgInputPin A7 // input pin number
#define LSwitch 2 //switch input pin


EMGFilters myFilter; //filtro del mioeléctrico
// our emg filter only support "SAMPLE_FREQ_500HZ" or "SAMPLE_FREQ_1000HZ"
// other sampleRate inputs will bypass all the EMG_FILTER
enum SAMPLE_FREQUENCY sampleRate = SAMPLE_FREQ_500HZ;
enum NOTCH_FREQUENCY humFreq = NOTCH_FREQ_50HZ;

int sample_interval = 500; //microseconds. sample_interval debe coincidir con la frequencia de muestreo del filtro

int velHorario = 255;
int velAntihorario = 255;

int paridad = 0;
int start = 1;
unsigned long Threshold = 0;

//variables para el treshold dinámico
int inercia_senal = 30; //inercia señal original ----------------
int inercia_trsh =  10; //inercia del threshold ------------

int trsh_60 = 80; //threshold fijo para valores debajo de 60

int prim_int = 800; //limite del primer intervalo 
double funParametro_1 = 1.3; //modifica la altura del threshold para valores < 800 --------

int seg_int = 2000; //limite del segundo intervalo 
double funParametro_2 =1.2; //modifica la altura del threshold para valores <2000 ---------
 
//inicializar moving average
movingAvg movAvg_myo(inercia_senal);
movingAvg aux_trh(inercia_trsh);

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


void motorAntihorario(int velAntihorario){
  digitalWrite(9, LOW); 
  analogWrite(10, velAntihorario);
  }

void motorHorario(int velHorario){
  digitalWrite(10, LOW);
  analogWrite(9, velHorario);
}

void motorApagar(){
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
}


float fmap(float x, float in_min, float in_max, float out_min, float out_max)
{   return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;}

void setup() {
  
  Serial.begin(115200);
  
  myFilter.init(sampleRate, humFreq, true, true, true);
  movAvg_myo.begin();
  aux_trh.begin(); 

  pinMode(9,OUTPUT);  //motor 1 pwmD9 
  pinMode(10,OUTPUT);  //motor 1 pwmD10 
  pinMode(LSwitch, INPUT); //Final de carrera

}

void loop() {

    if(start){ //configuración inicial
      delayFiltering(500);
      start = 0;
    }
      
    // proceso de filtrado
    int Value= analogRead(SensorEmgInputPin);
    int DataAfterFilter = myFilter.update(Value);
    unsigned  long envlope = sq(DataAfterFilter);
    unsigned  long mov_avg = movAvg_myo.reading(envlope);

    if(Threshold < 60){Threshold = aux_trh.reading(trsh_60);} //treshold dinámico
    else if(Threshold < prim_int ){Threshold = aux_trh.reading(mov_avg*(1+(funParametro_1-pow(Threshold,1/30))));}
    else if(Threshold < seg_int ){Threshold = aux_trh.reading(mov_avg*(1+(funParametro_2-pow(Threshold,1/30))));} 
    else{Threshold = aux_trh.reading(mov_avg*(1+(1.2-pow(Threshold,1/30))));}
    delayMicroseconds(sample_interval); 

    Serial.print("absuared Data: ");
    Serial.println(mov_avg);
    Serial.print("threshold: ");
    Serial.println(Threshold);

    if(mov_avg > 10000){return;} //eliminar picos
    if(mov_avg < Threshold){ return;} //el motor no es accionado         
      
 //motor es accionado

    paridad++;
    if(paridad == 2){
        paridad = 0;      
    }

    if (paridad) { //cerrar por un tiempo fijo
        motorHorario(velHorario);
        delayFiltering(450); //filtrar mientras el motor funciona
    } 
      
    else{ //abrir hasta final de carrera
      while(digitalRead(LSwitch) == LOW){
          motorAntihorario(velAntihorario);
          delayFiltering(2);//mayor que 2
      }
      while(digitalRead(LSwitch) == HIGH){
          motorHorario(velHorario);
          delayFiltering(2);//mayor que 2
      }
    }       
    motorApagar(); 
    delayFiltering(300);        
}
