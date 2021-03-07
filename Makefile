CC=gcc
C_STANDARD= -std=c99
COMPILER_WARNINGS= -Wno-missing-braces -Wall
# -LDirectory -lFile.a
LINKER_FLAGS= -LC:/Development/mingw32/i686-w64-mingw32/lib -lws2_32 

client:
	$(CC) client.c -o output/client.exe -O1 $(C_STANDARD) $(COMPILER_WARNINGS) $(INCLUDES) $(LINKER_FLAGS) 
server:
	$(CC) server.c -o output/server.exe -O1 $(C_STANDARD) $(COMPILER_WARNINGS) $(INCLUDES) $(LINKER_FLAGS) 
run_client: client
	./output/client.exe
run_server: server
	./output/server.exe
clean:
	rm -rf output/*.exe output/*.o *.exe *.o