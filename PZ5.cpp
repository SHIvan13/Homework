#include <iostream>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <sstream>

class Buffer{
    protected:
        int size;
        int* p;
    public:
        Buffer(int sz){
            p = new int[sz];
            size = sz;
            std::cout << "Array created" << std::endl;
        }

        Buffer(const Buffer& cp){
            p = new int[cp.size];
            size = cp.size;
            for (int i = 0; i < size; i++){
                p[i] = cp.p[i];
            }
            std::cout << "Array copied" << std::endl;
        }

        void print(){
            for (int i = 0; i < size; i++){
                std::cout << p[i] << " ";
            }
            std::cout << std::endl;
        }

        void setValue(int ind, int v){
            if (ind >= size) {
                std::cout << "Error: out of bounds" << std::endl;
            }
            else if(v < -100 || v > 100){
                std::cout << "Value should be in range [-100, 100]" << std::endl;
            }
            else{
                p[ind] = v;
            }
        }

        int getValue(int ind){
            if (ind >= size) {
                std::cout << "Error: out of bounds" << std::endl;
            }
            else{
                return p[ind];
            }
            return p[ind] = 0;
        }

        void toEnd(int v){
            if(v < -100 || v > 100){
                std::cout << "Value should be in range [-100, 100]" << std::endl;
            }
            else{
                int new_size = size + 1;
                int* new_p = new int[new_size];
                for (int i = 0; i < size; i++){
                    new_p[i] = p[i];
                }
                new_p[new_size-1] = v;
                delete[] p;
                p = new_p;
                size = new_size;
                std::cout << "Array resized, value setted" << std::endl;
            }
        }

        void add(const Buffer& b){
            if (b.size <= size){
                for (int i = 0; i < b.size; i++){
                    p[i] += b.p[i];
                }
            }
            else{
                for (int i = 0; i < size; i++){
                    p[i] += b.p[i];
                }
            }
            
            
            std::cout << "Arrays summed" << std::endl;
        }

        void sub(const Buffer& b){
            if (b.size <= size){
                for (int i = 0; i < b.size; i++){
                    p[i] -= b.p[i];
                }
            }
            else{
                for (int i = 0; i < size; i++){
                    p[i] -= b.p[i];
                }
            }

            std::cout << "Arrays subtructed" << std::endl;
        }

        virtual ~Buffer(){
            delete[] p;
            std::cout << "Array deleted" << std::endl;
        }
};

class ArrTxt : public Buffer{
    public:
        using Buffer::Buffer;

        void exportTxt(){
            auto now = std::chrono::system_clock::now();
            auto time_t = std::chrono::system_clock::to_time_t(now);

            std::stringstream filename;
            filename << std::put_time(std::localtime(&time_t), "%d_%m_%Y_%H_%M_%S") << ".txt";

            std::ofstream expFile(filename.str());

            if(expFile.is_open()){
                for (int i = 0; i < size; i++){
                    expFile << p[i] << std::endl;
                }
                std::cout << "Exported to txt file" << std::endl;
                expFile.close();
            }
            else{
                std::cerr << "Could not create export file";
            }

        }
};

class ArrCSV : public Buffer{
    public:
        using Buffer::Buffer;

        void exportCSV(){
            auto now = std::chrono::system_clock::now();
            auto time_t = std::chrono::system_clock::to_time_t(now);

            std::stringstream filename;
            filename << std::put_time(std::localtime(&time_t), "%d_%m_%Y_%H_%M_%S") << ".csv";

            std::ofstream expFile(filename.str());

            if(expFile.is_open()){
                for (int i = 0; i < size; i++){
                    expFile << p[i] << std::endl;
                }
                std::cout << "Exported to csv file" << std::endl;
                expFile.close();
            }
            else{
                std::cerr << "Could not create export file";
            }
        }
};


int main(){
    ArrCSV arr1(10);
    ArrTxt arr2(10);

    for (int i = 0; i < 10; i++){
        arr1.setValue(i, i+1);
        arr2.setValue(i, i+1);
    }

    arr1.exportCSV();
    arr2.exportTxt();
}