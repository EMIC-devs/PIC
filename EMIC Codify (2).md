# EMIC CODIFY

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

Espero que estas mejoras te sean útiles. ¡Déjame saber si necesitas algo más!