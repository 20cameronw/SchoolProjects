#include <fstream>
#include <string>


int IMAGE_SIZE = 224;

void matwrite(const string& filename, const Mat& mat)
{
    ofstream fs(filename, fstream::binary);

    // Data
    int type = mat.type();
    if (mat.isContinuous())
    {
        fs.write(mat.ptr<char>(0), (mat.dataend - mat.datastart));
    }
    else
    {
        int rowsz = CV_ELEM_SIZE(type) * mat.cols;
        for (int r = 0; r < mat.rows; ++r)
        {
            fs.write(mat.ptr<char>(r), rowsz);
        }
    }
}

int main()
{
    // Save data

    {
        cv::Mat Img = cv::imread("image.jpg");
        //randu(m, 0, 5);
        matwrite("bin_file.bin", Img);
    }
    return 0;
}

