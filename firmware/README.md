README: Control Mioeléctrico para Control de Motores utilizando Arduino

Este código de Arduino está diseñado para habilitar el control mioeléctrico de un motor utilizando un sensor EMG analógico. El código utiliza la biblioteca "movingAvg" para calcular promedios móviles y la biblioteca "EMGFilters" para filtrar las señales EMG. El código está destinado a ser utilizado con un sensor EMG analógico, como el sensor "Analog_EMG_Sensor_by_OYMotion_SKU_SEN0240".

Para usar este código, sigue los siguientes pasos:

Paso 1: Configuración del Hardware

Conecta el sensor EMG analógico a la placa de Arduino. El cable de señal del sensor debe conectarse al pin A7 de Arduino (o cambia el valor de "SensorEmgInputPin" al número de pin apropiado en el código).
Conecta el motor a los pines apropiados de Arduino para el control del motor. El motor se controla mediante señales PWM, así que asegúrate de conectarlo a los pines apropiados con capacidad de PWM (por ejemplo, D9 y D10).
Paso 2: Configuración del Software

Instala las bibliotecas "movingAvg" y "EMGFilters" en tu entorno de desarrollo de Arduino. Estas bibliotecas son necesarias para que el código funcione correctamente.
Copia y pega el código proporcionado en tu entorno de desarrollo de Arduino.
Paso 3: Configuración

Configura los parámetros en el código para adaptarlos a tus requisitos específicos. Por ejemplo, puedes ajustar la frecuencia de muestreo, la frecuencia de rechazo, el intervalo de muestreo, los parámetros de control del motor y los valores de umbral según tus necesidades.
Asegúrate de leer y entender la documentación de las bibliotecas "movingAvg" y "EMGFilters" para configurarlas y utilizarlas correctamente en tu código.
Paso 4: Carga y Ejecución

Carga el código en tu placa de Arduino.
Abre el Monitor Serie en tu entorno de desarrollo de Arduino para ver la salida del código.
Enciende tu motor y tu sensor EMG.
El código realizará el control mioeléctrico del motor basado en las señales EMG filtradas y los valores de umbral calculados durante la ejecución.
Nota: Es importante calibrar adecuadamente los valores de umbral para tu configuración específica para asegurar un control mioeléctrico confiable y preciso del motor. Experimenta con diferentes valores de umbral y parámetros de control del motor para lograr el rendimiento deseado.

Para obtener más información sobre el código, consulta los comentarios en el código y la documentación de las bibliotecas "movingAvg" y "EMGFilters". Además, consulta la documentación del sensor EMG analógico utilizado en tu configuración para obtener más detalles sobre su uso y calibración.

Descargo de responsabilidad: Este código se proporciona tal cual y puede requerir más modificaciones y pruebas para tu aplicación específica. Úsalo bajo tu propio riesgo y siempre sigue las precauciones de seguridad apropiadas al trabajar con motores y circuitos eléctricos.