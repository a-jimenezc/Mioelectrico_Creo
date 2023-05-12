# Proyecto Mioeléctrico

## Descripción
Este proyecto consiste en el desarrollo de una prótesis mioeléctrica para personas con extremidades superiores amputadas. La prótesis utiliza la señal mioeléctrica generada por un músculo para activar un motor que controla la mano de la prótesis. Además, se utiliza una impresora 3D para fabricar las piezas de la prótesis en PLA. 

## Requisitos
- Sensor de señal mioeléctrica DF-Robot
- Microcontrolador Arduino Nano
- Diferentes componenetes electrónicos (ver lista)
- Motor para la mano de la prótesis
- Impresora 3D y material PLA

## Funcionamiento
- El sensor captura la señal mioeléctrica del músculo y la envía al Arduino Nano.
- El Arduino Nano procesa la señal en tiempo real utilizando un algoritmo que incluye un filtro digital y una función de activación.
- La función de activación identifica la orden del usuario para activar la prótesis. La orden se envía mediante una contracción brusca del músculo.
- El motor se controla en lazo abierto, alternando el sentido de giro para abrir y cerrar la mano de la prótesis.
- El movimiento del motor se transmite a la mano de la prótesis mediante un eslabón triangular de transmisión.

## Próximos pasos
Actualmente, se está finalizando el desarrollo de esta segunda versión de la prótesis. Es necesario realizar pruebas en pacientes para evaluar el funcionamiento de la misma en condiciones reales. Adicionalmente, se requiere trabajar en la electrónica y el mecanismo de control de la prótesis. 

Revisar la carpeta documentación para más información.

## Autores
Antonio Jiménez Caballero

Otros autores....

## Licencia
Por definir.

## Contribuciones
Luis Villafani
Otros contribuyentes....

Se aceptan contribuciones al proyecto. Por favor, crea un "pull request" con tus propuestas.

## Contacto
Por definir.
