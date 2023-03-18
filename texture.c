#include "cub3d.h"

// - in a linked list, one node for each texture, parse the texture files in char**
//		and create a {character: color} map
// - find orientation of the wall hit by the ray to read from the according texture file
// - find the x coordinate the ray hit in the grid cell to know which x "index"
//		in the texture file to read from to render pixel from top to bottom on the given x index