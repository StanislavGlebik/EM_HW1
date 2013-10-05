#include <stxxl.h>
#include <syscall.h>

using stxxl::syscall_file;
using stxxl::file;
using std::cout;
using std::endl;

void generateBigFile(const char * filename, int billions) {

    syscall_file file(filename, file::WRONLY);
    stxxl::vector<float> v_write (&file);

    for (int i = 0; i < billions * 1000000000; ++i) {
      v_write.push_back(1.0);
    }
}

int main(int argc, char * argv[]) {
  if (argc < 3) {
    cout << "No filename or size!" << endl;
  }
  
  generateBigFile(argv[1], atoi(argv[2]));
}
