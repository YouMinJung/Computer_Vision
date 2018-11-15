#include <stdio.h>
#include <stdlib.h>

int main() {
	int **input_image;
        FILE *file1 = fopen("background_sample.ppm", "r"); // input file read
        char M, N;  // Magic Number    P = M, 3 = N
        int XX, YY, MAX;  // width, height, max bright

        int x, y;
	int i;

        // read image header
        fscanf(file1, "%c%c%d%d%d", &M, &N, &XX, &YY, &MAX);
        // assign memory dynamic
        input_image = (int**)malloc(sizeof(int*) * YY);
        for(i=0; i<YY; i++)
                input_image[i] = (int*)malloc(sizeof(int) * XX *3);

        // read image data
        for(y=0; y<YY; y++)
                for(x=0; x<XX*3; x++)
                        fscanf(file1, "%d", &input_image[y][x]);


	// create diffrent image
	int **image2;
        image2 = (int**)malloc(sizeof(int*) * YY);
        for(i=0; i<YY; i++)
                image2[i] = (int*)malloc(sizeof(int) * XX *3);

	// copy input_image to image2
	for(y=0; y<YY; y++) 
		for(x=0; x<XX*3; x++)
			image2[y][x] = input_image[y][x];
	
	// white : 255 255 255 
        for(y=0; y<YY; y++) {
                for(x=1; x<XX*3-1; x+=3) {
			if(image2[y][x-1] != 255 && image2[y][x] != 255 && image2[y][x+1] != 255) {
				image2[y][x-1] = 0;
				image2[y][x] = 0;
				image2[y][x+1] = 0;
			} 
		}
	}
                   
	// result image
	FILE *file3 = fopen("remove_background_result.ppm", "w");
	int **image3;
        image3 = (int**)malloc(sizeof(int*) * YY);
        for(i=0; i<YY; i++)
                image3[i] = (int*)malloc(sizeof(int) * XX *3);

        for(y=0; y<YY; y++)
                for(x=0; x<XX*3; x++)
                        image3[y][x] = abs(input_image[y][x] - image2[y][x]);

	fprintf(file3, "%c%c\n%d %d\n%d\n", M, N, XX, YY, MAX);
        for(y=0; y<YY; y++) { 
                for(x=0; x<XX*3; x++) { 
                        fprintf(file3, "%d ", image2[y][x]);
                }
                fprintf(file3, "\n");
        }
}


