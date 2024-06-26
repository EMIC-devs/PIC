
# EMIC CODIFY.

### Introducción.

EMIC es una plataforma para desarrollar todos los componentes necesarios para implementar una solución completa dentro del paradigma industria 4.0, incluyendo, dispositivos electrónicos industriales, paneles de control WEB, HMI, funciones lambda para el despliegue de modelos de ML, etc. Está compuesta por módulos de software ordenados en bibliotecas, una familia de módulos de hardware, y un entorno de desarrollo de alto nivel.

El uso de la plataforma como herramienta de desarrollo, permite acelerar los tiempos de salida al mercado y eliminar la deuda técnica inherente a todo proceso tecnológico, mejorando significativamente el método tradicional de desarrollo de producto de forma disruptiva.

El éxito de EMIC se explica en el modelo de trabajo colaborativo basado en un esquema modular, escalable, ordenado y autodescriptivo, que permite dividir las etapas necesarias para obtener soluciones complejas en tareas más simples que son llevadas a cabo por distintos actores en distintos momentos. 

Por un lado desarrolladores crean bibliotecas de con el código para manejar recursos de hardware, modelos de ML, widgets para dashboard, filtros digitales, protocolos, servicios webs, etc. Estas bibliotecas incluyen metatexto para su clasificación y descripción.

EMIC interpreta el metatexto que describe el contenido de las bibliotecas y lo presenta en una interfaz de usuario como ícono o etiqueta. Permitiendo que el código sea accesible desde un entorno de programación a alto nivel para los integradores.

Al momento en que los integradores (o los mismos desarrolladores) deseen crear aplicaciones para una solución a requerimiento específico, desde el editor EMIC podrán generar un script que contenga la lógica de funcionamiento de la solución. Ese script es utilizado por otro proceso del sistema, que accede al código creado por los Desarrolladores y lo integra para obtener un resultado final, que puede ser un código ejecutable en el hardware específico, una aplicación web que corre en cualquier dispositivo, o un modelo de machine learning que puede ser ejecutado en un proceso en la nube.

Los archivos que contienen el código creado por los desarrolladores estarán alojados en repositorios de GitHub y organizados respetando las especificaciones de EMIC logrando que el sistema pueda reconocer e interpretar el contenido. Además del código con las funciones que integran cada librería se agregan comandos EMIC, que son instrucciones que el sistema ejecutará en el caso que sea invocado por el sistema, es decir cuando forme parte de una solución final. 


### EMIC Codify.

Cuando el sistema EMIC fusiona el script desarrollado en la etapa de integración con las distintas librerías que integran la solución, lo hace siguiendo las indicaciones proporcionadas por los desarrolladores.

Estas indicaciones se hacen utilizando comandos en un lenguaje de programación creado especialmente para el manejo de documentos de texto y código llamado EMIC Codify.

Utilizando EMIC Codify se establece la relación entre la definición de los módulos EMIC y sus dependencias, así como las dependencias de cada archivo dentro de una biblioteca. Además este lenguaje de programación permite moldear a cada librería dentro de un proyecto específico, es decir que los archivos pueden tomar distintas formas, adaptándose automáticamente a la necesidad de cada solución.

Cuando se compila el proyecto, una vez que esta listo el script, el sistema comienza a generar la solución interpretando los comandos ubicados en un archivo llamado **generate.emic**. Estos comandos indican los pasos a seguir, incluyendo las rutas con las ubicaciones de todas las dependencias del proyecto. A medida que se invoca a los archivos para formar parte de la solución, se ejecutan los comandos EMIC que se encuentran en esos archivos.

Los comandos que con la forma **EMIC:xxxx(yyyy)** indican una acción que se ejecuta inmediatamente o evalúan una condición para determinar si el próximo bloque de código debe ser interpretado o ignorado.

El resto de la lineas de texto que no contienen comandos será enviadas a un archivo de salida que formará parte de la solución final. Aunque si dentro de este texto se encuentra una expresión de la forma **.{xxx.yyy}.** será reemplazado por otro texto que fué definido previamente.

Para acceder a los distintos archivos contenidos, tanto en el repositorio, como en el proyecto que se está editando, se usa un sistema de rutas y volúmenes lógicos. De esta manera para referirse a un archivo en particular no hace falta conocer su verdadera ubicación.
Los volúmenes lógicos son:

| Volumen | Referencia.|
|---------|------------|
|`DEV:`   |Se encuentran los archivos del repositorio.|
|`TARGET:`|Se van almacenando los archivos generados en el proceso de compilación.|
|`SYS:`   |Se crean los archivos de configuración de cada aplicación.|
|`USER:`  |Archivos del usuario (integrador)|


### Comandos EMIC Codify:
---------------------------------------------
### setImput

Indica al sistema que se debe procesar un archivo. Luego el sistema continua ejecutando las lineas restantes del archivo que se estaba procesando.
Al ejecutar el comando para procesar un archivo, se pueden definir mediante pares de clave-valor un conjunto de ***macros*** que serán usada como texto variable durante el procesamiento.

#### Sintaxis:
```
EMIC:setInput([origin:][dir/]file[[,key=value]])
```


##### Definiciones: 
`origin` (opcional) : volumen en el que se ubica el archivo. Si se omite se usará el volumen actual.

`dir`    (opcional) : ruta del archivo.

`file`   : nombre del archivo.

`key` (opcional) : nombre de cada parámetro que será utilizado en la interpretación del archivo. 

`value` (opcional) : valor tomará el parametro que reemplaza a la clave en la interpretación del archivo.

--------------
### setOutput
Establece el archivo de salida. Todo el texto generado durante el procesamiento será enviado al archivo seleccionado, si el archivo no existe se creará en el momento que se intente escribir en él. Cada vez que se ejecuta este comando la salida actual se almacena para ser restablecida posteriormente. 

#### Sintaxis:
```
EMIC:setOutput([target:][dir/]file)
```

##### Definiciones: 
`target` (opcional) : volumen en el que se encuentra el archivo de salida. Si se omite se usará el volumen de salida actual.

`dir`    (opcional) : ruta del archivo. Si no existe, se crea. Si se omite, se usará la ruta de salida actual.

`file`   : nombre del archivo. Si el archivo no existe, lo crea

----------
### restoreOutput
Restablece es archivo de salida al destino anterior.

#### Sintaxis:
`EMIC:restoreOutput`

----------------------
#### copy

#### Sintaxis:
`EMIC:copy([origin:][dir1/]file1,[target:][dir2/]file2[[,key=value]])`

- `origin` (opcional) : volumen en el que se ubica el archivo. Si se omite se usará el volumen actual.

- `dir1`    (opcional) : ruta del archivo.

- `file1`   : nombre del archivo.

- `target` (opcional) : volumen en el que se encuentra el archivo de salida. Si se omite se usará el volumen de salida actual.

- `dir`    (opcional) : ruta del archivo. Si no existe, se crea. Si se omite, se usará la ruta de salida actual.

- `file`   : nombre del archivo. Si el archivo no existe, lo crea

- `key` (opcional) : nombre de cada parámetro que será utilizado en la interpretación del archivo. 

- `value` (opcional) : valor tomará el parámetro que reemplaza a la clave en la interpretación del archivo.


#### EMIC:if
#### EMIC:elif
#### EMIC:ifdef
#### EMIC:ifndef
#### EMIC:else
#### EMIC:endif
-----------------------------------
### define

Define una nueva ***macro*** formada por una clave y un valor, que sera almacenada para su posterior utilización.

#### Sintaxis:
`EMIC:define([group.]key,value)`

##### Definiciones: 
`group` (opcional) : Define el grupo en el que se almacena la ***macro***.

`key` : Clave para referenciar a la ***macro***.

`value` : Texto de la ***macro****

--------------------------------
### unDefine
Borra una ***macro***.

#### Sintaxis:

`EMIC:unDefine(key)`

#### Definiciones:
`key` : Clave para referenciar a la ***macro***.

--------------------------------------
#### .{**key**}.

Reemplaza .{[**group**.]**key**}. por el valor asignado con EMIC:define([**group**.]**key**,**value**).

### EMIC:foreach(**group**)    .{Item}.     EMIC:endfor







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