
# EMIC CODIFY.

### Introducción.

EMIC es una plataforma para desarrollar todos los componentes necesarios para implementar una solución completa dentro del paradigma industria 4.0, incluyendo, dispositivos electrónicos industriales, paneles de control WEB, HMI, funciones lambda para el despliegue de modelos de ML, etc. Está compuesta por módulos de software ordenados en bibliotecas, una familia de módulos de hardware, y un entorno de desarrollo de alto nivel.

El uso de la plataforma como herramienta de desarrollo, permite acelerar los tiempos de salida al mercado y eliminar la deuda técnica inherente a todo proceso tecnológico, mejorando significativamente el método tradicional de desarrollo de producto de forma disruptiva.

El éxito de EMIC se explica en el modelo de trabajo colaborativo basado en un esquema modular, escalable, ordenado y autodescriptivo, que permite dividir las etapas necesarias para obtener soluciones complejas en pequeñas tareas que son llevadas a cabo por distintos actores en distintos momentos. 

Por un lado desarrolladores crean bibliotecas de con el código para manejar recursos de hardware, modelos de ML, widgets para dashboard, filtros digitales, protocolos, servicios webs, etc. Estas bibliotecas incluyen metatexto para su clasificación y descripción.

EMIC interpreta el metatexto que describe el contenido de las bibliotecas y lo presenta en una interfaz de usuario como ícono o etiqueta. Permitiendo que el código sea accesible desde un entorno de programación a alto nivel para los integradores.

Al momento en que los integradores (o los mismos desarrolladores) deseen crear aplicaciones para una solución a requerimiento específico, desde el editor EMIC podrán generar un script que indique la lógica de funcionamiento de la solución. Ese script es utilizado por otro proceso del sistema, que accede al código creado por los Desarrolladores y lo integra para obtener un resultado final, que puede ser un código ejecutable en el hardware específico, una aplicación web que corre en cualquier dispositivo, o un modelo de machine learning que puede ser ejecutado en un proceso en la nube.

Los archivos que contienen el código creado por los desarrolladores deberán estar alojados en repositorios de GitHub y organizados de tal forma que el sistema EMIC pueda reconocer e interpretar el contenido, además del código con las funciones que integran cada librería se incluyen comandos EMIC, que son instrucciones que el sistema ejecutará en el caso que sea invocado por el sistema, es decir cuando forme parte de una solución final. 


### EMIC Codify.

Cuando el sistema EMIC fusiona el script desarrollado en la etapa de integración con las distintas librerías que integran la solución, lo hace siguiendo las indicaciones proporcionadas por los desarrolladores.

Estas indicaciones se hacen utilizando comandos en un lenguaje de programación creado especialmente para el manejo de documentos de texto y código llamado EMIC Codify.

Utilizando EMIC Codify se establece la relación entre la definición de los módulos EMIC y sus dependencias, así como las dependencias de cada archivo dentro de una biblioteca o driver. Además el lenguaje permite moldear a cada librería dentro de un proyecto específico, es decir que los archivos pueden tomar distintas formas, adaptándose automáticamente a la necesidad de cada solución.

Cuando se compila el proyecto, una vez que esta listo el script, el sistema comienza a generar la solución interpretando los comandos ubicados en un archivo llamado **generate.emic**. Estos comandos indican los pasos a seguir, incluyendo las rutas con las ubicaciones de todas las dependencias del proyecto. A medida que se invoca a los archivos para formar parte de la solución, se ejecutan los comandos EMIC que se encuentran en esos archivos.

Los comandos que con la forma EMIC:xxxx(yyyy) indican una acción que se ejecuta inmediatamente o evalúan una condición para determinar si el próximo bloque de código debe ser interpretado o ignorado.

El resto de la lineas de texto que no contienen comandos será enviadas a un archivo de salida que formará parte de la solución final. Aunque si dentro de este texto se encuentra una expresión de la forma .{xxx.yyy,zzz}. será reemplazado por otro texto que fué definido previamente.



### Comandos EMIC Codify:

```
EMIC:setInput([origin:][dir/]file[,key=value][, ......])
```

Indica al sistema que se debe incluir un nuevo archivo que será procesado inmediatamente. Luego el sistema continua ejecutando las lineas restantes del archivo que se estaba procesando.

##### Definiciones: 
`origin` (opcional) : volumen en el que se ubica el archivo.

`dir`    (opcional) : ruta del archivo.

`file`   : nombre del archivo.

`key` (opcional) : nombre de un parámetro que será utilizado en la interpretación del archivo.

`value` (opcional) : valor que reemplaza a la clave en la interpretación del archivo.




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