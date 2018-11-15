#include <stdio.h>
#include <stdlib.h>

void template1(int temp_num) {

        int **template_image; // assign template image pointer
        FILE *file1 = fopen("hangul_plate0.pgm", "r"); // input file read
        char M,N;  // Magic Number    P = M, 2 = N
        int XX, YY, MAX;  // width, height, max bright

        int x, y;    // image use it(width, height)
        int i; // malloc

        // read image header
        fscanf(file1, "%c%c%d%d%d", &M, &N, &XX, &YY, &MAX);
        // assign memory dynamic
        template_image = (int**)malloc(sizeof(int*) * YY);
        for(i=0; i<YY; i++)
                template_image[i] = (int*)malloc(sizeof(int) * XX);

        // read image data
        for(y=0; y<YY; y++)
                for(x=0; x<XX; x++)
                        fscanf(file1, "%d", &template_image[y][x]);

        int top_value=0, bottom_value=0;
        int state = 0; // first value use
        // find template point - top, bottom
        for(y=0; y<YY; y++) {
                for(x=0; x<XX; x++) {
                        if(template_image[y][x] == 0 && state == 0) {
                                top_value = y;
                                state = 1;
                        }
                }
        }
        state=0;
        for(y=YY-1; y>0; y--) {
                for(x=0; x<XX; x++) {
                        if(state==0 && template_image[y][x] == 0) {
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
                        if(state==0 && template_image[y][x] == 0) {
                                Xvalues1[i] = x;
                                state=1;
                        }

                        if(template_image[y][x] == 255 && x >= Xvalues1[i]) white++;
                }

                if(white == YY && state==1) {
                        Xvalues2[i] = x;
                        i++;
                        state=0;
                }
                white=0;
        }

	int k=0;

	for(k=0; k<i; k++) {

		// creat result image;
		XX = Xvalues2[k] - Xvalues1[k];
		YY = bottom_value - top_value +1;

		FILE *image = fopen("result_image.pgm", "w");
		fprintf(image, "%c%c\n%d %d\n%d\n", M, N, XX, YY, MAX);
		
		for(y= top_value; y<bottom_value+1; y++) {
	        	for(x=Xvalues1[k]; x<Xvalues2[k]; x++) {
                        	fprintf(image, "%4d", template_image[y][x]);
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

		// write to number_templates.h
		FILE *file2 = fopen("hangul_templates.h", "a+"); // write file
                fprintf(file2, "int H_%d[30][30] = { \n", k+temp_num);
                for(y=0; y<YY; y++) {
                        for(x=0; x<XX; x++) {
				if(y == YY-1 && x == XX-1) fprintf(file2, "%4d ", result2[y][x]);
				else fprintf(file2, "%4d,",  result2[y][x]);
                        }	
                        fprintf(file2, "\n");
                }
                fprintf(file2, "};\n\n");

		fclose(read);
		fclose(file2);

		system("rm result_image.pgm"); // remove file
	}
}

