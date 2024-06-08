# Pet-Vet-Health
 
Pet Vet Health es un proyecto realizado en la clase TC1030. Trata sobre un sistema gestor para las consultas de una veterinaria, en donde se pueden añadir consultas y servicios en general, para posteriormente guardar su información, y de esa forma, en un futuro buscarla en caso de ser necesario. De la misma manera, se pueden generar archivos `HTML` que se pueden convertir a PDF.

### Indice:

 - [Inicio](#pet-vet-health)
 - [Correciones realizadas](#correcciones-realizadas)
 - [Funcionamiento](#funcionamiento)
 - [Diagrama UML](#diagrama-uml)
 - [Casos en los que dejaría de funcionar](#aspectos-que-pueden-afectar-que-deje-de-funcionar)
 - [Como correr el programa](#como-correr-el-programa)
 - [Capturas del funcionamiento](#capturas-del-funcionamiento-del-programa)

## Correcciones realizadas

 - $\color{red} \text{Identifico los casos que harían que el proyecto deje de funcionar:}$

    Antes no se contaba con un apartado donde se mostraban dichos casos, después de analizarlo, se encontraron casos concretos de este proyecto los cuáles podrían hacer que deje de funcionar. Dichos casos se encuentran en [este apartado](#aspectos-que-pueden-afectar-que-deje-de-funcionar).

 - $\color{red} \text{Genero un diagrama de clases UML correcto y y explico su relación con el problema de forma clara:}$

    Al generar el diagrama UML por primera vez hubo un pequeño error al hacer la clase `MedicalCheck` ya que no se metieron las clases `Owner` y `Vet` como punteros.

    Sin embargo, con el paso de las entregas, se terminó modificando la estructura general de las clases.

    Al final se cuentan con 2 diagramas UML, el [primero(que tiene errores)]("https://github.com/EdCanCe/Pet-Vet-Health/blob/main/Extra/oldUML.jpeg"), y el [nuevo](#diagrama-uml).

 - $\color{red} \text{Herencia, Modificadores de acceso y Sobreescritura}$

   Al momento de la 2da entrega se entregó un programa el cuál no corrió. Para que corriese se ocupaba que estuviese el archivo `database.txt`, sin embargo, dentro del archivo `.gitignore` se englobaron a todos los archivos `.txt`, por esto mismo, dicho archivo no se subió, y, por ende, no se pudo compilar.

   Se eliminaron los archivos `.txt` del `.gitignore`, haciendo así que ya se pudisen subir y pudiese compilar.

   De la misma manera se recomendaron separar las clases (que en ese momento estaban todas dentro del `main.cpp`) para que cada una tuviera su `.h`, por lo que se separaron para que cada clase contara con su propio archivo. Sin embargo, las clases hijas se pusieron dentro del mismo archivo de la clase madre.


## Funcionamiento

Se hizo un programa de gestión de una veterinaria. El mismo permite crear perfiles para veterinarios y dueños, y, dentro del último, poderle añadir sus mascotas.

Con los perfiles hechos, se pueden realizar servicios a dichas mascotas, dentro de éstos está un chequeo médico, una cirugía, el servicio de un baño para la mascota o de un hotel, para que por un tiempo se quede en la veterinaria.

Al final, con los servicios hechos, se pueden imprimir de 2 maneras, una de éstas siendo una impresión simple en consola, mientras que si se busca imprimir dicho servicio como una orden en PDF, se genera un archivo `.html` que se abre automáticamente, dentro de ahí el archivo `.js` hará que se "imprima" el documento, los navegadores permiten guardar como PDF envés de imprimir, lo cual permitiría generar un PDF del mismo. Se decidió de hacer de esta manera para que no se tuvieran que implementar librerías externas y directamente se abra en el navegador del usuario.

Para la generación de PDF se recomienda desactivar la función de márgenes dentro de el apartado de imprimir en el navegador. También se recomienda activar el apartado de los gráficos de fondo. La escala se recomienda dejarla por defecto.

Si lo único que se quiere hacer es probar el funcionamiento de clases se recomienda compilar y correr `test.cpp` ya que no ocupa input por parte del usuario. 

Si se quiere ver el funcionamiento real del programa compilar y correr `main.cpp`, ya que es el verdadero programa. Se incluyeron unos pequeños datos dentro de éste para que de igual forma pueda ser probado.

La documentación en general está comentada en el código, pero también puede ver la documentación en [este archivo](https://github.com/EdCanCe/Pet-Vet-Health/blob/main/Extra/Documentation.md)

## Diagrama UML

![](Extra/UML.jpeg)

## Aspectos que pueden afectar que deje de funcionar

Al programa se le implementó un sistema en el cual recibe strings de entrada, y luego éstas son convertidas a enteros en caso de ser necesario, por lo mismo, las entradas del usuario no harían que el programa deje de funcionar.

Sin embargo, si al archivo `database.txt` se ve corrompido o no existe, podría hacer que el programa no funcione, ya que al iniciar la ejecución del programa éste mismo trata de abrir dicho archivo para obtener los datos que se le han ido ingresando conforme el paso del tiempo.

El programa utiliza vectores, por lo mismo, se ocuparía una versión de C++ que contenga dicha biblioteca. En caso de no tenerla podría ocasionar que el programa no compile.

Hay otro caso en donde no sería tal cual que deje de funcionar, sin embargo, podría hacer que el PDF generado se vea mal. Este caso se podría deber a que cuando el archivo `.js` manda a imprimir la página, el usuario tenga o no opciones marcadas en ese apartado. Como por ejemplo:

 - El ancho de página
 - Los márgenes
 - Imprimir los fondos

De la misma manera, el archivo `.css` utiliza una fuente de [Google fonts](https://fonts.google.com/), por lo que si no se cuenta con internet, sí se podrá imprimir, pero, no se vería como se tenía planeado.

## Como correr el programa

En la terminal ubicarse en el directorio de la carpeta.

Se compila igual tanto para linux como para windows, con: `g++ main.cpp`.

Para correr en linux: `./a.out`.

Para correr en windows con cmd: `a.exe`.

Para correr en windows con bash: `./a.exe`.


## Capturas del funcionamiento del programa