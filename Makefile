
run: build
	@./build/app

build: clean
	@gcc app.c -o build/app

clean:
	@rm -rf build/
	@mkdir build/