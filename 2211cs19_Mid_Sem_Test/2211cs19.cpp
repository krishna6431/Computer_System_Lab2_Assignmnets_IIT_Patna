//Name : Krishna Kant Verma
//Roll No: 2211cs19
//Mid Sem Exam Assignmnet

//All required important Libraries
#include<bits/stdc++.h>
//using namespace as a standard
using namespace std;

//creating class of pair to store both values and their corresponding indexes as values in problem b;
class pairArray{
//creating members of the class
public:
	long long first;
	long long second;
};

//creating custom comparator to use it in merge sort to sort in corresponding order of array 2
static bool customSortComparator(pairArray pair1 , pairArray pair2){
	if(pair1.second == pair2.second){
		return pair1.first <= pair2.first;
	}
	//return if index lesser than second index
	return pair1.second < pair2.second;
}

//merge array function to merge the two splitted array accordance to the arary 2.
void mergeArrays(pairArray arr1[], pairArray arr2[], long long n1,long long n2, pairArray arr3[],long long stillLeft,pairArray pairArr[])
{
    //creating variable i , j , k to iterated
	long long i = 0, j = 0, k = 0;
	//run till element out of bound
	while (i<n1 && j <n2)
	{
	    //compare if index of array A less than index of Array 2
		if (arr1[i].second < arr2[j].second){
			arr3[k++].first = arr1[i++].first;
		}
		else{
			arr3[k++].first = arr2[j++].first;
		}
			
	}
	//fill left out elements
	while (i < n1){
		arr3[k++].first = arr1[i++].first;
	}	
	
	//fill final left out elements
	if(stillLeft){
		sort(pairArr,pairArr+n2,customSortComparator);
	}	
	
	//fill left out elements
	while (j < n2){
		arr3[k++].first = arr2[j++].first;
	}
	
}

//a merge sort function to recursively split aray into two halves and finally merge them together
void mergeSort(pairArray pairArr[] , long long i , long long j){
    pairArray pairArr2[j];
	if(i==0){
		mergeArrays(pairArr,pairArr,i,j,pairArr2,1,pairArr);
		return;
	}
	//finding mid
	long long mid = (i+j)/2;
	//recursively calling left half
	mergeSort(pairArr , 0 , mid);
	//recursively calling right half
	mergeSort(pairArr,mid+1,j);
	//merge them together
	mergeArrays(pairArr,pairArr,i,j,pairArr2,0,pairArr);
}

//reconstructing the array as a form of pair of arrays which store the elements in respective format
void reConstruct(pairArray pairArr[], long long firstArr[] , long long secondArr[],long long n , long long m){
	for(int i = 0 ; i < n ; i++){
		pairArr[i].first = firstArr[i];
	}
	//creating frequencey array
	long long mapArr[1000000];
	for(int i = 0 ; i < 1000000 ; i++){
		mapArr[i] = 999999;
	}
	//fill the values in freqArr and values also
	for(int i = 0; i < m ; i++){
		mapArr[secondArr[i]] = i;
	}
	for(int i = 0 ; i < n ; i++){
		pairArr[i].second = mapArr[firstArr[i]];
	}
}
//function to print the values after applying custom sorting
void printSortedArray(pairArray pairArr[],long long n){
	cout << "Printing Sorted Array(Acc. to Pos of Array B): ";
	for(long long i = 0 ; i < n ; i++){
		cout << pairArr[i].first << " "; 
	}
	cout << endl;
}

//main function starts from here
int main(){
    
    //taking input size of array1
	cout << "Enter Size of Array 1: ";
	long long n;
	cin >> n;
	if(n > 99999){
		cout << "Please enter Value of N <= 99999" << endl;
		return 0;
	}
	//taking input first array
	cout << "Enter the Values in Array 1: ";
	long long firstArr[n];
	
	for(int i = 0 ; i < n ; i++){
		cin >> firstArr[i];
	}
	//taking input size of array 2
	cout << "Enter Size of Array 2: ";
	long long m; 
	cin >> m;
	if(m > 99999){
		cout << "Please enter Value of M <= 99999" << endl;
		return 0;
	}
	
	//taking input elements of array 2
	cout << "Enter the Values in Array 2: ";
	
	long long secondArr[m];
	for(int i = 0 ; i < m ; i++){
		cin >> secondArr[i];
	}
	
	//creating pair of array
	pairArray pairArr[n];
	
	reConstruct(pairArr,firstArr,secondArr,n,m);
    //calling merge sort
	mergeSort(pairArr,0,n);
	//calling printArray function to print array
	printSortedArray(pairArr,n);
	return 0;
}
//thank you so much
//Time Complexity : O(NLogN)

