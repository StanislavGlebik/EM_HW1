#define BLOCK_SIZE_4KB 4 * 1024
#define BLOCK_SIZE_8KB 8 * 1024
#define BLOCK_SIZE_16KB 16 * 1024
#define BLOCK_SIZE_32KB 32 * 1024
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
#define BLOCK_SIZE_34MB 34 * 1024 * 1024
#define BLOCK_SIZE_36MB 36 * 1024 * 1024
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
        std::cout << (StatsAfter - StatsBefore) << std::endl;
    }
};

template <typename VectorType>
double getSum(const char * filename) {
  syscall_file file(filename, file::RDONLY || file::DIRECT);
  VectorType v_read(&file);
  double result = 0;
  typedef typename VectorType::const_iterator c_it;
  for (c_it it = v_read.begin(); it != v_read.end(); ++it) {
    result += *it;
  }

  return result;
}

template <typename VectorType>
void getAllPrefixSums(const char * inputFilename, const char * outputFilename) {
  syscall_file inputFile(inputFilename, file::RDONLY || file::DIRECT);
  syscall_file outputFile(outputFilename, file::RDWR);

  VectorType v_read(&inputFile);
  VectorType v_write(&outputFile);

  double result = 0;
  typedef typename VectorType::const_iterator c_it;
  for (c_it it = v_read.begin(); it != v_read.end(); ++it) {
    result += *it;
    v_write.push_back(result);
  }

}

int main(int argc, char * argv[]) {
  if (argc < 2) {
    cout << "No filename!" << endl;
    return 0;
  }
  
  #define RUN(SIZE, BLOCKS_IN_PAGE) \
  {\
    typedef stxxl::VECTOR_GENERATOR<float, BLOCKS_IN_PAGE, 1, BLOCK_SIZE_##SIZE>::result vector_type;\
    cout << #SIZE << " Blocks in page: " << #BLOCKS_IN_PAGE << endl;\
    Profiler profiler;\
    cout << getSum<vector_type>(argv[1]) << endl;\
  }

 #define RUN_ALL_PREFIX_SUM(SIZE, BLOCKS_IN_PAGE) \
  {\
    typedef stxxl::VECTOR_GENERATOR<float, BLOCKS_IN_PAGE, 1, BLOCK_SIZE_##SIZE>::result vector_type;\
    cout << "Prefix sums: " << #SIZE << " Blocks in page: " << #BLOCKS_IN_PAGE << endl;\
    Profiler profiler;\
    getAllPrefixSums<vector_type>(argv[1], argv[2]);\
  }  

  RUN_ALL_PREFIX_SUM(4KB, 1)
  RUN_ALL_PREFIX_SUM(8KB, 1)
  RUN_ALL_PREFIX_SUM(16KB, 1)
  RUN_ALL_PREFIX_SUM(32KB, 1)
  RUN_ALL_PREFIX_SUM(64KB, 1)
  RUN_ALL_PREFIX_SUM(128KB, 1)
  RUN_ALL_PREFIX_SUM(256KB, 1)
  RUN_ALL_PREFIX_SUM(512KB, 1)
  RUN_ALL_PREFIX_SUM(1024KB, 1)
  RUN_ALL_PREFIX_SUM(2MB, 1)
  RUN_ALL_PREFIX_SUM(4MB, 1)
  RUN_ALL_PREFIX_SUM(8MB, 1)
  RUN_ALL_PREFIX_SUM(16MB, 1)
  RUN_ALL_PREFIX_SUM(32MB, 1)
  RUN_ALL_PREFIX_SUM(34MB, 1)
  RUN_ALL_PREFIX_SUM(36MB, 1)
  
  RUN(4KB, 1)
  RUN(8KB, 1)
  RUN(16KB, 1)
  RUN(32KB, 1)
  RUN(64KB, 1)
  RUN(128KB, 1)
  RUN(256KB, 1)
  RUN(512KB, 1)
  RUN(1MB, 1)
  RUN(2MB, 1)
  RUN(4MB, 1)
  RUN(8MB, 1)
  RUN(16MB, 1)
  RUN(32MB, 1)
  RUN(34MB, 1)
  RUN(36MB, 1)

  RUN(4KB, 2)
  RUN(8KB, 2)
  RUN(16KB, 2)
  RUN(32KB, 2)
  RUN(64KB, 2)
  RUN(128KB, 2)
  RUN(256KB, 2)
  RUN(512KB, 2)
  RUN(1MB, 2)
  RUN(2MB, 2)
  RUN(4MB, 2)
  RUN(8MB, 2)
  RUN(16MB, 2)
  RUN(32MB, 2)
  RUN(34MB, 2)
  RUN(36MB, 2)

  RUN(4KB, 3)
  RUN(8KB, 3)
  RUN(16KB, 3)
  RUN(32KB, 3)
  RUN(64KB, 3)
  RUN(128KB, 3)
  RUN(256KB, 3)
  RUN(512KB, 3)
  RUN(1MB, 3)
  RUN(2MB, 3)
  RUN(4MB, 3)
  RUN(8MB, 3)
  RUN(16MB, 3)
  RUN(32MB, 3)
  RUN(34MB, 3)
  RUN(36MB, 3)

  RUN(4KB, 4)
  RUN(8KB, 4)
  RUN(16KB, 4)
  RUN(32KB, 4)
  RUN(64KB, 4)
  RUN(128KB, 4)
  RUN(256KB, 4)
  RUN(512KB, 4)
  RUN(1MB, 4)
  RUN(2MB, 4)
  RUN(4MB, 4)
  RUN(8MB, 4)
  RUN(16MB, 4)
  RUN(32MB, 4)
  RUN(34MB, 4)
  RUN(36MB, 4)

}

