#include<iostream>
#include<string>
#include<vector>
#include"bitmap.h"

using namespace std;

void askForImages();
void averagePixels();
void restOfImages();
void addImg(vector<vector <Pixel> >);
void resizeVector();
int height;
int width;
int imagesAdded = 0;

vector < vector< vector< Pixel> > > composite;
int imgCount = 0;

int main()
{
    askForImages();
    restOfImages();
    averagePixels();
   

    return 0;
}
//asks for the first image so that the computer could check if it is valid and then save the height and width of the image into constant varibales.
void askForImages() //asks the user for the image to compose with. 
{
       //ask for the first image
        Bitmap image;
        string filename;
        vector <vector<Pixel> > bmp;
        cout<<"Please give me your first image"<<endl;
        cin>>filename;
        image.open(filename);
        if(image.isImage())//checks if the first image is valid
        {
            bmp = image.toPixelMatrix();
            height = bmp.size();
            width = bmp[0].size();
            imgCount++;
            composite.resize(height);
            for(int r = 0; r < composite.size(); r ++)
            {
                composite[r].resize(width);
            }
            //action: save the height and width into constant-global variables.
            //increment count to make sure they don't go over ten images
        }
        else 
        {
            //tell them the image is invalid 
            cout<<"I am sorry, that file is invalid."<<endl;
        }
}
//asks for more images and calls the fucntion addImg when it as a valid image basing it off the size of the image.
void restOfImages()
{
    Bitmap image;
    bool moreImages = true;
    bool loop;
    string response;
    vector<vector<Pixel > > img;
    cout<<"Please give me no more than 9 more files. If you want to less than 9 files type done."<<endl;
        do{
            cout<<"Please give me no more than 9 more files. If you want less than 9 files type done. Make sure you give me at least one more file."<<endl;
            cout<<"please type the filename"<<endl;
            cin>>response;
            if(response == "Done" || response == "done")
            {                                   
                moreImages = false;
                loop = false;
            }
            image.open(response);
            if(image.isImage())//if the same size and a valid image then call the funciton
            {
                img = image.toPixelMatrix();
                if(img.size() == height && img[0].size() == width)
                {
                    imgCount++;
                    resizeVector();
                    addImg(img);

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
                loop = false;
            }
            response.clear();
          }while(moreImages == true && imgCount < 11);
          if(imgCount == 10)
          {
                cout<<"You have reached max images. I will no make the composite image."<<endl;
          }
}
//adds a pixel matrix to an array of bitmaps

void resizeVector()
{
    for(int r = 0; r < height; r++)
    {
        for(int c = 0; c < width; c++)
        {
            composite[r][c].resize(imgCount);
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
            composite[r][c][imagesAdded] = bmp[r][c];   
        }
    }
    imagesAdded++;
}
//average pixels within the arrays using for loops
void averagePixels()
{
        int sumRed = 0;
        int sumGreen = 0;
        int sumBlue = 0;
        int average; 
        const int DEPTH = imgCount;
        Pixel rgb;
        for(int r = 0; r < height; r++)
        {
            for(int c = 0; c < width; c++)
            {
                for(int z; z < DEPTH; z++)
                {
                    //grab the rgb values of each 
                    composite[r][c][z] = rgb;
                    sumRed = sumRed + composite[r][c][z].red;
                    sumGreen = sumGreen + composite[r][c][z].green;
                    sumBlue = sumBlue + composite[r][c][z].blue;
                }
            }
        }
}

