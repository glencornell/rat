dnl UCL RAT configure script.
dnl $Header: /cs/research/mice/starship/src/local/CVS_repository/rat/configure.in,v 1.54 2004/11/16 14:39:36 ucaccsp Exp $
dnl
dnl Process this file with GNU autoconf to generate a configure script.

AC_PREREQ([2.71])
AC_INIT([rat],[4.4.01],[])
AC_CONFIG_SRCDIR([converter.c])
AC_CONFIG_HEADERS([ratconf.h:config.h.in])

AC_CONFIG_MACRO_DIRS([m4])

AM_INIT_AUTOMAKE([foreign subdir-objects])

LT_INIT

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_INSTALL

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h fcntl.h inttypes.h malloc.h netdb.h netinet/in.h stdint.h sys/ioctl.h sys/param.h sys/socket.h sys/time.h unistd.h])

VERSION=`cat VERSION`
AC_SUBST(VERSION)

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_UID_T
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_INT8_T
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_FUNC_FORK
AC_FUNC_MALLOC
AC_FUNC_STRTOD
AC_CHECK_FUNCS([atexit bzero gethostbyname gethostname gettimeofday inet_ntoa isascii memmove memset pow putenv select snprintf sqrt strcasecmp strchr strdup strerror strncasecmp strrchr strstr strtoul uname usleep])

# This is kind-of ugly, but necessary to get the OSTYPE to match those used
# in earlier versions of rat (and, despite what rms thinks, I don't like my
# system being identified as "linux-gnu". [csp]
case "$host_os" in
 	*linux*   ) OSTYPE=Linux    ;;
 	*solaris* ) OSTYPE=Solaris  ;;
	*freebsd* ) OSTYPE=FreeBSD  ;;
	*netbsd*  ) OSTYPE=NetBSD   ;;
	*irix*    ) OSTYPE=Irix     ;;
	*darwin*  ) OSTYPE=Darwin   ;;
	*         ) OSTYPE=$host_os ;;
esac
dnl AC_SUBST(OSTYPE)

# define target endianness
AC_C_BIGENDIAN
AS_IF([test "x$ac_cv_c_bigendian" = "xyes"],
            AC_DEFINE([WORDS_BIGENDIAN],[1],[Define to 1 if the target is a big endian architecture]),
            AC_DEFINE([WORDS_BIGENDIAN],[0],[Define to 1 if the target is a big endian architecture]))

# is char unsigned?
AC_C_CHAR_UNSIGNED

#------------------------------------------------------------------------------
# GCC-specific warning flags:  Set these late since some tests won't build
# with all these warnings enabled.
#------------------------------------------------------------------------------
if test "$GCC" = yes
then
        CFLAGS="$CFLAGS -W -Wall -Wbad-function-cast -Wmissing-prototypes"
fi

#-----------------------------------------------------------------------------
# Check for various headers                                                 
#-----------------------------------------------------------------------------
AC_CHECK_HEADERS(stdint.h inttypes.h sys/filio.h malloc.h bstring.h)
AC_CHECK_HEADERS(sys/sockio.h)

#-----------------------------------------------------------------------------
# Check for missing declarations
#-----------------------------------------------------------------------------
AC_MSG_CHECKING([for kill declaration])
AC_EGREP_CPP(kill, [#include <signal.h>],
	AC_MSG_RESULT(present), [
	AC_MSG_RESULT(missing)
	AC_DEFINE([KILL_NOT_DECLARED],[],[for kill declaration])
])

#-----------------------------------------------------------------------------
# Check for libraries                                                       
#-----------------------------------------------------------------------------
AC_SEARCH_LIBS(socket, socket)
AC_SEARCH_LIBS(inet_addr, nsl)
AC_SEARCH_LIBS(dlopen, dl)
AC_SEARCH_LIBS([sin], [m])

#-----------------------------------------------------------------------------
# The (?which?) library does not work with unsigned characters.
# Force the compiler to use signed chars.
#-----------------------------------------------------------------------------
if test $ac_cv_c_char_unsigned = yes
then
        if test "$GCC" = yes
        then
                CFLAGS="$CFLAGS -fsigned-char"
        else
                case "$host_os" in
                # I don't know when "-signed" was added to IRIX CC
                # so err on the side of using it.
                irix*)  CFLAGS="$CFLAGS -signed"
                        ;;
                # need e.g. --force-signed-chars=-signed
                *)      AC_MSG_ERROR([I don't know how to force signed chars])
                        ;;
                esac
        fi
fi
#  __CHAR_UNSIGNED__ will be defined; hope this is OK.

#-----------------------------------------------------------------------------
# Audio device selection, derived from host type.  Could be smart and probe 
# what's there, but can't guarantee that build host has audio device(s).  RAT
# probes devices at startup from those compiled in so this is not an issue
# when re-distributing.
#-----------------------------------------------------------------------------
AUD_INC=""
AUD_LIB=""
AUD_OBJ=""

case "$target" in
*solaris*)
	SUNAUDIOHOME="/usr/demo/SOUND"
	O1KHOME="/opt/SUNWo1kp"
	AC_ARG_WITH(sun-audio,    [  --with-sun-audio=DIR    specify Sun audio support home], SUNAUDIOHOME=$withval)
	AUD_INC="$AUD_INC -I$SUNAUDIOHOME/include"
	AUD_OBJ="$AUD_OBJ auddev_sparc.o" 
	AC_DEFINE([HAVE_SPARC_AUDIO],[],[HAVE_SPARC_AUDIO])
	AC_ARG_WITH(osprey-audio, [  --with-osprey=DIR       specify Osprey (Sunvideo Plus PCI) support home], O1KHOME=$withval)
	AC_CHECK_HEADER($O1KHOME/include/oti_audio_device.h,
		[AUD_INC="$AUD_INC -I$O1KHOME/include"
		 AUD_OBJ="$AUD_OBJ auddev_osprey.o"
		 AC_DEFINE([HAVE_OSPREY_AUDIO],[],[specify Osprey (Sunvideo Plus PCI) support home])])
	;;
*linux*)
	# Do we have telephony drivers?
	AC_CHECK_HEADER(linux/telephony.h,[
		AC_MSG_CHECKING([for recent telephony drivers])
		AC_EGREP_HEADER(PHONE_CID, linux/telephony.h,[ 
			AC_MSG_RESULT(present)
			AUD_SRC="$AUD_SRC auddev_ixj.c"
			AC_DEFINE([HAVE_IXJ_AUDIO],[],[have telephony drivers])
		],AC_MSG_RESULT(missing))
	])
	;;
*freebsd*)
	# PC Speaker device on FreeBSD
	AC_CHECK_HEADERS(machine/pcaudioio.h)
	if test "$ac_cv_header_machine_h"="yes" ; then
		AUD_OBJ="$AUD_OBJ auddev_pca.o"
		AC_DEFINE([HAVE_PCA_AUDIO],[],[FreeBSD PC speaker device])
	fi
	# Note luigi and newpcm have compatible soundcard.h files but
	# mixer behaves differently under both systems.  During runtime
	# only one of these modules will be used.
	AUD_OBJ="$AUD_OBJ auddev_luigi.o auddev_newpcm.o"
	AC_DEFINE([HAVE_LUIGI_AUDIO],[],[HAVE_LUIGI_AUDIO]) 
  	AC_DEFINE([HAVE_NEWPCM_AUDIO],[],[HAVE_NEWPCM_AUDIO]) 
	;;
*netbsd*)
	AC_CHECK_LIB(ossaudio, main)
	if test "$ac_cv_lib_ossaudio_main"="yes"; then
		AC_CHECK_HEADERS(sys/soundcard.h soundcard.h)
		AUDIOBJ="$AUDIOBJ auddev_oss.o"
		AUD_LIB="$AUD_LIB -lossaudio"
		AC_DEFINE([HAVE_OSS_AUDIO],[],[HAVE_OSS_AUDIO])
	fi
	AC_CHECK_HEADERS(sys/audioio.h)
	AUD_OBJ="$AUDIOBJ auddev_netbsd.o"
	AC_DEFINE([HAVE_NETBSD_AUDIO],[],[HAVE_NETBSD_AUDIO])
	;;
*irix*)
	AUD_LIB="$AUD_LIB -laudio"
	AUD_OBJ="$AUD_OBJ auddev_sgi.o"
	AC_DEFINE([HAVE_SGI_AUDIO],[],[HAVE_SGI_AUDIO])
	;;
*hpux*)
	AUD_LIB="$AUD_LIB -lAlib"
	AUD_OBJ="$AUD_OBJ auddev_hpux_raw.o"
	AC_DEFINE([HAVE_HP_AUDIO],[],[HAVE_HP_AUDIO])
	;;
*darwin*)
	AUD_LIB="$AUD_LIB -framework CoreAudio -framework AudioToolbox -framework AudioUnit -framework CoreServices"
        AUD_OBJ="$AUD_OBJ auddev_macosx.o"
	AC_DEFINE([HAVE_MACOSX_AUDIO],[],[HAVE_MACOSX_AUDIO])

dnl Check for 64-bit host gcc - in Snow Leopard+ Can only use 64-bit when 10.4 compat not enabled
AC_MSG_CHECKING([for a 64-bit gcc on OSX])
        if gcc -v 2>&1 | grep host=x86_64 >& /dev/null ; then
              AC_MSG_RESULT([Forcing 32-bit binary])
              #CFLAGS="$CFLAGS -arch i386 -arch x86_64"
              CFLAGS="$CFLAGS -arch i386"
              LIBS="$LIBS -mmacosx-version-min=10.4"
        else
              AC_MSG_RESULT([No - Only building 32-bit binary])
        fi
	;;
esac

AC_SUBST(AUD_OBJ)
AC_SUBST(AUD_INC)
AC_SUBST(AUD_LIB)

###############################################################################
# IPv6 related configuration options (needs to go before common to guarantee
# linkage).

AC_ARG_ENABLE(ipv6,
        [  --enable-ipv6           enable ipv6],
	AC_DEFINE([HAVE_IPv6],[],[HAVE_IPv6]))

AC_ARG_ENABLE(kame-ipv6,
	[  --enable-kame-ipv6      enable kame implementation of ipv6],
	[
		AC_DEFINE([HAVE_IPv6],[],[HAVE_IPv6])
		LIBS="$LIBS -L/usr/local/v6/lib -linet6"
	])

#-----------------------------------------------------------------------------
# Check for UCL Multimedia Base (formerly common) library
#-----------------------------------------------------------------------------
PKG_CHECK_MODULES([UCLMMBASE], [libuclmmbase])
PKG_CHECK_MODULES([TK], [tk8.6])
PKG_CHECK_MODULES([TCL], [tcl8.6])
PKG_CHECK_MODULES([ALSA], [alsa], [
    use_alsa=yes
    AC_DEFINE([HAVE_ALSA],[1],[Define if ALSA sound drivers are available])])
AM_CONDITIONAL([ALSA],[test "x$use_alsa" = "xyes"])


# GSM flag checks
#-----------------------------------------------------------------------------
# Check if Signed arithmetic shift right (SASR).  If SASR then -1 >> 1 == 1.
# Return value from test program of zero indicates success.
#-----------------------------------------------------------------------------
AC_CACHE_CHECK(signed arithmetic shift right, gsm_cv_sasr,
	AC_RUN_IFELSE([AC_LANG_SOURCE([[int main() { return (-1 >> 1) != -1;}]])],[gsm_cv_sasr=yes],[gsm_cv_sasr=no],[]))
if test $gsm_cv_sasr = yes ; then
	AC_DEFINE([SASR],[],[SASR])
fi

#-----------------------------------------------------------------------------
# GSM Options, almost certainly not sensible on all platforms, performance
# tests in a configure script ?
#-----------------------------------------------------------------------------
AC_DEFINE([FAST],[],[fast])
AC_DEFINE([USE_FLOAT_MUL],[],[USE_FLOAT_MUL])

#-----------------------------------------------------------------------------
# Just check if g728 library exists behind this directory.
#-----------------------------------------------------------------------------
G728_DIR=${PARENT}/g728lib
G728_LIB=${G728_DIR}
EXTRA_CODEC_OBJ=

AC_CHECK_LIB(g728,
	g728_encoder_init,
	[
		G728_INC=-I${G728_DIR}
		G728_LIB="-L${G728_LIB} -lg728"
		G728_CODEC_OBJ="codec_g728.o"
		AC_DEFINE([HAVE_G728],[],[have g728 encoder])
	],
	[
		G728_INC=
		G728_LIB=
		G728_CODEC_OBJ=
	],
	-L${G728_LIB} -lm)

AC_SUBST(G728_INC)
AC_SUBST(G728_LIB)
AC_SUBST(G728_CODEC_OBJ)

#-----------------------------------------------------------------------------
# Assorted Enable options 
#-----------------------------------------------------------------------------
AC_ARG_ENABLE(optimize,
        [  --enable-optimize       enable optimization],
        [if test $enableval = yes
        then
		AC_DEFINE([NDEBUG],[],[NDEBUG])
	fi])
AC_ARG_ENABLE(profile,
        [  --enable-profile        enable profiling],
        [if test $enableval = yes
        then
                if test "$GCC" = yes
                then
                        CFLAGS="$CFLAGS -pg"
                else
                        AC_MSG_ERROR(Don't know how to enable profiling for $CC)
                fi
        fi])
AC_ARG_ENABLE(bounds,
        [  --enable-bounds         enable bounds checking],
        [if test $enableval = yes
        then
                if test "$GCC" = yes
                then
                        CFLAGS="$CFLAGS -fbounds-checking"
                        LIBS="$LIBS -lcheck"
                else
                        AC_MSG_ERROR(Don't know how to enable profiling for $CC)
                fi
        fi])
AC_ARG_ENABLE(debug,
        [  --enable-debug          enable debug messages and code],
        [if test $enableval = yes
        then
                AC_DEFINE([DEBUG],[],[enable debug])
        fi])
AC_ARG_ENABLE(debug-mem,
        [  --enable-debug-mem      enable memory debugging code],
        [if test $enableval = yes
        then
                AC_DEFINE([DEBUG_MEM],[],[DEBUG_MEM])
        fi])

AC_CONFIG_FILES([Makefile
        tests/Makefile])
AC_OUTPUT
