/* Transformations */
void translate(coord3D *points, int size, float xt, float yt, float zt)
{
	int i;
	for(i = 0; i < size; ++i)
	{
		points[i].x += xt;
		points[i].y += yt;
		points[i].z += zt;
	}
}

void scale(coord3D *points, int size, float xs, float ys, float zs)
{
	int i;
	for(i = 0; i < size; ++i)
	{
		points[i].x = points[i].x * xs;
		points[i].y = points[i].y * ys;
		points[i].z = points[i].z * zs;
	}
}

void rotate(coord3D *points, int size, float angle_x, float angle_y, float angle_z)
{
	/* The angles are given in degrees */

	angle_x = rad(angle_x);
	angle_y = rad(angle_y);
	angle_z = rad(angle_z);

	float xn, yn, zn;

	int i;
	for(i = 0; i < size; ++i)
	{
		/* X Rotation*/
		yn = points[i].y * cos(angle_x) - points[i].z * sin(angle_x);
		zn = points[i].z * cos(angle_x) + points[i].y * sin(angle_x);

		points[i].y = yn;
		points[i].z = zn;

		/* Y Rotation */
		xn = points[i].x * cos(angle_y) - points[i].z * sin(angle_y);
		zn = points[i].z * cos(angle_y) + points[i].x * sin(angle_y);

		points[i].x = xn;
		points[i].z = zn;

		/* Z Rotation */
		xn = points[i].x * cos(angle_z) - points[i].y * sin(angle_z);
		yn = points[i].y * cos(angle_z) + points[i].x * sin(angle_z);

		points[i].x = xn;
		points[i].y = yn;
	}
}