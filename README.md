# Robust-Audio Tool (RAT)

Copyright (C) 1995-2001 University College London
All rights reserved.

This software is distributed under license, see the file [COPYRIGHT](COPYRIGHT) for full
terms and conditions.

## More Information & FAQ

Further information, and a list of frequently asked questions (with answers)
is available from <http://www-mice.cs.ucl.ac.uk/multimedia/software/rat/>

## Install

See the file [INSTALL.TXT](INSTALL.md) for installation and compilation instructions.

### Dependencies

This project depends upon alsa-lib (Linux), tcl, and tk.  For Fedora
based systems, install the following packages:

```bash
sudo dnf install alsa-lib alsa-lib-devel tcl tcl-devel tk tk-devel
```

This project also requires `librat`, also known as the UCL Common Code
Library.  You can get it
[here](https://github.com/glencornell/rat-common).  Before proceding,
make sure that `librat` is installed on your system.

### Building and installing a package

```bash
autoreconf -vi
./configure
make rpm
sudo dnf install rpmbuild/RPMS/x86_64/rat-[0-9]*.$(uname -m).rpm
```

## Running

### Firewall

You will need to open a few ports in your firewall:

```bash
# Add the ports for your secific network audio conference. Any ports
# will work, but the port number for RTCP is just after that of RTP.
# For example, 5004 (RTP) and 5005 (RTCP).
sudo firewall-cmd --zone=public --add-port=5004/udp --permanent
sudo firewall-cmd --zone=public --add-port=5005/udp --permanent

# Add the port for the local mbus traffic:
sudo firewall-cmd --zone=public --add-port=47000/udp --permanent

# Reload the firewall and make sure the ports are open:
sudo firewall-cmd --reload
sudo firewall-cmd --zone=public --list-ports
```

### Running rat

```bash
rat 224.1.2.3/5004
```

### Configuring

There are a few configuration files stored in your home directory that
you can modify:

 - `~/.mbus`: MBUS configuration parameters
 - `~/.RATdefaults`: Settings for RAT (default codec, sample rate, etc)
 - `~/.RTPdefaults`: Your information published to other conference members

## Community

Send comments, suggestions and bug-reports to <rat-trap@cs.ucl.ac.uk>. A
mailing list for general discussion on related issues is now available,
send mail to <rat-users-request@cs.ucl.ac.uk> to subscribe. All users of
rat are encouraged to join this list.

## Overview

RAT is a network audio tool that allows users to particpate in audio
conferences over the internet. These can be between two participants
directly, or between a group of participants on a common multicast group.
No special features are required to use RAT in point-to-point mode, but to
use the multicast conferencing facilities of RAT, a connection to the
Mbone, or a similar multicast capable network, is required. RAT is based on
IETF standards, using RTP above UDP/IP as its transport protocol, and
conforming to the RTP profile for audio and video conferences with minimal
control.

In addition to the features provided by other Mbone audio conferencing
tools RAT offers the following additional functionality:

  - Sender based repair of damaged audio streams
    - FEC in the form of redundant packet transmission
    - Support for interleaved audio
  - Received based repair of damaged audio streams
  - Adaptive scheduling protection
  - Secure conferencing
  - Improved statistics and diagnostic features
  - Conference coordination bus
  - Transcoder operation
  - Sound localisation and externalisation

This list is correct for RAT v3.2, earlier versions have a more limited feature
set.

## Sender based repair of damaged audio streams

Unless some form of resource reservation protcol (eg: [RSVP](https://datatracker.ietf.org/doc/html/rfc2205)) is used, an IP
based network, such as the Internet or the Mbone, will occasionally lose
packets. These lost packets result in broken up audio, which rapidly
becomes unintelligible as the loss rate increases. RAT implements two
sender based repair schemes to recover from this problem: [redundant
transmission](#redundant-transmission) and [interleaving](#interleaving).

### Redundant Transmission

Redundant transmission is the means by which a (more) heavily compressed
copy of a packet is piggy-backed onto the following packet. If the original
packet is lost, the redundant copy can be used in its place. Because the
redundant packet is very heavily compressed, sound quality suffers, but is
still better than having no audio to play out in the place of the lost
packet. Clearly, there exists a tradeoff between the amount of compression
used for the redundant packet (and hence stream bandwidth/overhead), and
the quality of the resultant audio.

Redundant transmission was developed by UCL and INRIA Sophia-Antipolis, as
part of the MICE/MERCI multimedia conferencing projects. It is discussed
further in the following papers:

  - Vicky Hardman, Angela Sasse, Mark Handley and Anna Watson,
  ["Reliable Audio for Use over the Internet"](http://www-mice.cs.ucl.ac.uk/multimedia/publications/inet95-rat.ps), in Proceedings of
  INET'95, June 1995, Honolulu, Hawaii.

  - Isidor Kouvelas, Orion Hodson, Vicky Hardman and Jon Crowcroft,
  ["Redundancy Control in Real-Time Internet Audio Conferencing"](https://csperkins.org/research/rat/publications/redundancy-avspn97.pdf), in
  Proceedings of AVSPN 97, September 1997, Aberdeen, Scotland, UK.

  - Colin Perkins, Isidor Kouvelas, Orion Hodson, Vicky Hardman, Mark
  Handley, Jean-Chrysostome Bolot, Andres Vega-Garcia, Sacha
  Fosse-Parisis, ["RTP Payload for Redundant Audio Data"](https://www.csperkins.org/publications/1997/09/rfc2198/rfc2198.txt), IETF
  Audio/Video Transport Working Group, RFC2198, September 1997.

  - C. S. Perkins, O. Hodson & V. Hardman, ["A Survey of Packet-Loss
  Recovery Techniques for Streaming Audio"](https://www.csperkins.org/publications/1998/09/IEEE-Network-1998/IEEE-Network-1998.pdf), IEEE Network Magazine,
  September/October 1998.

### Interleaving

As an alternative to redundant transmission, recent versions of RAT provide
the option to send interleaved audio. Units of audio data are resequenced
before transmission, so that originally adjacent units are separated by a
guaranteed distance in the transmitted stream, and returned to their
original order at the receiver. Interleaving disperses the effect of packet
losses. If, for example, units are 5ms in length and packets 20ms (ie: 4
units per packet), then the first packet could contain units 1, 5, 9, 13;
the second packet would contain units 2, 6, 10, 14; and so on. It can be
seen that the loss of a single packet from an interleaved stream results in
multiple small gaps in the reconstructed stream, as opposed to the single
large gap which would occur in a non-interleaved stream.

Although interleaving does not reduce the amount of loss observed, it does
significantly improve the perceived quality of an audio stream. The obvious
disadvantage of interleaving is that it increases latency. This limits the
use of this technique for interactive applications, although it performs
well for non-interactive use. The major advantage of interleaving is that
it does not increase the bandwidth requirements of a stream.

## Receiver based repair of damaged audio streams

Receiver based recovery schemes rely on producing a replacement for a lost
packet which is similar to the original. This is possible since audio
signals, and in particular speech, exhibit large amounts of short-term self
similarity. As such, these techniques work for relatively small loss rates
(less than 15%), and for small packets (4-40ms). When the loss length
approaches the length of a phoneme (5-100ms) these techniques breakdown,
since whole phonemes may be missed by the listener.

It is, therefore, clear that receiver based repair schemes are not a
substitute for sender-based repair, but rather work in tandem with it. A
sender-based scheme is used to repair most losses, leaving a small number
of isolated gaps to be repaired. Once the effective loss rate has been
reduced in this way, receiver based repair forms a cheap and effective
means of patching over the remaining loss.

A number of receiver based repair schemes are implemented in RAT:

  - Silence substituation
  - Packet repetition
  - Pattern matching repair

### Silence Substitution

A simple form of receiver based recovery is silence substitution. The gap
left by a lost packet is filled with silence, to maintain the timing
relationship between the surrounding packets. It is only effective with
short packet lengths (less than 4ms) and low loss rates (less than 2%),
making it suitable for striped audio with narrow and distributed stripes
over low loss paths.

The performance of silence substitution degrades rapidly as packet sizes
increase, and quality is unacceptably bad for the 40ms packet size in
common use in network audio conferencing tools. Despite this, the use of
silence substitution is widespread, primarily because it is simple to
implement.

Packet repetition replaces lost packets with copies of the packets that
arrived immediately before the loss.  It has low computational complexity
and performs reasonably well. The subjective quality of repetition is
improved by gradually fading repeated units. The GSM system, for example,
advocates the repetition of the first 20ms with the same amplitude and
followed by fading the repeated signal to zero amplitude over the next
320ms.

The use of repetition with fading is a good compromise between the poor
performance of silence substitution, and the more complex pattern matching
scheme.

Pattern matching repair uses audio before and after the loss to interpolate
a suitable signal to cover the loss. It performs somewhat better than
packet repetition, but is significantly more computationally intesive.

### Adaptive Scheduling Protection

Current general purpose operating systems, such as Unix and Windows 95, do
not provide adequate support for real-time services in their scheduling
algorithms. RAT uses a novel adaptive algorithm, where the DMA driven audio
playout is used to `cushion' the system against scheduling anomolies. This
is described in the following paper:

  - Isidor Kouvelas and Vicky Hardman, ["Overcoming Workstation
  Scheduling Problems in a Real-Time Audio Tool"](https://www.usenix.org/legacy/publications/library/proceedings/ana97/full_papers/kouvelas/kouvelas_html/paper_backup.html), in Proceedings of
  Usenix Annual Technical Conference, January 1997, Anaheim,
  California.

## Secure Conferencing

RAT allows for secure conferencing, whereby media streams and participant
identity information can be encrypted using DES. Other encryption
algorithms can easily be added.

## Improved Statistics and diagnostic features

Like other RTP-based audio tools, RAT provides reception quality
statistics and user information for all participants in a
conference. In addition, it has a graphical display of the loss
to/from each participant, making diagnosis of problems a simple
matter.

## Conference coordination bus

RAT implements a conference coordination bus, whereby the user
interface and media engine are separated, and communicate via an IPC
mechanism. This allows for complete control of RAT by another process
operating on the same host. Advantages of this split approach include:

  - Customised user-interface: the existing RAT user interface can
    easily be replaced, with no loss of functionality.

  - Lip-synchronisation: RAT can communicate with a videa tool, to
    synchronise audio and video.

  - Integration with wide area conference control: a separate
      conference control process may be run on the same host as the
    audio/video tools. This can use the conference bus to control the
    media tools, to provide, for example H.323 conference control.

## Transcoder operation

When the bandwidth available is not constant for all participants in a
conference, or when some participants do not have multicast capable
access, the RAT transcoder/gateway may be used. This connects two
multicast groups, or one multicast group and a single unicast
host. RTP packets received from either group are transcoded into the
format specified for the other group, multiple sources are mixed
together, and the resulting stream is transmitted to the other
group. This allows for different codecs to be used in each group,
meaning that the bandwidth requirements are different.

## Future research

Future developments planned include:

  - Additional codecs, for low bandwidth speech and high quality music.
  - Investigation of different error recovery techniques.

## Project Background

UCL has a well-established multimedia and communications research
group.  One of the current research topics is multimedia conferencing
applications over the Internet Mbone. We are in the process of
developing a next generation audio tool, RAT, for use over the
Internet, as part of a suite of integrated multimedia tools. The
research is aimed at providing software systems on heterogeneous
workstations (Unix and Windows based). The group has existing
collaborative and industrially funded application piloting projects.

## Sponsors

The RAT project was funded by the EPSRC under the Multimedia and
Networked Applications Programme, Bristish Telecommunications plc, and
the European Commision (Telematics Applications Programme, Research
Sector).  It has benefited from hardware donations by Hewlett-Packard
and Sun Microsystems, and software donations by Microsoft.

## TODO

Feature Enhancements:

- [ ] Add Opus codec
- [ ] Add 256 bit AES encryption
- [ ] Create text-based UI for headless operation
- [ ] Allow full-duplex operation
- [ ] Publish SDP over SAP
- [ ] Reduce jitter by switching to realtime scheduler

Refactor:

- [ ] Merge the rat-common code with this, as there is no other applications using rat-common
- [ ] Organize files into subdirectories

Deprecated capabilities to be removed:

- [ ] Remove DES encryption

Testing:

- [ ] Unit tests
- [ ] Performance tests
