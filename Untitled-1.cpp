#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;


const int MAX_PEOPLE = 30;

// structure definition
/* Write the definition of the Sales structure with the following fields:
- name, a string
- amount, and integer 
*/
struct Sales {
   string name;
   int amount;
};
// function prototypes
double detCommissionPercent(int);
double detAmountEarned(int);
/* Write your code here */
void insertSort(Sales list[], int noPeople);
void readSalesData(string filename, Sales list[], int &noPeople);
void showSalesData(Sales list[], int noPeople);
void saveSalesData(string filename, Sales list[], int noPeople);

int main()
{
    // array definition
    Sales list[MAX_PEOPLE];
    
    // other variables
    int noPeople;           // actual size of arrays
    string filename;
    
    // function calls
    cout << "Enter input file name: ";
    cin >> filename;
    readSalesData(filename + ".txt", list, noPeople);
    insertSort(list, noPeople);
    
    string answer;
    cout << "\nShow Report(Y/N)? ";
    cin >> answer;
    if (answer == "y" || answer == "Y")
        showSalesData(list, noPeople);
    saveSalesData(filename + "_report.txt", list, noPeople);
    return 0;
}

/* Write your code here. For each function definition write a short comment too,
as demonstrated in previous assignments */

/*~*~*~*~*~*~
 This function determines the commision percent based on the following table:
    Sales        Commission
   $0 - 1000        3%
 1001 - 5000        4.5%
 5001 - 10,000      5.25%
 over 10,000        6%
*~*/
double detCommissionPercent(int sales)
{
    double commission = 0;
    
  /* Write your code here */
    if (sales >= 0 && sales <= 1000) {
       commission = 3;
    } else if (sales >= 1001 && sales <= 5000) {
       commission = 4.5;
    } else if (sales >= 5001 && sales <= 10000) {
       commission = 5.25;
    } else {
       commission = 6;
    }
    return commission;
}

/*~*~*~*~*~*~
 This function determines the amount earned:
 it calls the detCommisionPercent) function.
*~*/
double detAmountEarned(int sales)
{
    double amountEarned = 0;
    /* Write your code here */
    double commission = detCommissionPercent(sales);
    amountEarned = commission * sales / 100.0;
    
    return amountEarned;
}

void readSalesData(string filename, Sales list[], int &noPeople) {
   ifstream inFile;
   inFile.open(filename);
   if (inFile) {
      int i = 0;
      while(inFile >> list[i].amount && i < MAX_PEOPLE) {
      getline(inFile, list[i].name, ';');
      i++;
      }
      noPeople = i;
      if (!inFile.eof()) {
         cout << "The array is full and there's more data in the file." << endl;
         cout << "The program ends here!" << endl;
         exit (EXIT_FAILURE);
      }
   } else {
      cout << "Error opening the input file: " << filename << "." << endl; 
      exit (EXIT_FAILURE);
   }
}

void insertSort(Sales list[], int noPeople) {
   for(int cur = 0; cur < noPeople; cur++){
      Sales hold = list[cur];
      int back = cur - 1;
      while (back >= 0 && hold.amount > list[back].amount){
         list[back + 1] = list[back];
         back--;
      }
      list[back + 1] = hold;
   }
}

void showSalesData(Sales list[], int noPeople) {
   cout << endl;
   cout << "Sorted List:" << endl;
   for (int i = 0; i < noPeople; i++) {
      double commission = detCommissionPercent(list[i].amount);
      double amountEarned = detAmountEarned(list[i].amount);
      cout << "$ " << setw(5) << list[i].amount << list[i].name << ", " <<
              commission << "% ($" << amountEarned << ")" << endl;
   }
}

void saveSalesData(string filename, Sales list[], int noPeople) {
   ofstream outfile;
   outfile.open(filename);
   outfile << "Sorted List:" << endl;
   for (int i = 0; i < noPeople; i++) {
      double commission = detCommissionPercent(list[i].amount);
      double amountEarned = detAmountEarned(list[i].amount);
      outfile << "$ " << setw(5) << list[i].amount << list[i].name << ", " <<
              commission << "% ($" << amountEarned << ")" << endl;
   }
   outfile.close();
   cout << "The Sales Report has been saved to \"" << filename << "\"" << endl;
}