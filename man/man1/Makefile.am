# Define the section number for the man page (e.g., 1 for user commands)
man_MANS = rat.1

# Install the man page into the correct man directory
install-data-hook:
	mkdir -p $(DESTDIR)$(mandir)/man1
	$(INSTALL_DATA) $(man_MANS) $(DESTDIR)$(mandir)/man1/

# Clean-up rule for the man page
uninstall-hook:
	rm -f $(DESTDIR)$(mandir)/man1/$(man_MANS)

EXTRA_DIST = $(man_MANS)
