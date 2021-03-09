All:
	g++ chat.cpp -o chat  -fpermissive
	g++ chat1.cpp -o chat1 -fpermissive
	./chat &
	./chat1
	#pkill chat

push:
	git add .
	git commit -m "see web page"
	git push origin HEAD:remake
