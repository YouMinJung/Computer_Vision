#include <stdio.h>
#define MAX_LABEL 5000
#define max(x,y) (((x) > (y)) ? (x) : (y))
#define min(x,y) (((x) < (y)) ? (x) : (y))

int main(int argc, char *argv[]) 
{
	int image1[1000][1000];
	int image2[1000][1000]; 
	int image3[1000][1000]; 

	FILE *file1, *file2; // file
	char M,N;  // Magic Number    P = M, 2 = N
	int XX, YY, MAX;  // width, height, max bright 
	int x, y;    // image1 use it(width, height)
	int xx, yy;  // image2 use it(width, height)

	int r, c, sum=0;
	int erosion_mask[3][3] = {  {255, 255, 255},
			   		{255, 255, 255},
			   		{255, 255, 255} };

	int dilation_mask[3][3] = { {0, 0, 0},
			   		{0, 0, 0},
			   		{0, 0, 0} };

	int sumX=0, sumY=0, Ssum=0;
	int sobel_maskX[3][3] = { {-1, 0, 1},
			    				{-2, 0, 2},
			    				{-1, 0, 1} };

	int sobel_maskY[3][3] = { {-1, -2, -1},
			    				{0, 0, 0},
			    				{1, 2, 1} };

	// read image header
	file1 = fopen(argv[1], "r");
	fscanf(file1, "%c", &M);
	fscanf(file1, "%c", &N);
	fscanf(file1, "%d", &XX);
	fscanf(file1, "%d", &YY);
	fscanf(file1, "%d", &MAX);
	
	// read image data
	for(y=0; y<YY; y++)
		for(x=0; x<XX; x++)
			fscanf(file1, "%d", &image1[y][x]);

// binarization
    	for(y=0; y<YY; y++){
        	for(x=0; x<XX; x++) {
            		if(image1[y][x] > 120)
				image1[y][x] = 255;
			else
				image1[y][x] = 0;
        	}
    	}

// if background is white, then reverse image
	int background = 0;
	for(y=0; y<10; y++){
        	for(x=0; x<10; x++) {
			if(image1[y][x] == 255)
				background++;
		}
	}	

	if(background > 10) {
		for(y=0; y<YY; y++){
        		for(x=0; x<XX; x++) {
				if(image1[y][x] == 255)
					image1[y][x] = 0;
				else 
					image1[y][x] = 255;
			}
		}
	}

// delete pepper and salt
	// Opening
	// erosion
	for(y=0; y<YY-2; y++) {
        	for(x=0; x<XX-2; x++) {
			for(r=0; r<3; r++) {
				for(c=0; c<3; c++) {
					if(image1[y+r][x+c] == erosion_mask[r][c]) sum++;
				}
			}
			if(sum == 9) image2[y+1][x+1] = 255;
			else image2[y+1][x+1] = 0;

			sum = 0;
        	}
	}

	// dilation
	for(y=0; y<YY-2; y++) {
        	for(x=0; x<XX-2; x++) {
			for(r=0; r<3; r++) {
				for(c=0; c<3; c++) {
					if(image2[y+r][x+c] == dilation_mask[r][c]) sum++;
				}
			}
			if(sum == 9) image3[y+1][x+1] = 0;
			else image3[y+1][x+1] = 255;

			sum = 0;
        	}
	}

	// Closing
	// dilation
	for(y=0; y<YY-2; y++) {
        	for(x=0; x<XX-2; x++) {
			for(r=0; r<3; r++) {
				for(c=0; c<3; c++) {
					if(image3[y+r][x+c] == dilation_mask[r][c]) sum++;
				}
			}
			if(sum == 9) image1[y+1][x+1] = 0;
			else image1[y+1][x+1] = 255;

			sum = 0;
        	}
	}

	// erosion
	for(y=0; y<YY-2; y++) {
        	for(x=0; x<XX-2; x++) {
			for(r=0; r<3; r++) {
				for(c=0; c<3; c++) {
					if(image1[y+r][x+c] == erosion_mask[r][c]) sum++;
				}
			}
			if(sum == 9) image2[y+1][x+1] = 255;
			else image2[y+1][x+1] = 0;

			sum = 0;
        	}
	}

// image write
	file2 = fopen("processing_result.pgm", "w");
	fprintf(file2, "%c", M);
        fprintf(file2, "%c\n", N);
        fprintf(file2, "%d %d\n", XX, YY);
        fprintf(file2, "%d\n", MAX);

        for(y=0; y<YY; y++){
            for(x=0; x<XX; x++){
                fprintf(file2, "%4d", image2[y][x]);
		}
		fprintf(file2, "\n");
	}
	fclose(file1);
	fclose(file2);

// read processed image
	file1 = fopen("processing_result.pgm", "r");
	fscanf(file1, "%c", &M);
	fscanf(file1, "%c", &N);
	fscanf(file1, "%d", &XX);
	fscanf(file1, "%d", &YY);
	fscanf(file1, "%d", &MAX);
	
	// read image data
	for(y=0; y<YY; y++)
		for(x=0; x<XX; x++)
			fscanf(file1, "%d", &image1[y][x]);


	int i,temp,cnt;
	int label = 0;
	int max_label, min_label, min_eq;
	int eq_tbl[MAX_LABEL][2], hash[MAX_LABEL];
	int coin_value[MAX_LABEL];
	int coin_value2[MAX_LABEL];

// do labeling
	for(y=1; y<YY; y++){
		for(x=1; x<XX; x++) {
			if(image1[y][x] == 255) {
				if((image1[y-1][x] == 0) && (image1[y][x-1] == 0)) {
					label++;
					image1[y][x] = label;
					eq_tbl[label][0] = label;
					eq_tbl[label][1] = label;
				}
				else if((image1[y-1][x] != 0) && (image1[y][x-1] == 0))
					image1[y][x] = image1[y-1][x];
				else if((image1[y][x-1] != 0) && (image1[y-1][x] == 0))
					image1[y][x] = image1[y][x-1];
				else {
					max_label = max(image1[y-1][x], image1[y][x-1]);
					min_label = min(image1[y-1][x], image1[y][x-1]);
					image1[y][x] = min_label;
					min_eq = min(eq_tbl[max_label][1], eq_tbl[min_label][1]);
					eq_tbl[max_label][1] = min_eq;
					eq_tbl[min_label][1] = min_eq;
				}
			}
		}
	}

	// eq_table arrange
	for(i=1; i<=label; i++)
		eq_tbl[i][1] = eq_tbl[ eq_tbl[i][1] ][1];

	// hash => arrange table
	for(i=1; i<=label; i++)
		hash[ eq_tbl[i][1] ] = eq_tbl[i][1];

	cnt=1;
	for(i=1; i<=label; i++)
		if(hash[i] != 0)
			hash[i] = cnt++;

	for(i=1; i<=label; i++)
		eq_tbl[i][1] = hash[ eq_tbl[i][1] ];

	// second scan
	for(y=1; y<YY; y++) {
		for(x=1; x<XX; x++) {
			if(image1[y][x] != 0) {
				temp = image1[y][x];
				image1[y][x] = eq_tbl[temp][1];
			}
		}
	}

	int price = 0;
	int total_price = 0;
	int area = 0, perimeter = 0, center = 0;
	int state = 0;  // 1:Coin,  0:Non-coin
	int coin_num = 0;

// show labeling result and price
	for(label=1; label < cnt; label++) {
		printf("label = %d\n", label);

		// segmentation depend on the label
		for(y=1; y<YY; y++)
			for(x=1; x<XX; x++)
				if(image1[y][x] == label)
					image2[y][x] = 255;
				else
					image2[y][x] = 0;

// calculate coin's perimeter
		// contour - sobel mask
		for(y=0; y<YY-2; y++) {
                for(x=0; x<XX-2; x++) {
					for(r=0; r<3; r++) {
						for(c=0; c<3; c++) {
							sumX += image2[y+r][x+c] * sobel_maskX[r][c];
							sumY += image2[y+r][x+c] * sobel_maskY[r][c];
						}
					}
					Ssum = abs(sumX) + abs(sumY);
					if(Ssum > 255) Ssum = 255;
					else if(Ssum < 0) Ssum = 0;

					image3[y+1][x+1] = Ssum;
					Ssum = 0;
					sumX = 0;
					sumY = 0;
                }
		}

		for(y=0; y<YY-2; y++) {
            for(x=0; x<XX-2; x++) {
                if(image3[y][x] == 255) perimeter++;
            }
        }

// calculate coin's area
		for(y=0; y<YY-2; y++) {
            for(x=0; x<XX-2; x++) {
                if(image2[y][x] == 255) area++;
            }
        }

		int countX = 0, countY = 0;
		double valueX = 0, valueY = 0;

// recognize coin (is it coin??) - center of mass
		for(y=0; y<YY-2; y++) {
				for(x=0; x<XX-2; x++) {
					if(image2[y][x] == 255) countX++;
				}
				valueX += y * countX;
				countX = 0;
		}

		for(x=0; x<XX-2; x++) {
				for(y=0; y<YY-2; y++) {
					if(image2[y][x] == 255) countY++;
				}
				valueY += x * countY;
				countY = 0;
		}

		valueX /= area;
		valueY /= area;
		valueX += 0.5;
		valueY += 0.5;
		valueX = (int)valueX;
		valueY = (int)valueY;

		int half = 0;
		double coin_area = 0;

		for(x=valueY+10; x<XX-2; x++) {
			if(image3[(int)valueX][x] > 100) {
				half = x - valueY;
				break;
			}
		}

		coin_area = half * half * 3.14;
		if(coin_area <= area - 1000  || coin_area <= area + 1000) state = 1;
		else state = 0;

		if(state == 1) {
			printf("\tPerimeter result is %d\n", perimeter);
			printf("\tArea result is %d\n", area);
			printf("\tCenter of Mass is ( %lf, %lf )\n", valueY, valueX);
			image3[(int)valueX][(int)valueY] = 255;

			coin_value[coin_num] = perimeter;
			coin_value2[coin_num] = area;
			coin_num++;
		}
		else printf("This is not Coin...\n");
		perimeter = 0;
		area = 0;
		valueX = 0;
		valueY = 0;
		state = 0;

		// image write
        file2 = fopen("label_result.pgm", "w");
        fprintf(file2, "%c", M);
        fprintf(file2, "%c\n", N);
        fprintf(file2, "%d %d\n", XX, YY);
        fprintf(file2, "%d\n", MAX);

        for(y=0; y<YY; y++){
            for(x=0; x<XX; x++){
                fprintf(file2, "%4d", image3[y][x]);
            }
            fprintf(file2, "\n");
        }

		fclose(file2);
		system("xv label_result.pgm");
		
	}

	int j=0, k=0, tmp=0;

	// sort perimeter
	for(j=0;j<coin_num;j++) {
        for(k=0;k<coin_num-1;k++) {
            if(coin_value[k] > coin_value[k+1]) {
                tmp = coin_value[k];   
                coin_value[k] = coin_value[k+1];
                coin_value[k+1] = tmp;
            }
        }
    }

    // sort area
    for(j=0;j<coin_num;j++) {
        for(k=0;k<coin_num-1;k++) {
            if(coin_value2[k] > coin_value2[k+1]) {
                tmp = coin_value2[k];   
                coin_value2[k] = coin_value2[k+1];
                coin_value2[k+1] = tmp;
            }
        }
    }

    int coin_state=0;  // price
    int sub_num = 0; // big 10 coin

    for(i=0; i<coin_num-1; i++) {
    	if(coin_value2[i+1] - coin_value2[i] > 320 && coin_value[i+1] - coin_value[i] > 15) {
    		coin_state++;
    	}

    	if(coin_value2[coin_num-1] > 6000) {
	    	if(coin_state == 0) {
	    		total_price += 10;
	    	}
	    	else if(coin_state == 1) {
	    		total_price += 50;
	    	}
	    	else if(coin_state == 2) {
	    		total_price += 100;
	    	}
	    	else if(coin_state == 3) {
	    		total_price += 100;
	    	}
	    	else if(coin_state == 4) {
	    		total_price += 500;
	    	}
	    }
	    else {
	    	if(coin_value2[i+1] - coin_value2[i] < 320 && coin_value2[i+1] - coin_value2[i] > 74)
	    		sub_num++;

	    	if(coin_state == 0) {
	    		total_price += 10;
	    	}
	    	else if(coin_state == 1) {
	    		total_price += 100;
	    	}
	    	else if(coin_state == 2) {
	    		total_price += 500;
	    	}
	    }
    }
    total_price += 10; // first value 

    for(i=0; i<sub_num; i++) {
    	total_price -= 90;
    }

	printf("\n<< Total Price >> is %d\n\n", total_price);

	return 0;
}
