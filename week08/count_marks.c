#include <stdio.h>

int main(int argc, char* argv[]) {

	int  num;
	FILE *fp;
    int totalover50=0;
    int count=0;
    
	fp = fopen(argv[1], "r");
	if (fp != NULL) {
		//file was opened
		while (!feof(fp)) {
			//there is still something left to read
			if (fscanf(fp, "%d", &num) != 1)
				break; //the file format is not as i expected
			count++;
            if(num>=50){
                totalover50++;
            }
		}

        float percent = (totalover50*100.0)/count;

        printf("total marks above 50: %d \nthe average is (%d/%d) = %.2f %% \n",totalover50,totalover50,count,percent);

		fclose(fp);
	}
	
	return 0;
}
