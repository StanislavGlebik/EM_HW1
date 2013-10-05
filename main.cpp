#define BLOCK_SIZE_64KB 64 * 1024
#define BLOCK_SIZE_128KB 128 * 1024
#define BLOCK_SIZE_256KB 256 * 1024
#define BLOCK_SIZE_512KB 512 * 1024
#define BLOCK_SIZE_1MB 1024 * 1024
#define BLOCK_SIZE_2MB 2 * 1024 * 1024
#define BLOCK_SIZE_4MB 4 * 1024 * 1024
#define BLOCK_SIZE_8MB 8 * 1024 * 1024
#define BLOCK_SIZE_16MB 16 * 1024 * 1024
#define BLOCK_SIZE_32MB 32 * 1024 * 1024
#define BLOCK_SIZE_64MB 64 * 1024 * 1024
#define BLOCK_SIZE_128MB 128 * 1024 * 1024

#include <stxxl.h>
#include <syscall.h>
#include <iostream>

using stxxl::syscall_file;
using stxxl::file;

using std::cin;
using std::cout;
using std::endl;


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
    stxxl::vector<float> v_write (&file);

    for (int i = 0; i < 1000000000; ++i) {
      v_write.push_back(1.0);
    }
}

template <typename VectorType>
double getSum(const char * filename) {
  syscall_file file(filename, file::RDONLY);
  VectorType v_read(&file);
  double result = 0;
  typedef typename VectorType::const_iterator c_it;
  for (c_it it = v_read.begin(); it != v_read.end(); ++it) {
    result += *it;
  }

  return result;
}

int main() {
  #define RUN(SIZE) \
  {\
    typedef stxxl::VECTOR_GENERATOR<float, 4, 8, BLOCK_SIZE_##SIZE>::result vector_type;\
    cout << #SIZE << endl;\
    Profiler profiler;\
    cout << getSum<vector_type>("bigFile.txt") << endl;\
  }
  RUN(2MB)
  RUN(4MB)
  RUN(8MB)
  
}

