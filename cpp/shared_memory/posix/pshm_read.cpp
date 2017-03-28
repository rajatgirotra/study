#include <cstdio>  // for perror()
#include <cstdlib>  // for exit()
#include <cstring> // for memcpy()
#include <iostream>
#include <sys/mman.h>  // for shm_open(), mmap() etc.
#include <unistd.h>  // for ftruncate()
#include <sys/stat.h>  // for fstat()
#include <fcntl.h>  // for O_CREAT etc
using namespace std;

int main(int argc, char* argv[]) {
    // Open an existing shared memory object
    int retVal = 0;
    auto fd = shm_open("dev_shm", O_RDWR, S_IRUSR);
    if (fd <= 0) {
        perror("shm_open failed");
        exit(1);
    }

    // Get its size
    struct stat buf;
    retVal = fstat(fd, &buf);
    if (retVal != 0) {
        perror("fstat failed");
        exit(1);
    }

    // Create a shared memory segment using mmap()
    void* addr = mmap(NULL, buf.st_size, PROT_READ, MAP_SHARED, fd, 0);
    if (addr == nullptr) {
        perror("mmap failed()");
        exit(1);
    }

    // Close file descriptor as we longer need it
    retVal = close(fd);
    if (retVal != 0) {
        perror("mmap failed()");
        exit(1);
    }

    // Read from shared memory
    char msg[100] {};
    memcpy(msg, addr, buf.st_size);
    cout << "Read from SHM: " << msg << endl;

    // unmap shared memory
    retVal = munmap(addr, buf.st_size);
    if (retVal != 0) {
        perror("mmap failed()");
        exit(1);
    }

    // call shm_unlink
    retVal = shm_unlink("dev_shm");
    if (retVal != 0) {
        perror("shm_unlink failed()");
        exit(1);
    }

    return 0;
}
