/*
** Nofrendo (c) 1998-2000 Matthew Conte (matt@conte.com)
**
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of version 2 of the GNU Library General 
** Public License as published by the Free Software Foundation.
**
** This program is distributed in the hope that it will be useful, 
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
** Library General Public License for more details.  To obtain a 
** copy of the GNU Library General Public License, write to the Free 
** Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
**
** Any permitted reproduction of these routines, in whole or in part,
** must bear this legend.
**
**
** event.c
**
** OS-independent event handling
** $Id: event.c,v 1.3 2001/04/27 14:37:11 neil Exp $
*/

#include <stdlib.h>
#include "noftypes.h"
#include "event.h"
#include "nesinput.h"



/* pointer to our current system's event handler table */
static event_t *system_events = NULL;

/* standard keyboard input */
static nesinput_t kb_input = { INP_JOYPAD0, 0 };
static nesinput_t kb_alt_input = { INP_JOYPAD1, 0 };



static void func_event_joypad1_a(int code)
{
   input_event(&kb_input, code, INP_PAD_A);
}

static void func_event_joypad1_b(int code)
{
   input_event(&kb_input, code, INP_PAD_B);
}

static void func_event_joypad1_start(int code)
{
   input_event(&kb_input, code, INP_PAD_START);
}

static void func_event_joypad1_select(int code)
{
   input_event(&kb_input, code, INP_PAD_SELECT);
}

static void func_event_joypad1_up(int code)
{
   input_event(&kb_input, code, INP_PAD_UP);
}

static void func_event_joypad1_down(int code)
{
   input_event(&kb_input, code, INP_PAD_DOWN);
}

static void func_event_joypad1_left(int code)
{
   input_event(&kb_input, code, INP_PAD_LEFT);
}

static void func_event_joypad1_right(int code)
{
   input_event(&kb_input, code, INP_PAD_RIGHT);
}

static void func_event_joypad2_a(int code)
{
   input_event(&kb_alt_input, code, INP_PAD_A);
}

static void func_event_joypad2_b(int code)
{
   input_event(&kb_alt_input, code, INP_PAD_B);
}

static void func_event_joypad2_start(int code)
{
   input_event(&kb_alt_input, code, INP_PAD_START);
}

static void func_event_joypad2_select(int code)
{
   input_event(&kb_alt_input, code, INP_PAD_SELECT);
}

static void func_event_joypad2_up(int code)
{
   input_event(&kb_alt_input, code, INP_PAD_UP);
}

static void func_event_joypad2_down(int code)
{
   input_event(&kb_alt_input, code, INP_PAD_DOWN);
}

static void func_event_joypad2_left(int code)
{
   input_event(&kb_alt_input, code, INP_PAD_LEFT);
}

static void func_event_joypad2_right(int code)
{
   input_event(&kb_alt_input, code, INP_PAD_RIGHT);
}



/* NES events */
static event_t nes_events[] =
{
   NULL, /* 0 */
   NULL,
   NULL,
   NULL,
   NULL,
   NULL,
   NULL,
   NULL,
   NULL,
   /* saves */
   NULL,
   NULL, /* 10 */
   NULL,
   NULL,
   NULL,
   NULL,
   NULL,
   NULL,
   NULL,
   NULL,
   NULL,
   NULL, /* 20 */
   /* GUI */
   NULL,
   NULL,
   NULL,
   NULL,
   NULL,
   NULL,
   NULL,
   NULL,
   /* sound */
   NULL,
   NULL, /* 30 */
   NULL,
   NULL,
   NULL,
   NULL,
   NULL,
   NULL,
   NULL,
   /* picture */
   NULL,
   NULL,
   NULL,
   NULL, /* 40 */
   NULL,
   NULL,
   NULL,
   /* joypad 1 */
   func_event_joypad1_a,
   func_event_joypad1_b, 
   func_event_joypad1_start,
   func_event_joypad1_select,
   func_event_joypad1_up,
   func_event_joypad1_down,
   func_event_joypad1_left, /* 50 */
   func_event_joypad1_right,
   /* joypad 2 */
   func_event_joypad2_a,
   func_event_joypad2_b,
   func_event_joypad2_start,
   func_event_joypad2_select,
   func_event_joypad2_up,
   func_event_joypad2_down,
   func_event_joypad2_left,
   func_event_joypad2_right,
   /* NSF control */
   NULL, /* 60 */
   NULL,
   NULL,
   /* OS-specific */
   NULL,
   NULL,
   NULL,
   NULL,
   NULL,
   NULL,
   NULL,
   NULL, /* 70 */
   NULL,
   /* last */
   NULL
};
static event_t *event_system_table[NUM_SUPPORTED_SYSTEMS] =
{
   NULL, /* unknown */
   NULL, /* autodetect */
   nes_events, /* nes */
};



void event_init(void)
{
   input_register(&kb_input);
   input_register(&kb_alt_input);
}

/* set up the event system for a certain console/system type */
void event_set_system(system_t type)
{
   ASSERT(type < NUM_SUPPORTED_SYSTEMS);

   system_events = event_system_table[type];
}

void event_set(int index, event_t handler)
{
   /* now, event_set is used to set osd-specific events.  We should assume
   ** (for now, at least) that these events should be used across all
   ** emulated systems, so let's loop through all system event handler
   ** tables and add this event...
   */
   int i;

   for (i = 0; i < NUM_SUPPORTED_SYSTEMS; i++)
   {
      if(event_system_table[i])
      {
         event_system_table[i][index] = handler;
      }
   }
}


event_t event_get(int index)
{
   return system_events[index];
}


/*
** $Log: event.c,v $
** Revision 1.3  2001/04/27 14:37:11  neil
** wheeee
**
** Revision 1.2  2001/04/27 11:10:08  neil
** compile
**
** Revision 1.1.1.1  2001/04/27 07:03:54  neil
** initial
**
** Revision 1.18  2000/11/25 20:26:05  matt
** removed fds "system"
**
** Revision 1.17  2000/11/09 14:05:42  matt
** state load fixed, state save mostly fixed
**
** Revision 1.16  2000/11/05 16:37:18  matt
** rolled rgb.h into bitmap.h
**
** Revision 1.15  2000/11/01 17:33:26  neil
** little crash bugs fixed
**
** Revision 1.14  2000/11/01 14:15:35  matt
** multi-system event system, or whatever
**
** Revision 1.13  2000/10/27 12:59:48  matt
** api change for ppu palette functions
**
** Revision 1.12  2000/10/26 22:48:05  matt
** no need for extern
**
** Revision 1.11  2000/10/25 00:23:16  matt
** makefiles updated for new directory structure
**
** Revision 1.10  2000/10/23 17:50:46  matt
** adding fds support
**
** Revision 1.9  2000/10/23 15:52:04  matt
** better system handling
**
** Revision 1.8  2000/10/22 15:01:51  matt
** prevented palette changing in VS unisystem games
**
** Revision 1.7  2000/10/10 13:03:54  matt
** Mr. Clean makes a guest appearance
**
** Revision 1.6  2000/08/16 02:58:34  matt
** random cleanups
**
** Revision 1.5  2000/07/27 01:15:33  matt
** name changes
**
** Revision 1.4  2000/07/26 21:36:13  neil
** Big honkin' change -- see the mailing list
**
** Revision 1.3  2000/07/23 15:17:19  matt
** non-osd calls moved from osd.c to gui.c
**
** Revision 1.2  2000/07/21 12:07:40  neil
** added room in event_array for all osd events
**
** Revision 1.1  2000/07/21 04:26:38  matt
** initial revision
**
*/
