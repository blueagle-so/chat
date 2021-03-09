All:
	g++ chat.cpp -o chat  -fpermissive
	g++ chat1.cpp -o chat1 -fpermissive
	./chat &
	telnet 127.0.0.1 3111
	#./chat1
	#pkill chat
	#pkill chat1

push:
	git add .
	git commit -m "see web page"
	git push origin HEAD:remake
