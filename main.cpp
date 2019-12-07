#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

class GenLinearData
{
public:
    GenLinearData(int low, int high, int size)
    : random_engine_{std::random_device{}()}
    , distribution_{low, high}

    {
        for (int j=0 ; j < size; j++)
        {
            numbers.push_back(std::vector<int>{j, 2*j+distribution_(random_engine_)});
        }
    }

    std::vector<std::vector<int>> operator()()
    {
        return numbers;
    }
private:
    std::mt19937 random_engine_;
    std::uniform_int_distribution<int> distribution_;
    std::vector<std::vector<int>> numbers;
};


class LinearRegression
{
public:
    LinearRegression(int epochs, std::vector<std::vector<int>> array)
    : epochs{epochs}
    , array{array}
    , weights{std::vector<double>{0.1, 0.1}}
    , lr{0.1}
    {
    }

    std::vector<double> compute_jac(std::vector<int> X)
        {
        double jac0 = (weights[0]*X[0]+weights[1]-X[1])*weights[0];
        double jac1 = (weights[0]*X[0]+weights[1]-X[1]);
        return std::vector<double>{jac0, jac1};
        }

    void fit()
    {
    for (int epoch=1; epoch<=epochs; epoch++)
         {
         for (std::vector<int> X : array)
               {
               std::vector<double> jac = compute_jac(X);
               weights[0] = weights[0] - jac[0]*weights[0]*lr/array.size() ;
               weights[1] = weights[1] - jac[1]*weights[1]*lr/array.size() ;
               }
         }
    }

    void forward()
    {

        for (std::vector<int> number : array)
        {
            std::cout << number[0] << "counter" << std::endl;
            std::cout << number[1] << std::endl;
            std::cout << weights[0]*number[0]+weights[1] << std::endl;
        }

    }

private:
    int epochs;
    std::vector<std::vector<int>> array;
    std::vector<double> weights;
    double lr;
};


int main()
{
    int epochs = 2;
    GenLinearData linear_data = GenLinearData(-5, 5, 500);
    LinearRegression lr = LinearRegression(epochs, linear_data());
    lr.fit();
    lr.forward();

}
