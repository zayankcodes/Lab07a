#include "WordCount.h"
#include "tddFuncs.h"
#include <sstream>
#include <string>
using namespace std;

int main() {
  WordCount wc;

  wc.addAllWords("Sentence is a sentence");
  ASSERT_EQUALS(4, wc.getTotalWords());
  ASSERT_EQUALS(3, wc.getNumUniqueWords());
  ASSERT_EQUALS(2, wc.getWordCount("sentence"));
  ASSERT_EQUALS(1, wc.getWordCount("is"));
  ASSERT_EQUALS(1, wc.getWordCount("a"));

  std::ostringstream byWord;
  wc.dumpWordsSortedByWord(byWord);
  std::istringstream r1(byWord.str());
  std::string line;
  std::getline(r1,line); ASSERT_EQUALS(std::string("sentence,2"), line);
  std::getline(r1,line); ASSERT_EQUALS(std::string("is,1"), line);
  std::getline(r1,line); ASSERT_EQUALS(std::string("a,1"), line);

  wc.addAllWords("fun fun");
  ASSERT_EQUALS(6, wc.getTotalWords());
  ASSERT_EQUALS(4, wc.getNumUniqueWords());

  std::ostringstream byOcc;
  wc.dumpWordsSortedByOccurence(byOcc);
  std::istringstream r2(byOcc.str());
  std::getline(r2,line); ASSERT_EQUALS(std::string("a,1"), line);
  std::getline(r2,line); ASSERT_EQUALS(std::string("is,1"), line);
  std::getline(r2,line); ASSERT_EQUALS(std::string("fun,2"), line);
  std::getline(r2,line); ASSERT_EQUALS(std::string("sentence,2"), line);

  return 0;
}
