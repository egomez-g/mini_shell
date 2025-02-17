# Minishell

## Descripción
Minishell es un proyecto que consiste en la implementación de un shell simple similar a Bash. Su desarrollo permite comprender el funcionamiento de procesos, tuberías, redirecciones y la gestión de señales en un entorno UNIX.

## Requisitos
- Necesitamos tener make instalado para poder ejecutarlo.
- Lenguaje: C
- Librerías externas permitidas: `readline`, `printf`, `malloc`, `free`, `write`, `fork`, `execve`, `pipe`, `wait`, `signal`, entre otras.
- Se debe respetar la Norminette.
- No se permiten fugas de memoria.

## Características principales
- Muestra un prompt interactivo para recibir comandos.
- Implementa un historial de comandos.
- Ejecuta binarios basados en la variable de entorno `PATH` o mediante rutas absolutas/relativas.
- Manejo de comillas simples y dobles.
- Soporte para variables de entorno y el código de salida `$?`.
- Implementación de redirecciones (`<`, `>`, `>>`, `<<`).
- Soporte para pipes (`|`).
- Manejo de señales como `Ctrl+C`, `Ctrl+D`, `Ctrl+\`.
- Implementación de los siguientes builtins:
  - `echo` (con opción `-n`)
  - `cd` (con rutas absolutas y relativas)
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`

## Instalación
Clonar el repositorio y compilar el proyecto:
```bash
 git clone https://github.com/egomez-g/mini_shell.git
 cd minishell
 make
```

## Uso
Ejecutar el shell con:
```bash
./minishell
```
