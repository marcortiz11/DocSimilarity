# DocSimilarity

Para generar los ejecutables introduzca en la terminal la directiva `make main`

```shell
$make all
```

## Contenido

El repositorio contiene funciones para calcular:

  - Similitud de Jaccard de dos documentos.

  - Aproximación del grado de similitud de Jaccard a traves de una representacion via
signatures minhash basadas en t funciones de hash.

  - Hallar documentos similares en una colleción usando Locality-Sensitive Hashing (LSH) basado en signatures minhash.

Hay un ejecutable para cada funcion: `mainJaccard`, `mainSignatures` y `mainLHS`. Cada uno de ellos pide los parametros que necesita para funcionar por la linea de comandos. Es importante tomar en cuenta que cada vez que se pida un path a un documento o una coleccion de documentos, la direccion relativa siempre empezará desde el directorio principal del repositorio.

Para usar colecciones de documentos personalizadas, se deben colocar en un directorio nuevo de forma enumerada, e.g `1.txt`, `2.txt`, etc.
