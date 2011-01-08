#include <iostream>

#include <llvm/Target/TargetSelect.h>

using namespace std;
using namespace llvm;

int main(int argc, char** argv)
{
    cout << "Hello, cruel world!" << endl;
    InitializeNativeTarget();
    cout << "Goodbye." << endl;
    return 0;
}