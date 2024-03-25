#include "thread/Thread.h"
#include "mutex/Mutex.h"
#include "smart_pointer/SharedPtr.h"

int main() {
    SharedPtr<int> a = SharedPtr<int>(new int(4));
    SharedPtr<int> b = SharedPtr<int>(new int(10));
    b = a;
    return 0;
}