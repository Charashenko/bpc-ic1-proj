build: clean
	@gcc -ggdb -m32 -fno-stack-protector -z execstack -lcrypto app.c -o build/app
	@cp resources/store_template store

run: build
	@./build/app

clean:
	@rm -rf build/
	@mkdir build/
