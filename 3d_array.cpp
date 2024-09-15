#pragma once
#include <fstream>

using namespace std;

namespace
{
    constexpr int I = 20;
    constexpr int J = 30;
    constexpr int K = 40;
    const double D = 1.0;
    const double h1 = 1.0, h2 = 1.0, h3 = 1.0;
    const double tau = 0.01;

    void read_file(double data[I][J][K])
    {
        ifstream fin("input.raw", ios_base::binary);
        fin.read((char*)&data[0][0][0], sizeof(double) * I * J * K);
        fin.close();
    }

    void write_file(double data[I][J][K])
    {
        ofstream fout("output_3d.raw", ios_base::binary);
        fout.write((char*)&data[0][0][0], sizeof(double) * I * J * K);
        fout.close();
    }

    void copy(double arr_adress[I][J][K], double arr_source[I][J][K])
    {
        for (int i = 0; i < I; ++i)
        {
            for (int j = 0; j < J; ++j)
            {
                for (int k = 0; k < K; ++k)
                {
                    arr_adress[i][j][k] = arr_source[i][j][k];
                }
            }
        }

    }
}

void array3D()
{
    double data[I][J][K] = { {{0}} };
    double temp[I][J][K] = { {{0}} };

    read_file(data);

    for (int n = 0; n < 100; ++n)
    {
        for (int i = 1; i < I - 1; ++i)
        {
            for (int j = 1; j < J - 1; ++j)
            {
                for (int k = 1; k < K - 1; ++k)
                {
                    const double part1 = (data[i + 1][j][k] - 2.0 * data[i][j][k] + data[i - 1][j][k]) / (h1 * h1);
                    const double part2 = (data[i][j + 1][k] - 2.0 * data[i][j][k] + data[i][j - 1][k]) / (h2 * h2);
                    const double part3 = (data[i][j][k + 1] - 2.0 * data[i][j][k] + data[i][j][k - 1]) / (h3 * h3);
                    temp[i][j][k] = D * tau * (part1 + part2 + part3) + data[i][j][k];
                }
            }
        }
        copy(data, temp);
    }

    write_file(data);
}