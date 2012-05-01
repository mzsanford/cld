
build:
	python -u setup.py build

install: build
	sudo python -u setup.py install

# Really? Can't test without install?
test: install
	python -u test.py
