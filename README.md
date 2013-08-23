This is an experimental and educational attempt at a Perceptual Hashing Library
written in C++ using OpenCV Mat objects as keys, and an abstract Datatype as a value.

If you have comments or suggestions on ways to improve this code, notice errors or have questions,
feel free to contact me. This is for education only, so feedback is greatly appreciated.

The Perceptual Hashing algorithm implemented is described here:
http://www.hackerfactor.com/blog/?/archives/432-Looks-Like-It.html

Current Todo's:
	- Handle Collisions
	- Implement a hash[image_object] = DataType style syntax for assignments of new hashes
	- Auto-resizing?
	- Possibly move getHash function into its own source file
	- Possibly create a new getHash function using Discrete Cosine Transformations for more flexibility
	- Pay attention to coding standards, spend time working on efficiency.