#pragma once
#include <iostream>
#include <algorithm>

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

class ChildBuff : public Buffer{
    public:
        using Buffer::Buffer;

        int average(){
            int summa = 0;
            for (int i = 0; i < size; i++){
                summa += p[i];
            }
            return summa / size;
        }
        
        double mid(){
            int temp[size];

            for (int i = 0; i < size; i++){
                temp[i] = p[i];
            }

            std::sort(temp, temp + size);

            for (int i = 0; i < size; i++){
                    std::cout << temp[i] << " ";
                } 
            std::cout << std::endl;

            if (size % 2 == 0){
                return static_cast<double>(temp[(size / 2) - 1] + temp[(size / 2)]) / 2.0;
            }
            else{
                return static_cast<double>(temp[((size + 1) / 2) - 1]);
            }
        }

        int minVal(){
            int temp[size];

            for (int i = 0; i < size; i++){
                temp[i] = p[i];
            }

            return *std::min_element(temp, temp + size);
        }

        int maxVal(){
            int temp[size];

            for (int i = 0; i < size; i++){
                temp[i] = p[i];
            }

            return *std::max_element(temp, temp + size);
        }
};
