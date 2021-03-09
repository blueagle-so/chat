All:
	g++ chat.cpp -o chat  -fpermissive
	g++ chat1.cpp -o chat1 -fpermissive
	./chat &
	./chat1
	#pkill chat
