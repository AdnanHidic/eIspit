#include "imageprocessor.h"

const int ImageProcessor::group_bbox_x_coordinates [] = {16, 40, 64, 88, 112, 136, 160, 184};

const QString ImageProcessor::groupchars [] = {"A","B","C","D","E","F","G","H"};
const QString ImageProcessor::groupnums [] = {"1","2","3","4","5","6","7","8"};

///
/// \brief ImageProcessor::extract Na osnovu pripremljene slike formira instnacu klase uradjen ispit
/// \param img - pripremljena slika, 500x770, ispravno orijentirana, bw
/// \return ispit ocitan iz slike
///
FinishedExam ImageProcessor::extract(Mat img)
{
    FinishedExam exam;

    // extraction of group
    GroupID gid = extract_group(img);

    // if group was not detected
    if (gid==GroupID_NONE){
        exam.setValid(false);
        return exam;
    }
    else{
        exam.setGroupID(gid);
    }


    // extraction of candidate ID
    QString candidateID = extract_candidateID(img);

    // if candidate ID was not detected or is incorrect
    if (candidateID.length()==0){
        exam.setValid(false);
        return exam;
    }
    else{
        exam.setCandidateID(candidateID);
    }


    // extraction of answers to questions
    QVector<AnswerID> answers = extract_answers(img);

    exam.setAnswers(answers);

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

    int criteria = bbox_height*bbox_width*group_success_pct;
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
        for (int j=x;j<x+bbox_width;j++){
            for (int k=y;k<y+bbox_height;k++){
                uchar c = img.at<uchar>(k,j);
                if (c==0)
                    number_of_pixels[i]++;
            }

        }
    }
    return number_of_pixels;
}

// data about candidate id need to be located within rectangle
// rectangle starts @75,580 and width=132, height=172
// returns empty string if the detection encountered a problem
QString ImageProcessor::extract_candidateID(const Mat &img)
{
    // first we get the subimage that contains our Region Of Interest
    Mat ROI(img,Rect(75,580,132,172));
    int criteria = bbox_height*bbox_width*group_success_pct;

    //imshow("Subsection", ROI);

    // then we get the indexes of filled bounding boxes one by one, if multiple are selected, empty string is returned
    // foreach group
    QVector<int> detected_px;
    QString cid = "";
    for (int i = 0; i < 5; i++){
        // get vector of counted px at each characteristic position
        detected_px = count_pixels_by_column(ROI, cid_bbox_x_start + i*cid_bbox_x_offset, cid_bbox_y_start, cid_bbox_y_offset, 8);

        // then for each position
        for (int j = 0; j < 8; j++){
            // if there are many px's at it
            if (detected_px[j]>=criteria){
                // add symbol to string
                if (i<3)
                    cid+= groupchars[j];
                else
                    cid+= groupnums[j];
            }
        }
        // its an error yo
        if (cid.size()!=(i+1))
            return "";
    }

    return cid;
}

// counts pixels in the entire column (for candidate id)
QVector<int> ImageProcessor::count_pixels_by_column(const Mat &img, int startX, int startY, int diffY, int num)
{
    QVector<int> number_of_pixels(num);
    int x = startX,y;
    for (int i = 0; i < num ; i++){
        y = i * diffY + startY;
        // now we have the top left corner of the bounding box
        for (int j = x; j < x+bbox_width; j++){
            for (int k = y; k < y+bbox_width; k++){
                uchar c = img.at<uchar>(k,j);
                if (c==0)
                    number_of_pixels[i]++;
            }
        }
    }

    return number_of_pixels;
}

// counts pixels in the entire row (for exam answers)
QVector<int> ImageProcessor::count_pixels_by_row(Mat &img, int startX, int startY, int diffX, int num)
{
    QVector<int> number_of_pixels(num);
    int x, y = startY;
    for (int i = 0; i < num ; i++){
        x = i * diffX + startX;

        //rectangle(img,Rect(x,y,bbox_height,bbox_width),Scalar(0, 255, 0));

        // now we have the top left corner of the bounding box
        for (int j = x; j < x+bbox_width; j++){
            for (int k = y; k < y+bbox_width; k++){
                uchar c = img.at<uchar>(k,j);
                if (c==0)
                    number_of_pixels[i]++;
            }
        }
    }
    return number_of_pixels;
}

QVector<AnswerID> ImageProcessor::extract_answers(const Mat &img)
{
    // first we get the subimage that contains our Region Of Interest
    Mat ROI(img,Rect(386,244,100,502));
    int criteria = bbox_height*bbox_width*answ_success_pct;

    QVector<AnswerID> answers(20);
    QVector<int> pixels_per_choice;
    // foreach question
    for (int i = 0; i < 20; i++){
        pixels_per_choice = count_pixels_by_row(ROI,answ_bbox_x_start,answ_bbox_y_start + i * answ_bbox_y_offset,answ_bbox_x_offset,4);
        for (int j = 0; j < 4; j++){
            if (pixels_per_choice[j] >= criteria){
                if (answers[i]==AnswerID_NONE){
                    answers[i] = (AnswerID)(j+1);
                }
                else {
                    answers[i] = AnswerID_NONE;
                    break;
                }
            }
        }
    }
    //imshow("Name",ROI);

    return answers;
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
    //img = ImagePreprocessor::prepare(img);

    // now we extract the exam from the prepared image
    exam = extract(img);

    return exam;
}
