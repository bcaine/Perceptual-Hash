#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "phash.hpp"
#include <iostream>

using namespace cv;
using namespace std;

/*
	Author: Ben Caine
	Date: 8/22/2013

	These are some basic, ugly, purely functional tests for my phash
	library to check that these functions work in the naive case.

	Someday proper unit tests will be added...
*/
int main() {
    Mat lenna = imread("images/lenna.jpg");
    Mat cameraman = imread("images/cameraman.png");
    Mat lenna_copy = imread("images/lenna.jpg");

    // Init a pHash of size 50 to take strings as their datatype
    phash<string> hash(50);

    // Put two test images in the hash
    hash[lenna] = "Hello Lenna!";
    hash[cameraman] = "Hey, what's up Cameraman";

    // Test at(img) function too
    hash.at(cameraman) = "Changing things up, Mr. Cameraman";

    assert(hash.size() == 2);

    // Output the strings we saved
    cout<<hash.at(lenna)<<endl;
    cout<<hash.at(cameraman)<<endl;

    // Test that with a different image object of the same image,
    // it still pulls up the correct data
    cout<<hash[lenna_copy]<<endl;

    assert(hash[lenna] == hash[lenna_copy]);

    hash[lenna_copy] = "This is totally a different Lenna...";

    cout<<hash[lenna_copy]<<endl;

    cout<< "Hash Size: " << hash.size() << endl;
    cout<< "Hash Max Size: " << hash.max_size() << endl;

    cout<<"Erasing Lenna (Copy), size should be 1 now"<<endl;
    hash.erase(lenna_copy);

    assert(hash.size() == 1);

    cout<< "Hash Size: " << hash.size() << endl;

    cout<<"Clearing"<<endl;
    hash.clear();

    assert(hash.size() == 0);

    cout<<hash[lenna_copy]<<endl;

    cin.get();
    cin.ignore();
    return 0;
}
