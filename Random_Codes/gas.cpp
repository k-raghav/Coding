#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int main() {
    static const int arr[] = {204, 918, 18, 17, 35, 739, 913, 14, 76, 555, 333, 535, 653, 667, 52, 987, 422, 553, 599, 765, 494, 298, 16, 285, 272, 485, 989, 627, 422, 399, 258, 959, 475, 983, 535, 699, 663, 152, 606, 406, 173, 671, 559, 594, 531, 824, 898, 884, 491, 193, 315, 652, 799, 979, 890, 916, 331, 77, 650, 996, 367, 86, 767, 542, 858, 796, 264, 64, 513, 955, 669, 694, 382, 711, 710, 962, 854, 784, 299, 606, 655, 517, 376, 764, 998, 244, 896, 725, 218, 663, 965, 660, 803, 881, 482, 505, 336, 279};
    vector<int> gas(arr, arr + sizeof(arr) / sizeof(arr[0]) );
    static const int arr1[] = {273, 790, 131, 367, 914, 140, 727, 41, 628, 594, 725, 289, 205, 496, 290, 743, 363, 412, 644, 232, 173, 8, 787, 673, 798, 938, 510, 832, 495, 866, 628, 184, 654, 296, 734, 587, 142, 350, 870, 583, 825, 511, 184, 770, 173, 486, 41, 681, 82, 532, 570, 71, 934, 56, 524, 432, 307, 796, 622, 640, 705, 498, 109, 519, 616, 875, 895, 244, 688, 283, 49, 946, 313, 717, 819, 427, 845, 514, 809, 422, 233, 753, 176, 35, 76, 968, 836, 876, 551, 398, 12, 151, 910, 606, 932, 580, 795, 187};
    vector<int> cost(arr1, arr1 + sizeof(arr1) / sizeof(arr1[0]) );
    cout << "30 " << gas[30] << " " << cost[30] << endl;
    cout << "31 " << gas[31] << " " << cost[31] << endl;
    cout << "32 " << gas[32] << " " << cost[32] << endl;
    int n = gas.size();
    int looper = 0;
    while(looper < n) {
        int start = -1;
        for(int i = looper ; i < n ;i++) {
            if(gas[i] >= cost[i])  {
                start = i;
		break;
            }
        }
        if(start == -1) return start;
    	cout << looper << " " << start << " " << gas[start] << " " << cost[start] << endl;
        int current_fuel = gas[start] - cost[start];
        int count = 1;
        for(int i = 1 ; i < n ; i++) {
            int index = (i + start) % n;
            current_fuel += gas[index];
            if(current_fuel < cost[index]) {
                break;
            }
            else {
                count++;
                current_fuel -= cost[index];
            }
        }
        if(count == n) return start;
        looper++;
    }
    return -1;
}
