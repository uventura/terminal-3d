#include "lib/header3D.c"

int main()
{
	screen scr;
	coord3D triangle[3], copy[3], center_mass;
	float angle;

	init(&scr, 20, 20, ' ');

	clock_t initial_time;
	double delta_t;
	
	/* Vertices */
	triangle[0] = set_point(0, 0, 0);
	triangle[1] = set_point(2, 0, 0);
	triangle[2] = set_point(2, 2, 0);
		
	/* Index Buffer */
	int elements = 6;
	unsigned int ib[6] = 
	{
		0, 1,
		1, 2,
		2, 0
	};

	/* Matrix Transformations */
	translate(triangle, 3, 10, 10, 10);
	
	center_mass = centerObj(triangle, 3);
	translate(triangle, 3, -center_mass.x, -center_mass.y, -center_mass.z);
		scale(triangle, 3, 4, 4, 4);
	translate(triangle, 3, center_mass.x, center_mass.y, center_mass.z);

	copy_array(triangle, copy, 3);

	ortographic(triangle, 3);
	/*-----------*/

	int size_r;
	coord3D *resultant_obj;

	printf("%d\n", size_r);

	initial_time = clock();
	angle = 0;

	while(1)
	{
		delta_t = (double)(clock() - initial_time) / CLOCKS_PER_SEC;
		if(delta_t >= 0.008)
		{
			translate(triangle, 3, -center_mass.x, -center_mass.y, -center_mass.z);
				rotate(triangle, 3, 0, angle, 0);
			translate(triangle, 3, center_mass.x, center_mass.y, center_mass.z);

			ortographic(triangle, 3);

			resultant_obj = build_lines(triangle, ib, elements, &size_r);
			ortographic(resultant_obj, size_r);

			clr_scr(&scr);
				point_to_scr(&scr, resultant_obj, size_r);
			show_scr(scr);

			copy_array(copy, triangle, 3);

			angle++;
			if(angle == 361)
				angle = 0;
			
			initial_time = clock();
		}
	}
}