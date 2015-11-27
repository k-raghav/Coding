#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int main() {
    bool found = false;
    //bool available = true;
    static const int arr[] = {444, 994, 508, 72, 125, 299, 181, 238, 354, 223, 691, 249, 838, 890, 758, 675, 424, 199, 201, 788, 609, 582, 979, 259, 901, 371, 766, 759, 983, 728, 220, 16, 158, 822, 515, 488, 846, 321, 908, 469, 84, 460, 961, 285, 417, 142, 952, 626, 916, 247, 116, 975, 202, 734, 128, 312, 499, 274, 213, 208, 472, 265, 315, 335, 205, 784, 708, 681, 160, 448, 365, 165, 190, 693, 606, 226, 351, 241, 526, 311, 164, 98, 422, 363, 103, 747, 507, 669, 153, 856, 701, 319, 695, 52};
    vector<int> A(arr, arr + sizeof(arr) / sizeof(arr[0]) );
    for (int i = 0 ; i < A.size() ; i++ ) {
    	cout << A[i] << " ";
    }
    cout << endl;
    for(int i=A.size()-1; i>0; i--)
    {
        int j=i-1;
        while(j>=0)
        {
            if(A[i] < A[j])
            {
            	--j;
            }
            else
            {
            	found = true;
            	break;
            }
        }
        cout<<j << " " << A[j]<<endl;
        if(found)
        {
            int temp;
            temp = A[j];
            A[j] = A[i];
            A[i] = temp;
            sort(A.begin()+j+1, A.end());
            break;
        }
        
    }
    if(!found)
    {
        reverse(A.begin(), A.end());
    }
    for (int i = 0 ; i < A.size() ; i++ ) {
    	cout << A[i] << " ";
    }
    cout << endl;
}
