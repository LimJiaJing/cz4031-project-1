#include <fstream> //ifstream
#include <sstream>  // stringstream
#include <iostream> // cout, endl
#include <iomanip>  // ws
#include <map>      // map
using namespace std;

// https://www.w3schools.com/cpp/cpp_access_specifiers.asp
//https://reactgo.com/cpp-remove-first-n-characters/#:~:text=To%20remove%20the%20first%20n%20characters%20of%20a%20string%2C%20we,remove%20from%20the%20index%200.&text=Note%3A%20The%20erase()%20function,of%20creating%20a%20new%20string.
//https://stackoverflow.com/questions/67488565/getting-specific-data-from-a-text-file-in-c
//https://www.programiz.com/cpp-programming/string-float-conversion
class Record {
  private:    
    int R_name;
    int R_avgrating;
    int R_numofvotes;   
  public:
    void SetRecord(int name, int avgrating, int numofvotes);
    int getName() { return R_name; }
    int getAvgRating() { return R_avgrating; }
    int getNumOfVotes()  { return R_numofvotes; }
};
void Record::SetRecord(int name,int avgrating,int numofvotes)
{
    R_name = name;
    R_avgrating = avgrating;
    R_numofvotes = numofvotes;
}
int main() {
ifstream infile("data.tsv");
string line;
//int numofrecords=-1;
// while (getline(infile, line))
// {
//     numofrecords+=1;
// }
// cout<< numofrecords;

//actual number of record is 1070318
Record Records[5];

int count =0;
int skip_header = 0;
int record_number = 0;
while (getline(infile, line))
{
    if(skip_header ==0)
    {
        skip_header = 1;
        continue;
    }
    string string_component;
    stringstream record_string(line); 
    cout << "This is the line "<<line;
    cout << "\n";
    int name;
    int average_rating_int;
    int numofvotes;
    for (int i = 0; i < 3; i++) {
     getline(record_string, string_component, '\t'); 
     if(i==0)
     {
        string_component.erase(0,2);
        name = stoi(string_component);
     }
     else if (i==1)
     {
        float average_rating_float = stof(string_component);
        average_rating_int = static_cast<int>(average_rating_float*10);
     }
     else
     {
        numofvotes = stoi(string_component);
     }
    }
    Records[record_number].SetRecord(name,average_rating_int,numofvotes);
    cout << Records[record_number].getName() << "\t"<< Records[record_number].getAvgRating() << "\t"<< Records[record_number].getNumOfVotes() ;
    cout << "\n";
    record_number++;
    if(record_number>5)
    {
        break;
    }
}
infile.close();
return 0;
}