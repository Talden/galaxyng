#include "influence.h"

int
CMD_influence(int argc, char* argv[])
{
	printf("This command not yet implemented\n");
	return 1;
}

struct _map {
	double* influence;
	double* factor;
} pi_map[768][768];

void
draw_maps(game* aGame)
{
	player*     P;
	planet*     p;
	
	FILE*      mapfile;      /* output for map */
	char*      err;
	char       map_title[64];
	
	gdImagePtr map_png;	/* image */
	int        white;        /* colour indices */
	
	double     scale;
	
	int        brect[8];
	int        i, j, k;
	int        iscale;
	
	char       font[1024];
	
	int        idx, x, y, player_nbr;
	int        x0, y0, df, d_e, d_se;
	int        r, g, b;
	
	double     weight;
	double     influence;
	double     factor, limit;
	
	int        map_colors[42][4] = {
		{0, 0, 0, 0},               /* black */
		{255, 255, 255, 0},         /* white */
		{0, 255, 127, 0},           /* spring green */
		{205, 92, 92, 0},           /* indian red */
		{132, 112, 255, 0},         /* light slate blue */
		{193, 255, 193, 0},         /* DarkSeaGreen1 */
		{238, 154, 73, 0},          /* tan2 */
		{178, 34, 34, 0},           /* firebrick */
		{85, 107, 47, 0},           /* dark olive green */
		{255, 250, 205, 0},         /* lemon chiffon */
		{240, 255, 255, 0},         /* azure */
		{230, 230, 250, 0},         /* lavender */
		{255, 228, 225, 0},         /* misty rose */
		{235, 245, 230, 0},         /* mint cream */
		{135, 206, 250, 0},         /* light sky blue */
		/**/ {176, 224, 230, 0},   /* powder blue */
		{0, 206, 209, 0},           /* dark turquoise */
		{0, 255, 255, 0},           /* cyan */
		{102, 205, 170, 0},         /* medium aquamarine */
		{46, 139, 87, 0},           /* sea green */
		{152, 251, 152, 0},         /* pale green */
		{173, 255, 47, 0},          /* green yellow */
		{107, 142, 35, 0},          /* olive drab */
		/**/ {238, 232, 170, 0},   /* pale goldenrod */
		{255, 215, 0, 0},           /* gold */
		{222, 184, 135, 0},         /* burlywood */
		{255, 160, 122, 0},         /* light salmon */
		{255, 140, 0, 0},           /* dark orange */
		{240, 128, 128, 0},         /* light coral */
		{100, 149, 237, 0},         /* cornflower blue */
		{255, 99, 71, 0},           /* tomato */
		{255, 105, 180, 0},         /* hot pink */
		/**/ {219, 112, 147, 0},   /* pale violet red */
		{176, 48, 96, 0},           /* maroon */
		{186, 85, 211, 0},          /* medium orchid */
		{148, 0, 211, 0},           /* dark violet */
		{255, 250, 250, 0},         /* snow1 */
		{255, 246, 143, 0},         /* khaki1 */
		{238, 220, 130, 0},         /* LightGoldenrod2 */
		{205, 155, 155, 0},         /* RosyBrown3 */
		{139, 95, 101, 0},          /* LightPink4 */
		{205, 150, 205, 0},         /* plum3 */
	};
	
	enum map_type mt;
	int  nbr_of_players;

	nbr_of_players = numberOfElements(aGame->players);
	scale = 765.0 / aGame->galaxysize;
	iscale = (int)scale;

	if (aGame->serverOptions.fontpath)
		sprintf(font, "%s/influence.ttf", aGame->serverOptions.fontpath);
	else
		strcpy(font, "./influence.ttf");
	
	for (mt = FirstMap; mt < NbrMaps; mt++) {
		switch(mt) {
			case EffIndMap:
				sprintf(buf, "%s/data/%s/%03d_effind.png",
						galaxynghome, aGame->name, aGame->turn);
				strcpy(map_title, "Effective Industry");
				break;

#if 0
			case ShipAttMap:
				sprintf(buf, "%s/data/%s/%03d_shpatt.png",
						galaxynghome, aGame->name, aGame->turn);
				strcpy(map_title, "Ship Attack Potential");
				break;
				
			case ShipDefMap:
				sprintf(buf, "%s/data/%s/%03d_shpdef.png",
						galaxynghome, aGame->name, aGame->turn);
				strcpy(map_title, "Ship Defense Potential");
				break;
#endif
			default:
				break;
		}
		
		mapfile = GOS_fopen(buf, "wb");
		
		map_png = gdImageCreateTrueColor(1024, 768);
		
		for (i = 0; i < nbr_of_players+2; i++) {
			map_colors[i][3] = gdImageColorAllocate(map_png, map_colors[i][0],
													map_colors[i][1],
													map_colors[i][2]);
		}
		
		white = map_colors[1][3];
		
		gdImageRectangle(map_png, 0, 0, 1023, 767, white);
		gdImageLine(map_png, 767, 0, 767, 767, white);
		gdImageLine(map_png, 767, 745, 1023, 745, white);
		gdImageLine(map_png, 767, 723, 1023, 723, white);
		sprintf(buf, "%s   Turn: %d", aGame->name, aGame->turn);
		err = gdImageStringFT((gdImagePtr) NULL, &brect[0], white, font,
							  12., 0., 0, 0, buf);
		if (err)
			fprintf(stderr, "%s\n", err);
		
		gdImageStringFT(map_png, NULL, white, font, 12., 0.,
						896 - (brect[4] / 2), 762, buf);
		
		err = gdImageStringFT((gdImagePtr) NULL, &brect[0], white, font,
							  12., 0., 0, 0, map_title);
		if (err)
			fprintf(stderr, "%s\n", err);

		gdImageStringFT(map_png, NULL, white, font, 12., 0.,
						896 - (brect[4] / 2), 740, map_title);

		/* set  up variables to hold the influence, one double for each
		 * player. We'll combine at the end
		 */
		for (j = 0; j < 768; j++) {
			for (k = 0; k < 768; k++) {
				if (pi_map[j][k].influence == NULL) {
					pi_map[j][k].influence =
						(double*)calloc(nbr_of_players, sizeof(double));
					pi_map[j][k].factor =
						(double*)calloc(nbr_of_players, sizeof(double));
				}
				else {
					memset((void*)pi_map[j][k].influence, 0,
						   sizeof(double)*nbr_of_players);
					memset((void*)pi_map[j][k].factor, 0,
						   sizeof(double)*nbr_of_players);
				}
			}
		}
		

		/* draw the player names in the key */
		i = 2;                        /* nations off by 2 due to black/white */
		for (P = aGame->players; P; P = P->next) {
			err = gdImageStringFT(map_png, NULL, map_colors[i][3], font, 10.,
								  0., 770, 3 + ((i - 1) * 15), P->name);
			if (err)
				fprintf(stderr, "%s\n", err);
			i++;
		}      
		
		
		/* now add up the influence for each player */
		for (p = aGame->planets; p; p = p->next) {
			player* owner;
			
			owner = p->owner;
			
			player_nbr = ptonum(aGame->players, owner) - 1;

			if (player_nbr < 0 && mt == EffIndMap)
				continue;

			switch(mt) {
				case EffIndMap:
					weight = effectiveIndustry(p->pop, p->ind);
					influence = factor = 0.9;
					limit = 0.5;
					break;
#if 0
				case ShipAttMap:
					weight=addShipAtt(aGame, p);
					influence = factor = 0.925;
					limit = 0.1;
					break;
					
				case ShipDefMap:
					weight=addShipDef(aGame, P);
					influence = factor = 0.925;
					limit = 0.1;
					break;
#endif
				default:
					break;
			}	
			
			x = (int) ((scale * p->x) + 1);
			y = (int) ((scale * p->y) + 1);
			
			idx = 1;
			while (weight > limit) {
				weight *= factor;
				influence *= factor;
				
				x0 = 0;
				y0 = idx;
				
				df = 1 - idx;
				d_e = 3;
				d_se = -2 * idx + 5;
				
				do {
					if (x+x0 < 767 && y + y0 < 767) {
						pi_map[x+x0][y+y0].influence[player_nbr] += weight;
						pi_map[x+x0][y+y0].factor[player_nbr] += influence;
					}
					
					if (x0 && (x-x0 > 1 && y+y0<767)) {
						pi_map[x-x0][y+y0].influence[player_nbr] += weight;
						pi_map[x-x0][y+y0].factor[player_nbr] += influence;
					}
					
					if (y0 && (x+x0 < 767 && y-y0 > 1)) {
						pi_map[x+x0][y-y0].influence[player_nbr] += weight;
						pi_map[x+x0][y-y0].factor[player_nbr] += influence;
					}
					
					if (x0 && y0 && (x-x0>1 && y-y0>1)) {
						pi_map[x-x0][y-y0].influence[player_nbr] += weight;
						pi_map[x-x0][y-y0].factor[player_nbr] += influence;
					}
					
					if (x0 != y0) {
						if (x+y0<767 && y+x0<767) {
							pi_map[x+y0][y+x0].influence[player_nbr] += weight;
							pi_map[x+y0][y+x0].factor[player_nbr] += influence;
						}
						
						if (x0 && (x+y0<767 && y-x0>1)) {
							pi_map[x+y0][y-x0].influence[player_nbr] += weight;
							pi_map[x+y0][y-x0].factor[player_nbr] += influence;
						}
						
						if (y0 && (x-y0>1 && y+x0<767)) {
							pi_map[x-y0][y+x0].influence[player_nbr] += weight;
							pi_map[x-y0][y+x0].factor[player_nbr] += influence;
						}
						
						if (x0 && y0 && (x-y0>1 && y-x0>1)) {
							pi_map[x-y0][y-x0].influence[player_nbr] += weight;
							pi_map[x-y0][y-x0].factor[player_nbr] += influence;
						}
					}
					
					if (df < 0) {
						df += d_e;
						d_e += 2;
						d_se += 2;
					}
					else {
						df += d_se;
						d_e += 2;
						d_se += 4;
						y0--;
					}
					
					x0++;
				} while (x0 < y0);
				idx++;
			}
		}
		
		
		for (i = 1; i < 767; i++) {
			for (j = 1; j < 767; j++) {
				int winning_player;
				double max_weight;
				
   				max_weight = 0.0;
				winning_player = -1;
				for (k = 0; k < nbr_of_players; k++) {
					if (max_weight < pi_map[i][j].influence[k]) {
						max_weight = pi_map[i][j].influence[k];
						winning_player = k;

						if (pi_map[i][j].factor[k] > 1.0)
							pi_map[i][j].factor[k] = 1.0;
					}
				}
				
				if (winning_player == -1)
					continue;
				
				r = map_colors[winning_player+2][0] * pi_map[i][j].factor[winning_player];
				g = map_colors[winning_player+2][1] * pi_map[i][j].factor[winning_player];
				b = map_colors[winning_player+2][2] * pi_map[i][j].factor[winning_player];

				gdImageSetPixel(map_png, i, j,
								gdImageColorResolve(map_png, r, g, b));
			}
		}
		for (p = aGame->planets; p; p = p->next) {
			x = (int) ((scale * p->x) + 1);
			y = (int) ((scale * p->y) + 1);
			gdImageArc(map_png, x, y, 2, 2, 0, 360, white);
		}
		gdImagePng(map_png, mapfile);
		fclose(mapfile);
		gdImageDestroy(map_png);
	}
	return;
}

