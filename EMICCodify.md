
# EMIC CODIFY.

### Introducción.

EMIC es una plataforma para desarrollar todos los componentes necesarios para implementar una solución completa dentro del paradigma industria 4.0, incluyendo, dispositivos electrónicos industriales, paneles de control WEB, HMI, funciones lambda para el despliegue de modelos de ML, etc. Está compuesta por módulos de software ordenados en bibliotecas, una familia de módulos de hardware, y un entorno de desarrollo de alto nivel.

El uso de la plataforma como herramienta de desarrollo, permite acelerar los tiempos de salida al mercado y eliminar la deuda técnica inherente a todo proceso tecnológico, mejorando significativamente el método tradicional de desarrollo de producto de una forma disruptiva.

El éxito de EMIC se explica en el modelo de trabajo colaborativo basado en un esquema modular, escalable, ordenado y autodescriptivo, que permite dividir las etapas necesarias para obtener soluciones complejas en pequeñas tareas que son llevadas a cabo por distintos actores en distintos momentos. 

Por un lado desarrolladores crean bibliotecas de con código para manejar recursos de hardware, modelos de ML, widgets para dashboard, filtros digitales, manejadores de protocolos, servicios webs, etc. Estas bibliotecas incluyen metatexto para su clasificación y autodescripción.

Los Integradores generan aplicaciones para dar solución a requerimientos específicos de sus clientes, generando un script que indica la lógica de funcionamiento de la solución. 

EMIC utiliza las etiquetas que desciben el contenido de las bibliotacas y lo presenta como recursos disponibles en una interfaz de usuario. Esto permite que el código esté accesible en alto nivel para los integradores.


El script resultante es dirigido a otro subproceso del sistema, que invoca al código creado por los Desarrolladores y lo integra para obtener un resultado final, que puede ser un código ejecutable en el hardware específico, una aplicación web que corre en cualquier dispositivo, o un modelo de machine learning que puede ser ejecutado en un proceso en la nube.


### EMIC Codify.

Cuando el sistema EMIC fuciona el script con las distintas librerías que integran la solución, lo hace siguiendo indicaciónes proporcinadas por los desarrolladores.

Estas indicaciones se hacen utilizando comandos en un lenguaje de programción desarrollado especialmente para el manejo de documentos de texto y código llamado EMIC Codify.

Utilizando EMIC Codify se establece la relación entre la definición de los módulos EMIC y sus dependencias, así como las dependencias de cada archivo dentro de una bibliteca o driver. Además el lenguaje permite moldear a cada librería dentro de un proyecto específico, es decir que los archivos pueden tomar distintas formas, adaptendose automáticamente a la necesidad de cada solución.

### Comados EMIC Codify:

#### #insertFile(**dir**/**file**[,param=value][, ......])

Procesa el archivo llamado **file** ubicado en el directorio **dir**, el orden de búsqueda es el siguiente:

Salida

target

/DEV

/USER


#### #newRFIcode(dir/file[,param=value][, ......])
##### #setFile dir/file
##### #reSetFile dir/file
##### #unSetFile
##### #define
##### #undef
##### #copy
##### ##include
##### #addToMacro
##### -{  }-
##### _{  }_
##### .{  }.
##### //No RFI scan   
##### #else
##### #ifdef
##### #ifndef
##### #elif
##### 
##### #if
##### #endif
##### 
##### #aplyUsingDriver



  
#addToList
#using
#useDriver
#include
doCMDejec
doCMDf
doCMD
doInit
doPoll
doStream
/**<   */
/*RFI ModuloReferencia
//RFI TAG:driverName=
/*RFI


-------------------------------------------------------------



### Comandos EMIC Codify:

#### EMIC:setInput([**origin**:][**dir**/]**file**[,**key**=**value**][, ......])

Procesa el archivo llamado **file** ubicado en el directorio **dir**, a ubicado en **origin**. Ademas se crea un diccionario temporal con un conjunto de claves y 

#### EMIC:setOutput([**target**:][**dir**/]**file**)

Redirige la salida al archivo llamado **file** ubicado en el directorio **dir**, a ubicado en **origin**.

#### EMIC:reSetOutput

Redirige la salida al destino anterior.

#### EMIC:define([**group**.]**key**,**value**)

Define una nueva entrada al diccionario con el nombre **key** y cuyo valor sera **value**, en el caso que la clave este precedida por el nombre de un grupo, asigna la entrada al grupo, si el grupo no existe lo crea.

#### EMIC:unDefine(**key**)

Borra la entrada con el nombre **key** del diccionario.

#### .{**key**}.

Reemplaza .{[**group**.]**key**}. por el valor asignado con EMIC:define([**group**.]**key**,**value**).

### EMIC:foreach(**group**)    .{Item}.     EMIC:endfor



#### EMIC:copy([**origin**:][**dir**/]**file**,[**target**:][**dir**/]**file**)

Copia el contenido del documento ubicado en [**origin**:][**dir**/]**file**, en [**target**:][**dir**/]**file**.



#### EMIC:if
#### EMIC:elif
#### EMIC:ifdef
#### EMIC:ifndef
#### EMIC:else
#### EMIC:endif




  
#addToList
#using
#useDriver
#include
doCMDejec
doCMDf
doCMD
doInit
doPoll
doStream
/**<   */
/*RFI ModuloReferencia
//RFI TAG:driverName=
/*RFI