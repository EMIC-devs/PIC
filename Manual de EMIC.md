# EMIC 
- [1. Una iniciativa para compartir experiencias y mejorar la productividad de programadores de sistemas embebidos.](#1-una-iniciativa-para-compartir-experiencias-y-mejorar-la-productividad-de-programadores-de-sistemas-embebidos)
  - [1.1. ¿Que es EMIC?](#11-que-es-emic)
  - [1.2. La evolución de EMIC:](#12-la-evolución-de-emic)
  - [1.3. Estado actual de EMIC.](#13-estado-actual-de-emic)
  - [1.4. El futuro de EMIC:](#14-el-futuro-de-emic)
  - [1.5. ¿Quienes pueden pertenecer a la comunidad EMIC?](#15-quienes-pueden-pertenecer-a-la-comunidad-emic)
  - [1.6. ¿Cómo se usa EMIC?](#16-cómo-se-usa-emic)
- [2. Generación de Aplicaciones y documentos.](#2-generación-de-aplicaciones-y-documentos)
- [3. Modulos.](#3-modulos)
- [EMIC CODIFY](#emic-codify)
  - [Introducción](#introducción)
  - [EMIC Codify](#emic-codify-1)
  - [Comandos EMIC Codify](#comandos-emic-codify)
  - [setInput](#setinput)
    - [Sintaxis:](#sintaxis)
    - [Definiciones:](#definiciones)
  - [setOutput](#setoutput)
    - [Sintaxis:](#sintaxis-1)
    - [Definiciones:](#definiciones-1)
  - [restoreOutput](#restoreoutput)
    - [Sintaxis:](#sintaxis-2)
  - [copy](#copy)
    - [Sintaxis:](#sintaxis-3)
    - [Definiciones:](#definiciones-2)
  - [define](#define)
    - [Sintaxis:](#sintaxis-4)
    - [Definiciones:](#definiciones-3)
  - [unDefine](#undefine)
    - [Sintaxis:](#sintaxis-5)
    - [Definiciones:](#definiciones-4)
  - [.{group.key}.](#groupkey)
  - [EMIC:foreach(**group**)    .{Item}.     EMIC:endfor](#emicforeachgroup----item-----emicendfor)
    - [Sintaxis:](#sintaxis-6)
  - [if](#if)
    - [Sintaxis:](#sintaxis-7)
    - [Definiciones:](#definiciones-5)
  - [elif](#elif)
    - [Sintaxis:](#sintaxis-8)
    - [Definiciones:](#definiciones-6)
  - [ifdef](#ifdef)
    - [Sintaxis:](#sintaxis-9)
    - [Definiciones:](#definiciones-7)
  - [ifndef](#ifndef)
    - [Sintaxis:](#sintaxis-10)
    - [Definiciones:](#definiciones-8)
  - [else](#else)
    - [Sintaxis:](#sintaxis-11)
    - [Definiciones:](#definiciones-9)
  - [endif](#endif)
    - [Sintaxis:](#sintaxis-12)
    - [Definiciones:](#definiciones-10)
- [4. Bibliotecas.](#4-bibliotecas)
- [Organizacion de los repositorios](#organizacion-de-los-repositorios)
  - [5. Organización de archivos y carpetas en **SOURCE Documents:**.](#5-organización-de-archivos-y-carpetas-en-source-documents)
  - [5.1. \_api.](#51-_api)
  - [5.2. \_drivers, \_hard, \_hal \_util, \_pcb, \_OS, \_main, \_interprete, \_templates.](#52-_drivers-_hard-_hal-_util-_pcb-_os-_main-_interprete-_templates)
  - [5.3. \_modulos.](#53-_modulos)
  - [5.4. Funcionamiento.](#54-funcionamiento)

<div style="page-break-after: always;"></div>

## 1. Una iniciativa para compartir experiencias y mejorar la productividad de programadores de sistemas embebidos.

### 1.1. ¿Que es EMIC?

EMIC significa Electrónica Modular Inteligente Colaborativa. Está compuesto por: un conjunto de funciones y drivers, un editor de script simple e intuitivo que junto con un sistema de integración, puede crear código listo para compilar o ejecutar.

En un principio EMIC fué creado para crear programas en lenguaje C, pero en el último tiempo se puso a prueba en desarrollo de paginas web (HTML, CSS y JS). Con muy buenos resultados.

Además, EMIC es agnóstico respecto a la arquitectura, familia de microcontroladores y compiladores. Y se busca que las funciones y drivers aportados por los usuarios también lo sean.

### 1.2. La evolución de EMIC: 

Todo comenzó cuándo un grupo de programadores intercambiaba código con el fin de mejorar la productividad y calidad de sus desarrollos.

Vieron que la eficiencia podría mejorar si todo el código desarrollado, cumplía con cierta normalización y buenas prácticas, y comenzaron a redactar las reglas para que las funciones puedan reutilizarse de forma automática, incluso sin la necesidad de comprender a fondo el funcionamiento del código desarrollado por otros programadores.

Con el correr del tiempo la cantidad de código generado fue creciendo y hubo que organizarlos en carpetas. Pudiendo separar, de esta manera, las funciones que utilizan recursos de bajo nivel y las que pertenecen a distintas capas de abstracción, la [lógica de negocio ](#1 "conjunto de algoritmos que realizan el trabajo que el usuario desea ejecutar")  y la descripción del hard.  

Más tarde se crea una aplicación de consola que siguiendo paso a paso un archivo de comandos automatiza la creación de código. Esto marcó un cambio fundamental, principalmente, porque cuando el código generado está basado en funciones que ya fueron probadas, casi siempre funciona a la primera. Dependiendo solamente de la lógica de negocio. Los tiempos de desarrollo se redujeron de meses a días 

Las reglas originales evolucionaron con el paso del tiempo, se agregaron: etiquetado de bibliotecas,drivers con funciones no bloqueantes, máquinas de estado y bibliotecas genéricas. EL sistema completo se convirtió de esta manera en un [*sistema operativo multi-tarea cooperativo*](https://es.wikipedia.org/wiki/Multitarea_cooperativa "ver en wikipedia")

Se creó un entorno de desarrollo en la nube, que incluye un editor, un generador de código y compilador, esta nueva herramienta permite generar la lógica de negocio de forma intuitiva y rápida, evitando errores de sintaxis. En esta etapa la plataforma permitió utilizar hardware y firmware existente para crear equipos electrónicos en pocos minutos.

Posteriormente se diseñó un protocolo para comunicar microcontroladores, esto permite modularizar los desarrollos, de forma que cada parte de un dispositivo electrónico puede recombinarse. Este sistema modular permite crear nuevos dispositivos en pocos minutos combinando módulos de hardware existentes. EMIC está pensado para que el desarrollador de sistemas embebidos viva una experiencia única. Logrando productos robustos y confiables en tiempo record.

### 1.3. Estado actual de EMIC.

El proyecto EMIC es dinámico, semana tras semana se crean nuevas funciones, drivers completos y nuevo hardware, es por eso que las posibilidades de aplicaciones crecen.

Hoy EMIC cuenta con 50 módulos de hardware desarrollados por distintos miembros de la comunidad. Entre los que se encuentran los módulos de conectividad (WiFi, Bluetooth, LoRa WAN, radios con modulación FSK y LoRa, RS485, RS232); Módulos de display (siete segmentos y gráficos); sensores (temperatura, humedad, corriente, tensión, celdas de cargas, gases, etc); actuadores (relés, motores paso a paso, triacs, salidas PWM, etc ); entradas y salidas digitales y analógicas; entre otros.

Respecto al firmware, podemos nombrar: comunicación SPI, I2C, Uart; Timers, salidas PWM, contadores, interrupciones, conversores AD, protocolos: MQTT, HTTP, JSON parser; controladores para ESP8266, sensores DHT22, DHT11, ADS1231, motores PXP, seven segment; MQ14 

### 1.4. El futuro de EMIC:

El sistema sigue evolucionando, estamos incorporando nuevas funciones, experimentando con procesamiento de datos con inteligencia artificial, y despliegue de dockers para servicios web. Además estamos desarrollando un asistente para el desarrollo de hardware.
Para acelerar el crecimiento convocamos a todos los interesados a participar de esta gran experiencia de desarrollo colaborativo. La invitación va dirigida tanto a personas que tienen un camino recorrido en el mundo de los embebidos, desarrollo web y modelos de IA, como a quienes están dando sus primeros pasos, las contribuciones esperadas pueden ser: simples comentarios, validación de código, aporte de ideas, desarrollo de funciones y drivers, diseño de hardware, desarrollo de dockers para servidores backend, modelos de IA, etc.

Si bien, el aporte de más desarrolladores y usuarios que validen cada pieza de la plataforma es importante para la comunidad. No es necesario compartir todo el código creado, cada usuario puede trabajar en forma privada y luego decidir que quiere compartir con el resto. 

### 1.5. ¿Quienes pueden pertenecer a la comunidad EMIC?

No hay restricciones para pertenecer a la comunidad, el requisito mas importante el ser un apasionado por la electrónica, los sistemas embebidos, el desarrollo web, la IA o las otras tecnologías que impulsan la cuarta revolución industrial o "industria 4.0", también se valora el espíritu colaborativo.
Cada miembro puede disponer libremente del resultado logrado por el uso de la plataforma, pero es importante mantener informado a la comunidad sobre los resultados técnicos utilizando los canales oficiales.
No es obligatorio compartir todos los desarrollos con la comunidad, cada uno decide libremente qué y cuando compartir, pero es deseable que los miembros hagan aportes de forma regular.
Tipos de aportes que se esperan:

- Desarrollo circuitos de hardware (esquemáticos y PCB)
- Desarrollo de software (funciones, drivers, widgets basados en webComponents, APIS en dockers, modelos de IA, etc)
- Testeo y validación en campo.
- Publicaciones en redes y difusión.
- Propuestas de ideas para desarrollos colaborativos.
- Otros aportes valorados por la comunidad.


### 1.6. ¿Cómo se usa EMIC? 

Para utilizar la plataforma con todos sus beneficios debe ser miembro oficial de la comunidad, para ello tiene que enviar un correo a comunidad@emic.io solicitarlo formalmente.
Hay dos maneras de utilizar la plataforma EMIC:

1) **Modo Integración de soluciones 4.0:** 
   Pensado para aquellas personas que necesiten desarrollar una aplicación basada en hardware, firmware, modelos de IA, contenedores dockers o widgets web existentes con el objetivo de resolver un problema específico.
   Todos los miembros de la comunidad pueden usar la plataforma en este modo ingresando en [*editor.emic.io*](https://editor.emic.io), allí encontrará los recursos que fueron desarrollados por él y otros miembros.
   Si necesita utilizar algún módulo de hardware desarrollado por otro miembro, puede solicitarlo en forma directa o por medio de los canales oficiales. En ese caso, el precio del módulo es pactado entre el desarrollador y el integrador. También se puede utilizar el hardware que algunos desarrolladores deciden ceder a la comunidad y por lo tanto su valor es muy conveniente.
   
1) **Modo Desarrollo:**
   Quienes tienen conocimientos en algunas de las areas de que componen la plataforma, pueden participar como desarrollador.
   Los desarrolladores tiene acceso con derechos especiales a los repositorios de la comunidad, cada repositorio es organizado y mantenido por un grupo elegido por consenso. Ademas, cada desarrollador si lo desea puede trabajar de forma independiente en sus propios repositorios, donde puede experimentar o crear código que no desee compartir con la comunidad.
   

## 2. Generación de Aplicaciones y documentos.

En la etapa de integración, se crea el *script* mediante un proceso de edición utilizando la herramienta disponible en la web editor.emic.io. Es decir el sistema toma el documento creado en el proceso de edición del *script* y los transforma en código para un lenguaje de programación específico, como por ejemplo C, LaTex, Javascript  o HTML (Tutorial de edición de *script*).

Luego, el sistema utiliza el código generado y junto con las bibliotecas alojadas en los repositorios utilizados en el proyecto, crea los documentos listos para compilar (en caso de c o latex), o para publicar (en caso de python, JS, HTML, etc.).

Cuando el integrador comienza a editar el *script*, primero debe elegir que módulos integrarán la solucuion a diseñar, es por ello, que se le presentará una lista con todos los módulos disponibles, que pueden ser módulos de hardware, aplicaciones que corren en la nube, dashboard, modelos de Inteligencia artificial, etc. La lista de módulos esta en crecimiento y son el aporte de los desarrolladores expertos.

Una vez que fueron seleccionados los módulos, comienza la edición del *Script* de cada uno, para ello cuenta con un conjunto de recursos disponibles específico para tipo de módulo que se está editando. Estos recursos son llamados bibliotecas o drivers, y forman parte de la definición de cada módulo, tambien son aportados por los desarrolladores expertos, podemos decir que un módulo está definido por un conjuntos de driver. Cabe aclarar un driver puede estar incluido en mas de un módulo.

EL proceso de creación de drivers, bibliotecas y módulos que realiza un desarrollador experto es similar a la creación de aplicaciónes o documento de forma tradicional, donde se usa cualquier editor de texto. El desarrallodor crea los fragmentos de código que luego formará parte de la solución integrada, dentro de ese conjunto de bibliotecas estan las llamadas apis, que son las bibliotecas que se utilzan como conexión entre el *Script* y el código aportado por los desarrolladores.

La única deferencia entre una api y las otras bibliotecas es que algunos fragmentos de código de las apis tienen asociado metatexto, es decir una descripción para que un proceso del sistema EMIC, llamado Discovery reconozca el metatexto para presentar la entrada a la librería como un recurso disponible para ser usado en el *Script* por el integrador.

## 3. Modulos.

Los módulos EMIC son el elemento central del sistema, es para el desarrollador el objetivo final y para el integrador el comienzo. En decir que es la interface entre los dos mundos.
Existen distintos tipos de módulos, los que representan a un hardware específico y sus capacidades o funciones, los que definen a una interface visual en la nube, los que definen una aplicación para teléfonos móviles o tablets y PC, y los que definen un proceso alojado en un servidor como bases de datos; procesos backends; e instancias modelos de inteligencia artificial.
A si vez los módulos EMIC, estan compuestos por drivers, que son un grupo de funciones y características, podriamos decir que los módulos estan definidos por un conjunto de drivers, ademas de tener otros elementos que los describen.
A continuacion de muestra un ejemplo de la definición de un módulos de hardware con funciones de comunicación Bluetooth:

## EMIC CODIFY

### Introducción

EMIC es una plataforma para desarrollar todos los componentes necesarios para implementar una solución completa dentro del paradigma de Industria 4.0, incluyendo dispositivos electrónicos industriales, paneles de control web, HMI, funciones lambda para el despliegue de modelos de ML, etc. Está compuesta por módulos de software organizados en bibliotecas, una familia de módulos de hardware y un entorno de desarrollo de alto nivel.

El uso de la plataforma como herramienta de desarrollo permite acelerar los tiempos de salida al mercado y eliminar la deuda técnica inherente a todo proceso tecnológico, mejorando significativamente el método tradicional de desarrollo de producto de forma disruptiva.

El éxito de EMIC se explica en el modelo de trabajo colaborativo basado en un esquema modular, escalable, ordenado y autodescriptivo, que permite dividir las etapas necesarias para obtener soluciones complejas en tareas más simples que son llevadas a cabo por distintos actores en distintos momentos.

Por un lado, los desarrolladores crean bibliotecas con el código para manejar recursos de hardware, modelos de ML, widgets para paneles de control, filtros digitales, protocolos, servicios web, etc. Estas bibliotecas incluyen metatexto para su clasificación y descripción.

EMIC interpreta el metatexto que describe el contenido de las bibliotecas y lo presenta en una interfaz de usuario como íconos o etiquetas, permitiendo que el código sea accesible desde un entorno de programación de alto nivel para los integradores.

Cuando los integradores (o los mismos desarrolladores) deseen crear aplicaciones para una solución a un requerimiento específico, desde el editor EMIC podrán generar un script que contenga la lógica de funcionamiento de la solución. Ese script es utilizado por otro proceso del sistema, que accede al código creado por los desarrolladores y lo integra para obtener un resultado final, que puede ser un código ejecutable en el hardware específico, una aplicación web que corre en cualquier dispositivo, o un modelo de machine learning que puede ser ejecutado en un proceso en la nube.

Los archivos que contienen el código creado por los desarrolladores estarán alojados en repositorios de GitHub y organizados respetando las especificaciones de EMIC, logrando que el sistema pueda reconocer e interpretar el contenido. Además del código con las funciones que integran cada biblioteca, se agregan comandos EMIC, que son instrucciones que el sistema ejecutará en el caso de ser invocado por el sistema, es decir, cuando forme parte de una solución final.

### EMIC Codify

Cuando el sistema EMIC fusiona el script desarrollado en la etapa de integración con las distintas bibliotecas que integran la solución, lo hace siguiendo las indicaciones proporcionadas por los desarrolladores.

Estas indicaciones se realizan utilizando comandos en un lenguaje de programación creado especialmente para el manejo de documentos de texto y código llamado EMIC Codify.

Utilizando EMIC Codify se establece la relación entre la definición de los módulos EMIC y sus dependencias, así como las dependencias de cada archivo dentro de una biblioteca. Además, este lenguaje de programación permite moldear cada biblioteca dentro de un proyecto específico, es decir, que los archivos pueden tomar distintas formas, adaptándose automáticamente a la necesidad de cada solución.

Cuando se compila el proyecto, una vez que está listo el script, el sistema comienza a generar la solución interpretando los comandos ubicados en un archivo llamado **generate.emic**. Estos comandos indican los pasos a seguir, incluyendo las rutas con las ubicaciones de todas las dependencias del proyecto. A medida que se invocan los archivos para formar parte de la solución, se ejecutan los comandos EMIC que se encuentran en esos archivos.

Los comandos con la forma **EMIC:xxxx(yyyy)** indican una acción que se ejecuta inmediatamente o evalúan una condición para determinar si el próximo bloque de código debe ser interpretado o ignorado.

El resto de las líneas de texto que no contienen comandos serán enviadas a un archivo de salida que formará parte de la solución final. Aunque, si dentro de este texto se encuentra una expresión de la forma **.{xxx.yyy}.**, será reemplazada por otro texto que fue definido previamente.

Para acceder a los distintos archivos contenidos, tanto en el repositorio, como en el proyecto que se está editando, se usa un sistema de rutas y volúmenes lógicos. De esta manera, para referirse a un archivo en particular no hace falta conocer su verdadera ubicación.
Los volúmenes lógicos son:

| Volumen   | Referencia                                                        |
|-----------|-------------------------------------------------------------------|
| `DEV:`    | Volumen donde se encuentran los archivos del repositorio.         |
| `TARGET:` | Volumen donde se van almacenando los archivos generados en el proceso de compilación. |
| `SYS:`    | Volumen donde se crean los archivos de configuración de cada aplicación. |
| `USER:`   | Volumen donde se ubican los archivos del usuario (integrador).    |

### Comandos EMIC Codify

> Nota: Los términos entre corchetes son opcionales y entre dobles corchetes se pueden repetir varias veces.

---

### setInput

Inicializa el procesamiento de un archivo. Cuando finaliza, se continuará procesando el archivo actual. Al ejecutar el comando, se pueden definir pares de clave-valor llamados ***macros*** que serán usados como texto variable durante el procesamiento.

#### Sintaxis:

```markdown
EMIC:setInput([origin:][dir/]file[[,key=value]])
```

#### Definiciones:

| Nombre   | Opcional | Descripción                                                                                         |
|----------|:--------:|-----------------------------------------------------------------------------------------------------|
| `origin` | Sí       | Volumen en el que se ubica el archivo. Si se omite, se usará el volumen actual.                     |
| `dir`    | Sí       | Ruta del archivo.                                                                                   |
| `file`   | No       | Nombre del archivo.                                                                                 |
| `key`    | Sí       | Nombre de cada parámetro que será utilizado en la interpretación del archivo.                       |
| `value`  | Sí       | Valor que tomará el parámetro que reemplaza a la clave en la interpretación del archivo.            |

---

### setOutput

Establece el archivo de salida. Todo el texto generado durante el procesamiento siguiente al comando será enviado al archivo indicado. Si el archivo no existe, se creará en el momento en que se intente escribir en él. Cada vez que se ejecuta este comando, la salida actual se almacena para ser restablecida posteriormente.

#### Sintaxis:

```markdown
EMIC:setOutput([target:][dir/]file)
```

#### Definiciones:

| Nombre   | Opcional | Descripción                                                                                        |
|----------|:--------:|----------------------------------------------------------------------------------------------------|
| `target` | Sí       | Volumen en el que se encuentra el archivo de salida. Si se omite, se usará el volumen de salida actual. |
| `dir`    | Sí       | Ruta del archivo. Si no existe, se crea. Si se omite, se usará la ruta de salida actual.                |
| `file`   | No       | Nombre del archivo. Si el archivo no existe, se crea.                                             |

---

### restoreOutput

Restablece el archivo de salida al destino anterior.

#### Sintaxis:

```markdown
EMIC:restoreOutput
```

---

### copy

Indica al sistema que se debe procesar un archivo y enviar el texto generado durante el procesamiento a un archivo de salida especificado. Si el archivo no existe, se creará en el momento en que se intente escribir en él. Al ejecutar el comando, se pueden definir mediante pares de clave-valor un conjunto de ***macros*** que serán usadas como texto variable durante el procesamiento.

#### Sintaxis:

```markdown
EMIC:copy([origin:][dir1/]file1,[target:][dir2/]file2[[,key=value]])
```

#### Definiciones:

| Nombre   | Opcional | Descripción                                                                                       |
|----------|:--------:|---------------------------------------------------------------------------------------------------|
| `origin` | Sí       | Volumen en el que se encuentra el archivo de entrada. Si se omite, se usará el volumen actual.    |
| `dir1`   | Sí       | Ruta del archivo de entrada. Si se omite, se usará la ruta del archivo procesado actualmente.     |
| `file1`  | No       | Nombre del archivo de entrada.                                                                    |
| `target` | Sí       | Volumen en el que se encuentra el archivo de salida. Si se omite, se usará el volumen de salida actual. |
| `dir2`   | Sí       | Ruta del archivo de salida. Si no existe, se crea. Si se omite, se usará la ruta de salida actual. |
| `file2`  | No       | Nombre del archivo de salida. Si el archivo no existe, se crea.                                   |
| `key`    | Sí       | Nombre de cada parámetro que será utilizado en la interpretación del archivo.                     |
| `value`  | Sí       | Valor que tomará el parámetro que reemplaza a la clave en la interpretación del archivo.          |

---

### define

Define una nueva ***macro*** formada por una clave y un valor, que será almacenada para su posterior utilización.

#### Sintaxis:

```markdown
EMIC:define([group.]key,value)
```

#### Definiciones:

| Nombre   | Opcional | Descripción                                                                        |
|----------|:--------:|------------------------------------------------------------------------------------|
| `group`  | Sí       | Nombre del grupo en que se define la macro. Si se omite, se usa el grupo por defecto ***global*** |
| `key`    | No       | Clave que identifica a la ***macro***.                                             |
| `value`  | No       | Texto que se guarda de la ***macro***.                                              |

---

### unDefine

Borra una ***macro***.

#### Sintaxis:

```markdown
EMIC:unDefine([group.]key)
```

#### Definiciones:

| Nombre   | Opcional | Descripción                                                                        |
|----------|:--------:|------------------------------------------------------------------------------------|
| `group`  | Sí       | Nombre del grupo en que se define la macro. Si se omite, se usa el grupo por defecto ***global*** |
| `key`    | No       | Clave que identifica a la ***macro***.                                             |

---

### .{group.key}.

Este comando se usa en las partes del texto que queremos que sean sustituidas por otro texto definido previamente.

Reemplaza .{[**group**.]**key**}. por el valor asignado con:

```markdown
EMIC:define([**group**.]**key**,**value**)
```

---

### EMIC:foreach(**group**)    .{Item}.     EMIC:endfor

#### Sintaxis:

```markdown
EMIC:foreach(group)
    .{Item}. 
EMIC:endfor
```

---

### if

#### Sintaxis:

```markdown
EMIC:if(condition)
```

#### Definiciones:

| Nombre   | Opcional | Descripción        |
|----------|:--------:|--------------------|
| `condition` | No | La condición a evaluar. |

---

### elif

#### Sintaxis:

```markdown
EMIC:elif(condition)
```

#### Definiciones:

| Nombre   | Opcional | Descripción        |
|----------|:--------:|--------------------|
| `condition` | No | La condición a evaluar. |

---

### ifdef

#### Sintaxis:

```markdown
EMIC:ifdef(macro)
```

#### Definiciones:

| Nombre   | Opcional | Descripción        |
|----------|:--------:|--------------------|
| `macro` | No | La macro a evaluar si está definida. |

---

### ifndef

#### Sintaxis:

```markdown
EMIC:ifndef(macro)
```

#### Definiciones:

| Nombre   | Opcional | Descripción        |
|----------|:--------:|--------------------|
| `macro` | No | La macro a evaluar si no está definida. |

---

### else

#### Sintaxis:

```markdown
EMIC:else
```

#### Definiciones:

---

### endif

#### Sintaxis:

```markdown
EMIC:endif
```

#### Definiciones:

---

```plaintext
/**<   */
/*RFI ModuloReferencia
//RFI TAG:driverName=
/*RFI
```


## 4. Bibliotecas.

LLamamos biblitotecas a todos los archivos que el sistema EMIC incluye en la generacion de un resultado por medio del comando  **#insertFile(dir/file.emic)**, es decir una biblitoca es procesada por el sistema EMIC, cuando es referencida por un módulo o por otra biblioteca.
 Las biblitecas tambien estan formadas por comandos [EMIC CODIFY](EMICCodify.md), aunque normalmente tienen además, fragmentos de téxto que no es interpretado por el sistema y simplemente es transcripto desde la biblioteca al documento generado como salida del sistema.

## Organizacion de los repositorios

### 5. Organización de archivos y carpetas en **SOURCE Documents:**.


EMIC </br>
  ├──  📁[_api](#_api) </br>
  ├──  📁[_drivers](_drivers) </br>
  ├──  📁[_hard](_hard) </br>
  ├──  📁[_hal](_hal) </br>
  ├──  📁[_interprete](_interprete) </br>
  ├──  📁[_modulos](_modulos) </br>
  ├──  📁[_OS](_OS)  </br>
  ├──  📁[_pcb](_placas)  </br>
  ├──  📁[_templates](_templates)  </br>
  ├──  📁[_util](_util)  </br>
  


### 5.1. _api.

En la carpeta [_api](_api) están contenidos las funciones que tienen conexión con la lógica de negocio, es decir, puede tener funciones o variables que pueden ser accedidas desde el *script*.

Los recursos almacenados (funciones y variables, en el caso de la creación de código) en _api, se describen en archivos de texto destinados a tal fin. 



### 5.2. _drivers, _hard, _hal _util, _pcb, _OS, _main, _interprete, _templates.

En estas carpetas hay código que si bien cumplen distintas funciones (en correspondencia con su nombre) no recibe ningún tratamiento especial por parte del sistema. Para que un archivo almacenado en esta carpeta forme parte de una aplicación, deberá ser invocada por un recurso de nivel superior.

### 5.3. _modulos.

En esta carpeta se almacena la descripción de los recursos de mayor nivel llamdos módulos. Que a su vez están compuestos por otros recursos definidos en la carpeta _api


### 5.4. Funcionamiento.

Como plataforma colaborativa, el propósito principal de EMIC es generar distintos tipos de documentos, como programas ejecutables por los módulos electrónicos, aplicaciones de teléfonos inteligentes o tablets y páginas webs.

Los ingredientes necesarios para generar estas aplicaciones y documentos se dividen en dos clases:

  1. El material creado por los usuarios expertos en distintas áreas del conocimiento. Dentro de esta categoría están incluidos archivos en distintos formato estándar. Por ejemplo:

      * Código C (*.c)
      * Header (*.h)
      * Web (*.html, *.css, *.js)
      * Latex (*.tex)
      * Markdown (*.md)

  Estos archivos van acompañados de metatexto y comandos que el sistema interpreta para saber como tratarlos.

  2. El *script* creado por cualquier usuario (incluyendo a los expertos). La herramienta utilizada para esta tarea es el [editor EMIC](https://editor.emic-io) edición del tipo *drag&drop*  dentro de un entorno intuitivo. Donde además de código se pueden editar páginas web de manera y pantallas gráficas de manera visual.
  
En otras palabras, en una aplicación EMIC se fusionan el conocimiento y la experiencia de desarrolladores e integradores y generan un resultado de alta calidad.


![Diagrama de Funcionamiento](img/DiagramaFucionamientoEMIC.png)

Vemos en el diagrama de funcionamiento, los distintos pasos para crear una aplicación web o un dispositivo electrónico.
El sistema esta formado por cuatro procesos que transforman distintos  documentos de entrada en otros de salidas (EMIC Discovery, EMIC Transcriptor, EMIC Marge, EMIC Compiler), tres almacenes de documentos (SOURCE Documents, Intermediate Documents, y FINAL Documents) y un editor de Script.

**EMIC Discovery:** este proceso es el encargado transformar los documentos alojado en *Source Documents* en información utilizada por el editor, es decir que genera una lista de recursos que luego pueden ser utilizados por quien edita el escript.

**EMIC Transcriptor:** este proceso parte del script editado por el usuario y genera un documento que contiene la misma información pero en un formato diferente.

**EMIC Merge:** partiendo del los documentos originales y del script transcripto, este proceso genera documentos que pertenecen a distinto formatos estándares como código C, latex, HTML, javascript, etc.

**EMIC Compiler:** en caso que los documentos generados por EMIC marge necesiten ser compilados, este proceso se encarga de ejecutar al compilador que corresponde dependiendo del tipo de documento generado.

**Intermediate Documents:** almacén donde residen los documentos generados por el transcriptor.

**TARGET Documents:** acá se almacena el primer resultado útil,

**SOURCE Documents:** es donde se almacenan los documentos creados por los desarrolladores del código fuente, este código va acompañado por información adicional, que describe el comportamiento dentro del sistema. Esta único lugar donde los usuarios ingresan documentos en forma directa y donde los desarrolladores compartimos código con el resto. Dada la importancia de esta carpeta se dedicará una sección para explicarla en detalle su estructura.







[#1]: conjunto de algoritmos que realizan el trabajo que el usuario desea ejecutar
