All:
	clang++ chat.cpp -o chat  -fpermissive
	#./chat &
	./chat


push:
	git add .
	git commit
	# -m "see web page https://blueagle-so.github.io"
	GIT_SSL_NO_VERIFY=true git push  -f	
