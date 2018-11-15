#include <stdio.h>
#include <stdlib.h>
#include "alphabet_templates.h"

int main(int argc, char* argv[])
{
	int **input_image;
        FILE *file1 = fopen("alphabet_plate0.pgm", "r"); // input file read
        char M, N;  // Magic Number    P = M, 2 = N
        int XX, YY, MAX;  // width, height, max bright

        int x, y;
        int i=0, j=0;

	static int distance[26]; // hamming distance
	int class=0; // licence plate result

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
                                if(abs(result2[y][x] - A_0[y][x]) == 255) distance[0]++;
                                if(abs(result2[y][x] - A_1[y][x]) == 255) distance[1]++;
                                if(abs(result2[y][x] - A_2[y][x]) == 255) distance[2]++;
                                if(abs(result2[y][x] - A_3[y][x]) == 255) distance[3]++;
                                if(abs(result2[y][x] - A_4[y][x]) == 255) distance[4]++;
                                if(abs(result2[y][x] - A_5[y][x]) == 255) distance[5]++;
                                if(abs(result2[y][x] - A_6[y][x]) == 255) distance[6]++;
                                if(abs(result2[y][x] - A_7[y][x]) == 255) distance[7]++;
                                if(abs(result2[y][x] - A_8[y][x]) == 255) distance[8]++;
                                if(abs(result2[y][x] - A_9[y][x]) == 255) distance[9]++;
				if(abs(result2[y][x] - A_10[y][x]) == 255) distance[10]++;
                                if(abs(result2[y][x] - A_11[y][x]) == 255) distance[11]++;
                                if(abs(result2[y][x] - A_12[y][x]) == 255) distance[12]++;
                                if(abs(result2[y][x] - A_13[y][x]) == 255) distance[13]++;
                                if(abs(result2[y][x] - A_14[y][x]) == 255) distance[14]++;
                                if(abs(result2[y][x] - A_15[y][x]) == 255) distance[15]++;
                                if(abs(result2[y][x] - A_16[y][x]) == 255) distance[16]++;
                                if(abs(result2[y][x] - A_17[y][x]) == 255) distance[17]++;
                                if(abs(result2[y][x] - A_18[y][x]) == 255) distance[18]++;
                                if(abs(result2[y][x] - A_19[y][x]) == 255) distance[19]++;
				if(abs(result2[y][x] - A_20[y][x]) == 255) distance[20]++;
                                if(abs(result2[y][x] - A_21[y][x]) == 255) distance[21]++;
                                if(abs(result2[y][x] - A_22[y][x]) == 255) distance[22]++;
                                if(abs(result2[y][x] - A_23[y][x]) == 255) distance[23]++;
                                if(abs(result2[y][x] - A_24[y][x]) == 255) distance[24]++;
                                if(abs(result2[y][x] - A_25[y][x]) == 255) distance[25]++;
                        }
                }

		int min = distance[0];
	        for(j=0; j<26; j++) {
        	        if(distance[j] < min) {
                	        min = distance[j];
                        	class = j;
              		}
		}

		if(class == 0) printf("A");
		else if(class == 1) printf("B");
		else if(class == 2) printf("C");
		else if(class == 3) printf("D");
		else if(class == 4) printf("E");
		else if(class == 5) printf("F");
                else if(class == 6) printf("G");
                else if(class == 7) printf("H");
                else if(class == 8) printf("I");
		else if(class == 9) printf("J");
                else if(class == 10) printf("K");
		else if(class == 11) printf("L");
                else if(class == 12) printf("M");
                else if(class == 13) printf("N");
                else if(class == 14) printf("O");
                else if(class == 15) printf("P");
                else if(class == 16) printf("Q");
                else if(class == 17) printf("R");
                else if(class == 18) printf("S");
                else if(class == 19) printf("T");
		else if(class == 20) printf("U");
                else if(class == 21) printf("V");
                else if(class == 22) printf("W");
                else if(class == 23) printf("X");
                else if(class == 24) printf("Y");
                else if(class == 25) printf("Z");

		// init
		for(j=0; j<26; j++) distance[j] = 0;
                fclose(read);
                system("rm result_image.pgm"); // remove file
        }
	printf("\n");
}


