#include "imagepreprocessor.h"

///
/// \brief ImageProcessor::prepare Priprema sliku za dalju obradu.
/// \param img - neobradjena slika
/// \return rezultat obrade slike, fixne velicine, korektno orijentirano, crno bijelo, po mogucnosti da su prezivjele samo tackice
///
///
///
//funkcija kreirana po uzoru na MATLAB imadjust funkciju koje nema u openCV, a daje zadovoljavajuce rezultate za ovakvu namjenu
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

    // Transformacija intenziteta
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

//funkcija sluzi za uklanjanje svih objekata na slici koji su manji od parametra size
Mat remove_small_objects( Mat img_in1, int size )
{
    IplImage* img_in = new IplImage(img_in1);
    IplImage* img_out       = cvCloneImage( img_in );
    CvMemStorage* storage   = cvCreateMemStorage( 0 );
    CvSeq* contours         = NULL;
    CvScalar black          = CV_RGB( 0, 0, 0 );
    CvScalar white          = CV_RGB( 255, 255, 255 );
    double area;

    // sve konture u binarnoj slici
    cvFindContours( img_in, storage, &contours, sizeof( CvContour ), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE );

    while( contours ){
        area = cvContourArea( contours, CV_WHOLE_SEQ );
        if( fabs( area ) <= size )  // ukoliko je manji parametra size
        {
             cvDrawContours( img_out, contours, white, white, -1, CV_FILLED, 8 );
        }
        else
        {
            //cvDrawContours( img_out, contours, black, black, -1, CV_FILLED, 8 );
        }
        contours = contours->h_next;
    }

    cvReleaseMemStorage( &storage );
    Mat img = Mat(img_out);
    return img;
}

//funkcija za racunanje ugla rotacije slike odnosno sadrzaja na istoj
double izracunaj_odstupanje(Mat image){
    Size size = image.size();
    bitwise_not(image, image);
    Mat element = getStructuringElement(MORPH_RECT, Size(5, 3));
    erode(image, image, element);
    vector<Point> points;
    Mat_<uchar>::iterator it = image.begin<uchar>();
    Mat_<uchar>::iterator end = image.end<uchar>();
    for (; it != end; ++it)
      if (*it)
        points.push_back(it.pos());
    RotatedRect box = minAreaRect(Mat(points));
    double angle = box.angle;
    if (angle < -45.)
      angle += 90.;
    return angle;
}


Mat ukloni_rotaciju(Mat src,double angle){
    bitwise_not(src, src);
    vector<Point> points;
    Mat_<uchar>::iterator it = src.begin<uchar>();
    Mat_<uchar>::iterator end = src.end<uchar>();
     for (; it != end; ++it)
       if (!(*it))
         points.push_back(it.pos());

     RotatedRect box = minAreaRect(Mat(points));
     Mat rotated;
     Mat rot_mat = cv::getRotationMatrix2D(box.center, angle, 1);
     warpAffine(src, rotated, rot_mat, src.size(), INTER_CUBIC, cv::BORDER_CONSTANT, cv::Scalar(255,255,255));
    Mat pom;
    rotated.copyTo(pom);
    //bitwise_not(pom,pom);
    points.clear();
    it = pom.begin<uchar>();
    end = pom.end<uchar>();
     for (; it != end; ++it)
       if (!(*it))
         points.push_back(it.pos());
    box = minAreaRect(Mat(points));
    cv::Size box_size = box.size;
    if (box.angle < -45.){
        std::swap(box_size.width, box_size.height);
    }
    Mat cropped;
    cv::getRectSubPix(rotated, box_size, box.center, cropped);
    return cropped;
}

Mat crop_image(Mat img)
{
    bitwise_not(img, img);
    vector<Point> points;
    Mat_<uchar>::iterator it = img.begin<uchar>();
    Mat_<uchar>::iterator end = img.end<uchar>();
    for (; it != end; ++it)
      if (!(*it))
        points.push_back(it.pos());
   RotatedRect box = minAreaRect(Mat(points));
   cv::Size box_size = box.size;
   if (box.angle < -45.){
       std::swap(box_size.width, box_size.height);
   }
   Mat cropped;
   cv::getRectSubPix(img, box_size, box.center, cropped);
    return cropped;
}

Mat ImagePreprocessor::prepare(Mat img)
{
    Mat img_gray, bin_image;
    cv::cvtColor(img,img_gray,CV_RGB2GRAY);
    double angle = izracunaj_odstupanje(img_gray);
    if(angle > 0.1 || angle < -0.1)
        img_gray = ukloni_rotaciju(img_gray,angle);
    else{
        //bitwise_not(img_gray, img_gray);
        img_gray = crop_image(img_gray);
    }
    //img_gray = crop_image(img_gray);
    resize(img_gray, img_gray, Size(500,770), 0, 0, INTER_CUBIC);  //prilagodjavanje optimalnoj rezoluciji
  //  img = img_gray;
   // ImageAdjust( img_gray, img_gray, 0, 1, 0.3, 1, 0.5);  //iz nekog razloga nakon rotacije slika postaje svjetlija pa nema potrebe za ovim ako se vrši rotacija
    for ( int i = 1; i < 8; i = i + 2 )
    medianBlur(img_gray,img_gray,i);
    morphologyEx(img_gray,img_gray,MORPH_CLOSE,getStructuringElement(MORPH_ELLIPSE,Size(10,10),Point(-1,-1)));
    morphologyEx(img_gray,img_gray,MORPH_ERODE,getStructuringElement(MORPH_ELLIPSE,Size(6,6),Point(-1,-1)));
    normalize(img_gray,img_gray,0,255,NORM_MINMAX);
    threshold ( img_gray, bin_image, 0, 255, THRESH_BINARY | THRESH_OTSU );
    img = bin_image;
    img = remove_small_objects(bin_image,200);
    return img;
}

