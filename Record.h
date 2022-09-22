#ifndef DATE_H
#define DATE_H
#include <cstdint>

class Record {
  private:    
    int R_name;
    int16_t R_avgrating;
    int R_numofvotes;
  public:
    Record(int R_name, int16_t R_avgrating, int R_numofvotes);
    void SetRecord(int name, int16_t avgrating, int numofvotes);
    int getName() { return R_name; }
    int16_t getAvgRating() { return R_avgrating; }
    int getNumOfVotes()  { return R_numofvotes; }
};

#endif