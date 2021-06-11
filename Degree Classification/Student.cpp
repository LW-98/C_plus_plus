#include "Module.h"
#include "Student.h"
#include <vector>
#include <iostream>

using namespace std;

Student::Student(const string& uid) {
  id = uid;
}

bool Student::updateMark(string moduleCode, float mark) {
  if (MCT.find(moduleCode) == MCT.end()) { // Check if module exists
    return false;
  }

  int counter = 0;
  
  for (string i : moduleList) { // Loop through taken modules
    if (!i.compare(moduleCode)) { // If module is found, update corresponding value in markList
      markList[counter] = (float) mark;
      return true;
    }
    counter++;
  }
  return false;
}

istream& operator>>(istream& is, Student& student) {
  string line;
  
  while (getline(is, line)) {
    student.addModule(line.substr(0,6), stof(line.substr(7)));
  }
  return is;
}

ostream& operator<<(ostream& os, const Student& student) {
  os << student.id << '\t' << student.calcDegClass();
  return os;
}

int Student::calculateCreditsWithMark(float mark) const {
  int counter = 0;
  int credits = 0;

  for (float i : markList) {
    // Check if desired mark has been achieved.
    // Also make sure it is not the 60 credit MSc project - this is useful for calculating MSc degree classification as I need taught credits (not including the project)
    if (i >= mark && MCT.at(moduleList[counter]) != 60) {
      credits += MCT.at(moduleList[counter]);
    }
    counter++;
  }
  return credits;
}
