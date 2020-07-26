![alt image](Escudo-UdeC_300x233.png)

<p align="center" style="font-size:24pt; font-bold:true">Estructuras de Datos</p>
<p align="center" style="font-size:24pt; font-bold:true">Proyecto 2</p>
<p align="center" style="font-size:14pt; font-bold:true">Felipe Alejandro Cerda Saavedra</p>
<p align="center" style="font-size:14pt; font-bold:true">Matrícula: 2019060121</p>
<p align="center" style="font-size:14pt; font-bold:true">Victini Schultz Solano</p>
<p align="center" style="font-size:14pt; font-bold:true">Matrícula: 201600000</p>

<div style="page-break-after: always;"></div>

## Descripción de la tarea

En el presente informe examinaremos la técnica de compresión de datos **Re-Pair** mediante la implementación de dos soluciones que luego compararemos. Para ambos casos la información será representada como una lista enlazada.

La primera funciona directamente recorriendo la lista de datos y buscando el par mas frecuente para luego, en otra iteración, reemplazarlo por un nuevo símbolo inexistente en la secuencia. Este proceso se repite hasta que ya no quedan pares con frecuencia mayor a 1 y en todos los casos se recorre la secuencia de principio a fin. La segunda implementación extiende la funcionalidad de la lista y agrega punteros a las ocurrencias anteriores y posteriores para cada par. Además, utiliza la estructura de datos **MAX-heap** para saber cual es el par de mayor frecuencia y a medida que reemplaza dicho par en la secuencia original actualiza el **MAX-heap**. La segunda solución supone una mejora sustancial sobre la eficiciencia tiempo de la primera implementación. Por una lado, para cada reemplazo solo recorre la lista en aquellas posiciones en las que se debe reemplazar y por otro lado actualiza la información en MAX-heap al mismo tiempo. En la primera solución tanto la busqueda del par mas frecuente como su reemplazo en lista se realizan recorriendo la lista completa. Dicha ganancia en eficiencia se analizará primero desde el punto de vista teórico y sus resultados serán validados por una evaluación experimental.

## Descripción de la solución propuesta

### Solución 1

#### Diagrama de Clase Solucion 1

![alt image](./Solucion_1.png)

### Solución 2

#### Diagrama de Clase Solucion 2

![alt image](./Solucion_2.png)

## Detalles de la implementación

### Implementación Solución 1

#### Reseña Solución 1

#### Demostración de Ejecución Solución 1

Como se ha señalado previamente, la solución 1 resuelve el problema mediante la iteración de dos operaciones consecutivas:

1. Recorrer la lista para buscar el par de mayor frecuencia.
2. Si la frecuencia del par anterior es mayor a 1, recorrer la lista para reemplazarlo por un nuevo símbolo(no presente en la lista).

A continuación mostramos ejemplo de la ejecución de ambos pasos.

**Creación Lista Enlazada**

```cpp


```

**Buscar par mayor frecuencia:**

```cpp


```

**Reemplazar par mayor frecuencia**

```cpp


```

**Salida del programa**

```cpp

```

### Implementación Solución 1

#### Reseña Solución 1

#### Demostración de Ejecución Solución 1


**Creación Lista Enlazada**

```cpp


```

**Buscar par mayor frecuencia:**

```cpp


```

**Reemplazar par mayor frecuencia**

```cpp


```

**Salida del programa**

```cpp

```


detalles de implementación (debe incluir un ejemplo
completo con al menos 3 pasos donde se vea cómo se van actualizando los punteros y estructuras
de datos, para la versión avanzada).

## Evaluación experimental

## Anexos