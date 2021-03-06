

#include <iostream>
#include <fstream>
#include <inttypes.h>
#include <stdio.h>
#include <array>
#include <immintrin.h>


using namespace std;


uint64_t fileSize;
fstream file;


uint8_t CODE[20];
static uint8_t buf[0x7ffffff];

void encodeFile()
{

    uint16_t enOption;


    file.read((char*)buf, fileSize);



    for (uint64_t i = 0; i < 20; i++)
    {

        _rdseed16_step(&enOption);

        enOption = enOption % 9;


        switch (enOption)
        {
            case 0:
            {
                for (uint64_t j = 0; j < fileSize; j++)
                    buf[j] = ~buf[j];

                CODE[i] = 0;
                break;
            }


            case 1:
            {
                for (uint64_t j = 0; j < fileSize; j++)
                    buf[j]--;

                CODE[i] = 1;
                break;
            }


            case 2:
            {
                for (uint64_t j = 0; j < fileSize; j++)
                    buf[j]++;

                CODE[i] = 2;
                break;
            }

            case 3:
            {
                for (uint64_t j = 0; j < fileSize; j++)
                {
                    uint8_t tmp = buf[j];

                    _asm {
                        mov al, [tmp]
                        rol al, 1
                        mov tmp, al
                    }

                    buf[j] = tmp;
                }

                CODE[i] = 3;
                break;
        
            }

            case 4:
            {
                for (uint64_t j = 0; j < fileSize; j++)
                {
                    uint8_t tmp = buf[j];

                    _asm {
                        mov al, [tmp]
                        ror al, 1
                        mov tmp, al
                    }

                    buf[j] = tmp;
                }

                CODE[i] = 4;
                break;
            }
        
            case 5:
            {
                for (uint64_t j = 0; j < fileSize; j++)
                    buf[j] -= 0xa2;

                CODE[i] = 5;
                break;
            }

            case 6:
            {
                for (uint64_t j = 0; j < fileSize; j++)
                    buf[j] += 0xa2;

                CODE[i] = 6;
                break;
            }

            case 7:
            {
                for (uint64_t j = 0; j < fileSize; j++)
                {
                    uint8_t tmp = buf[j];

                    _asm {
                        mov al, [tmp]
                        rol al, 4
                        mov tmp, al
                    }

                    buf[j] = tmp;
                }

                CODE[i] = 7;
                break;
            }

            case 8:
            {
                for (uint64_t j = 0; j < fileSize; j++)
                {
                    uint8_t tmp = buf[j];

                    _asm {
                        mov al, [tmp]
                        ror al, 4
                        mov tmp, al
                    }

                    buf[j] = tmp;
                }

                CODE[i] = 8;
                break;
            }

            case 9:
            {
                for (uint64_t j = 0; j < fileSize; j++)
                {
                    uint8_t tmp = buf[j];

                    _asm {
                        mov al, [tmp]
                        rol al, 2
                        mov tmp, al
                    }

                    buf[j] = tmp;
                }

                CODE[i] = 9;
                break;
            }



        }
            
            


    }

    file.seekg(0, ios::beg);

}




int main(int argc, char** argv)
{

    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " file_to_encrypt" << endl;
    }

    cout << "WARNING REMEMBER YOUR CODE. IF YOU FORGET YOUR CODE YOU WONT DECRYPT YOUR FILE" << endl;

    file.open(argv[1], ios::in | ios::out | ios::binary);

    file.seekg(0, ios::end);

    fileSize = file.tellg();

    file.seekg(0, ios::beg);

    if (fileSize > 0x7ffffff)
        cout << dec << "This file doesnt support files larger than " << 0x7ffffff << " bytes" << endl;

    else
        cout << "SIZE OK" << endl;
  
    cout << "File size: " << fileSize << endl;

    cout << "Processing..." << endl;

    encodeFile();

    file.write((char*)buf, fileSize);


    cout << "your code to decode this file is:" << endl;

    for (int i = 19; i >= 0; i--)
        printf("%d", CODE[i]);

    cout << endl;


}
