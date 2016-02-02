# Perceptual Hashing
##### Header only library using OpenCV

This is an experimental and educational attempt at a Perceptual Hashing Library written in C++ using OpenCV Mat objects as keys, and an abstract Datatype as a value.

I hacked this together to play with perceptual hashing, so if you have comments, suggestions, notice errors, etc. feel free to contact me. I did this for education purposes only, so feedback is much appreciated.

The Perceptual Hashing algorithm implemented is described here:
http://www.hackerfactor.com/blog/?/archives/432-Looks-Like-It.html

Todo's:
	- Implement a hash[image_object] = DataType style syntax for assignments of new hashes
	- Auto-resizing?
	- Possibly create a new getHash function using Discrete Cosine Transformations for more flexibility
