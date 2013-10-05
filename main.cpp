#define BLOCK_SIZE 2 * 1024 * 1024

#include <stxxl.h>
#include <syscall.h>
#include <iostream>

using stxxl::syscall_file;
using stxxl::file;

using std::cin;
using std::cout;
using std::endl;

typedef stxxl::VECTOR_GENERATOR<float, 4, 8, BLOCK_SIZE>::result vector_type;
typedef vector_type::const_iterator c_it;


class Profiler
{
private:
    stxxl::stats_data StatsBefore;
    stxxl::stats_data StatsAfter;

public:
    Profiler()
    {
        StatsBefore = *stxxl::stats::get_instance();
    }

    ~Profiler()
    {
        StatsAfter = *stxxl::stats::get_instance();

        Dump();
    }

private:
    void Dump()
    {
        std::cerr << (StatsAfter - StatsBefore) << std::endl;
    }
};

void generateBigFile(const char * filename) {

    syscall_file file(filename, file::WRONLY);
    vector_type v_write (&file);
    
    for (int i = 0; i < 1000000000; ++i) {
      v_write.push_back(1.0);
    }
}

double getSum(const char * filename) {
  syscall_file file(filename, file::RDONLY);
  vector_type v_read(&file);
  double result = 0;

  for (c_it it = v_read.begin(); it != v_read.end(); ++it) {
    result += *it;
  }

  return result;
}

int main() {
  {
    Profiler profiler;
    cout << getSum("bigFile.txt") << endl;
  }
}

