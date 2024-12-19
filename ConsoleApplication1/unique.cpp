#include <iostream>
#include <string>
#include <set>
#include <fstream>
#include <algorithm>
#include <vector>


enum Option {
  matching, 
  unique
};

std::string matchFlag("-m");
std::string uniqueFlag("-u");

//get the flag
Option getFlag(char* argv[]);
//read and process the file
std::set<std::string> readFile(char* filename);
//matching between n files
std::set<std::string> findMatches(std::vector<std::set<std::string>> files);
std::set<std::string> findUnique(std::vector<std::set<std::string>> files);


int main(int argc, char* argv[]) {
  std::cout << "working" << std::endl;

  Option result = getFlag(argv);
  std::vector<std::set<std::string>> files;

  for (int i = 2; i < argc; i++) {
    std::cout << "working in loop" << std::endl;
    std::set<std::string> file;
    file = readFile(argv[i]);
    files.push_back(file);
  }


  switch (result) {
    case matching:
      std::cout << "matching content" << std::endl;
      for (std::string setprint : findMatches(files)) {
        std::cout << setprint << std::endl;
      }
      break;
    case unique:
      std::cout << "unique content" << std::endl;
      for (std::string setprint : findUnique(files)) {
        std::cout << setprint << std::endl;
      }
      break;
    default:
      std::cout << "neither" << std::endl;
      break;
  }
}

Option getFlag(char* argv[]) {
  std::string flag = argv[1];
  if (flag == matchFlag) {
    //std::cout << "matching" << std::endl;
    return matching;
  }
  if (flag == uniqueFlag) {
    //std::cout << "unique" << std::endl;
    return unique;
  }
}

std::set<std::string> readFile(char* filename) {
  std::fstream file(filename);
  std::set<std::string> lines;
  std::string line;
  while (getline(file, line)) {
    lines.insert(line);
  }

  for (auto n : lines) {
    std::cout << n << std::endl;
  }

  file.close();
  return lines;
}

std::set<std::string> findMatches(std::vector<std::set<std::string>> files) {
  if (files.size() == 1) {
    return files[0];
  }

  std::set<std::string> matches = files[0];

  for (int i = 1; i < files.size(); i++) {
    std::vector<std::string> intersection{};
    std::set_intersection(matches.begin(), matches.end(),
                                    files[i].begin(), files[i].end(), std::back_inserter(intersection));

    matches.clear();
    matches.insert(intersection.begin(), intersection.end());
  }
  return matches;
} //set_symmetric_difference

std::set<std::string> findUnique(std::vector<std::set<std::string>> files) {
  if (files.size() == 1) {
    return files[0];
  }

  std::set<std::string> matches;
  std::set<std::string> masterMatchList;
  for (auto cur : files) {
    masterMatchList.insert(cur.begin(), cur.end());
  }
  std::vector<std::string> intersection{};
  for (int i = 0; i < files.size(); i++) {
    
    std::set_symmetric_difference(
        masterMatchList.begin(), masterMatchList.end(),
                                  files[i].begin(),
                          files[i].end(), std::back_inserter(intersection));
  }
  for (auto cur : intersection) {
    matches.insert(cur);
  }
  return matches;
}


