# so_long

## Overview
so_long is a 2D tile-based game built with the MLX42 graphics library as part of the 42 curriculum. The player navigates a map to collect all collectibles and reach the exit, while the program enforces strict map validation and clean resource management.

## Build
```bash
make
```
## Clean
```bash
make clean
make fclean
make re
```
## Run
```bash
make 
./so_long valid_map/subject_map.ber
```
## Map Rules
Maps are `.ber` files and must follow these rules:
- Rectangular and surrounded by walls (`1`).
- Exactly one player (`P`) and one exit (`E`).
- At least one collectible (`C`).
- All collectibles and the exit must be reachable from the player start.

Sample maps live in:
- `valid_map/`
- `invalid_map/`

## Key Files
- `includes/so_long.h` — core structs and function prototypes
- `src/validate_map.c` — map validation pipeline
- `src/validate_map_helpers.c` — reachability DFS helpers
- `src/initialize.c` — MLX42 and texture setup
- `src/render.c` — tile rendering
- `src/game_logic.c` — movement and win condition
  
## Notes
- Uses MLX42;
