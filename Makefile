SHELL := /bin/bash

.PHONY: setup test run fmt clean

setup:
	@echo "Running one-time setup..."
	@chmod +x src/hello.sh

test:
	@echo "Running tests (placeholder)..."
	@bash -n src/hello.sh
	@echo "✓ Shell script passes syntax check"

run:
	@./src/hello.sh

fmt:
	@echo "Format step (add black/go fmt/eslint/etc here)"

clean:
	@echo "Nothing to clean (yet)"
