#
# Makefile for the tests
#
ACLOCAL_AMFLAGS=-I m4
AM_CPPFLAGS = $(all_includes) -DHIDE_SOURCE_STRINGS $(UCLMMBASE_CFLAGS)

noinst_PROGRAMS = test_convert rtone test_pktbuf test_rdncy test_3d	\
		native test_codecs test_ts test_repair			\
		test_audio_fmt_convert probeaudio

test_convert_SOURCES = test_convert.c
test_convert_LDADD = $(UCLMMBASE_LIBS) $(top_builddir)/libuclaudio.la	\
	$(top_builddir)/libuclcodec.la					\
	$(top_builddir)/libuclsndfile.la
test_convert_LDFLAGS = $(all_libraries)

rtone_SOURCES = rtone.c
rtone_LDADD =  $(UCLMMBASE_LIBS) $(top_builddir)/libuclaudio.la	\
	$(top_builddir)/libuclcodec.la					\
	$(top_builddir)/libuclsndfile.la
rtone_LDFLAGS = $(all_libraries)

test_pktbuf_SOURCES = test_pktbuf.c $(top_srcdir)/pktbuf.c $(top_srcdir)/playout.c $(top_srcdir)/ts.c
test_pktbuf_LDADD =  $(UCLMMBASE_LIBS) $(top_builddir)/libuclaudio.la	\
	$(top_builddir)/libuclcodec.la					\
	$(top_builddir)/libuclsndfile.la
test_pktbuf_LDFLAGS = $(all_libraries)

test_repair_SOURCES = test_repair.c $(top_srcdir)/repair.c
test_repair_LDADD =  $(UCLMMBASE_LIBS) $(top_builddir)/libuclaudio.la	\
	$(top_builddir)/libuclcodec.la					\
	$(top_builddir)/libuclsndfile.la
test_repair_LDFLAGS = $(all_libraries)

test_rdncy_SOURCES = test_rdncy.c $(top_srcdir)/cc_rdncy.c $(top_srcdir)/pktbuf.c $(top_srcdir)/playout.c $(top_srcdir)/ts.c $(top_srcdir)/channel_types.c
test_rdncy_LDADD =  $(UCLMMBASE_LIBS) $(top_builddir)/libuclaudio.la	\
	$(top_builddir)/libuclcodec.la					\
	$(top_builddir)/libuclsndfile.la
test_rdncy_LDFLAGS = $(all_libraries)

test_3d_SOURCES = test_3d.c $(top_srcdir)/render_3D.c
test_3d_LDADD =  $(UCLMMBASE_LIBS) $(top_builddir)/libuclaudio.la	\
	$(top_builddir)/libuclcodec.la					\
	$(top_builddir)/libuclsndfile.la
test_3d_LDFLAGS = $(all_libraries)

native_SOURCES = native.c
native_LDADD =  $(UCLMMBASE_LIBS) $(top_builddir)/libuclaudio.la	\
	$(top_builddir)/libuclcodec.la					\
	$(top_builddir)/libuclsndfile.la
native_LDFLAGS = $(all_libraries)

test_codecs_SOURCES = test_codecs.c
test_codecs_LDADD =  $(UCLMMBASE_LIBS) $(top_builddir)/libuclaudio.la	\
	$(top_builddir)/libuclcodec.la					\
	$(top_builddir)/libuclsndfile.la
test_codecs_LDFLAGS = $(all_libraries)

test_ts_SOURCES = test_ts.c $(top_srcdir)/ts.c
test_ts_LDADD =  $(UCLMMBASE_LIBS) $(top_builddir)/libuclaudio.la	\
	$(top_builddir)/libuclcodec.la					\
	$(top_builddir)/libuclsndfile.la
test_ts_LDFLAGS = $(all_libraries)

test_audio_fmt_convert_SOURCES = test_audio_fmt_convert.c
test_audio_fmt_convert_LDADD =  $(UCLMMBASE_LIBS) $(top_builddir)/libuclaudio.la	\
	$(top_builddir)/libuclcodec.la					\
	$(top_builddir)/libuclsndfile.la
test_audio_fmt_convert_LDFLAGS = $(all_libraries)

probeaudio_SOURCES = probeaudio.c
probeaudio_CFLAGS = $(UCLMMBASE_CFLAGS)
probeaudio_LDADD = $(UCLMMBASE_LIBS) $(top_builddir)/libuclaudio.la	\
	$(top_builddir)/libuclcodec.la

