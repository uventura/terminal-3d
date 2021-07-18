/* Copy a 3D Point*/

void copy_array(coord3D *a1, coord3D *a2, int size)
{
	int i;
	for(i = 0; i < size; i++)
	{
		a2[i] = a1[i];
	}
}

/* Object Settings*/

coord3D set_point(float px, float py, float pz)
{
	coord3D n_Point;

	n_Point.x = px;
	n_Point.y = py;
	n_Point.z = pz;

	return n_Point;
}

void point_to_scr(screen *scr, coord3D *points, int size)
{
	int i;

	for(i = 0; i < size; ++i)
	{
		if(points[i].x >= 0 && points[i].x < scr->width && points[i].y >= 0 && points[i].y < scr->height)
			scr->elements[scr->height - (int)points[i].y - 1][(int)points[i].x] = 'o';
	}
}

coord3D centerObj(coord3D *points, int size)
{
	int i;
	
	coord3D center;
	center.x = 0;
	center.y = 0;
	center.z = 0;

	for(i = 0; i < size; ++i)
	{
		center.x += points[i].x;
		center.y += points[i].y;
		center.z += points[i].z;
	}

	center.x = center.x / size;
	center.y = center.y / size;
	center.z = center.z / size;

	return center;
}

/* Build Line */
coord3D *build_lines(coord3D *points, unsigned int *Ibuffer, int n, int *size_r)
{
	*size_r = 0;

	coord3D *result;
	result = malloc(sizeof(coord3D));

	float px, py, pz, coef_xy[2], coef_yz[2], max, min, j;

	int i, pos = -1, ib = 0;

	for(i = 0; i < n - 1; i = i + 2)
	{
		px = points[Ibuffer[i+1]].x;
		py = points[Ibuffer[i+1]].y;
		pz = points[Ibuffer[i+1]].z;

		ib = Ibuffer[i];

		max = points[ib].x;
		min = px;

		if(points[ib].x - px == 0)
		{
			coef_xy[0] = 1;
			coef_xy[1] = 1;

			coef_yz[0] = 0;
			coef_yz[1] = 0;

			max = points[ib].y;
			min = py;
		}
		else
		{
			coef_xy[0] = (points[ib].y - py) / (points[ib].x - px);
			coef_xy[1] = (points[ib].z - pz) / (points[ib].x - px);

			coef_yz[0] = py - coef_xy[0] * px;
			coef_yz[1] = pz - coef_xy[1] * px;
		}


		if(min > max)
		{
			min = min + max;
			max = min - max;
			min = min - max;
		}

		j = min;
		while(j <= max)
		{
			pos++;

			result[pos].x = j;
			if(points[ib].x - px == 0)
				result[pos].x = px;

			result[pos].y = (j * coef_xy[0]) + coef_yz[0];
			result[pos].z = (j * coef_xy[1]) + coef_yz[1];

			result = realloc(result, (pos + 2) * sizeof(coord3D));

			*size_r = pos + 1;

			j = j + 0.1;
		}
	}

	return result;
}