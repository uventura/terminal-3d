/* View */
void ortographic(coord3D *points, int size)
{
	int i;
	for(i = 0; i < size; ++i)
		points[i] = set_point(approach(points[i].x), approach(points[i].y), 0);
}