#include <cstdio>  // for perror()
#include <cstdlib>  // for exit()
#include <cstring> // for memcpy()
#include <sys/mman.h>  // for shm_open(), mmap() etc.
#include <unistd.h>  // for ftruncate()
#include <sys/stat.h>  // for fstat()
#include <fcntl.h>  // for O_CREAT etc

int main(int argc, char* argv[]) {
    // Create a shared memory object
    int retVal = 0;
    auto fd = shm_open("dev_shm", O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd <= 0) {
        perror("shm_open failed");
        exit(1);
    }

    // Set its size, 1MB
    const char* msg = "Hello Shared Memory";
    size_t sz = strlen(msg)+1;  // +1 to include end of string terminator
    retVal = ftruncate(fd, sz);
    if (retVal != 0) {
        perror("ftruncate failed");
        exit(1);
    }

    // Create a shared memory segment using mmap()
    void* addr = mmap(NULL, sz, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
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

    // Write a string "Hello Shared Memory"
    memcpy(addr, msg, sz);

    // unmap shared memory
    retVal = munmap(addr, sz);
    if (retVal != 0) {
        perror("mmap failed()");
        exit(1);
    }

    // call shm_unlink
    // retVal = shm_unlink("dev_shm");
    // if (retVal != 0) {
    //     perror("shm_unlink failed()");
    //     exit(1);
    // }

    return 0;
}
