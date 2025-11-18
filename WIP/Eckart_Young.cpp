#include <Eigen/Dense>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using Eigen::MatrixXd;

// ================== PPM LOADING =====================
struct Image {
    int width;
    int height;
    MatrixXd R, G, B;
};

Image load_ppm(const std::string& filename) {
    std::ifstream f(filename, std::ios::binary);
    if (!f.is_open()) throw std::runtime_error("Cannot open PPM file");

    std::string magic;
    f >> magic;
    if (magic != "P3" && magic != "P6")
        throw std::runtime_error("Unsupported PPM format (must be P3 or P6)");

    int w, h, maxval;
    f >> w >> h >> maxval;
    f.ignore(256, '\n'); // skip to pixel data

    Image img;
    img.width = w;
    img.height = h;
    img.R = MatrixXd(h, w);
    img.G = MatrixXd(h, w);
    img.B = MatrixXd(h, w);

    if (magic == "P3") {
        // ASCII format
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                int r, g, b;
                f >> r >> g >> b;
                img.R(i, j) = r;
                img.G(i, j) = g;
                img.B(i, j) = b;
            }
        }
    } else {
        // P6 binary format
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                unsigned char rgb[3];
                f.read(reinterpret_cast<char*>(rgb), 3);
                img.R(i, j) = rgb[0];
                img.G(i, j) = rgb[1];
                img.B(i, j) = rgb[2];
            }
        }
    }

    return img;
}

// ================== PPM WRITING =====================
void save_ppm(const Image& img, const std::string& filename) {
    std::ofstream f(filename, std::ios::binary);
    f << "P6\n" << img.width << " " << img.height << "\n255\n";

    for (int i = 0; i < img.height; i++) {
        for (int j = 0; j < img.width; j++) {
            unsigned char r = std::clamp((int)img.R(i, j), 0, 255);
            unsigned char g = std::clamp((int)img.G(i, j), 0, 255);
            unsigned char b = std::clamp((int)img.B(i, j), 0, 255);
            unsigned char rgb[3] = {r, g, b};
            f.write(reinterpret_cast<char*>(rgb), 3);
        }
    }
}

// ================== ECKART-YOUNG APPROX =====================
MatrixXd rank_k_approx(const MatrixXd& M, int k) {
    Eigen::BDCSVD<MatrixXd> svd(M, Eigen::ComputeThinU | Eigen::ComputeThinV);

    MatrixXd U = svd.matrixU();
    MatrixXd Vt = svd.matrixV().transpose();
    Eigen::VectorXd S = svd.singularValues();

    MatrixXd Uk = U.leftCols(k);
    MatrixXd Vk = Vt.topRows(k);

    MatrixXd Sk = S.head(k).asDiagonal();

    return Uk * Sk * Vk;
}

// ================== MAIN =====================
int main() {
    try {
        std::string input = "image.ppm";
        std::string output = "svd_image.ppm";
        int k = 20; // rank

        Image img = load_ppm(input);

        Image out = img;
        out.R = rank_k_approx(img.R, k);
        out.G = rank_k_approx(img.G, k);
        out.B = rank_k_approx(img.B, k);

        save_ppm(out, output);

        std::cout << "Wrote " << output << " with rank " << k << "\n";
    }
    catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}
