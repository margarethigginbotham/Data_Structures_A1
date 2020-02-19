//******************************************************************//
//   PROGRAM:    CSCI 340 Assignment 1                              //
//   PROGRAMMER: Margaret Higginbotham                              //
//   LOGON ID:   z1793581                                           //
//   DUE DATE:   January 29, 2018                                   //
//                                                                  //
//   FUNCTION:   Implements a linear search, binary search, and     //
//               print vector function                              //
//******************************************************************//

#include <algorithm>				//Include Statements
#include <vector>
#include <iostream>
#include <iomanip>

using std::cout;				//Using Statements
using std::endl;
using std::vector;
using std::setw;
using std::fixed;
using std::left;

const int DATA_SIZE = 200;			//Constants
const int DATA_RANGE = 200;
const int DATA_SEED = 9;
const int SEARCH_SEED = 17;
const int NO_ITEMS = 8;
const int ITEM_W = 4;

int linear_search(const vector<int>& inputVec, const int x, int& comparisons) {
  vector<int>::const_iterator iterator;		//Implementing iterator
  comparisons = 0;				//Starts comparisons at 0

  //Loops through vector until target is found
  for(iterator = inputVec.begin(); iterator != inputVec.end(); iterator++){
    comparisons++;				//Increment the comparisons
    if(*iterator == x)				//If iterator = x (Target)
      return x;					//Return x (Target)
  }

  return -1;					//Else return -1
}

int binary_search(const vector<int>& inputVec, const int x, int& comparisons) {
  comparisons = 0;				//Starts comparisons at 0

  int start = 0;				//Starts start at 0
  int end = inputVec.size() - 1;		//Starts end at the final value
  int middle = (end + start) / 2;		//Starts mid at the middle value

  while(start <= end){				//While start is less than end
    comparisons++;				//Increment comparisons

    if(x == inputVec[middle])			//If x (Target) is mid
      return x;					//Return mid

    else if(x < inputVec[middle]){		//Else if x (Target) is less than mid
      end = middle - 1;				//Split the vector in half to get a
      middle = (end + start) / 2;
    }						//new end

    else{
      start = middle + 1;			//Else Split the vector in half to get
      middle = (end + start) / 2;		//a new start
    }

    comparisons++;				//Increment comparisons
  }

  return -1;					//Otherwise it returns -1
}

void print_vec( const vector<int>& vec ){
  vector<int>::const_iterator iterator;		//Implementing iterator
  int count = 0;				//Implementing a counter

  for(iterator = vec.begin(); iterator != vec.end(); iterator++){
    //Ensures only a certain amount of numbers are displayed on each line
    if(count % NO_ITEMS == 0 && count != 0)
      cout << endl;
    cout << fixed << left << setw(ITEM_W) << *iterator;	//Print statement
    count++;					//Continues to print
  }

  cout << endl;
}

void average_comparisons(const vector<int>& inputVec, const vector<int>& searchVec, int (*search)(const vector<int>&, const int, int&) ) {
  int i, comparison = 0, sum = 0, found = 0;
  int res = 0;

  for (i = 0; i < (int)searchVec.size(); i++) {
    res = search( inputVec, searchVec[i], comparison );
    sum += comparison;

    if ( res >= 0 )
      found++;
  }

  cout << found << " numbers are found. The average number of comparisons in each search: " << (double)sum/(double)searchVec.size() << endl << endl;
}

int random_number() {
  return rand()%DATA_RANGE + 1;
}

int main () {
  // -------- create unique random numbers ------------------//
  vector<int> inputVec(DATA_SIZE);
  srand(DATA_SEED);
  generate(inputVec.begin(), inputVec.end(), random_number);
  sort(inputVec.begin(), inputVec.end());
  vector<int>::iterator it = unique(inputVec.begin(), inputVec.end());
  inputVec.resize( it - inputVec.begin() );
  random_shuffle( inputVec.begin(), inputVec.end() );

  cout << "------ Data source: " << inputVec.size() << " unique random numbers ------" << endl;
  print_vec(inputVec);
  cout << endl;

  // -------- create random numbers to be searched ---------//
  vector<int> searchVec(DATA_SIZE/2);
  srand(SEARCH_SEED);
  generate(searchVec.begin(), searchVec.end(), random_number);

  cout << "------ " << searchVec.size() << " random numbers to be searched: ------" << endl;
  print_vec(searchVec);
  cout << endl;

  cout << "Linear search: ";
  average_comparisons(inputVec, searchVec, linear_search);
  cout << "Binary search: ";
  average_comparisons(inputVec, searchVec, binary_search);

  sort(inputVec.begin(), inputVec.end());
  cout << "------- numbers in data source are now sorted ---------" << endl << endl;
  cout << "Linear search: ";
  average_comparisons(inputVec, searchVec, linear_search);
  cout << "Binary search: ";
  average_comparisons(inputVec, searchVec, binary_search);

return 0;

}
