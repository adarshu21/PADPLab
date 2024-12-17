#include <gd.h>
#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[]){
    
    omp_set_num_threads(4); //set as a 4 thread program
    int tid, temp, red,green, blue, color, x,h,y,w;
    temp = red = green = blue = color = x = y = h = w = 0;
    
    if(argc!=3)
        {
        printf("Insufficient arguments. Exiting...");
        exit(1);
        }
        
        
    char *input = argv[1]; //input file path
    char *output = argv[2]; //output file path
    
    FILE *fp = fopen(input, "r");
    gdImagePtr img = gdImageCreateFromPng(fp);
    
     w = gdImageSX(img); //find width of image
     h = gdImageSY(img); //find height of image 
     printf("Width: %d, Height: %d\n",w,h);

    double t = omp_get_wtime();
    
    //parallelize here
    //schedule( [scheduling_type (guided/static/dynamic)], [number of iterations in each chunk] )
    #pragma omp parallel for schedule(guided,100) /*schedule(static,50)*/ /* schedule(dynamic,50) */ 
    							/*schedule(guided, 50) */
    for(x = 0; x<w; x++)
        for(y = 0; y<h; y++)
            {
            tid = omp_get_thread_num(); //get thread number
            
            color = gdImageGetPixel(img,x,y); //get pixel
            red = gdImageRed(img,color); //Extract R of RGB value of pixel
            blue = gdImageBlue(img,color); //Extract B of RGB value of pixel
            green = gdImageGreen(img,color); //Extract G of RGB value of pixel
            
            //temp = (red+blue+green)/3;  //a method to bring color down to greyscale. homogenize the RGB values
            
            temp = (int)(0.2126*red + 0.7152*green + 0.0722*blue);  //gives better greyscale conversion
       //above formula is optional, it follows ITU-Recommendation 709 luma calculation for better greyscale conversion
            
            
            if(tid==0)
            	color = gdImageColorAllocate(img, temp, 0, 0); //red scale
            else if(tid==1)
            	color = gdImageColorAllocate(img, 0, temp, 0); //green scale
            else if(tid==2)
	            color = gdImageColorAllocate(img, 0, 0, temp); //blue scale
            else 
   		    color = gdImageColorAllocate(img,temp, temp, temp); //to convert image to greyscale, set all RGB to same calculated temp value
            gdImageSetPixel(img,x,y,color);
            }
    
    t = omp_get_wtime() - t;
    printf("Time Taken: %.4f\n",t);
    
    fp = fopen(output, "w");
    gdImagePng(img,fp);  //output image to new file 
    fclose(fp);
    gdImageDestroy(img);
    
    return 0;
}
