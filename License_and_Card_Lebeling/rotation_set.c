#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
	int input_image[700][700];
	int image2[700][700];
        FILE *file1 = fopen("line.pgm", "r"); // input file read
        char M, N;  // Magic Number    P = M, 2 = N
        int XX, YY, MAX;  // width, height, max bright

        int x, y;
        int left, right;
        double xo, yo;

        // read image header
        fscanf(file1, "%c%c%d%d%d", &M, &N, &XX, &YY, &MAX);
        
        // read image data
        for(y=0; y<YY; y++)
                for(x=0; x<XX; x++)
                        fscanf(file1, "%d", &input_image[y][x]);

	int firstY=0, firstX=0, secondY=0, secondX=0;
	int state=0;

	for(y=0; y<YY; y++) {
		for(x=0; x<XX; x++) {
			if(input_image[y][x] == 0 && state == 0) {
				firstY = y;
				firstX = x;
				state = 1;
			}

			if(input_image[y][x] == 0 && state == 1 && firstY < y) {
				secondY = y;
				secondX = x;
				state = 2;
			}
		}
	}

	float cos_theta=1, sin_theta = 0;
	float Yvalue=0, Xvalue=0, third=0;

	if(secondX == 0 && secondY == 0) {
		printf("There is no need to rotate.\n");
	}
	else {
		Yvalue = abs(firstY - secondY); 
		Xvalue = abs(firstX - secondX);
		third = Yvalue*Yvalue + Xvalue*Xvalue; 
		third = sqrt(third);

		cos_theta = Xvalue/third;
		sin_theta = Yvalue/third;

		// do rotation
		for(y=0; y<YY; y++)
	                for(x=0; x<XX; x++) {
        	                xo = (x - XX/2) * cos_theta - (y - YY/2) * sin_theta + XX/2;
                	        yo = (x - XX/2) * sin_theta + (y - YY/2) * cos_theta + YY/2;

                        	if(xo > XX-1) xo = XX-1;
                        	if(xo < 0) xo=0;
                        	if(yo > YY-1) yo = YY-1;
                        	if(yo < 0) yo=0;

                        	image2[(int)yo][(int)xo] = input_image[y][x];
                	}

        	//interpolation
        	for(y=0; y<YY; y++) {
                	for(x=1; x<XX-1; x++) {
                        	left = image2[y][x-1];
                        	right = image2[y][x+1];
                        	if(left != 0 && right != 0 && image2[y][x] == 0)
                                	image2[y][x] = (left+right)/2;
                	}
        	}

		// image write
		FILE *file2 = fopen("line_result.pgm", "w");
	        fprintf(file2, "%c", M);
       		fprintf(file2, "%c\n", N);
        	fprintf(file2, "%d %d\n", XX, YY);
        	fprintf(file2, "%d\n", MAX);

        	for(y=0; y<YY; y++){
                	for(x=0; x<XX; x++){
                        	fprintf(file2, "%d ", image2[y][x]);
                	}
                	fprintf(file2, "\n");
        	}
	}
}
