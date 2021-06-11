#ifndef STUDENT_H_
#define STUDENT_H_

#include <iostream>
#include <string>
#include <vector>

using std::istream;
using std::ostream;
using std::string;
using std::vector;

const int MAX_MODULES = 20;
const int BSC_YEAR_CREDIT = 120;
const int MSC_YEAR_CREDIT = 180;

class Student {
public:
  
  // Constructor, with student's userid as argument
	Student(const string& uid);

	// Add this module to the student, with the given mark.

  // Adding module depends on if student is BSc or MSc, therefore needs to be pure virtual
	virtual bool addModule(string moduleCode, float mark) = 0;

	// Update the mark of this module.
	// If moduleCode does not appear in the MCT table,
	// or if the student have not already added this module,
	// do nothing and return false. Otherwise return true.
	bool updateMark(string moduleCode, float mark);

	// Returns the CWA of the student taking all the modules added so far into account.
	// For BSc students it is a weighted average of Y2 and Y3 CWAs.
	// For MSc students it is a weighted average of all modules.

  // Same as 'addModule()' - depends on if student is BSc or MSc therefore pure virtual
	virtual float cwa() const = 0;

	// Returns a string which is one of the degree classification results

  // Same as above
	virtual string calcDegClass() const = 0;

	// The input stream operator, that reads module code and marks from the
	// input stream and add it to the student as done by addModule().
	friend istream& operator>>(istream& is, Student& student);

	friend ostream& operator<<(ostream& os, const Student& student);
protected:
  string id;
  // Having seperate lists allows for easy lookups. I.e. the mark for the module at position 3 in moduleList is at position 3 in markList.
  vector<string> moduleList;
  vector<float> markList;

  // This method calculates the number of credits at a particular grade. E.g. how many credits where a mark of 70+ has been achieved.
  // Useful for calculating degree classification
  int calculateCreditsWithMark(float mark) const;
};

class BScStudent : public Student {
public:
  BScStudent(const string& uid);

  // CWA for Y2 and Y3 respectively.
  float y2cwa() const;
  float y3cwa() const;

  // Adding a module to an old BSc student is the same as adding one to a new student
  // Therefore method can stay here
  bool addModule(string moduleCode, float mark) override;

  // This method calculates the total credits of failed modules
  // Pure virtual because pass requirements are different for old and new students. Same for 'calcDegClass()'.
  virtual int calculateFailedCredits() const = 0;

  string calcDegClass() const override = 0;

protected:
  int creditsTwo; // Total credits for taken 2nd year modules
  int creditsThree; // Total credits for taken 3rd year modules
};

class BScStudentOld : public BScStudent {
public:
  BScStudentOld(const string& uid);

  float cwa() const override;
  string calcDegClass() const override;
  int calculateFailedCredits() const override;
};

class BScStudentNew : public BScStudent {
public:
  BScStudentNew(const string& uid);

  float cwa() const override;
  string calcDegClass() const override;
  int calculateFailedCredits() const override;

private:
  // Same as 'calculateCreditsWithMark()', but for year 3 only. Useful for degree classification for (only) new BScStudents.
  int calculateY3CreditsWithMark(float mark) const;
};

class MScStudent : public Student {
public:
  MScStudent(const string& uid);

  bool addModule(string moduleCode, float mark) override;
  string calcDegClass() const override;
  float cwa() const override;
  
private:
  int numOfCredits; // Total number of credits for taken modules
};

#endif
