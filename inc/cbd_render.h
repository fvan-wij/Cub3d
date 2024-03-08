#ifndef CBD_RENDER_H
# define CBD_RENDER_H
# include <stdint.h>

#define WHITE 		0xFFFFFFFF
#define	OFF_WHITE	0xF0F0F0FF
#define RED 		0xFF0000FF
#define GREEN 		0x00FF00FF
#define BLUE 		0x0000FFFF

#define TILES 		(64 + 64)
#define TILESIZE 	WIDTH / TILES
#define	MAPSIZE		WIDTH - (TILESIZE * 16)
#define RADARW		626
#define RADARH		448

int32_t	color(uint8_t r, uint8_t g, uint8_t b);

#endif //CBD_RENDER_H
