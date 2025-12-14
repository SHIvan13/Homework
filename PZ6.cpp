#include <iostream>

class Buffer{
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
            try{
                if (ind >= size) {
                    throw std::out_of_range("Error: out of bounds");
                }
                else if(v < -100 || v > 100){
                    throw std::invalid_argument("Value should be in range [-100, 100]");
                }
                p[ind] = v;
            } catch(const std::exception& e){
                std::cerr << e.what() << std::endl;
            }
        }

        int getValue(int ind){
            try{
                if (ind >= size || ind < 0) {
                    throw std::out_of_range("Error: out of bounds");
                }
                return p[ind];
            } catch(const std::exception& e){
                std::cerr << e.what() << std::endl;
            }
        }

        void toEnd(int v){
            try{
                if(v < -100 || v > 100){
                    throw std::invalid_argument("Value should be in range [-100, 100]");
                }
                
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
            } catch(const std::exception& e){
                std::cerr << e.what() << std::endl;
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

        ~Buffer(){
            delete[] p;
            std::cout << "Array deleted" << std::endl;
        }
};

int main(){
    Buffer arr(10);
    for (int i = 0; i < 10; i++){
        arr.setValue(i, i+1);
    }
    
   arr.getValue(13);
   arr.setValue(1, 101);
}