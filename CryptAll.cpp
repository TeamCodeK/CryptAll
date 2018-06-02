#include <string>
#include <iostream>
#include <fstream>
#include <vector>

bool encrypt(std::string file_path, int key) {
  std::ifstream read(file_path, std::ios_base::binary);
  if (read) {
    read.seekg(0, std::ios::end);
    int length = read.tellg();
    read.seekg(0, std::ios::beg);
    char* buffer = new char[length];
    read.read(buffer, length);

    std::ofstream write(file_path, std::ios_base::binary);
    buffer[0] += key;
    write.clear();
    write.write(buffer, length);
    write.close();

    delete[] buffer;
    return true;
  }
  return false;
}

bool decrypt(std::string file_path, int key) {
  std::ifstream read(file_path, std::ios_base::binary);
  if (read) {
    read.seekg(0, std::ios::end);
    int length = read.tellg();
    read.seekg(0, std::ios::beg);
    char* buffer = new char[length];
    read.read(buffer, length);

    std::ofstream write(file_path, std::ios::binary);
    buffer[0] -= key;
    write.clear();
    write.write(buffer, length);
    write.close();

    delete[] buffer;
    return true;
  }
  return false;
}

auto split(std::string files_string, char str) {
  std::vector<std::string> o;
  std::string s;
  for (int i = 0; i != files_string.length(); i++) {
    if (files_string[i] == str) {
      o.push_back(s);
      s = "";
    }
    else {
      s.push_back(files_string[i]);
    }
  }
  return o;
}

std::string readFile(std::string file) {
  std::ifstream read(file, std::ios::in);
  if (read) {
    read.seekg(0, std::ios::end);
    int length = read.tellg();
    read.seekg(0, std::ios::beg);
    char *buffer = new char[length];
    read.read(buffer, length);
    read.close();
    std::string buf;
    buf = buffer;
    return buf;
  }
  return NULL;
}

int main() {
	std::string files_string;
  //files_string = "Huy";
  system("ls > ls.txt");
  files_string = readFile("ls.txt");
  system("rm ls.txt");
  std::cout << files_string << std::endl;
  auto f = split(files_string, '\n');
  // for (auto it = f.begin(); it != f.end(); it++) {
  //     std::cout << "it " + *it << std::endl;
  // }

  std::string a = "";
  int key;
  std::cout << ">> [e] Encrypt or [d] Decrypt: ";
  std::cin >> a;
  std::cout << ">> Key: ";
  std::cin >> key;
  if (a == "e") {
    std::cout << "Encrypt... \n";
    for (std::vector<std::string>::iterator it = f.begin(); it != f.end(); ++it) {
      bool en = encrypt(*it, key);
      if (en == true) {
        std::cout << "Encrypt " + *it + "\n";
      }
      else {
        std::cout << "Fail to encrypt " + *it + "\n";
      }
    }
  }
  else if (a == "d") {
    std::cout << "Decrypt...";
    for (std::vector<std::string>::iterator it = f.begin(); it != f.end(); ++it) {

      bool de = decrypt(*it, key);
      if (de == true) {
        std::cout << "Decrypt " + *it + "\n";
      }
      else {
        std::cout << "Fail to decrypt " + *it + "\n";
      }
    }
  }
}
