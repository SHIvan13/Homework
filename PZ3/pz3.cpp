#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <cmath>
#include <dirent.h>

struct PGMImage {
    int width, height, maxVal;
    std::vector<std::vector<int>> pixels;
};

struct FilterResult {
    std::string filename;
    double mse;
    double psnr;
    double mae;
};

void addNoise(PGMImage* img, int num){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distVal(0, img->maxVal);
    std::uniform_int_distribution<> distX(0, img->width);
    std::uniform_int_distribution<> distY(0, img->height);

    for (int i = 0; i < num; i++) {
        int row = distY(gen) % img->height;
        int col = distX(gen) % img->width;
        img->pixels[row][col] = distVal(gen);
    }
}

void createImg(const PGMImage& img, const std::string& name){
    std::ofstream file(name);
    if (file.is_open()){
        file << "P2" << std::endl << img.width << " " << img.height << std::endl << img.maxVal << std::endl;
        for(int i = 0; i < img.height; i++){
            for(int j = 0; j < img.width; j++){
                file << img.pixels[i][j] << std::endl;
            }
        }
        file.close();
    }
    else{
        throw std::runtime_error("Cannot open the file");
    }
}

int filter(PGMImage* img, int size){
    if (size % 2 == 0){
        std::cout << "Size must be odd";
        return 0;
    }

    int padding = size / 2; 

    for(int i = padding; i < img->height - padding; i++){
        for(int j = padding; j < img->width - padding; j++){
            std::vector<int> window;
            for (int ki = -padding; ki <= padding; ki++) {
                for (int kj = -padding; kj <= padding; kj++) {
                    window.push_back(img->pixels[i + ki][j + kj]);
                }
            }
            std::sort(window.begin(), window.end());
            img->pixels[i][j] = window[window.size() / 2];
        }
    }
    return 0;
}

PGMImage readPGM(const std::string& filename) {
    std::ifstream file(filename);
    PGMImage img;
    
    std::string s;
    std::getline(file, s); // P2
    std::getline(file, s); // comment
    
    file >> img.width >> img.height >> img.maxVal;
    img.pixels.resize(img.height, std::vector<int>(img.width));

    for(int i = 0; i < img.height; i++){
        for(int j = 0; j < img.width; j++){
            file >> img.pixels[i][j];
        }
    }
    file.close();
    return img;
}

FilterResult compareImages(const PGMImage& orig, const PGMImage& filtered, const std::string& name) {
    FilterResult result;
    result.filename = name;
    
    double mse = 0.0;
    double mae = 0.0;
    int totalPixels = orig.width * orig.height;
    
    for(int i = 0; i < orig.height; i++){
        for(int j = 0; j < orig.width; j++){
            double diff = orig.pixels[i][j] - filtered.pixels[i][j];
            mse += diff * diff;
            mae += std::abs(diff);
        }
    }
    
    result.mse = mse / totalPixels;
    result.mae = mae / totalPixels;
    result.psnr = 20 * log10(255.0 / sqrt(result.mse));
    
    return result;
}

void saveResultsToCSV(const std::vector<FilterResult>& results, const std::string& filename) {
    std::ofstream file(filename);
    file << "Filename,MSE,PSNR,MAE\n";
    for(const auto& result : results) {
        file << result.filename << "," << result.mse << "," << result.psnr << "," << result.mae << "\n";
    }
    file.close();
}

std::vector<std::string> getPGMFiles(const std::string& directory) {
    std::vector<std::string> files;
    DIR* dir = opendir(directory.c_str());
    if (dir == nullptr) return files;
    
    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        std::string filename = entry->d_name;
        if (filename.length() > 4 && filename.substr(filename.length() - 4) == ".pgm") {
            files.push_back(filename);
        }
    }
    closedir(dir);
    return files;
}

int main(){
    std::string inputDir = "input_images";
    std::string outputDir = "output_images";
    
    // Create output directory
    system(("mkdir -p " + outputDir).c_str());
    
    std::vector<FilterResult> results;
    
    std::vector<std::string> pgmFiles = getPGMFiles(inputDir);
    
    for(const auto& filename : pgmFiles) {
        std::string inputPath = inputDir + "/" + filename;
        
        // Read original image
        PGMImage original = readPGM(inputPath);
        
        // Create working copy
        PGMImage noisy = original;
        
        // Add noise and filter
        addNoise(&noisy, 50000);
        filter(&noisy, 3);
        
        // Save filtered image
        std::string outputPath = outputDir + "/filtered_" + filename;
        createImg(noisy, outputPath);
        
        // Compare with original
        FilterResult result = compareImages(original, noisy, filename);
        results.push_back(result);
        
        std::cout << "Processed: " << filename << std::endl;
    }
    
    // Save results to CSV
    saveResultsToCSV(results, "filter_results.csv");
    
    std::cout << "Processing complete. Results saved to filter_results.csv" << std::endl;
    
    return 0;
}