#include "Module.h"
#include "Student.h"
#include <cstring>
#include <algorithm>

using namespace std;

BScStudentOld::BScStudentOld(const string& uid) : BScStudent(uid) {}

float BScStudentOld::cwa() const {
  return (this->y2cwa() * 0.4) + (this->y3cwa() * 0.6);
}

// To assign a degree class, I used the OCWA to split each 'if'. I then used nested if's to check for the other rules.
// I sorted the OCWA by descending order, as it made it easier to check the conditions.
// E.g. if it was ascending, I would have to do intervals (0 <= OCWA <= 39.5) for every 'if' instead.
// This acts like a switch without 'break', meaning it will keep falling down the ladder until it meets conditions it satisfies.
string BScStudentOld::calcDegClass() const {
  if (creditsTwo != 120 || creditsThree != 120)
    return "INSUFFICIENT CREDITS";
  
  int failedCredits = calculateFailedCredits();
  float ocwa = cwa();
  
  if (ocwa < 34.5 || failedCredits >= 50) // Check for fail before anything else
    return "FAIL";
  else {
    if (ocwa >= 69.5) { // OCWA greater than 69.5
      return "FIRST CLASS";
    }
    if (ocwa >= 66.5) { // OCWA greater than 66.5
      if (calculateCreditsWithMark(69.5) >= 120)
	if (failedCredits < 40)
	  return "FIRST CLASS";
	else
	  return "UPPER SECOND CLASS";
      else
	if (calculateCreditsWithMark(69.5) >= 90 && calculateCreditsWithMark(67.5) >= 120 && failedCredits < 40)
	  return "BORDERLINE FIRST CLASS";
    }
    if (ocwa >= 59.5) { // OCWA greater than 59.5
      return "UPPER SECOND CLASS";
    }
    if (ocwa >= 56.5) { // OCWA greater than 56.5
      if (calculateCreditsWithMark(59.5) >= 120) {
	if (failedCredits < 40)
	  return "UPPER SECOND CLASS";
	else
	  return "LOWER SECOND CLASS";
      } else
	if (calculateCreditsWithMark(59.5) >= 90 && calculateCreditsWithMark(57.5) >= 120 && failedCredits < 40)
	  return "BORDERLINE UPPER SECOND CLASS";
    }
    if (ocwa >= 49.5) { // OCWA greater than 49.5
      return "LOWER SECOND CLASS";
    }
    if (ocwa >= 46.5) { // OCWA greater than 46.5
      if (calculateCreditsWithMark(49.5) >= 120)
	if (failedCredits < 40)
	  return "LOWER SECOND CLASS";
	else
	  return "THIRD CLASS";
      else
	if (calculateCreditsWithMark(49.5) >= 90 && calculateCreditsWithMark(47.5) >= 120 && failedCredits < 40)
	  return "BORDERLINE LOWER SECOND CLASS";
    }
    if (ocwa >= 39.5) // OCWA greater than 39.5
      return "THIRD CLASS";
    return "PASS";
  }
}

int BScStudentOld:: calculateFailedCredits() const {
  int counter = 0;
  int failedCredits = 0;
  
  for (float i : markList) {
    if (i < 34.5) {
      failedCredits += MCT.at(moduleList[counter]);
    } else if (i >= 34.5 && i < 39.5) {
      switch (moduleList[counter][2]) {
      case '2':
	if (this->y2cwa() < 39.5)
	  failedCredits += MCT.at(moduleList[counter]);
	break;
      case '3':
	if (this->y3cwa() < 39.5)
	  failedCredits += MCT.at(moduleList[counter]);
	break;
      }
    }
    counter++;
  }
  return failedCredits;
}
