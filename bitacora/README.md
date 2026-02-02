/******************************** 
*Fecha: 2 de febrero 2026       *
*Autor: Santiago Camargo        *
*Tema: Taller 0/ Bitacora       *
*Estructuras de datos           *
********************************/

# Taller 0 — Bitácora Andoriana

**Asignatura:** Estructuras de Datos  
**Lenguaje:** C++11  
**Entorno:** Linux (Ubuntu)  
**Modalidad:** CLI (sin menús, todo por parámetros)

---

## Compilación

### Opción 1 - Compilación en un solo paso (recomendada):
```bash
g++ -std=c++11 -Wall -Wextra -pedantic -o bitacora main.cpp bitacora.cpp
```

### Opción 2 - Compilación por pasos:
```bash
g++ -std=c++11 -Wall -Wextra -pedantic -c main.cpp bitacora.cpp
g++ -std=c++11 -o bitacora main.o bitacora.o
```

### Compilación con símbolos de depuración (para gdb):
```bash
g++ -std=c++11 -g -Wall -Wextra -pedantic -o bitacora main.cpp bitacora.cpp
```

---

## Uso

### Ver ayuda
```bash
./bitacora help
```

### Comandos disponibles

#### 1. **init** - Inicializar base de datos
```bash
./bitacora init bitacora.bd
```

**Salidas esperadas:**
- Si no existe: `BD creada: bitacora.bd (N=0)`
- Si ya existe: `BD ya existe: bitacora.bd (no se modificó)`

---

#### 2. **add** - Agregar registro
```bash
./bitacora add bitacora.bd --nombre "Ana" --emocion feliz --felicidad 80 --energia 75 --sueno 8 --aguacate S
```

**Parámetros:**
- `--nombre`: Nombre del registro (máx 200 caracteres)
- `--emocion`: feliz | triste | neutral | ansioso
- `--felicidad`: 0..100
- `--energia`: 0..100
- `--sueno`: 0..24 (horas)
- `--aguacate`: S | N

**Salida esperada:**
```
Registro agregado. Total registros: 1
```

**Errores posibles:**
- `ERROR: BD no existe o está corrupta. Usa: ./bitacora init bitacora.bd`
- `ERROR: emocion inválida (usa: feliz/triste/neutral/ansioso)`
- `ERROR: felicidad fuera de rango (0..100)`
- `ERROR: energia fuera de rango (0..100)`
- `ERROR: horas_sueno fuera de rango (0..24)`
- `ERROR: aguacate inválido (usa: S o N)`

---

#### 3. **list** - Listar todos los registros
```bash
./bitacora list bitacora.bd
```

**Salida esperada (con datos):**
```
Bitácora Andoriana — 2 registro(s)
[0] Ana | feliz | F=80 E=75 | sueño=8 | aguacate=S
[1] Luis | triste | F=40 E=55 | sueño=6 | aguacate=N
```

**Salida esperada (BD vacía):**
```
BD vacía
```

---

#### 4. **find** - Buscar registro por nombre
```bash
./bitacora find bitacora.bd --nombre "Ana"
```

**Salida esperada (encontrado):**
```
Encontrado:
[0] Ana | feliz | F=80 E=75 | sueño=8 | aguacate=S
```

**Salida esperada (no encontrado):**
```
No encontrado
```

---

#### 5. **stats** - Estadísticas de nivel andoriano
```bash
./bitacora stats bitacora.bd --k 7
```

**Salida esperada:**
```
Stats Andorianas
Registros disponibles: 5
K solicitado: 7 (se usarán 5)
Promedio nivel andoriano (últimos 5): 73.28
```

**Fórmula del nivel andoriano:**
- `base = (felicidad + energia) / 2`
- Si `horas_sueno >= 7`: `base += 10`
- Si `horas_sueno < 7`: `base -= 10`
- Recortar al rango [0..100]

---

## Plan de Pruebas

### Pruebas del comando `init`

1. **Crear BD nueva:**
   ```bash
   ./bitacora init test.bd
   ```
   Resultado esperado: `BD creada: test.bd (N=0)`

2. **BD ya existe:**
   ```bash
   ./bitacora init test.bd
   ```
   Resultado esperado: `BD ya existe: test.bd (no se modificó)`

3. **Ruta inválida:**
   ```bash
   ./bitacora init /ruta/invalida/test.bd
   ```
   Resultado esperado: `ERROR: no se pudo crear la BD`

---

### Pruebas del comando `add`

1. **Agregar registro válido:**
   ```bash
   ./bitacora add test.bd --nombre "Juan" --emocion feliz --felicidad 90 --energia 85 --sueno 8 --aguacate S
   ```
   Resultado esperado: `Registro agregado. Total registros: 1`

2. **Emoción inválida:**
   ```bash
   ./bitacora add test.bd --nombre "Maria" --emocion contento --felicidad 80 --energia 70 --sueno 7 --aguacate N
   ```
   Resultado esperado: `ERROR: emocion inválida (usa: feliz/triste/neutral/ansioso)`

3. **Energía fuera de rango:**
   ```bash
   ./bitacora add test.bd --nombre "Pedro" --emocion neutral --felicidad 80 --energia 150 --sueno 7 --aguacate N
   ```
   Resultado esperado: `ERROR: energia fuera de rango (0..100)`

4. **Parámetros incompletos:**
   ```bash
   ./bitacora add test.bd --nombre "Ana" --emocion feliz
   ```
   Resultado esperado: `ERROR: faltan parámetros obligatorios`

---

### Pruebas del comando `list`

1. **BD vacía:**
   ```bash
   ./bitacora init vacia.bd
   ./bitacora list vacia.bd
   ```
   Resultado esperado: `BD vacía`

2. **BD con datos:**
   ```bash
   ./bitacora list test.bd
   ```
   Resultado esperado: Lista formateada con todos los registros

3. **BD no existe:**
   ```bash
   ./bitacora list noexiste.bd
   ```
   Resultado esperado: `ERROR: BD no existe o está corrupta`

---

### Pruebas del comando `find`

1. **Registro existe:**
   ```bash
   ./bitacora find test.bd --nombre "Juan"
   ```
   Resultado esperado: Muestra el registro de Juan

2. **Registro no existe:**
   ```bash
   ./bitacora find test.bd --nombre "NoExiste"
   ```
   Resultado esperado: `No encontrado`

3. **Nombres repetidos (retorna el primero):**
   ```bash
   ./bitacora add test.bd --nombre "Repetido" --emocion feliz --felicidad 80 --energia 70 --sueno 8 --aguacate S
   ./bitacora add test.bd --nombre "Repetido" --emocion triste --felicidad 40 --energia 50 --sueno 5 --aguacate N
   ./bitacora find test.bd --nombre "Repetido"
   ```
   Resultado esperado: Muestra el primer registro con ese nombre

---

### Pruebas del comando `stats`

1. **BD vacía:**
   ```bash
   ./bitacora init vacia.bd
   ./bitacora stats vacia.bd --k 5
   ```
   Resultado esperado: `BD vacía`

2. **n < k (menos registros que k solicitado):**
   ```bash
   ./bitacora stats test.bd --k 100
   ```
   Resultado esperado: Usa todos los registros disponibles

3. **n >= k (suficientes registros):**
   ```bash
   ./bitacora stats test.bd --k 3
   ```
   Resultado esperado: Promedio de los últimos 3 registros

4. **k inválido:**
   ```bash
   ./bitacora stats test.bd --k 0
   ./bitacora stats test.bd --k -5
   ```
   Resultado esperado: `ERROR: k debe ser >0`

---

## Depuración con GDB

### Compilar con símbolos de depuración:
```bash
g++ -std=c++11 -g -Wall -Wextra -pedantic -o bitacora main.cpp bitacora.cpp
```

### Usar GDB:
```bash
gdb ./bitacora
```

### Comandos básicos de GDB:
```gdb
(gdb) run add test.bd --nombre "Test" --emocion feliz --felicidad 80 --energia 70 --sueno 8 --aguacate S
(gdb) backtrace
(gdb) break agregarRegistro
(gdb) run add test.bd --nombre "Test" --emocion feliz --felicidad 80 --energia 70 --sueno 8 --aguacate S
(gdb) print n
(gdb) next
(gdb) step
(gdb) continue
(gdb) quit
```

---

## Ejemplo de Sesión Completa

```bash
# 1. Compilar
g++ -std=c++11 -Wall -Wextra -pedantic -o bitacora main.cpp bitacora.cpp

# 2. Inicializar BD
./bitacora init mi_bitacora.bd

# 3. Agregar registros
./bitacora add mi_bitacora.bd --nombre "Ana" --emocion feliz --felicidad 80 --energia 75 --sueno 8 --aguacate S
./bitacora add mi_bitacora.bd --nombre "Luis" --emocion triste --felicidad 40 --energia 55 --sueno 6 --aguacate N
./bitacora add mi_bitacora.bd --nombre "Maria" --emocion neutral --felicidad 70 --energia 80 --sueno 7 --aguacate S

# 4. Listar todos
./bitacora list mi_bitacora.bd

# 5. Buscar uno específico
./bitacora find mi_bitacora.bd --nombre "Ana"

# 6. Ver estadísticas
./bitacora stats mi_bitacora.bd --k 3
```

---

## Errores Encontrados y Corregidos

### Error 1: Comando `add` no implementado
**Problema:** El archivo `main.cpp` original solo tenía los comandos `init` y `list`. El comando `add` no estaba implementado, por eso la BD siempre aparecía vacía.

**Solución:** Implementé completamente el comando `add` con:
- Parseo de todos los parámetros (`--nombre`, `--emocion`, etc.)
- Validación de cada parámetro
- Conversión de strings a valores numéricos
- Llamada a `agregarRegistro()`
- Guardado de la BD

**Evidencia de depuración:**
```bash
(gdb) break main
(gdb) run add test.bd --nombre "Test" --emocion feliz --felicidad 80 --energia 70 --sueno 8 --aguacate S
(gdb) print comando
# Mostraba que comando era "add" pero no había código para procesarlo
```

---

### Error 2: Comandos `find` y `stats` no implementados
**Problema:** Estos comandos tampoco estaban en el código original.

**Solución:** Implementé ambos comandos siguiendo las especificaciones del taller.

**Función afectada:** `main()` líneas 103-186

---

### Error 3: Validación de parámetros incompleta
**Problema:** No había verificación de que todos los parámetros obligatorios estuvieran presentes.

**Solución:** Agregué inicialización con valores inválidos (255) y validación al final del parseo.

**Código agregado:**
```cpp
if (nuevo.nombre.empty() || nuevo.emocion == 255 || nuevo.felicidad == 255 ||
    nuevo.energia == 255 || nuevo.horas_sueno == 255 || nuevo.aguacate == 255) {
    cout << "ERROR: faltan parámetros obligatorios\n";
    return 1;
}
```

---

## Formato de la Base de Datos Binaria

La BD usa el siguiente formato binario:

```
[uint32_t N]                    // Cantidad de registros (4 bytes)
Para cada registro:
  [uint16_t len]                // Longitud del nombre (2 bytes)
  [len bytes]                   // Nombre (sin \0)
  [uint8_t emocion]             // 0=feliz, 1=triste, 2=neutral, 3=ansioso
  [uint8_t felicidad]           // 0..100
  [uint8_t energia]             // 0..100
  [uint8_t horas_sueno]         // 0..24
  [uint8_t aguacate]            // 0=N, 1=S
```

---

## Notas Importantes

1. **Memoria dinámica:** Se usa `new[]` y `delete[]` para manejo de arreglos dinámicos.
2. **No usar STL:** No se usan contenedores como `vector`, `list`, etc.
3. **Archivo binario:** Siempre abrir con `ios::binary`.
4. **Validación:** Todos los campos se validan antes de guardar.
5. **Manejo de errores:** Se verifica cada operación de I/O.

---

## Limpieza de archivos

Para limpiar archivos compilados:
```bash
rm -f bitacora *.o *.bd
```

---

**Fin del README**
