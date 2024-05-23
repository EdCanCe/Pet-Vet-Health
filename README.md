# Pet-Vet-Health

---

**Elementos corregidos**

Se añadió la sección de elementos que pueden hacer que el programa deje de funcionar

---
 
Pet Vet Health es un proyecto realizado en la clase TC1030. Trata sobre un sistema gestor para las consultas de una veterinaria, en donde se pueden añadir consultas y guardar su información, para, posteriormente buscarla en caso de ser necesario.

## Diagrama UML
*No se ha actualizado*
La composición de las clases se puede ver en el siguiente diagrama:

![](UML.jpeg)

## Aspectos que pueden afectar que deje de funcionar
Primeramente está en la entrada de las variables. Por el momento no se tiene, pero se piensa implementar un verificador de variables, ya que, si se introduce un string donde pide entero puede crashear el programa.

Otro aspecto que puede orillar a que deje de funcionar son las direcciones de memoria. Haciendo pruebas ví que funcionaba bien si se tenía un animal y un dueño, sin embargo, el añadir otro animal puede hacer que se eliminen otras entradas o que crashee el programa.

## Como correr el programa

En la terminal ubicarse en el directorio de la carpeta.

Se compila igual tanto para linux como para windows, con `g++ main.cpp`.
Para correr en linux ``./a.out`.
Para correr en windows cmd `a.exe.
Para correr en windows bash `./a.exe`.