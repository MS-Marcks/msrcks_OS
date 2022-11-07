# msrcks_OS

## **Requisitos**
- qemu
- gcc
- make
- gdb

## **Progreso**

- [x] Entorno de desarrollo
- [x] Arranque básico
- [x] Interfaz con limine
- [x] Funciones básicas de impresión
- [x] Memoria física
- [x] Asignador de marcos de página
- [x] Interrupciones (IDT)
- [x] MEMORIA VIRTUAL

## **sub modulos**
- ### OVMFbin
    - ejecutar el comando: 
    ```bash
    git submodule add https://github.com/Absurdponcho/OVMFbin os/OVMFbin
    ``` 
- ### limine
    - ejecutar el comando: 
    ```bash
    git submodule add https://github.com/limine-bootloader/limine os/limine
    ``` 
- ### printf
    - ejecutar el comando: 
    ```bash
    git submodule add https://github.com/mpaland/printf os/src/print/printf
    ``` 

## **como habilitar el entorno de desallorro**
1. Modificar GNUmakefile para que apunte a tu gdb, qemu, etc.
 ```make
20) QEMU := "[PATH]/qemu-system-x86_64"
21) GDB := "[PATH]/gdb"
``` 
2. ejecutar `make setup`
3. ejecutar `make all`

## **Visor de VNC**
1. acceder al siguiente enlace para instalar el visor VNC: **[Visor TigerVNC](https://tigervnc.org/)**