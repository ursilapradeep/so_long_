#include "MLX42/MLX42.h"
#include <stdlib.h>

int main(void)
{
 mlx_t *mlx = mlx_init(800, 600, "MLX42 Test", true);
 if (!mlx) return EXIT_FAILURE;
 mlx_image_t *img = mlx_new_image(mlx, 128, 128);
 if (!img) { mlx_terminate(mlx); return EXIT_FAILURE; }
 if (mlx_image_to_window(mlx, img, 0, 0) < 0) { mlx_terminate(mlx); return EXIT_FAILURE; }
 mlx_loop(mlx);
 mlx_terminate(mlx);
 return EXIT_SUCCESS;
}