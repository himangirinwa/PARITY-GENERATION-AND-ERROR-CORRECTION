//PARITY GENERATOR USING HAMMING CODE

#include<iostream>
#include<vector>
#include<cmath>
#include<string>
#include<algorithm>
using namespace std;


class ParityGenerator{
    private:
        vector<int> data_bits, final_data_bits;
        int numOfParityBits = 0, numOfdataBits = 0, totalBits=0;

    public:
        //constructor
        ParityGenerator(string data);

        //function to calculate number of parity bits
        int calNumOfParityBits(int data_length);

        //function to generate hamming code
        vector<int> generateParity();

};


//constructor
ParityGenerator::ParityGenerator(string data){

    //removing white spaces from the received data if any
    data.erase(remove(data.begin(), data.end(), ' '), data.end());

    //data is in binary format
    numOfdataBits = data.size();

    //getting data bits
    for(int i=0; i<numOfdataBits; i++){
        data_bits.push_back(data.at(i)- 48);
    }


}


//calculating number of redundant bits required
int ParityGenerator::calNumOfParityBits(int data_length){

    //calculating number of parity bits required using formula
    // 2^(no. of parity bits) >= (total number of data bits)+(no. of parity bits)+ 1
    // 2^p >= n + p + 1

    int p=1;
    int n = data_length;

    while(true){
        if(pow(2.0, p) >= p + n + 1)
            break;

        p++;
    }

    return p;
}


//generating hamming code
vector<int> ParityGenerator::generateParity(){

    //calculating total number of parity bits
    numOfParityBits = ParityGenerator::calNumOfParityBits(numOfdataBits);
    //total bits in final hamming code
    totalBits = numOfdataBits + numOfParityBits;

    //getting final data bits in place
    final_data_bits.resize(totalBits);

    //finding position of redundant bits
    for(int i=0; i<numOfParityBits; i++){
        // Placing -1 at redundant bit's place to identify it later
        final_data_bits[pow(2, i) - 1] = -1;
    }

    //placing message bits except for the position where there is -1
    int j=0;
    for(int i=0; i<totalBits; i++){
        if(final_data_bits[i] != -1){
            final_data_bits[i] = data_bits[j];
            j++;
        }
    }


    //generating hamming code
    for(int i=0; i<totalBits; i++){

        //searching for redundant bits
        if(final_data_bits[i] != -1)
            continue;

        int x = log2(i + 1);
        int set_count = 0;

        // Find message bits containing set bit at x'th position
        for (int j = i + 2; j <= totalBits; j++) {

            if (j & (1 << x)) {

                if (final_data_bits[j-1] == 1) {
                    set_count++;
                }
            }
        }


        // Generating hamming code for even parity
        if(set_count%2 == 0)
            final_data_bits[i] = 0;
        else
            final_data_bits[i] = 1;
    }

    return final_data_bits;
}


int main(){

    string data;

    cout << "ENTER DATA IN BINARY FORMAT : ";
    cin >> data;

    ParityGenerator parity(data);
    vector<int> code = parity.generateParity();

    cout << "\nGENERATED HAMMING CODE : " ;
    for(int i=0; i<code.size(); i++){
        cout << code[i];
    }


    return 0;
}
