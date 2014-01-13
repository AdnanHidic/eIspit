#include "imageprocessor.h"

const int ImageProcessor::group_bbox_x_coordinates [] = {16, 40, 64, 88, 112, 136, 160, 184};


///
/// \brief ImageProcessor::extract Na osnovu pripremljene slike formira instnacu klase uradjen ispit
/// \param img - pripremljena slika, 500x770, ispravno orijentirana, bw
/// \return ispit ocitan iz slike
///
FinishedExam ImageProcessor::extract(Mat img)
{
    FinishedExam exam;

    GroupID gid = extract_group(img);

    // if group was not detected
    if (gid==GroupID_NONE){
        exam.setValid(false);
        return exam;
    }
    else{
        exam.setGroupID(gid);
    }


    /*QString candidateID = extract_candidateID(img);

    // if candidate ID was not detected or is incorrect
    if (candidateID.length()==0){
        exam.setValid(false);
        return exam;
    }
    else{
        exam.setCandidateID(candidateID);
    }*/

    exam.setValid(true);
    return exam;
}

// data about group need to be located within rectangle
// rectangle starts @36,480 and width=210, height=20
// returns GroupID_NONE if the detection encountered a problem
GroupID ImageProcessor::extract_group(const Mat &img)
{
    // first we get the subimage that contains our Region Of Interest
    Mat ROI(img,Rect(36,480,210,20));

    // then we count the number of black pixels within characteristic bounding boxes
    // bounding box size iz 10x10, making 100 pixels. success pct dictates the number of black pixels
    // within the bounding box which is considered a filled field
    QVector<int> number_of_pixels = count_pixels_group(ROI);

    GroupID detected = GroupID_NONE;

    int criteria = group_bbox_height*group_bbox_width*group_success_pct;
    for (int i=0;i<8;i++){
        if (number_of_pixels[i]>=criteria){
            if (detected!=GroupID_NONE)
                return GroupID_NONE;
            else
                detected= GroupID(i+1);
        }
    }

    //imshow("Subsection", ROI);

    return detected;
}

QVector<int> ImageProcessor::count_pixels_group(const Mat &img)
{
    QVector<int> number_of_pixels(8);
    int x, y= group_bbox_y_coordinate;
    // foreach possible group
    for (int i=0;i<8;i++){
        x = group_bbox_x_coordinates[i];
        // foreach characteristic point within group
        for (int j=x;j<x+group_bbox_width;j++){
            for (int k=y;k<y+group_bbox_height;k++){
                uchar c = img.at<uchar>(k,j);
                if (c==0)
                    number_of_pixels[i]++;
            }

        }
    }
    return number_of_pixels;
}

FinishedExam ImageProcessor::load_exam(QString path)
{
    FinishedExam exam ;
    // image is loaded from file
    Mat img = imread(path.toStdString(),CV_LOAD_IMAGE_GRAYSCALE);

    // if the image could not be loaded, handle the unpleasantries
    if (img.data==NULL){
        exam.setValid(false);
        return exam;
    }

    // now we prepare the image for further processing
    img = ImagePreprocessor::prepare(img);

    // now we extract the exam from the prepared image
    exam = extract(img);

    return exam;
}
