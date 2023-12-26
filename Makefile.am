
#
# Makefile for the RAT project.
#
SUBDIRS = . tests man/man1

ACLOCAL_AMFLAGS=-I m4
AM_CPPFLAGS=-DHIDE_SOURCE_STRINGS

COMPAT_SOURCES = usleep.c snprintf.c usleep.h
COMMON_INCLUDES = \
	fatal_error.h \
	config_unix.h \
	config_win32.h \
	ratconf.h

lib_LTLIBRARIES = libuclaudio.la libuclcodec.la libuclsndfile.la
bin_PROGRAMS = rat-kill rat-media rat-ui rat

libuclaudio_la_SOURCES = \
	auddev_null.c \
	audio_fmt.c \
	audio_util.c \
	auddev_trans.c \
	auddev.c \
	auddev_alsa.h \
	auddev_atm.h \
	auddev.h \
	auddev_ixj.h \
	auddev_luigi.h \
	auddev_macosx.h \
	auddev_netbsd.h \
	auddev_newpcm.h \
	auddev_null.h \
	auddev_osprey.h \
	auddev_oss.h \
	auddev_pca.h \
	auddev_sgi.h \
	auddev_sparc.h \
	auddev_trans.h \
	auddev_win32.h \
	audio_fmt.h \
	audio.h \
	audio_types.h \
	audio_util.h
if ALSA
libuclaudio_la_SOURCES+=auddev_alsa.c
endif
libuclaudio_la_CFLAGS = $(UCLMMBASE_CFLAGS) $(ALSA_CFLAGS)
libuclaudio_la_LIBADD = $(UCLMMBASE_LIBS) $(ALSA_LIBS)

libuclcodec_la_SOURCES = codec.c codec_state.c codec_dvi.c		\
	codec_gsm.c codec_l8.c codec_l16.c codec_g711.c codec_g726.c	\
	codec_lpc.c codec_types.c codec_vdvi.c cx_g726.c cx_g726_16.c	\
	cx_g726_24.c cx_g726_32.c cx_g726_40.c cx_gsm.c cx_lpc.c	\
	cx_vdvi.c cx_dvi.c converter.c convert_util.c convert_extra.c	\
	convert_linear.c convert_sinc.c bitstream.c codec_wbs.c		\
	cx_wbs.c $(COMMON_INCLUDES) \
	bitstream.h \
	codec_acm.h \
	codec_compat.h \
	codec_dvi.h \
	codec_g711.h \
	codec_g726.h \
	codec_g728.h \
	codec_gsm.h \
	codec.h \
	codec_l16.h \
	codec_l8.h \
	codec_lpc.h \
	codec_state.h \
	codec_types.h \
	codec_vdvi.h \
	codec_wbs.h \
	cx_dvi.h \
	cx_g726.h \
	cx_gsm.h \
	cx_lpc.h \
	cx_vdvi.h \
	cx_wbs.h \
	converter.h \
	converter_types.h \
	convert_extra.h \
	convert_linear.h \
	convert_sinc.h \
	convert_util.h \
	convert_acm.h
libuclcodec_la_CFLAGS = $(UCLMMBASE_CFLAGS)
libuclcodec_la_LIBADD = $(UCLMMBASE_LIBS)

libuclsndfile_la_SOURCES = sndfile.c sndfile_au.c sndfile_raw.c sndfile_wav.c \
	$(COMMON_INCLUDES) \
	sndfile_au.h \
	sndfile.h \
	sndfile_raw.h \
	sndfile_types.h \
	sndfile_wav.h
libuclsndfile_la_CFLAGS = $(UCLMMBASE_CFLAGS)
libuclsndfile_la_LIBADD = $(UCLMMBASE_LIBS)

rat_SOURCES = main_control.c mbus_control.c codec_compat.c	\
	fatal_error.c process.c cmd_parser.c $(COMPAT_SOURCES) $(COMMON_INCLUDES) \
	cmd_parser.h \
	mbus_control.h \
	process.h
rat_CFLAGS = $(UCLMMBASE_CFLAGS)
rat_LDADD = $(UCLMMBASE_LIBS) libuclaudio.la libuclcodec.la libuclsndfile.la

rat_ui_SOURCES = ui_audiotool.c ui_transcoder.c tcltk.c mbus_ui.c	\
	main_ui.c fatal_error.c $(COMPAT_SOURCES) $(COMMON_INCLUDES) \
	mbus_ui.h \
	tcltk.h \
	transcoder.h \
	xbm/balloon.xbm \
	xbm/disk.xbm \
	xbm/left.xbm \
	xbm/pause.xbm \
	xbm/play.xbm \
	xbm/rat2.xbm \
	xbm/rat_med.xbm \
	xbm/rat_small.xbm \
	xbm/reception.xbm \
	xbm/rec.xbm \
	xbm/right.xbm \
	xbm/stop.xbm \
	xbm/ucl.xbm \
	xbm/waveform.xbm

rat_ui_CFLAGS = $(UCLMMBASE_CFLAGS) $(TK_CFLAGS)
rat_ui_LDADD = $(UCLMMBASE_LIBS) $(TK_LIBS)

rat_media_SOURCES = channel.c channel_types.c cc_vanilla.c cc_rdncy.c	\
	cc_layered.c render_3D.c repair.c ts.c playout.c net.c		\
	source.c session.c main_engine.c mbus_engine.c audio.c		\
	cushion.c mix.c parameters.c transmit.c playout_calc.c		\
	ui_send_rtp.c ui_send_audio.c ui_send_prefs.c ui_send_stats.c	\
	transcoder.c rtp_dump.c rtp_callback.c settings.c pdb.c		\
	pktbuf.c tonegen.c voxlet.c fatal_error.c $(COMPAT_SOURCES) $(COMMON_INCLUDES) \
	cc_layered.h \
	cc_rdncy.h \
	cc_vanilla.h \
	channel.h \
	channel_types.h \
	cushion.h \
	mbus_engine.h \
	mix.h \
	net.h \
	parameters.h \
	pdb.h \
	pktbuf.h \
	playout_calc.h \
	playout.h \
	render_3D.h \
	repair.h \
	repair_types.h \
	rtp_callback.h \
	rtp_dump.h \
	session.h \
	settings.h \
	source.h \
	tonegen.h \
	transcoder.h \
	transmit.h \
	ts.h \
	ui_send_audio.h \
	ui_send_prefs.h \
	ui_send_rtp.h \
	ui_send_stats.h \
	voxlet.h
nodist_rat_media_SOURCES = version.h
rat_media_CFLAGS = $(UCLMMBASE_CFLAGS)
rat_media_LDADD = $(UCLMMBASE_LIBS) libuclaudio.la libuclcodec.la libuclsndfile.la

rat_kill_SOURCES = rat-kill.c $(COMPAT_SOURCES)
rat_kill_CFLAGS = $(UCLMMBASE_CFLAGS)
rat_kill_LDADD = $(UCLMMBASE_LIBS)

BUILT_SOURCES = version.h
CLEANFILES = version.h

version.h: $(top_srcdir)/VERSION
	sed -e 's/.*/#define RAT_VERSION "v&"/' $? > $@

EXTRA_DIST = rat.spec.in VERSION README.md README.devices	\
	README.files README.gsm README.mbus README.playout		\
	README.timestamps COPYRIGHT

# Define the top-level directory for the RPM build
RPMBUILD ?= $(abs_top_builddir)/rpmbuild

# Define the name of the RPM spec file
specfile = $(PACKAGE_NAME).spec

.PHONY: rpmroot
rpmroot:
	mkdir -p $(RPMBUILD)/BUILD
	mkdir -p $(RPMBUILD)/RPMS
	mkdir -p $(RPMBUILD)/SOURCES
	mkdir -p $(RPMBUILD)/SPECS
	mkdir -p $(RPMBUILD)/SRPMS

.PHONY: rpm
rpm: dist-gzip rpmroot
	@cp $(distdir).tar.gz $(RPMBUILD)/SOURCES/
	@cp $(specfile) $(RPMBUILD)/SPECS/
	cd $(RPMBUILD) ; \
	rpmbuild -ba --define "_topdir $(RPMBUILD)" $(RPMBUILD)/SPECS/$(specfile)
