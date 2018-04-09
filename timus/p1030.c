/*
 * p1030 - Titanic
 *
 * Essentially a greater ciricle distance problem.
 *
 * Important to note that the result rounded to 2 decimal
 * places should be less than 100. We do this by comparing to
 * 99.995.
 *
 * https://en.wikipedia.org/wiki/Great-circle_distance
 */
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define EARTH_D_MILES 6875
#define EARTH_R_MILES 3437.5

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0)
#define radToDeg(angleInRadians) ((angleInRadians) * 180.0 / M_PI)

// Just buffer for what we are going to do.
char buff[256];

int main() {
	// Read first 3 lines, and read the next.
	for (int i = 0; i < 4; i++) {
		fgets(buff, sizeof(buff), stdin);
	} 
	// Now we need the coordinates.
	// We get the coordinates 
	char *startoff = buff;
	int X1 = strtol(startoff, &startoff, 10);
	startoff++;
	int X2 = strtol(startoff, &startoff, 10);
	startoff++;
	int X3 = strtol(startoff, &startoff, 10);
	startoff += 2;

	bool north = *startoff == 'N';

	// Latitude.
	// to convert to 1 and minus 1, 2*x - 1 
	double ship_lat = (2*north - 1) * degToRad((double)X1 + ((double)X2/60) + ((double)X3)/3600);

	// Second part of coordinates.
	fgets(buff, sizeof(buff), stdin);
	
	startoff = buff + 4;
	int Y1 = strtol(startoff, &startoff, 10);
	startoff++;
	int Y2 = strtol(startoff, &startoff, 10);
	startoff++;
	int Y3 = strtol(startoff, &startoff, 10);
	startoff += 2;
	bool east = *startoff == 'E';

	double ship_lon = (2*east-1) * degToRad(((double)Y1 + ((double)Y2/60) + ((double)Y3)/3600));

	// Skip 1 and read the other.
	fgets(buff, sizeof(buff), stdin);
	fgets(buff, sizeof(buff), stdin);

	startoff = buff;
	int A1 = strtol(startoff, &startoff, 10);
	startoff++;
	int A2 = strtol(startoff, &startoff, 10);
	startoff++;
	int A3 = strtol(startoff, &startoff, 10);
	startoff += 2;

	bool A_north = *startoff == 'N';

	double ice_lat = (2*A_north - 1) * degToRad((double)A1 + ((double)A2/60) + ((double)A3)/3600);

	// Second part of coordinates.
	fgets(buff, sizeof(buff), stdin);
	
	startoff = buff + 4;
	int B1 = strtol(startoff, &startoff, 10);
	startoff++;
	int B2 = strtol(startoff, &startoff, 10);
	startoff++;
	int B3 = strtol(startoff, &startoff, 10);
	startoff += 2;
	bool B_east = *startoff == 'E';

	double ice_lon = (2*B_east-1) * degToRad((double)B1 + ((double)B2/60) + ((double)B3)/3600);


	// We use the Vincenty formula to get correct results.
	double diff_lon = fabs(ice_lon - ship_lon);
	double central_angle = 
		atan2(
				hypot(
					cos(ice_lat)*sin(diff_lon),
					cos(ship_lat)*sin(ice_lat) - sin(ship_lat) * cos(ice_lat) * cos(diff_lon)
					),
				sin(ship_lat) * sin(ice_lat) + cos(ship_lat) * cos(ice_lat) * cos(diff_lon)
			 );
	double dist = central_angle * EARTH_R_MILES;

	printf("The distance to the iceberg: %.02f miles.\n", dist);
	if (dist < 99.995) {
		printf("DANGER!\n");
	}
		
	return 0;
}
