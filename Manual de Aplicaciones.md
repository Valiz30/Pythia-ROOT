# Pythia-ROOT!

## Instalacion 
NOTAS:
- La distribución para la que se implementó el Script es Ubuntu 20, se puede modificar el Script fácilmente para otras distribuciones, la explicación se desglosara en el apartado con el nombre "Diferente distribución"
- Se recomienda colocar el Script en la carpeta donde el usuario instale sus aplicaciones, el Script creara dos carpetas, ROOT Y PYTHIA
- La versión de ROOT es la 6.26/2, se puedo modificar el Script para versiones posteriores o anteriores, la explicación se desglosara en el apartado con el nombre "Cambio de versiones"
- La versión de PYTHIA es la 8.307, se puedo modificar el Script para versiones posteriores o anteriores, la explicación se desglosara en el apartado con el nombre "Cambio de versiones"
- Si usted ya cuenta con otras versiones, asegúrese de separarlas correctamente, con el fin de evitar problemas.
- En el caso de ROOT, se necesitara que ejecute cierto comando cada que necesite usarlo, el comando se desglosara en el apartado con el nombre "Iniciar ROOT"

El proceso de instalación de ambos paquetes, tanto ROOT como Pythia, debe de seguir la siguiente serie de pasos (ambos paquetes se instalan con el mismo Script):

1. Descargue el archivo que se encuentra en este repositorio con el nombre de InstalarRP.sh en la carpeta donde desee instalar ambos paquetes (Después de la instalación puede remover el archivo).
2. Ejecute la terminal de Linux como Super-Usuario y abra la carpeta donde almaceno el archivo Instalar.sh.
3. Se ejecuta el archivo Instalar.sh. A continuación, se mostrara un ejemplo:
`root@valiz:/home/valiz/Software# ./InstalarRP.sh`
4. Pedirá permisos de almacenamiento, después de acceder solo queda esperar a que termine la ejecución y tendrá ambos paquetes instalados.

### Diferente Distribución / Diferente Versión

Tanto como para una distribución diferente como para una versión de ROOT, se deberá de acceder al siguiente enlace: https://root.cern/install/all_releases/
1. Selecciona una versión y según sea la distribución que usted posea, solo tendrá que copiar el enlace que proporciona la página y colocarlo en la siguiente línea:

En lugar del siguiente texto: root_v6.26.02.Linux-ubuntu20-x86_64-gcc9.4.tar.gz

![imagen](https://user-images.githubusercontent.com/83610345/175755570-c552500c-0b2d-4c73-b753-75def3985bc7.png)

NOTA: También se debe de reemplazar en la siguiente línea:

![imagen](https://user-images.githubusercontent.com/83610345/175755687-f8f79288-7596-43d5-99db-3a633e2235c9.png)

En el caso de Pythia se hace el mismo proceso de forma análoga, reemplazando donde se descarga el paquete y se descomprime.

<h4 align="center">»»-------------¤-------------««</h4>

## Iniciar ROOT

Cada vez que necesite iniciar ROOT, primero tendrá que ejecutar la siguiente línea: `# source root/bin/thisroot.sh`

NOTA: Después de ejecutar la terminal tiene que localizarse en la carpeta con el nombre ROOT, que es la carpeta que crea el Script y es donde se guarda el archivo de instalación y la carpeta usada para root.
Dentro de la carpeta ROOT ejecute el comando anterior, o puede ejecutarlo usando la ruta absoluta del archivo de la siguiente manera: `# source rutaAbsoluta/thisroot.sh`

Después de esto con tan solo escribir `# root` en la terminal, se inicia.

Para **evitar** tener que ejecutar las líneas anteriores, a excepción de `# root`, cada que se ejecuta una nueva terminal, se recomienda añadir la línea **source rutaAbsoluta/thisroot.sh** al archivo **.bashrc**. Puedes acceder de la siguiente forma: 
`# nano ~/.bashrc` y añadirlo al final del archivo.

<h4 align="center">»»-------------¤-------------««</h4>

## Compilar y Ejecutar un archivo de Pythia en ROOT
Para poder ejecutar un archivo de Pythia dentro de ROOT, se debe de compilar el mismo mandando a llamar las librerías de ROOT desde la linea de comandos, un ejemplo sería de la siguiente forma: 
`g++ -I/rutaInstalacionPythia/pythia8307/include (acento invertido)root-config --cflags(acento invertido) nombreArchivo.cc -o nombreArchivo -lpythia8 -L/rutaInstalacionPythia/pythia8307/lib (acento invertido)root-config --glibs(acento invertido)` 

Nota: se deben añadir una librería a las variables del sistema con el siguiente comando para la compilación y ejecución del archivo y el uso de Pythia:  `export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/rutaInstalacionPythia/pythia8307/lib` 

Para **evitar** tener que ejecutar la línea anterior cada que se inicia el sistema operativo, se puede añadir la misma línea al final del archivo .bashrc. Puedes acceder de la siguiente forma:  `# nano ~/.bashrc`  

Uno de los casos para ejecutar un archivo de Pythia con ROOT, es obtener un Archivo.root de la ejecución del archivo en Pythia después de la compilación y esto se hace haciendo uso de las librerías de ROOT con las siguientes líneas dentro de nuestro código: 

`#include "TFile.h"` Es el archivo de cabecera para la creación del archivo

`TFile *output = new TFile("Archivo.root", "recreate");` Sera el apuntador que generara nuestro archivo de salida

`output->Write();` Escribe en el archivo

`output->Close();` Se cierra el archivo

Para la ejecución del archivo en ROOT, se usa el siguiente comando: 

`$ root Archivo.root`

<h4 align="center">»»-------------¤-------------««</h4>

## Compilar y ejecutar las aplicaciones del Repositorio

### Nota: 
Antes de compilar una aplicación, se necesita enlazar un diccionario de ROOT con los archivos que se trabajaran. Esto para el caso en el que se requiera que la aplicación funcione de manera independiente a la terminal de ROOT. 

- Solo se ejecutará la siguente línea: `rootcling -f Dict.cxx -c principal.h LinkDef.h`
  **principal.h** es la librería que contendrá las clases usadas en nuestra aplicación, además de las variables globales. 
  **LinkDef.cxx** es el archivo que conectará el diccionario de ROOT con nuestra aplicación, se debe especificar la clase a la que estará ligado. 
  **Dict.cxx** es el archivo que se creará y que contendrá el enlace de ROOT con nuestra aplicación. 
- En el caso de las aplicaciones cargadas en el repositorio, ya no es necesario que se ejecute la línea, puesto que ya existe la conexión. 

Para ejecutar la aplicación, es necesario tener los archivos antes mencionados en el mismo lugar que el archivo con el código principal para que se pueda ejecutar correctamente. 

### Compilando usando un archivo Makefile: 
- Para cada aplicación se creó un archivo Makefile que se encuentra en su carpeta asignada. 
- Para compilar se introduce la siguiente línea `make nombreAplicacion` 

#### Nota:
Los archivos Makefile cargados en el repositorio necesitan ser modificados. Se debe especificar la dirección donde se encuentran los archivos necesarios mencionados en el apartado **Compilar y Ejecutar un archivo de Pythia en ROOT** 


### Ejecutar la aplicación 
Para ejecutar la aplicación solo es necesario la siguiente línea: `./nombreAplicacion` 

<h4 align="center">»»-------------¤-------------««</h4>

