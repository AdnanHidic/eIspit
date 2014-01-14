#include "imagepreprocessor.h"

///
/// \brief ImageProcessor::prepare Priprema sliku za dalju obradu.
/// \param img - neobradjena slika
/// \return rezultat obrade slike, fixne velicine, korektno orijentirano, crno bijelo, po mogucnosti da su prezivjele samo tackice
///
int ImageAdjust(Mat src1,Mat  dst1,double low, double high,double bottom, double top,double gamma ){
    IplImage* src = new IplImage(src1);
    IplImage* dst = new IplImage(dst1);
if(low<0 && low>1 && high <0 && high>1&&bottom<0 && bottom>1 && top<0 && top>1 && low>high)  return -1;
    double low2 = low*255;
    double high2 = high*255;
    double bottom2 = bottom*255;
    double top2 = top*255;
    double err_in = high2 - low2;
    double err_out = top2 - bottom2;

    int x,y;
    double val;

    // intensity transform
    for( y = 0; y < src->height; y++)
    {
        for (x = 0; x < src->width; x++)
        {
            val = ((uchar*)(src->imageData + src->widthStep*y))[x];
            val = pow((val - low2)/err_in, gamma) * err_out + bottom2;
            if(val>255) val=255; if(val<0) val=0;
            ((uchar*)(dst->imageData + dst->widthStep*y))[x] = (uchar) val;
        }
    }
    dst1 = Mat(dst);
    return 0;
}

Mat remove_small_objects( Mat img_in1, int size )
{
    IplImage* img_in = new IplImage(img_in1);
    IplImage* img_out       = cvCloneImage( img_in );  // return image
    CvMemStorage* storage   = cvCreateMemStorage( 0 );    // container of retrieved contours
    CvSeq* contours         = NULL;
    CvScalar black          = CV_RGB( 0, 0, 0 ); // black color
    CvScalar white          = CV_RGB( 255, 255, 255 );   // white color
    double area;

    // find contours in binary image
    cvFindContours( img_in, storage, &contours, sizeof( CvContour ), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE );

    while( contours )   // loop over all the contours
    {
        area = cvContourArea( contours, CV_WHOLE_SEQ );
        if( fabs( area ) <= size )  // if the area of the contour is less than threshold remove it
        {
            // draws the contours into a new image

             cvDrawContours( img_out, contours, white, white, -1, CV_FILLED, 8 );
        }
        else
        {
            // fills in holes
            //cvDrawContours( img_out, contours, black, black, -1, CV_FILLED, 8 ); // removes white dots
        }
        contours = contours->h_next;    // jump to the next contour
    }

    cvReleaseMemStorage( &storage );
    Mat img = Mat(img_out);
    return img;
}


Mat ImagePreprocessor::prepare(Mat img)
{
    Mat img_gray, bin_image;
    cv::cvtColor(img,img_gray,CV_RGB2GRAY);
    //rotacija + podesavanje
    ImageAdjust( img_gray, img_gray, 0, 1, 0.3, 1, 0.5);
    for ( int i = 1; i < 8; i = i + 2 )
    medianBlur(img_gray,img_gray,i);
  //  GaussianBlur( img_gray, img_gray, Size(9, 9), 2, 2 );
    morphologyEx(img_gray,img_gray,MORPH_CLOSE,getStructuringElement(MORPH_ELLIPSE,Size(6,6),Point(-1,-1)));
    morphologyEx(img_gray,img_gray,MORPH_ERODE,getStructuringElement(MORPH_ELLIPSE,Size(4,4),Point(-1,-1)));
    normalize(img_gray,img_gray,0,255,NORM_MINMAX);
    threshold ( img_gray, bin_image, 0, 255, THRESH_BINARY | THRESH_OTSU );
    img = bin_image;
    img = remove_small_objects(bin_image,200);
    //erode(bin_image,bin_image,MORPH_ELLIPSE,Point(-1,-1),100);
    return img;
}

