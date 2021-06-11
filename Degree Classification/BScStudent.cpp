#include "Module.h"
#include "Student.h"
#include <iostream>
#include <algorithm>
using namespace std;

BScStudent::BScStudent(const string& uid) : Student(uid) {
  creditsTwo = 0;
  creditsThree = 0;
}

bool BScStudent::addModule(string moduleCode, float mark) {
  if (MCT.find(moduleCode) == MCT.end()) { // Check if module exists
    return false;
  } else {
    int credits = MCT.at(moduleCode);
    if (count(moduleList.begin(), moduleList.end(), moduleCode)) // Check if module is already in moduleList (already been added)
      return false;
    else if (moduleCode[2] != '2' && moduleCode[2] != '3') // Check if module is not BSc
      return false;
    else {
      switch (moduleCode[2]) { // Check if module credits go over credit limit, if not then add to respective credit total
      case '2':
	if (creditsTwo + credits > BSC_YEAR_CREDIT)
	  return false;
	else
	  creditsTwo += credits;
	break;
      case '3':
	if (creditsThree + credits > BSC_YEAR_CREDIT)
	  return false;
	else
	  creditsThree += credits;
	break;
      }
      moduleList.push_back(moduleCode); // Add module to list of modules
      markList.push_back(mark); // Add mark to list of marks
    }
  }
  return true;
}

float BScStudent::y2cwa() const {
  float num = 0; // Numerator for CWA of a year
  int credits = 0; // Denominator for CWA of a year
  int counter = 0; // Counter for loop
  
  for (string i: moduleList) {
    if (i[2] == '2') { // Check if module is from second year
      num += (float) markList[counter] * (float) MCT.at(moduleList[counter]);
      credits += MCT.at(moduleList[counter]);
    }
    counter++;
  }
  if (credits == 0) // If credits = 0, then no second year modules
    return 0.0;
  return (float) num/ (float) credits;
}

// Same as above but third year
float BScStudent::y3cwa() const {
  float num = 0;
  int credits = 0;
  int counter = 0;
  
  for (string i: moduleList) {
    if (i[2] == '3') {
      num += (float) markList[counter] * (float) MCT.at(moduleList[counter]);
      credits += MCT.at(moduleList[counter]);
    }
    counter++;
  }
  if (credits == 0)
    return 0.0;
  return (float) num/ (float) credits;
}