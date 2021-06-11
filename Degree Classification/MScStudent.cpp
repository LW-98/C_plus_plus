#include "Module.h"
#include "Student.h"
#include <algorithm>

MScStudent::MScStudent(const string& uid) : Student(uid) {
  numOfCredits = 0;
}

bool MScStudent::addModule(string moduleCode, float mark) {
  if (MCT.find(moduleCode) == MCT.end()) {
    return false;
  } else {
    int credits = MCT.at(moduleCode);
    if (count(moduleList.begin(), moduleList.end(), moduleCode))
      return false;
    else if (numOfCredits + credits > MSC_YEAR_CREDIT)
      return false;
    else if (moduleCode[2] != '7')
      return false;
    else {
      moduleList.push_back(moduleCode);
      markList.push_back(mark);
      numOfCredits += credits;
    }
  }
  return true;
}

float MScStudent::cwa() const {
  float num = 0;
  int credits = 0;

  int count = 0;
  int counter = 0;
  for (string i: moduleList) {
    num += (float) markList[counter] * (float) MCT.at(moduleList[counter]);
    credits += MCT.at(moduleList[counter]);
    count++;
    counter++;
  }
  if (count == 0)
    return 0.0;
  return num/credits;
}

// To assign a degree class, I used the OCWA to split each 'if'.
// I sorted the OCWA by descending order, as it made it easier to check the conditions.
// E.g. if it was ascending, I would have to do intervals (0 <= OCWA <= 39.5) for every 'if' instead.
// This acts like a switch without 'break', meaning it will keep falling down the ladder until it meets conditions it satisfies.
string MScStudent::calcDegClass() const {
  float ocwa = cwa();
  float projectMark;
  int counter = 0;
  int credits = 0, narrowFailCredits = 0, badFailCredits = 0;
  
  for (string i: moduleList) { // Loop through modules
    credits += MCT.at(i); // Find total sum of credits
    if (markList[counter] < 49.5) { // Check if module has been failed badly or narrowly
      if (markList[counter] >= 39.5)
	narrowFailCredits += MCT.at(i);
      else
	badFailCredits += MCT.at(i);
    }
    if (MCT.at(i) == 60)
      projectMark = markList[counter]; // Find mark for project
    counter++;
  }

  if (credits != 180)
    return "INSUFFICIENT CREDITS";
  if ((ocwa >= 69.5 || calculateCreditsWithMark(69.5) >= 60) && projectMark > 69.5 && (narrowFailCredits == 0 && badFailCredits == 0))
    return "DISTINCTION";
  if ((ocwa >= 59.5 || calculateCreditsWithMark(59.5) >= 60) && projectMark >= 59.5 && narrowFailCredits <= 15 && badFailCredits == 0)
    return "MERIT";
  if ((ocwa >= 49.5 || calculateCreditsWithMark(49.5) >= 90) && projectMark >= 49.5 && narrowFailCredits <= 30 && badFailCredits == 0)
    return "PASS";
  return "FAIL";
}
