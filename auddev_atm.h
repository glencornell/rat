/*
 * FILE:     auddev_atm.h
 * PROGRAM:  RAT
 * AUTHOR:   Orion Hodson
 *
 * Copyright (c) 1998-2001 University College London
 * All rights reserved.
 *
 * $Id: auddev_atm.h 3477 2001-01-08 20:30:13Z ucaccsp $
 */

#ifndef _AUDDEV_ATM_H_
#define _AUDDEV_ATM_H_
int  atm_audio_device_count (void);
const char *
     atm_audio_device_name(audio_desc_t ad);
int  atm_audio_supports(audio_desc_t ad, audio_format *fmt);

int  atm_audio_open       (audio_desc_t ad, audio_format* ifmt, audio_format *ofmt);
void atm_audio_close      (audio_desc_t ad);
void atm_audio_drain      (audio_desc_t ad);
int  atm_audio_duplex     (audio_desc_t ad);
void atm_audio_set_igain   (audio_desc_t ad, int gain);
int  atm_audio_get_igain   (audio_desc_t ad);
void atm_audio_set_ogain (audio_desc_t ad, int vol);
int  atm_audio_get_ogain (audio_desc_t ad);
void atm_audio_loopback   (audio_desc_t ad, int gain);
int  atm_audio_read       (audio_desc_t ad, u_char *buf, int in_bytes);
int  atm_audio_write      (audio_desc_t ad, u_char *buf, int out_bytes);
void atm_audio_non_block  (audio_desc_t ad);
void atm_audio_block      (audio_desc_t ad);

void          atm_audio_oport_set   (audio_desc_t ad, audio_port_t port);
audio_port_t  atm_audio_oport_get   (audio_desc_t ad);
int           atm_audio_oport_count (audio_desc_t ad);
const audio_port_details_t*
              atm_audio_oport_details (audio_desc_t ad, int idx);

void          atm_audio_iport_set   (audio_desc_t ad, audio_port_t port);
audio_port_t  atm_audio_iport_get   (audio_desc_t ad);
int           atm_audio_iport_count (audio_desc_t ad);
const audio_port_details_t*
              atm_audio_iport_details (audio_desc_t ad, int idx);

int  atm_audio_is_ready  (audio_desc_t ad);
void atm_audio_wait_for  (audio_desc_t ad, int delay_ms);
#endif /* _AUDDEV_ATM_H_ */
