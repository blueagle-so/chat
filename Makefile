All:
	g++ chat.cpp -o chat  -fpermissive
	./chat &
	./chat
	pkill chat


push:
	git add .
	git commit
	# -m "see web page https://blueagle-so.github.io"
	git push
	#git push origin HEAD:remake
