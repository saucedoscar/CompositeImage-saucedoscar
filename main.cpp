#include<iostream>
#include<string>
#include<vector>
#include"bitmap.h"

using namespace std;

void askForFirstImage();
void averagePixels();
void restOfImages();
void addImg(vector<vector <Pixel> >);
void resizeCube();

int height;
int width;
int imagesAdded = 0;

vector < vector< vector< Pixel> > > cube;
vector <vector<Pixel> > finalImage;
int imgCount = 0;

int main()
{
    askForFirstImage();
    if(imgCount > 0)
    {
        restOfImages();
    }
    else
    {
        askForFirstImage();
    }
    if(imgCount > 0 )
    {
    averagePixels();
    }
    else{
    cout<<"I am sorry I did not recieve more than 2 valid images"<<endl;
    }

    return 0;
}
//asks for the first image so that the computer could check if it is valid and then save the height and width of the image into constant varibales.
void askForFirstImage() //asks the user for the image to compose with. 
{
       //ask for the first image
        Bitmap image;
        string filename;
        vector <vector<Pixel> > bmp;
        cout<<"Please give me your first image"<<endl;
        cin>>filename;
        image.open(filename);
        cout<<endl;
        if(image.isImage())//checks if the first image is valid
        {
            bmp = image.toPixelMatrix();
            height = bmp.size();
            width = bmp[0].size();
            imgCount++;
            cube.resize(height);
            finalImage.resize(height);
            for(int r = 0; r < cube.size(); r ++)
            {
                cube[r].resize(width);
                finalImage[r].resize(width);
            }
            //action: save the height and width into constant-global variables.
            //increment count to make sure they don't go over ten images
        }
        else 
        {
            //tell them the image is invalid 
            cout<<"I am sorry, that file is invalid."<<endl;
        }
        filename.clear();
}
//asks for more images and calls the fucntion addImg when it as a valid image basing it off the size of the image.
void restOfImages()
{
    Bitmap image;
    bool moreImages = true;
    string response;
    vector<vector<Pixel > > img;
        do{
            cout<<"Please give me no more than 9 more files or type 'DONE'. Make sure you give me at least one more file."<<endl;
            cout<<"please type the filename"<<endl;
            cin>>response;
            if(response == "Done" || response == "done" || response == "DONE")
            {                                   
                break;
            }
            image.open(response);
            if(image.isImage())//if the same size and a valid image then call the funciton
            {
                img = image.toPixelMatrix();
                if(img.size() == height && img[0].size() == width)
                {
                    if(imgCount < 11)
                    {
                        imgCount++;
                        resizeCube();
                        addImg(img);
                    }
                    else
                    {
                        cout<<"You have reached max images. I will now make the final image."<<endl;
                        moreImages = false;
                    }
                }
                else
                {
                    cout<<"I am sorry that image is invalid. Please try again or type done if that's all the images you want to give me."<<endl;
                    moreImages = true;
                }
            }
            else
            {
                moreImages = false;
            }
            response.clear();
          }while(moreImages == true && imgCount < 11);
}
//adds a pixel matrix to an array of bitmaps

void resizeCube()
{
    for(int r = 0; r < height; r++)
    {
        for(int c = 0; c < width; c++)
        {
            cube[r][c].resize(imgCount);
        }
    }
}
void addImg(vector<vector<Pixel > > bmp)
{
   //adds the bmp to the composite vector of vector of vectors
    for(int r = 0; r < height; r++)
    {
        for(int c = 0; c < width; c++)
        {
            cube[r][c][imagesAdded] = bmp[r][c];   
        }
    }
    imagesAdded++;
}
//average pixels within the arrays using for loops
void averagePixels()
{
        Bitmap image;
        int sumRed = 0;
        int sumGreen = 0;
        int sumBlue = 0;
        int averageRed = 0; 
        int averageGreen = 0;
        int averageBlue = 0;
        const int DEPTH = imgCount;
        Pixel rgb, rgb2;
        for(int r = 0; r < height; r++)
        {
            for(int c = 0; c < width; c++)
            {
                if(c == (cube.size()/2))
                {
                    cout<<"finished 50%"<<endl;
                }
                    for(int z; z < DEPTH; z++)
                    {
                        sumRed = 0;
                        sumGreen = 0;
                        sumBlue = 0;
                        averageRed = 0;
                        averageGreen = 0;
                        averageBlue = 0;
                        //grab the rgb values of each 
                        rgb = cube[r][c][z];
                        sumRed = sumRed + rgb.red;
                        sumGreen = sumGreen + rgb.green;
                        sumBlue = sumBlue + rgb.blue;
                    }
                
                averageRed = sumRed/imgCount;
                averageGreen = sumGreen/imgCount;
                averageBlue = sumBlue/imgCount;

                rgb2 = finalImage[r][c];
                rgb2.red = averageRed;
                rgb2.green = averageGreen;
                rgb.blue = averageBlue;
                finalImage[r][c] = rgb2;
            }                
        }
        image.fromPixelMatrix(finalImage);
        image.save("composite-saucedoscar.bmp");
}

