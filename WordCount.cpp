#include "WordCount.h"
#include <cctype>
#include <algorithm>
#include <sstream>

using namespace std;

WordCount::WordCount() {}

size_t WordCount::hash(std::string word) const {

  size_t accumulator = 0;
  for (size_t i = 0; i < word.size(); i++) {
    accumulator += word.at(i);
  }

  return accumulator % CAPACITY;
}

int WordCount::getTotalWords() const {

  int total = 0;
  for (size_t i = 0; i < CAPACITY; i++) {
    for (const auto& p : table[i]) total += p.second;
  }

  return total;
}

int WordCount::getNumUniqueWords() const {

  int total = 0;
  for (size_t i = 0; i < CAPACITY; i++) total += static_cast<int>(table[i].size());
  return total;

}

int WordCount::getWordCount(std::string word) const {

  string w = makeValidWord(word);
  if (w.empty()) return 0;
  size_t idx = hash(w);
  for (const auto& p : table[idx]) if (p.first == w) return p.second;

  return 0;

}

int WordCount::incrWordCount(std::string word) {

  string w = makeValidWord(word);
  if (w.empty()) return 0;
  size_t idx = hash(w);
  for (auto& p : table[idx]) {
    if (p.first == w) {
      p.second += 1;
      return p.second;
    }

  }

  table[idx].push_back({w,1});
  return 1;
}

int WordCount::decrWordCount(std::string word) {

  string w = makeValidWord(word);
  if (w.empty()) return -1;
  size_t idx = hash(w);

  for (size_t i = 0; i < table[idx].size(); i++) {

    if (table[idx][i].first == w) {
      if (table[idx][i].second > 1) {
        table[idx][i].second -= 1;
        return table[idx][i].second;
      } else {
        table[idx].erase(table[idx].begin()+i);
        return 0;
      }
    }
  }

  return -1;
}

bool WordCount::isWordChar(char c) {

  unsigned char uc = static_cast<unsigned char>(c);
  return std::isalpha(uc);
}

std::string WordCount::makeValidWord(std::string word) {

  std::string lower;
  lower.reserve(word.size());

  for (char c : word) {
    unsigned char uc = static_cast<unsigned char>(c);
    if (std::isalpha(uc)) lower.push_back(static_cast<char>(std::tolower(uc)));
    else if (c=='-' || c=='\'') lower.push_back(c);
  }

  while (!lower.empty() && !std::isalpha(static_cast<unsigned char>(lower.front()))) lower.erase(lower.begin());
  while (!lower.empty() && !std::isalpha(static_cast<unsigned char>(lower.back()))) lower.pop_back();

  if (lower.empty()) return lower;
  std::string out;
  out.reserve(lower.size());

  for (size_t i=0;i<lower.size();i++){
    char c=lower[i];
    if (c=='-' || c=='\'') {
      if (i==0 || i+1>=lower.size()) continue;
      if (!std::isalpha(static_cast<unsigned char>(lower[i-1]))) continue;
      if (!std::isalpha(static_cast<unsigned char>(lower[i+1]))) continue;
      out.push_back(c);
    } else if (std::isalpha(static_cast<unsigned char>(c))) {
      out.push_back(c);
    }
  }

  return out;
}

void WordCount::dumpWordsSortedByWord(std::ostream &out) const {
  std::vector<std::pair<std::string,int> > all;

  all.reserve(getNumUniqueWords());
  for (size_t i=0;i<CAPACITY;i++) for (std::vector<std::pair<std::string,int> >::const_iterator it=table[i].begin(); it!=table[i].end(); ++it) all.push_back(*it);

  std::sort(all.begin(), all.end(),
    [](const std::pair<std::string,int>& a, const std::pair<std::string,int>& b){
      return a.first > b.first;
    }
  );

  for (size_t i=0;i<all.size();++i) out << all[i].first << "," << all[i].second << "\n";

}


void WordCount::dumpWordsSortedByOccurence(std::ostream &out) const {

  std::vector<std::pair<std::string,int> > all;
  all.reserve(getNumUniqueWords());

  for (size_t i=0;i<CAPACITY;i++) for (std::vector<std::pair<std::string,int> >::const_iterator it=table[i].begin(); it!=table[i].end(); ++it) all.push_back(*it);

  std::sort(all.begin(), all.end(),
    [](const std::pair<std::string,int>& a, const std::pair<std::string,int>& b){
      if (a.second != b.second) return a.second < b.second;
      return a.first < b.first;
    }
  );

  for (size_t i=0;i<all.size();++i) out << all[i].first << "," << all[i].second << "\n";
}


void WordCount::addAllWords(std::string text) {
  std::istringstream iss(text);
  std::string token;
  while (iss >> token) incrWordCount(token);

}