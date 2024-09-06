#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct YearData {
    int year;
    double growthPrice;
    double inflation;
};

vector<YearData> readCSV(const string& filename) {
    vector<YearData> data;
    ifstream file(filename);
    string line;

    
    getline(file, line);

    while (getline(file, line)) {
        istringstream iss(line);
        string token;
        YearData yearData;

        getline(iss, token, '-');
        yearData.year = stoi(token);

        getline(iss, token, ',');
        getline(iss, token, ',');
        yearData.growthPrice = stod(token);

        getline(iss, token, ',');
        yearData.inflation = stod(token);

        data.push_back(yearData);

    }

    return data;
}

double calculateSellingPrice(const vector<YearData>& data, int purchaseYear, int sellingYear, double initialPrice) {
    double sellingPrice = initialPrice;
    for (const auto& yearData : data) {
        if (yearData.year > purchaseYear && yearData.year <= sellingYear) {
            sellingPrice *= (1 + (yearData.growthPrice - yearData.inflation) / 100);
        }
        // cout<<sellingPrice<<"*******"<<yearData.year<<endl;
    }
    return sellingPrice;
}



double calculateLTCG(double sellingPrice, double initialPrice) {
    double ans = sellingPrice - initialPrice;
    if (ans < 0){return 0;}
    return (sellingPrice - initialPrice) * 0.20;
}

int main() {
    string filename = "C:\\Users\\Krishna\\Desktop\\OOPD_A1\\price-inflation.csv";
    int purchaseYear = 2010;
    int sellingYear;
    double initialPrice = 5000000; // Rs 50 lakhs
    
    cout << "Enter the year of selling (between 2011 and 2030): ";
    cin >> sellingYear;

    if (sellingYear <= purchaseYear || sellingYear > 2030) {
        cout << "Invalid selling year. Please enter a year between 2011 and 2030." << endl;
        return 1;
    }
    
    vector<YearData> data = readCSV(filename);
    double sellingPrice = calculateSellingPrice(data, purchaseYear, sellingYear, initialPrice);
    double LTCG = calculateLTCG(sellingPrice, initialPrice);
    
    cout << fixed << setprecision(2);
    cout << "Estimated Selling Price: Rs " << sellingPrice << endl;
    cout << "Long-term Capital Gains Tax (LTCG): Rs " << LTCG << endl;
    
    return 0;
}
