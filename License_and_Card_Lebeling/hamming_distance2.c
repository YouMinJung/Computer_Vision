#include <stdio.h>
#include <stdlib.h>
#include "hangul_templates.h"

int main(int argc, char* argv[])
{
	int **input_image;
        FILE *file1 = fopen("hangul_plate1.pgm", "r"); // input file read
        char M, N;  // Magic Number    P = M, 2 = N
        int XX, YY, MAX;  // width, height, max bright

        int x, y;
        int i=0, j=0;

	static int distance[5]; // hamming distance
	int class=0; // licence plate result
	int si=0, ee=0, bi=0;

        // read image header
        fscanf(file1, "%c%c%d%d%d", &M, &N, &XX, &YY, &MAX);
        // assign memory dynamic
        input_image = (int**)malloc(sizeof(int*) * YY);
        for(i=0; i<YY; i++)
                input_image[i] = (int*)malloc(sizeof(int) * XX);

        // read image data
        for(y=0; y<YY; y++)
                for(x=0; x<XX; x++)
                        fscanf(file1, "%d", &input_image[y][x]);

	int top_value=0, bottom_value=0;
        int state = 0; // first value use
        // find template point - top, bottom
        for(y=0; y<YY; y++) {
                for(x=0; x<XX; x++) {
                        if(input_image[y][x] == 0 && state == 0) {
                                top_value = y;
                                state = 1;
                        }
                }
        }
        state=0;
        for(y=YY-1; y>0; y--) {
                for(x=0; x<XX; x++) {
                        if(state==0 && input_image[y][x] == 0) {
                                bottom_value = y;
                                state=1;
                        }
                }
        }
        state=0;
        YY = bottom_value - top_value +1;

	int white=0;
        int *Xvalues1, *Xvalues2;
        Xvalues1 = (int*)malloc(sizeof(int));
        Xvalues2 = (int*)malloc(sizeof(int));

        i=0; // number of template
        for(x=0; x<XX; x++) {
                for(y=top_value; y<bottom_value+1; y++) {
                        if(state==0 && input_image[y][x] == 0) {
                                Xvalues1[i] = x;
                                state=1;
                        }

                        if(input_image[y][x] == 255 && x >= Xvalues1[i]) white++;
                }

                if(white == YY && state==1) {
                        Xvalues2[i] = x;
                        i++;
                        state=0;
                }
                white=0;
        }

	int k=0;
	printf("Result : ");
        for(k=0; k<i; k++) {

                // creat result image;
                XX = Xvalues2[k] - Xvalues1[k];
                YY = bottom_value - top_value +1;

                FILE *image = fopen("result_image.pgm", "w");
                fprintf(image, "%c%c\n%d %d\n%d\n", M, N, XX, YY, MAX);

                for(y= top_value; y<bottom_value+1; y++) {
                        for(x=Xvalues1[k]; x<Xvalues2[k]; x++) {
                                fprintf(image, "%4d", input_image[y][x]);
                        }
                        fprintf(image, "\n");
                }

                fclose(image);

		// size normalization
                int result1[300][300];
                int result2[300][300];
                int xx, yy;

                FILE *read = fopen("result_image.pgm", "r");
                fscanf(read, "%c%c%d%d%d", &M, &N, &XX, &YY, &MAX);
                for(y=0; y<YY; y++)
                        for(x=0; x<XX; x++)
                                fscanf(read, "%d", &result1[y][x]);

                // normalize image size
                for(y=0; y<YY; y++)
                        for(x=0; x<XX; x++) {
                                yy = y*30/YY;
                                xx = x*30/XX;
                                result2[yy][xx] = result1[y][x];
                        }
                XX = XX * 30 / XX;
                YY = YY * 30 / YY;

		// hamming distance
                for(y=0; y<YY; y++) {
                        for(x=0; x<XX; x++) {
                                if(abs(result2[y][x] - H_0[y][x]) == 255) distance[0]++;
                                if(abs(result2[y][x] - H_1[y][x]) == 255) distance[1]++;
                                if(abs(result2[y][x] - H_2[y][x]) == 255) distance[2]++;
                                if(abs(result2[y][x] - H_3[y][x]) == 255) distance[3]++;
				if(abs(result2[y][x] - H_4[y][x]) == 255) distance[4]++;
                        }
                }

		int min = distance[0];
	        for(j=0; j<5; j++) {
        	        if(distance[j] < min) {
                	        min = distance[j];
                        	class = j;
              		}
		}

		if(class == 0) si=1;
		else if(class == 1) ee=1;
		else if(class == 2) printf("소");
		else if(class == 3) printf("나");
		else if(class == 4) bi=1;

		if(si ==1 && ee ==1){
			printf("시");
			si=0;
			ee=0;
		}
		else if(bi ==1 && ee ==1) {
			printf("비");
			ee=0;
			bi=0;
		}
	
		// init
		for(j=0; j<5; j++) distance[j] = 0;
                fclose(read);
                system("rm result_image.pgm"); // remove file
        }
	printf("\n");
}


