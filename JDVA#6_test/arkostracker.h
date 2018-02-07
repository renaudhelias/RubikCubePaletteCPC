//-----------------------------LICENSE NOTICE------------------------------------
//  This file is part of CPCtelera: An Amstrad CPC Game Engine
//  Copyright (C) 2009 Targhan / Arkos
//  Copyright (C) 2015 ronaldo / Fremos / Cheesetea / ByteRealms (@FranGallegoBR)
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//-------------------------------------------------------------------------------
//######################################################################
//### MODULE: Audio                                                  ###
//######################################################################
//### This module contains code for music and SFX players and other  ###
//### audio routines.                                                ###
//######################################################################
//
#ifndef CPCT_AUDIO_H
#define CPCT_AUDIO_H

//
// File: Audio Constants&Variables
//

//
// Arkos Player: full control version (without interrupts)
// 

// Arkos Player Music Control Functions
extern void cpct_akp_musicInit  (void* songdata);
extern void cpct_akp_musicPlay  ();
extern void cpct_akp_stop       ();

// Arkos Player Sound FX Control Functions (Only available if SFX is active)
extern void cpct_akp_SFXInit    (void* sfx_song_data);
extern void cpct_akp_SFXStopAll ();
extern void cpct_akp_SFXStop    (unsigned char stop_bitmask);
extern void cpct_akp_SFXPlay    (unsigned char sfx_num, unsigned char volume, unsigned char note, unsigned char speed, 
                                 unsigned int inverted_pitch, unsigned char channel_bitmask);
extern  unsigned int cpct_akp_SFXGetInstrument (unsigned char channel_bitmask);

// Arkos Player Fade in / out volume control (Only valid if Fades are active)
extern void cpct_akp_setFadeVolume(unsigned char volume);

//
// Variable: cpct_akp_digidrumStatus
//
//    This is an internal variable, updated by Arkos Tracker Player, 
// that is used by the player for signalling events to user code. You
// may read it at any time to know if any "event" has happened (as 
// signalled by the player) and then react accordingly. To know more,
// read about <Digidrums>.
// 
//
extern volatile  unsigned char cpct_akp_digidrumStatus;

//
// Variable: cpct_akp_songLoopTimes
//
//    This is an internal variable, updated by Arkos Tracker Player, 
// that contains the number of times the present song has looped. You
// may use it to know if a song has finished or if it has looped
// N times.
//
extern volatile  unsigned char cpct_akp_songLoopTimes;


// 
// Constants: Audio Channels (bitmasks)
//
//    Bitmask constants for referring to audio channels of the
// AY-3-8912 PSG chip.
//
//    AY_CHANNEL_A   - Audio Channel A (also referred as 0)
//    AY_CHANNEL_B   - Audio Channel B (also referred as 1)
//    AY_CHANNEL_C   - Audio Channel C (also referred as 2)
//    AY_CHANNEL_ALL - All audio channels (A, B & C)
//
#define AY_CHANNEL_A    0b00000001
#define AY_CHANNEL_B    0b00000010
#define AY_CHANNEL_C    0b00000100
#define AY_CHANNEL_ALL  0b00000111

#endif