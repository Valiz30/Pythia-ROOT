# Pythia-ROOT!
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

# Diferente Distribución / Diferente Versión

Tanto como para una distribución diferente como para una versión de ROOT, se deberá de acceder al siguiente enlace: https://root.cern/install/all_releases/
1. Selecciona una versión y según sea la distribución que usted posea, solo tendrá que copiar el enlace que proporciona la página y colocarlo en la siguiente línea:

En lugar del siguiente texto: root_v6.26.02.Linux-ubuntu20-x86_64-gcc9.4.tar.gz

![imagen](https://user-images.githubusercontent.com/83610345/175755570-c552500c-0b2d-4c73-b753-75def3985bc7.png)

NOTA: También se debe de reemplazar en la siguiente línea:

![imagen](https://user-images.githubusercontent.com/83610345/175755687-f8f79288-7596-43d5-99db-3a633e2235c9.png)

En el caso de Pythia se hace el mismo proceso de forma análoga, reemplazando donde se descarga el paquete y se descomprime.

# Iniciar ROOT

Cada vez que necesite iniciar ROOT, primero tendrá que ejecutar la siguiente línea: `# source root/bin/thisroot.sh`

NOTA: Después de ejecutar la terminal tiene que localizarse en la carpeta con el nombre ROOT, que es la carpeta que crea el Script y es donde se guarda el archivo de instalación y la carpeta usada para root.
Dentro de la carpeta ROOT ejecute el comando anterior, o puede ejecutarlo usando la ruta absoluta del archivo de la siguiente manera: `# source rutaAbsoluta/thisroot.sh`

Después de esto con tan solo escribir `# root` en la terminal, se inicia.

