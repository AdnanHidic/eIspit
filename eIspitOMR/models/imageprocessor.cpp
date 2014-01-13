#include "imageprocessor.h"

///
/// \brief ImageProcessor::prepare Priprema sliku za dalju obradu.
/// \param img - neobradjena slika
/// \return rezultat obrade slike, fixne velicine, korektno orijentirano, crno bijelo, po mogucnosti da su prezivjele samo tackice
///
Mat ImageProcessor::prepare(Mat img)
{
    // da je ovo normalan programski jezik, ovdje bi isao throw new NotImplementedException();
    return img;
}

///
/// \brief ImageProcessor::extract Na osnovu pripremljene slike formira instnacu klase uradjen ispit
/// \param img - pripremljena slika
/// \return ispit ocitan iz slike
///
FinishedExam ImageProcessor::extract(Mat img)
{
    FinishedExam exam;

    return exam;
}

FinishedExam ImageProcessor::load_exam(QString path)
{
    // image is loaded from file
    Mat img = imread(path.toStdString(),CV_LOAD_IMAGE_GRAYSCALE);

    // if the image could not be loaded, handle the unpleasantries
    if (img.data==NULL){
        // how?
    }

    // now we prepare the image for further processing
    img = prepare(img);

    // now we extract the exam from the prepared image
    FinishedExam exam = extract(img);

    return exam;
}
