RUSTC = ~/.cargo/bin/rustc
FILE = main.rs
BIN = main
OBJDIR = build
# Create the build directory if it doesn't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

run:
	$(RUSTC) $(FILE) -o $(OBJDIR)/$(BIN) && $(OBJDIR)/$(BIN)

clean:
	rm -f $(OBJDIR)/$(BIN)
