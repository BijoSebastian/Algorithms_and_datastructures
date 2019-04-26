#include <iostream>
#include <vector>
#include <limits>
#include <cmath>
#include <ctime>
#include <cstdlib>

using std::vector;
using std::cin;
using std::cout;
using std::max;

//The naive implimentation O(n^2)
int MaxPairwiseProduct(vector <int>& numbers){
    int product = std::numeric_limits<int>::min();
    int len = numbers.size();
    for (int i = 0; i<len-1; ++i)
        for (int j = i+1; j<len; ++j)
            if (product < numbers[i]*numbers[j])
                product = numbers[i]*numbers[j];
    return product;
}

//The efficient implimentation O(2n)
int MaxPairwiseProduct2(vector <int>& numbers){
    int large1 = std::numeric_limits<int>::min();
    int large2 = large1;
    int len = numbers.size();
    int index1 = 0;
    for (int i = 0; i<len; ++i)
        if (large1 < numbers[i]){
            large1 = numbers[i];
            index1 = i;
        }
    for (int i = 0; i<len; ++i)
        if ((i != index1) && (large2 < numbers[i]))
            large2 = numbers[i];
    return large1*large2;
}

//The efficient implimentation O(1.5n)
int MaxPairwiseProduct3(vector <int>& numbers){
    int len = numbers.size();
    int temp =  0;
    for (int i =0; i< len-1; i+=2){
        if (numbers[i]< numbers[i+1]){
            temp = numbers[i+1];
            numbers[i+1] = numbers[i];
            numbers[i] = temp;
        }
    }
    int large1 = std::numeric_limits<int>::min();
    int large2 = large1;
    int index1 = 0;
    for (int i = 0; i<len; i+=2)
        if (numbers[i]> large1){
            large1 = numbers[i];
            index1 = i;
        }
    for (int i = 0; i< len; i+=2)
        if ((numbers[i]> large2) && (i != index1))
            large2 = numbers[i];
    if (index1+1!=len) //This is the trick, it could only be one of these two (second term in the pair having the largest or second largest in the set)
        if (large2<numbers[index1+1])
            large2 = numbers[index1+1];
    return large1*large2;
}

int stress_test(int N, int M){
    srand(time(0));
    int flag_noerror = 0;
    for (int trial_no = 0; trial_no<5000; ++trial_no){
        int n = (rand()% N) + 2; //random number between 2 and N
        vector<int> numbers(n);
        for (int i = 0; i < n; ++i)
            numbers[i] = (rand()% M); //random number between 0 and M
        int64_t res1,res2;
        res1 = MaxPairwiseProduct(numbers);
        res2 = MaxPairwiseProduct3(numbers);
        if (res1 != res2){
            cout<<"error \nGround truth :"<<res1<<" Output :"<<res2<<"\n";
            flag_noerror = 1;
            cout<<"Number of inputs :"<<n<<"\n";
            cout<<"Numbers :";
            for (int i = 0; i < n; ++i)
                cout<<numbers[i]<<" ";
            cout<<"\n";
            break;
        }
    }
    return flag_noerror;
}

int main() {
    int64_t n;
    cout<<"Performing stress test...";
    if (stress_test(10, 50) == 0){
        cout<<"Cleared\n";
        cout<<"Enter number of inputs(at least 2 please): ";
        cin>>n;
        if (n>=2){
            vector<int> numbers(n);
            cout<<"Enter "<<n<<" inputs \n";
            for (int i = 0; i < n; ++i)
                cin>>numbers[i];
            int64_t product = MaxPairwiseProduct3(numbers);
            cout<<"Max product: "<<product << "\n";
        }
        else
            cout<<"Try again.";
    }
    else
        cout<<"Stress test failed";
    return 0;
}
