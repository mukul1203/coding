# Define the Python interpreter and package manager
PYTHON = python3
PIP = pip3

# Define the main Python script
MAIN_SCRIPT = main.py

# Define the test command (using pytest in this example)
TEST_CMD = pytest


# Rule to check if pytest is installed
.PHONY: check-pytest
check-pytest:
	@$(PYTHON) -m pytest --version >/dev/null 2>&1 || (echo "pytest not found, installing..."; $(PIP) install pytest)

# Default rule (run the main script)
.PHONY: run
run: check-pytest
	$(TEST_CMD) $(MAIN_SCRIPT)

# Clean rule (if you need it, for example to remove __pycache__)
.PHONY: clean
clean:
	find . -type d -name "__pycache__" -exec rm -rf {} +

# Phony targets
.PHONY: run clean
