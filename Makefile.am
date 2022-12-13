#
# Makefile for the RAT project.
#
ACLOCAL_AMFLAGS=-I m4
AM_CPPFLAGS=-DHIDE_SOURCE_STRINGS

COMPAT_SOURCES = usleep.c snprintf.c

lib_LTLIBRARIES = libuclaudio.la libuclcodec.la libuclsndfile.la
bin_PROGRAMS = rat-kill rat-media rat-ui rat

libuclaudio_la_SOURCES = auddev_null.c audio_fmt.c audio_util.c	\
	auddev_trans.c auddev.c
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
	cx_wbs.c
libuclcodec_la_CFLAGS = $(UCLMMBASE_CFLAGS)
libuclcodec_la_LIBADD = $(UCLMMBASE_LIBS)

libuclsndfile_la_SOURCES = sndfile.c sndfile_au.c sndfile_raw.c sndfile_wav.c
libuclsndfile_la_CFLAGS = $(UCLMMBASE_CFLAGS)
libuclsndfile_la_LIBADD = $(UCLMMBASE_LIBS)

rat_SOURCES = main_control.c mbus_control.c codec_compat.c	\
	fatal_error.c process.c cmd_parser.c $(COMPAT_SOURCES)
rat_CFLAGS = $(UCLMMBASE_CFLAGS)
rat_LDADD = $(UCLMMBASE_LIBS) libuclaudio.la libuclcodec.la libuclsndfile.la

rat_ui_SOURCES = ui_audiotool.c ui_transcoder.c tcltk.c mbus_ui.c	\
	main_ui.c fatal_error.c $(COMPAT_SOURCES)
rat_ui_CFLAGS = $(UCLMMBASE_CFLAGS) $(TK_CFLAGS)
rat_ui_LDADD = $(UCLMMBASE_LIBS) $(TK_LIBS)

rat_media_SOURCES = channel.c channel_types.c cc_vanilla.c cc_rdncy.c	\
	cc_layered.c render_3D.c repair.c ts.c playout.c net.c		\
	source.c session.c main_engine.c mbus_engine.c audio.c		\
	cushion.c mix.c parameters.c transmit.c playout_calc.c		\
	ui_send_rtp.c ui_send_audio.c ui_send_prefs.c ui_send_stats.c	\
	transcoder.c rtp_dump.c rtp_callback.c settings.c pdb.c		\
	pktbuf.c tonegen.c voxlet.c fatal_error.c $(COMPAT_SOURCES)
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
