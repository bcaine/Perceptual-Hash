#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "pHash.h"

#include <iostream>

using namespace cv;
using namespace std;

/*	
	Author: Ben Caine
	Date: 8/22/2013

	These are some basic, ugly, purely functional tests for my pHash library to
	check that these functions work in the naive case 
*/
int main()
{
	Mat hawaii = imread("C://Development//testimages//hawaii.jpg");
	Mat senior = imread("C://Development//testimages/senior_pic.jpg");
	Mat hawaii_2 = imread("C://Development//testimages//hawaii.jpg");

	// Init a pHash of size 50 to take Strings as their datatype
	pHash<String> hash(50);
	
	//Put two test images in the hash
	hash.set(hawaii, "Headshot of me in Maui");
	hash.set(senior, "My High School Senior Yearbook picture... I look young...");

	//Output the strings we saved
	cout<<hash.get(hawaii)<<endl;
	cout<<hash.get(senior)<<endl;
	
	//Test that with a different image object of the same image, it pulls up the correct data
	cout<<hash[hawaii_2]<<endl;

	//Test getKeys, currently appears either broken or I need to learn to iterate through Maps
	Mat temp;
	map<unsigned int, Mat> key_vals = hash.getKeys();

	cin.get();
	cin.ignore();
	return 0;
}