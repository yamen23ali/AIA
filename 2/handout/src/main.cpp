#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

#include "given.hpp"
#include "yours.hpp"
#include "app.cpp"


/*int main(int argc, char** argv) {
    std::vector<input> templates{
        input{"./data/template1.jpg", cv::imread("./data/template1.jpg", 0), 120, 3},
        input{"./data/template2.jpg", cv::imread("./data/template2.jpg", 0), 120, 3}};

    input query{"./data/query.jpg", cv::imread("./data/query.jpg", 0), 120, 3};

    cv::Mat output;
    yours::preprocessImage(query.img, output, query.bin_thresh, query.n_erosions);
    //given::showImage(output);

    app(templates, query, 10, 0.8);

    return 0;
}*/

int main(int argc, char** argv) {
    std::vector<input> templates{
        input{"./data/sign_template1.jpg", cv::imread("./data/sign_template1.jpg", 0), 240, 0},
        input{"./data/sign_template2.jpg", cv::imread("./data/sign_template2.jpg", 0), 240, 0},
        input{"./data/sign_template3.jpg", cv::imread("./data/sign_template3.jpg", 0), 240, 0}
    };

    input query{"./data/sign_query.jpg", cv::imread("./data/sign_query.jpg", 0), 240, 5};


    //cv::Mat output;
    //yours::preprocessImage(query.img, output, query.bin_thresh, query.n_erosions);
    //given::showImage(output);

   	app(templates, query, 10, 0.8);

    return 0;
}
