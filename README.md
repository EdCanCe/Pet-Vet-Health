# Pet-Vet-Health
 
Pet Vet Health es un proyecto realizado en la clase TC1030. Trata sobre un sistema gestor para las consultas de una veterinaria, en donde se pueden añadir consultas y guardar su información, para, posteriormente buscarla en caso de ser necesario.

## Correcciones realizadas

 - $\color{red} \text{Identifico los casos que harían que el proyecto deje de funcionar:}$

    Antes no se contaba con un apartado donde se mostraban dichos casos, después de analizarlo, se encontraron casos concretos de este proyecto los cuáles podrían hacer que deje de funcionar. Dichos casos se encuentran en [este apartado](#aspectos-que-pueden-afectar-que-deje-de-funcionar).

 - $\color{red} \text{Genero un diagrama de clases UML correcto y y explico su relación con el problema de forma clara}$

    Al generar el diagrama UML por primera vez hubo un pequeño error al hacer la clase `MedicalCheck` ya que no se metieron las clases `Owner` y `Vet` como punteros.

    Sin embargo, con el paso de las entregas, se terminó modificando la estructura general de las clases.

    Al final se cuentan con 2 diagramas UML, el [primero(que tiene errores)]("UML.jpg"), y el [nuevo](#diagrama-uml)

## Funcionamiento
Si lo único que se quiere hacer es probar el funcionamiento de clases se recomienda compilar y correr `test.cpp` ya que no ocupa input por parte del usuario. 

Si se quiere ver el funcionamiento real del programa compilar y correr `main.cpp`, ya que es el verdadero programa. Se incluyeron unos pequeños datos dentro de éste para que de igual forma pueda ser probado.

## Diagrama UML
**No se ha actualizado debido al constante cambio en clases**

La composición de las clases se puede ver en el siguiente diagrama:

![](UML.jpeg)

## Aspectos que pueden afectar que deje de funcionar

Al programa se le implementó un sistema en el cual recibe strings de entrada, y luego éstas son convertidas a enteros en caso de ser necesario, por lo mismo, las entradas del usuario no harían que el programa deje de funcionar.

Sin embargo, si al archivo `database.txt` se ve corrompido podría hacer que el programa no funcione, ya que al iniciar la ejecución del programa éste mismo trata de abrir dicho archivo para obtener los datos que se le han ido ingresando conforme el paso del tiempo.

## Como correr el programa

En la terminal ubicarse en el directorio de la carpeta.

Se compila igual tanto para linux como para windows, con `g++ main.cpp`.

Para correr en linux `./a.out`.

Para correr en windows cmd `a.exe`.

Para correr en windows bash `./a.exe`.
