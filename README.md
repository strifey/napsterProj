napsterProj Kyle Kelly
======================

Networking I project 1

To use: run make in the base directory. This will compile the server and client with gcc. Tested on gcc-4.6.3 and gcc-4.7.

	First, start the server. It takes no arguments

	Next, run the client. It takes arguments in this format:
		./nClient COMMAND IP PORT [FILE] [-d]

		Commands supported: addfile, listfiles
		Leave FILE and -d off when running listfiles
		addfile requires FILE but -d is optional
