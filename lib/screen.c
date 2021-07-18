/* Screen Settings */

void init(screen *scr, int w, int h, char sym)
{
	scr->width = w;
	scr->height = h;
	scr->symbol = sym;

	scr->elements = malloc(h * sizeof(char *));

	int i, j;
	for(i = 0; i < h; ++i)
	{
		scr->elements[i] = malloc(w * sizeof(char));

		for(j = 0; j < w; ++j)
			scr->elements[i][j] = sym;
	}
}

void show_scr(screen scr)
{
	int i, j;

	for(i = 0; i < scr.height; ++i)
	{
		for(j = 0; j < scr.width; ++j)
			printf("%c", scr.elements[i][j]);
		printf("\n");
	}
}

void clr_scr(screen *scr)
{
	int i, j;

	for(i = 0; i < scr->height; ++i)
	{
		for(j = 0; j < scr->width; ++j)
			scr->elements[i][j] = scr->symbol;
	}
}