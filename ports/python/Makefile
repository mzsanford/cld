
# Change here for python3
PYTHON=python

build: setup.py pycldmodule.cc
	$(PYTHON) -u setup.py build

clean:
	$(PYTHON) -u setup.py clean

install: build
	sudo $(PYTHON) -u setup.py install

# Really? Can't test without install?
test: install
	$(PYTHON) -u test.py
