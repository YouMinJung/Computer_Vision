#include <stdio.h>
#include <stdlib.h>
#include "number_templates.h"
#include "alphabet_templates.h"
#include "special_templates.h"

int main(int argc, char* argv[])
{
	int **input_image;
        FILE *file1 = fopen("card_plate.pgm", "r"); // input file read
        char M, N;  // Magic Number    P = M, 2 = N
        int XX, YY, MAX;  // width, height, max bright

        int x, y;
        int i=0;
	int w=0, mid=0;  // max x  
	int q=0;  // max y
	int k=0, j=0, t=0;

	static int distance[39]; // hamming distance
	int class=0;
	int Sclass[3]; // each result

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

	int top_value[3], bottom_value[3];
	int white=0;
        int state = 0; // first value use

        // find template point - top, bottom
        for(y=0; y<YY; y++) {
                for(x=0; x<XX; x++) {
			if(state == 0 && input_image[y][x] == 0) {
				top_value[q] = y;
				state=1;
			}

			if(input_image[y][x] == 255 && y>= top_value[q]) white++;
		}

		if(white == XX && state==1) {
			bottom_value[q] = y;
			q++;
			state=0;
		}
		white=0;
	}
	white=0;
	state=0;

	int Xvalues1[24], Xvalues2[24];
	int Xterm[4];
	Xterm[0] = 0;
	// x segementation
	for(k=0; k<q; k++) {
		YY = bottom_value[k] - top_value[k];
		for(x=0; x<XX; x++) {
                	for(y= top_value[k]; y<bottom_value[k]; y++) {
                                if(state==0 && input_image[y][x] == 0) {
                 	               Xvalues1[w] = x;
                        	       state=1;
                        	}

                        	if(input_image[y][x] == 255 && x >= Xvalues1[i]) white++;
                	}

                	if(white == YY && state==1) {
                        	Xvalues2[w] = x;
                        	w++;
                        	state=0;
                	}
                	white=0;
                }
		Xterm[k+1] = w;
	}

	printf("<< Result >>\n\n");
	for(k=0; k<q; k++) {
		// create result image
		for(j=Xterm[k]; j<Xterm[k+1]; j++) {
			// stage1 image - y segmentation result
                	YY = bottom_value[k] - top_value[k];
			// state2 image - x segmentation result
			XX = Xvalues2[j] - Xvalues1[j];

			FILE *image = fopen("result_image.pgm", "w");
                	fprintf(image, "%c%c\n%d %d\n%d\n", M, N, XX, YY, MAX);

                	for(y= top_value[k]; y<bottom_value[k]; y++) {
                        	for(x=Xvalues1[j]; x<Xvalues2[j]; x++) {
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
					// number
					if(abs(result2[y][x] - T_0[y][x]) == 255) distance[0]++;
                                	if(abs(result2[y][x] - T_1[y][x]) == 255) distance[1]++;
                                	if(abs(result2[y][x] - T_2[y][x]) == 255) distance[2]++;
                                	if(abs(result2[y][x] - T_3[y][x]) == 255) distance[3]++;
                                	if(abs(result2[y][x] - T_4[y][x]) == 255) distance[4]++;
                                	if(abs(result2[y][x] - T_5[y][x]) == 255) distance[5]++;
                                	if(abs(result2[y][x] - T_6[y][x]) == 255) distance[6]++;
                                	if(abs(result2[y][x] - T_7[y][x]) == 255) distance[7]++;
                                	if(abs(result2[y][x] - T_8[y][x]) == 255) distance[8]++;
                                	if(abs(result2[y][x] - T_9[y][x]) == 255) distance[9]++;

					// alphabet
					if(abs(result2[y][x] - A_0[y][x]) == 255) distance[10]++;
                                	if(abs(result2[y][x] - A_1[y][x]) == 255) distance[11]++;
                                	if(abs(result2[y][x] - A_2[y][x]) == 255) distance[12]++;
                                	if(abs(result2[y][x] - A_3[y][x]) == 255) distance[13]++;
                                	if(abs(result2[y][x] - A_4[y][x]) == 255) distance[14]++;
                                	if(abs(result2[y][x] - A_5[y][x]) == 255) distance[15]++;
                                	if(abs(result2[y][x] - A_6[y][x]) == 255) distance[16]++;
                                	if(abs(result2[y][x] - A_7[y][x]) == 255) distance[17]++;
                                	if(abs(result2[y][x] - A_8[y][x]) == 255) distance[18]++;
                                	if(abs(result2[y][x] - A_9[y][x]) == 255) distance[19]++;
                                	if(abs(result2[y][x] - A_10[y][x]) == 255) distance[20]++;
                                	if(abs(result2[y][x] - A_11[y][x]) == 255) distance[21]++;
                                	if(abs(result2[y][x] - A_12[y][x]) == 255) distance[22]++;
                                	if(abs(result2[y][x] - A_13[y][x]) == 255) distance[23]++;
                                	if(abs(result2[y][x] - A_14[y][x]) == 255) distance[24]++;
                                	if(abs(result2[y][x] - A_15[y][x]) == 255) distance[25]++;
                                	if(abs(result2[y][x] - A_16[y][x]) == 255) distance[26]++;
                                	if(abs(result2[y][x] - A_17[y][x]) == 255) distance[27]++;
                                	if(abs(result2[y][x] - A_18[y][x]) == 255) distance[28]++;
                                	if(abs(result2[y][x] - A_19[y][x]) == 255) distance[29]++;
                                	if(abs(result2[y][x] - A_20[y][x]) == 255) distance[30]++;
                                	if(abs(result2[y][x] - A_21[y][x]) == 255) distance[31]++;
                                	if(abs(result2[y][x] - A_22[y][x]) == 255) distance[32]++;
                                	if(abs(result2[y][x] - A_23[y][x]) == 255) distance[33]++;
                                	if(abs(result2[y][x] - A_24[y][x]) == 255) distance[34]++;
                                	if(abs(result2[y][x] - A_25[y][x]) == 255) distance[35]++;

					// special character
					if(abs(result2[y][x] - S_0[y][x]) == 255) distance[36]++;
	                                if(abs(result2[y][x] - S_1[y][x]) == 255) distance[37]++;
        	                        if(abs(result2[y][x] - S_2[y][x]) == 255) distance[38]++;

				}
			}
	
			int min0 = distance[0];
			int min1 = distance[10];
			int min2 = distance[36];

			// number
                	for(t=0; t<10; t++) {
                        	if(distance[t] < min0) {
                                	min0 = distance[t];
                                	Sclass[0] = t;
                        	}
                	}

			// alphabet
			for(t=10; t<36; t++) {
                                if(distance[t] < min1) {
                                        min1 = distance[t];
                                        Sclass[1] = t;
                                }
                        }
		
			// special character
			for(t=36; t<39; t++) {
                                if(distance[t] < min2) {
                                        min2 = distance[t];
                                        Sclass[2] = t;
                                }
                        }


			// context
			if(k==0) {
				class = Sclass[0];	
			}
			else if(k==2) {
				class = Sclass[1];
			}
			else {
				int min = distance[0];
				for(t=0; t<39; t++) {
					if(min > distance[t]) {
						min = distance[t];
						class = t;
					}
				}
			}

		
			if(class == 0) printf("0");
			else if(class == 1) printf("1");
                        else if(class == 2) printf("2");
                        else if(class == 3) printf("3");
                        else if(class == 4) printf("4");
                        else if(class == 5) printf("5");
                        else if(class == 6) printf("6");
                        else if(class == 7) printf("7");
                        else if(class == 8) printf("8");
                        else if(class == 9) printf("9");

                	else if(class == 10) printf("A");
                	else if(class == 11) printf("B");
                	else if(class == 12) printf("C");
                	else if(class == 13) printf("D");
                	else if(class == 14) printf("E");
                	else if(class == 15) printf("F");
                	else if(class == 16) printf("G");
                	else if(class == 17) printf("H");
                	else if(class == 18) printf("I");
                	else if(class == 19) printf("J");
                	else if(class == 20) printf("K");
                	else if(class == 21) printf("L");
                	else if(class == 22) printf("M");
                	else if(class == 23) printf("N");
                	else if(class == 24) printf("O");
                	else if(class == 25) printf("P");
                	else if(class == 26) printf("Q");
                	else if(class == 27) printf("R");
                	else if(class == 28) printf("S");
                	else if(class == 29) printf("T");
                	else if(class == 30) printf("U");
                	else if(class == 31) printf("V");
                	else if(class == 32) printf("W");
                	else if(class == 33) printf("X");
                	else if(class == 34) printf("Y");
                	else if(class == 35) printf("Z");
		
			else if(class == 36) printf("/");
	                else if(class == 37) printf("*");
        	        else if(class == 38) printf("&");	

                	// init
                	for(t=0; t<39; t++) distance[t] = 0;
                
			fclose(read);
                	system("rm result_image.pgm"); // remove file
		}
		printf("\n");
	}
	printf("\n");
}

