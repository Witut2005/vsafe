#include <iostream>
#include <fstream>
#include <inttypes.h>
#include <stdio.h>
#include <array>
#include <immintrin.h>

using namespace std;

fstream file;
uint64_t fileSize;
uint8_t tmp;
static char CODE[20];
static uint8_t buf[0x7ffffff];


int main(int argc, char** argv)
{

    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " file_to_decode" << endl;
    }

    file.open(argv[1], ios::binary | ios::in | ios::out);

    file.seekg(0, ios::end);
    fileSize = file.tellg();
    file.seekg(0, ios::beg);

    //buf = (uint8_t*)malloc(sizeof(uint8_t) * fileSize);

    if (fileSize > 0x7ffffff)
        cout << dec << "This file doesnt support files larger than " << 0x7ffffff << " bytes" << endl;

    else
        cout << "SIZE OK" << endl;

    file.read((char*)buf, fileSize);




    cout << "File size: " << fileSize << endl;
    cout << "type your code to decode your file:" << endl;
    cin >> CODE;
    
    cout << "Processing..." << endl;

    for (int i = 0; i < 20; i++)
    {
        if (!(CODE[i] >= '0' && CODE[i] < '4'))
        {
            cout << "bad code: " << CODE[i] << endl;
            exit(1);
        }
    }

    for (int i = 0; i < 20; i++)
    {
        if (CODE[i] == '0')
        {
            for (uint64_t j = 0; j < fileSize; j++)
                buf[j] = ~buf[j];
        }

        else if (CODE[i] == '1')
        {
            for (uint64_t j = 0; j < fileSize; j++)
                buf[j]++;
        }

        else if (CODE[i] == '2')
        {
            for (uint64_t j = 0; j < fileSize; j++)
                buf[j]--;
        }

        else if (CODE[i] == '3')
        {
            for (uint64_t j = 0; j < fileSize; j++)
            {
                tmp = buf[j];

                _asm {
                    mov al, [tmp]
                    ror al, 1
                    mov tmp, al
                }

                buf[j] = tmp;
            }
        }
    }

    file.seekg(0, ios::beg);
    file.write((char*)buf, fileSize);




}