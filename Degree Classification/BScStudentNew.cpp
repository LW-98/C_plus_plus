#include "Module.h"
#include "Student.h"
#include <algorithm>

BScStudentNew::BScStudentNew(const string& uid) : BScStudent(uid) {}

float BScStudentNew::cwa() const {
  return (this->y2cwa() * 0.33) + (this->y3cwa() * 0.67);
}

// To assign a degree class, I used the OCWA to split each 'if'. I then used nested if's to check for the other rules.
// I sorted the OCWA by descending order, as it made it easier to check the conditions.
// E.g. if it was ascending, I would have to do intervals (0 <= OCWA <= 39.5) for every 'if' instead.
// This acts like a switch without 'break', meaning it will keep falling down the ladder until it meets conditions it satisfies.
string BScStudentNew::calcDegClass() const {
  if (creditsTwo != 120 || creditsThree != 120)
    return "INSUFFICIENT CREDITS";
  
  int failedCredits = calculateFailedCredits();
  float ocwa = cwa();
  if (ocwa < 35 || failedCredits > 45) // Check for fail before anything else
    return "FAIL";
  else {
    if (ocwa >= 70 && failedCredits <= 30) // OCWA greater than 70
      return "FIRST CLASS";
    if (ocwa >= 68 && failedCredits <= 30 && calculateY3CreditsWithMark(70) >= 30) { // OCWA greater than 68
      if (calculateCreditsWithMark(70) >= 120)
	return "FIRST CLASS";
      if (calculateCreditsWithMark(70) >= 90 && calculateCreditsWithMark(68) >= 120)
	return "BORDERLINE FIRST CLASS";
    }
    if (ocwa >= 60) // OCWA greater than 60
      return "UPPER SECOND CLASS";
    if (ocwa >= 58 && calculateY3CreditsWithMark(60) >= 30) { // OCWA greater than 58
      if (calculateCreditsWithMark(60) >= 120)
	return "UPPER SECOND CLASS";
      if (calculateCreditsWithMark(60) >= 90 && calculateCreditsWithMark(58) >= 120)
	return "BORDERLINE UPPER SECOND CLASS";
    }
    if (ocwa >= 50) // OCWA greater than 50
      return "LOWER SECOND CLASS";
    if (ocwa >= 48 && calculateY3CreditsWithMark(50) >= 30) { // OCWA greater than 48
      if (calculateCreditsWithMark(50) >= 120)
	return "LOWER SECOND CLASS";
      if (calculateCreditsWithMark(50) >= 90 && calculateCreditsWithMark(48) >= 120)
	return "BORDERLINE LOWER SECOND CLASS";
    }
    if (ocwa >= 40) // OCWA greater than 40
      return "THIRD CLASS";
    if (ocwa >= 38 && calculateCreditsWithMark(40) >= 120 && calculateY3CreditsWithMark(40) >= 30) // OCWA greater than 38
      return "THIRD CLASS";
  }
  return "PASS";
}

int BScStudentNew::calculateY3CreditsWithMark(float mark) const {
  int counter = 0;
  int credits = 0;

  for (float i : markList) {
    if (i >= mark && moduleList[counter][2] == '3') {
      credits += MCT.at(moduleList[counter]);
    }
    counter++;
  }
  return credits;
}

int BScStudentNew:: calculateFailedCredits() const {
  int counter = 0;
  int failedCredits = 0;
  
  for (float i : markList) {
    if (i < 40) {
      failedCredits += MCT.at(moduleList[counter]);
    }
    counter++;
  }
  return failedCredits;
}