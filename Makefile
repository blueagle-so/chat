All:
	g++ chat.cpp -o chat  -fpermissive
	./chat &
	./chat
	pkill chat


push:
	git add .
	git commit -m "see web page"
	git push origin HEAD:remake
