//Error corrector using Hamming Code
//single bit error correction

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;

class ErrorCorrector {

private:
    vector<int> data_bits;
    int total_bits;

public:
    ErrorCorrector(string data);

    int calNumOfParityBits();

    int binaryToDecimal(string n);

    //utility function to check data
    void checker();
};

//constructor
ErrorCorrector::ErrorCorrector(string data){
    //removing white spaces from the received data if any
    data.erase(remove(data.begin(), data.end(), ' '), data.end());

    total_bits = data.size();

    //getting data bits
    for(int i=0; i<total_bits; i++){
        data_bits.push_back(data.at(i)- 48);
    }
}


//calculating number of redundant bits required
int ErrorCorrector::calNumOfParityBits(){

    //calculating number of parity bits required using formula
    // 2^(no. of parity bits) >= (total number of data bits)+(no. of parity bits)+ 1
    // 2^p >= n + p + 1

    int p=1;

    while(true){
        if(pow(2.0, p) >= total_bits + 1)
            break;

        p++;
    }

    return p;
}


int ErrorCorrector::binaryToDecimal(string parity){
    string num = parity;
    int dec_value = 0;

    // Initializing base value to 1, i.e 2^0
    int base = 1;

    int len = num.length();
    for (int i = len - 1; i >= 0; i--) {
        if (num[i] == '1')
            dec_value += base;
        base = base * 2;
    }

    return dec_value;
}


void ErrorCorrector::checker(){

    int parity_bits = calNumOfParityBits();
    string calculated_parity = "";
    for(int i=0; i<parity_bits; i++){
        int set_count = 0;
        int parity;
        // Find message bits containing set bit at i'th position
        for (int j = 1; j <= total_bits; j++) {

            if (j & (1 << i)) {

                if (data_bits[j-1] == 1)
                    set_count++;

            }
        }

        //checking for even parity
        if(set_count%2 == 0){
            parity = 0;
            calculated_parity.append(to_string(parity));
        }
        else{
            parity = 1;
            calculated_parity.append(to_string(parity));
        }
    }
    //getting position pointed by redundant bits
    int position = binaryToDecimal(calculated_parity);

    if(position == 0)
        cout << "\n\t\tNO SINGLE BIT ERROR EXIST IN THE RECEIVED DATA!";
    else
        cout << "\n\nBIT NUMBER " << position << " IS CORRUPTED!";
}





int main() {

    string received_data;
    cout << "ENTER DATA TO BE CHECKED IN BINARY FORMAT : ";
    cin >> received_data;


    ErrorCorrector e(received_data);
    e.checker();
    return 0;
}
