
# Taller 0 — Bitácora Andoriana

Asignatura: Estructuras de Datos
Lenguaje: C++11
Entorno: Linux (Ubuntu)
Modalidad: CLI (sin menús, todo por parámetros)

---

## Compilación

```bash
g++ -std=c++11 -Wall -Wextra -pedantic -o bitacora main.cpp bitacora.cpp
```

Para usar con gdb:
```bash
g++ -std=c++11 -g -o bitacora main.cpp bitacora.cpp
```

---

## Comandos Disponibles

### 1. Inicializar BD
```bash
./bitacora init bitacora.bd
```

### 2. Agregar registro
```bash
./bitacora add bitacora.bd --nombre "Ana" --emocion feliz --felicidad 80 --energia 75 --sueno 8 --aguacate S
```

Parámetros:
- `--nombre`: texto (máx 200 caracteres)
- `--emocion`: feliz | triste | neutral | ansioso
- `--felicidad`: 0-100
- `--energia`: 0-100
- `--sueno`: 0-24
- `--aguacate`: S | N

### 3. Listar registros
```bash
./bitacora list bitacora.bd
```

### 4. Buscar por nombre
```bash
./bitacora find bitacora.bd --nombre "Ana"
```

### 5. Estadísticas
```bash
./bitacora stats bitacora.bd --k 5
```

### 6. Ver ayuda
```bash
./bitacora help
```

---

## Ejemplos de Uso

```bash
# Crear la BD
./bitacora init bitacora.bd

# Agregar algunos registros
./bitacora add bitacora.bd --nombre "Santiago" --emocion feliz --felicidad 90 --energia 85 --sueno 8 --aguacate S
./bitacora add bitacora.bd --nombre "Chaustre" --emocion triste --felicidad 40 --energia 55 --sueno 6 --aguacate N

# Ver todos
./bitacora list bitacora.bd

# Buscar uno específico
./bitacora find bitacora.bd --nombre "Juan"

# Ver estadísticas
./bitacora stats bitacora.bd --k 2
```

---

## Pruebas Básicas

```bash
# Init
./bitacora init test.bd                    # Crea BD nueva
./bitacora init test.bd                    # Ya existe

# Add (válido e inválido)
./bitacora add test.bd --nombre "Pablo" --emocion feliz --felicidad 80 --energia 70 --sueno 7 --aguacate S
./bitacora add test.bd --nombre "Ana" --emocion contento --felicidad 80 --energia 70 --sueno 7 --aguacate N  # Error

# List, Find, Stats
./bitacora list test.bd
./bitacora find test.bd --nombre "Pablo"
./bitacora stats test.bd --k 3
```

---

## Depuración con gdb

```bash
g++ -std=c++11 -g -o bitacora main.cpp bitacora.cpp
gdb ./bitacora
(gdb) run add test.bd --nombre "Test" --emocion feliz --felicidad 80 --energia 70 --sueno 8 --aguacate S
(gdb) backtrace
(gdb) break agregarRegistro
(gdb) print n
(gdb) next
```

---

## Notas Técnicas

**Formato del archivo .bd (binario):**
- Header: uint32_t con cantidad de registros
- Por cada registro: longitud nombre + nombre + 5 bytes de datos

**Nivel Andoriano:**
- base = (felicidad + energia) / 2
- Si sueño >= 7: base + 10, sino: base - 10
- Limitar entre 0 y 100

**Validaciones:**
- Todos los campos son obligatorios
- Los rangos se validan antes de guardar
- Si hay error, no se modifica la BD

---

## Errores Corregidos

1. **Comando add no existía** - Por eso la BD siempre estaba vacía
2. **Comando find no existía** - Se implementó completo
3. **Comando stats no existía** - Se implementó completo
4. **Validación incompleta** - Ahora verifica todos los parámetros

Los archivos bitacora.h y bitacora.cpp estaban correctos.

---

## Limpiar archivos

```bash
rm -f bitacora *.o *.bd
```
