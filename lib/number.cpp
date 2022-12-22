#include "number.h"

#include <algorithm>
#include <string>

//константы для типа uint_2022_t
const int ksize_of_cell = 1000000000;
const int ksize_of_array = 68;
//функция для подсчета размера числа
int u_size(uint2022_t uint2022){
    int s;
    for (int i = 67; i >= 0 && uint2022.a[i] == 0; i--){
        s = i;
    }
    return (s);
}

uint2022_t from_uint(uint32_t i) {
    uint2022_t res_uint2022;
    res_uint2022.a[0] = i % ksize_of_cell;
    res_uint2022.a[1] = i / ksize_of_cell;
    return res_uint2022;
}

uint2022_t from_string(const char* buff) {
    uint2022_t res_uint2022;
    std::string str(buff);
    std::string str_buff;
    int i;
    std::reverse(str.begin(), str.end());

    for(i = 0; i < str.size(); i+=9) {
        str_buff = str.substr(i, 9);
        if (str_buff == "000000000") {
            res_uint2022.a[i / 9] = 0;
        } else {
        std::reverse(str_buff.begin(),str_buff.end());
        res_uint2022.a[i / 9] = std::stoi(str_buff);
        }
    }
    return res_uint2022;
}

uint2022_t operator+(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t res_uint2022;
    int buff = 0; //переход через десяток
    long long sum;
    for(int i = 0; i < ksize_of_array; i++) {
        sum = lhs.a[i] + rhs.a[i] + buff;
        res_uint2022.a[i] = sum % ksize_of_cell;
        buff =  sum / ksize_of_cell;
    }
    //проверка
    if(buff == 1) throw("Size of uint2022_t must be no higher than 300 bytes");
    return res_uint2022;
}

uint2022_t operator-(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t res_uint;
    int buff = 0;
    long long diff;
    for(int i = 0; i < ksize_of_array; i++) {
        if (lhs.a[i] == 0 && buff == 1) {
            res_uint.a[i] = ksize_of_cell - buff - rhs.a[i];
        } else {
            diff = lhs.a[i] - rhs.a[i] - buff;
            if(lhs.a[i] >= rhs.a[i]){
                res_uint.a[i] = diff;
                buff = 0;
            }
            else{
                res_uint.a[i] = ksize_of_cell + diff;
                buff = 1;
            }
        }
    }
    //проверка, является ли число отрицательным
    if(buff != 0) throw("uint2022_t must be positive");
    return res_uint;
}

uint2022_t operator*(const uint2022_t& lhs, const uint2022_t& rhs) {
    int left_size = u_size(lhs);
    int right_size = u_size(rhs);
    uint2022_t res_uint;
    unsigned long long buff = 0;
    unsigned long long prod;
    unsigned long long rhs_num;
    for(int it1 = 0; it1 < left_size; it1++) {
        for (int it2 = 0; it2 < right_size || buff != 0; it2++) {
            rhs_num = rhs.a[it2];
            prod = rhs_num * lhs.a[it1] + buff + res_uint.a[it1 + it2];
            res_uint.a[it1 + it2] = static_cast<int>(prod % ksize_of_cell);
            buff = static_cast<int>(prod / ksize_of_cell);
        }
    }
    return res_uint;
}

bool operator==(const uint2022_t& lhs, const uint2022_t& rhs) {
    bool f = true;
    for(int i = 0; i < ksize_of_array; i++){
        if(lhs.a[i] != rhs.a[i]) f = false;
    }
    return f;
}

bool operator!=(const uint2022_t& lhs, const uint2022_t& rhs) {
    bool f = false;
    for(int i = 0; i < ksize_of_array; i++){
        if(lhs.a[i] != rhs.a[i]) f = true;
    }
    return f;
}

std::ostream& operator<<(std::ostream& stream, const uint2022_t& value) {
    std::string str_sell = std::to_string(value.a[u_size(value) - 1]);
    stream << str_sell;
    for (int i = u_size(value) - 2; i >= 0; i--) {
        std::string str_sell = std::to_string(value.a[i]);
        str_sell = std::to_string(value.a[i]);
        for (int j = 0; j < 9 - str_sell.size(); j++) {
            stream << 0;
        }
        stream << value.a[i];
    }
    return stream;
}
