#include <stdio.h>
#include <vector>
#include <algorithm>


int myfun(std::vector<int>& num) {
    return num.size();
}

void myfun2(void) {
    auto avec = std::vector<int>{1, 2, 3, 4, 5};
    auto avec_out = myfun(avec);
    printf("%d", avec_out);
}

int main(){
    myfun2();
}
