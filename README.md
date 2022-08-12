# IZP 1. Project
## Overview
C program aimed at working with txt files.

Program filters txt file containing passwords and decides if the passwords comply with set requirements. Passwords that met the requirements are printed to ```stdout```.

## Building the project
Project is compiled using
```gcc -std=c99 -Wall -Wextra -Werror pwcheck.c -o pwcheck```

## Running syntax
```./pwcheck LEVEL PARAM [--stats] ```

```LEVEL``` Number (1-4) representing the level of password security

```PARAM``` Number specifying subrules

```--stats``` If entered, statistics are printed to ```stdout```
