/*
Copyright (C) 1996-1997 Id Software, Inc.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

/*
QuakeTM
Transactional implementation of the original Quake game
Copyright (C) 2008 Barcelona Supercomputing Center
Author: Vladimir Gajinov
*/

// sv_main.c -- server main program

#include "qwsvdef.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define CHAN_AUTO   0
#define CHAN_WEAPON 1
#define CHAN_VOICE  2
#define CHAN_ITEM   3
#define CHAN_BODY   4

extern int		framecount;			// GAJA: Added - Frame counter
extern float	srv_frametime_avg;  // GAJA: average frame time of last n frames

extern cvar_t	sv_phs;


// THREADPRIVATE ----------------------------------------------------------

extern client_t		*host_client;     // current client
enum redirect_e		sv_redirected;
char				outputbuf[8000];
THREADPRIVATE(host_client, sv_redirected, outputbuf)

// ------------------------------------------------------------------------


TM_CALLABLE
void SV_FlushRedirect (void);
TM_CALLABLE
static void SV_PrintToClient(client_t *cl, int level, char *string);
TM_CALLABLE
qboolean SV_SendClientDatagram (client_t *client);
TM_CALLABLE
void SV_UpdateClientStats (client_t *client);

/*
=============================================================================

Con_Printf redirection

=============================================================================
*/


/*
==================
SV_FlushRedirect
==================
*/
TM_CALLABLE
void SV_FlushRedirect (void)
{
	char	send[8000+6];

	if (sv_redirected == RD_PACKET)
	{
		send[0] = 0xff;
		send[1] = 0xff;
		send[2] = 0xff;
		send[3] = 0xff;
		send[4] = A2C_PRINT;
		Q_memcpy (send+5, outputbuf, Q_strlen(outputbuf)+1);

		NET_SendPacket (Q_strlen(send)+1, send, net_from);
	}
	else if (sv_redirected == RD_CLIENT)
	{
		CRITICAL_MESSAGE(host_client->msg_lock, CLIENT_MSG_LOCK, host_client->clientId, {
			ClientReliableWrite_Begin (host_client, svc_print, Q_strlen(outputbuf)+3);
			ClientReliableWrite_Byte (host_client, PRINT_HIGH);
			ClientReliableWrite_String (host_client, outputbuf);
		});
	}

	// clear it
	outputbuf[0] = 0;
}


/*
==================
SV_BeginRedirect

  Send Con_Printf data to the remote client
  instead of the console
==================
*/
TM_CALLABLE
void SV_BeginRedirect (redirect_t rd)
{
	sv_redirected = rd;
	outputbuf[0] = 0;
}


TM_CALLABLE
void SV_EndRedirect (void)
{
	SV_FlushRedirect ();
	sv_redirected = RD_NONE;
}


/*
================
Con_Printf

Handles cursor positioning, line wrapping, etc
================
*/

TM_CALLABLE
void Con_Printf (char *fmt, ...)
{
	va_list		argptr;
	char		msg[MAXPRINTMSG];
	
	va_start (argptr,fmt);
	Q_vsprintf (msg,fmt,argptr);  
	va_end (argptr);

	// add to redirected message
	if (sv_redirected)
	{
		if (Q_strlen (msg) + Q_strlen(outputbuf) > MAXPRINTMSG * sizeof(char) - 1)	// GAJA: SIZEOF sizeof(outputbuf) - 1
			SV_FlushRedirect ();
		Q_strcat (outputbuf, msg);
		return;
	}

	// GAJA save messages during transaction and print them after commit
	if (inTransaction == true)
	{
		AddMsg2List(false, msg);
		return;
	}

	Sys_Printf ("%s", msg);	// also echo to debugging console
	if (sv_logfile)
		fprintf (sv_logfile, "%s", msg);
}

/*
================
Con_DPrintf

A Con_Printf that only shows up if the "developer" cvar is set
================
*/
TM_CALLABLE
void Con_DPrintf (char *fmt, ...)
{
	va_list		argptr;
	char		msg[MAXPRINTMSG];

	if (!developer.value)
		return;

	va_start (argptr,fmt);
	Q_vsprintf (msg,fmt,argptr);  
	va_end (argptr);
	
	Con_Printf ("%s", msg);
}

/*
=============================================================================

EVENT MESSAGES

=============================================================================
*/

TM_CALLABLE
static void SV_PrintToClient(client_t *cl, int level, char *string)
{
	CRITICAL_MESSAGE(cl->msg_lock, CLIENT_MSG_LOCK, cl->clientId, {
		ClientReliableWrite_Begin (cl, svc_print, Q_strlen(string)+3);
		ClientReliableWrite_Byte (cl, level);
		ClientReliableWrite_String (cl, string);
	});
}


/*
=================
SV_ClientPrintf

Sends text across to be displayed if the level passes
=================
*/
TM_CALLABLE
void SV_ClientPrintf (client_t *cl, int level, char *fmt, ...)
{
	va_list		argptr;
	char		string[1024];
	
	if (level < cl->messagelevel)
		return;
	
	va_start (argptr,fmt);
	Q_vsprintf (string, fmt,argptr);  
	va_end (argptr);

	SV_PrintToClient(cl, level, string);
}

/*
=================
SV_BroadcastPrintf

Sends text to all active clients
=================
*/
TM_CALLABLE
void SV_BroadcastPrintf (int level, char *fmt, ...)
{
	va_list		argptr;
	char		string[1024];
	client_t	*cl;
	int			i;

	va_start (argptr,fmt);
	Q_vsprintf (string, fmt,argptr);  
	va_end (argptr);
	
	Sys_Printf ("%s", string);	// print to the console

	dummyMethod3();
	for (i=0, cl = svs.clients ; i<MAX_CLIENTS ; i++, cl++)
	{
		if (level < cl->messagelevel)
			continue;
		if (!cl->state)
			continue;

		SV_PrintToClient(cl, level, string);
	}
	dummyMethod4();
}

/*
=================
SV_BroadcastCommand

Sends text to all active clients
=================
*/
void SV_BroadcastCommand (char *fmt, ...)
{
	va_list		argptr;
	char		string[1024];
	
	if (!sv.state)
		return;
	va_start (argptr,fmt);
	vsprintf (string, fmt,argptr);
	va_end (argptr);

	CRITICAL_MESSAGE(sv_reldatagram_lock, SV_RELDATAGRAM_LOCK, 0, {
		MSG_WriteByte (&sv.reliable_datagram, svc_stufftext);
		MSG_WriteString (&sv.reliable_datagram, string);
	});
}


/*
=================
SV_Multicast

Sends the contents of sv.multicast to a subset of the clients,
then clears sv.multicast.

MULTICAST_ALL	same as broadcast
MULTICAST_PVS	send to clients potentially visible from org
MULTICAST_PHS	send to clients potentially hearable from org
=================
*/
TM_CALLABLE
void SV_Multicast (vec3_t origin, int to)
{
	client_t	*client;
	byte		*mask;
	mleaf_t		*leaf;
	int			leafnum;
	int			j;
	qboolean	reliable;
    // GAJA:
    qboolean    inrange = false;

	leaf = Mod_PointInLeaf (origin, sv.worldmodel);
	if (!leaf)
		leafnum = 0;
	else
		leafnum = leaf - sv.worldmodel->leafs;

	reliable = false;

	switch (to)
	{
	case MULTICAST_ALL_R:
		reliable = true;	// intentional fallthrough
	case MULTICAST_ALL:
		mask = sv.pvs;		// leaf 0 is everything;
		break;

	case MULTICAST_PHS_R:
		reliable = true;	// intentional fallthrough
	case MULTICAST_PHS:
		mask = sv.phs + leafnum * 4*((sv.worldmodel->numleafs+31)>>5);
		break;

	case MULTICAST_PVS_R:
		reliable = true;	// intentional fallthrough
	case MULTICAST_PVS:
		mask = sv.pvs + leafnum * 4*((sv.worldmodel->numleafs+31)>>5);
		break;

	default:
		mask = NULL;
		SV_Error ("SV_Multicast: bad to:%i", to);
	}

			dummyMethod1();
	CRITICAL_MESSAGE(sv_multicast_lock, SV_MULTICAST_LOCK, 0, {

		// send the data to all relevent clients
		for (j = 0, client = svs.clients; j < MAX_CLIENTS; j++, client++)
		{
			if (client->state != cs_spawned)
				continue;

			inrange = false;

			if (to == MULTICAST_PHS_R || to == MULTICAST_PHS) {
				vec3_t delta;
				VectorSubtract(origin, client->edict->v.origin, delta);
				if (Length(delta) <= 1024)
					inrange = true;
			}

			if (!inrange)
			{
				leaf = Mod_PointInLeaf (client->edict->v.origin, sv.worldmodel);
				if (leaf)
				{
					// -1 is because pvs rows are 1 based, not 0 based like leafs
					leafnum = leaf - sv.worldmodel->leafs - 1;
					if ( !(mask[leafnum>>3] & (1<<(leafnum&7)) ) )
					{
						//Con_Printf ("supressed multicast\n");
						continue;
					}
				}
			}

			CRITICAL_MESSAGE(client->msg_lock, CLIENT_MSG_LOCK, client->clientId, {
				if (reliable) {
					ClientReliableCheckBlock(client, sv.multicast.cursize);
					ClientReliableWrite_SZ(client, sv.multicast.data, sv.multicast.cursize);
				} else
					SZ_Write (&client->datagram, sv.multicast.data, sv.multicast.cursize);
			});
			dummyMethod2();
		}

		SZ_Clear (&sv.multicast);
	});
}


/*  
==================
SV_StartSound

Each entity can have eight independant sound sources, like voice,
weapon, feet, etc.

Channel 0 is an auto-allocate channel, the others override anything
allready running on that entity/channel pair.

An attenuation of 0 will play full volume everywhere in the level.
Larger attenuations will drop off.  (max 4 attenuation)

==================
*/  
TM_CALLABLE
void SV_StartSound (edict_t *entity, int channel, char *sample, int volume,
    float attenuation)
{       
    int         sound_num;
    //int			field_mask;
    int			i;
	int			ent;
	vec3_t		origin;
	qboolean	use_phs;
	qboolean	reliable = false;

	if (volume < 0 || volume > 255)
		SV_Error ("SV_StartSound: volume = %i", volume);

	if (attenuation < 0 || attenuation > 4)
		SV_Error ("SV_StartSound: attenuation = %f", attenuation);

	if (channel < 0 || channel > 15)
		SV_Error ("SV_StartSound: channel = %i", channel);

// find precache number for sound
							dummyMethod3();
    for (sound_num=1 ; sound_num<MAX_SOUNDS
        && sv.sound_precache[sound_num] ; sound_num++)
        if (!Q_strcmp(sample, sv.sound_precache[sound_num]))
            break;
							dummyMethod4();
    
    if ( sound_num == MAX_SOUNDS || !sv.sound_precache[sound_num] )
    {
        Con_Printf ("SV_StartSound: %s not precacheed\n", sample);
        return;
    }
    
	ent = NUM_FOR_EDICT(entity);

	if ((channel & 8) || !sv_phs.value)	// no PHS flag
	{
		if (channel & 8)
			reliable = true; // sounds that break the phs are reliable
		use_phs = false;
		channel &= 7;
	}
	else
		use_phs = true;

//	if (channel == CHAN_BODY || channel == CHAN_VOICE)
//		reliable = true;

	channel = (ent<<3) | channel;

	//field_mask = 0;
	if (volume != DEFAULT_SOUND_PACKET_VOLUME)
		channel |= SND_VOLUME;
	if (attenuation != DEFAULT_SOUND_PACKET_ATTENUATION)
		channel |= SND_ATTENUATION;

	// use the entity origin unless it is a bmodel
	if (entity->v.solid == SOLID_BSP)
	{
			dummyMethod3();
		for (i=0 ; i<3 ; i++)
			origin[i] = entity->v.origin[i]+0.5*(entity->v.mins[i]+entity->v.maxs[i]);
			dummyMethod4();
	}
	else
	{
		VectorCopy (entity->v.origin, origin);
	}

																									dummyMethod1();
	CRITICAL_MESSAGE(sv_multicast_lock, SV_MULTICAST_LOCK, 0, {
		MSG_WriteByte (&sv.multicast, svc_sound);
		MSG_WriteShort (&sv.multicast, channel);
		if (channel & SND_VOLUME)
			MSG_WriteByte (&sv.multicast, volume);
		if (channel & SND_ATTENUATION)
			MSG_WriteByte (&sv.multicast, attenuation*64);
		MSG_WriteByte (&sv.multicast, sound_num);
		for (i=0 ; i<3 ; i++)
			MSG_WriteCoord (&sv.multicast, origin[i]);

		if (use_phs)
			SV_Multicast (origin, reliable ? MULTICAST_PHS_R : MULTICAST_PHS);
		else
			SV_Multicast (origin, reliable ? MULTICAST_ALL_R : MULTICAST_ALL);
	});
}           


/*
===============================================================================

FRAME UPDATES

===============================================================================
*/

int		sv_nailmodel, sv_supernailmodel, sv_playermodel;

void SV_FindModelNumbers (void)
																									dummyMethod2();
{
	int		i;

	sv_nailmodel = -1;
	sv_supernailmodel = -1;
	sv_playermodel = -1;

											dummyMethod3();
	for (i=0 ; i<MAX_MODELS ; i++)
	{
		if (!sv.model_precache[i])
			break;
		if (!strcmp(sv.model_precache[i],"progs/spike.mdl"))
			sv_nailmodel = i;
		if (!strcmp(sv.model_precache[i],"progs/s_spike.mdl"))
			sv_supernailmodel = i;
		if (!strcmp(sv.model_precache[i],"progs/player.mdl"))
			sv_playermodel = i;
	}
}
											dummyMethod4();


/*
==================
SV_WriteClientdataToMessage

==================
*/
TM_CALLABLE
void SV_WriteClientdataToMessage (client_t *client, sizebuf_t *msg)
{
	int		i;
	edict_t	*other;
	edict_t	*ent;

	ent = client->edict;

	// send the chokecount for r_netgraph
	if (client->chokecount)
	{
		MSG_WriteByte (msg, svc_chokecount);
		MSG_WriteByte (msg, client->chokecount);
		client->chokecount = 0;
	}

	// send a damage message if the player got hit this frame
	if (ent->v.dmg_take || ent->v.dmg_save)
	{
		other = PROG_TO_EDICT(ent->v.dmg_inflictor);
		MSG_WriteByte (msg, svc_damage);
		MSG_WriteByte (msg, ent->v.dmg_save);
		MSG_WriteByte (msg, ent->v.dmg_take);
																													dummyMethod3();
		for (i=0 ; i<3 ; i++)
			MSG_WriteCoord (msg, other->v.origin[i] + 0.5*(other->v.mins[i] + other->v.maxs[i]));
																													dummyMethod4();
	
		ent->v.dmg_take = 0;
		ent->v.dmg_save = 0;
	}

	// a fixangle might get lost in a dropped packet.  Oh well.
	if ( ent->v.fixangle )
	{
		MSG_WriteByte (msg, svc_setangle);
																									dummyMethod3();
		for (i=0 ; i < 3 ; i++)
			MSG_WriteAngle (msg, ent->v.angles[i] );
		ent->v.fixangle = 0;
	}
}

/*
=======================
SV_UpdateClientStats

Performs a delta update of the stats array.  This should only be performed
when a reliable message can be delivered this frame.
=======================
*/
TM_CALLABLE
void SV_UpdateClientStats (client_t *client)
{
	edict_t	*ent;
	int		stats[MAX_CL_STATS];
	int		i;
	
	ent = client->edict;
	Q_memset (stats, 0, sizeof(stats));
	
	// if we are a spectator and we are tracking a player, we get his stats
	// so our status bar reflects his
	if (client->spectator && client->spec_track > 0)
		ent = svs.clients[client->spec_track - 1].edict;

	stats[STAT_HEALTH] = ent->v.health;
	stats[STAT_WEAPON] = SV_ModelIndex(PR_GetString(ent->v.weaponmodel));
	stats[STAT_AMMO] = ent->v.currentammo;
	stats[STAT_ARMOR] = ent->v.armorvalue;
	stats[STAT_SHELLS] = ent->v.ammo_shells;
	stats[STAT_NAILS] = ent->v.ammo_nails;
	stats[STAT_ROCKETS] = ent->v.ammo_rockets;
	stats[STAT_CELLS] = ent->v.ammo_cells;
	if (!client->spectator)
		stats[STAT_ACTIVEWEAPON] = ent->v.weapon;
	// stuff the sigil bits into the high bits of items for sbar
	stats[STAT_ITEMS] = (int)ent->v.items | ((int)pr_global_struct->serverflags << 28);

			dummyMethod1();
	CRITICAL_MESSAGE(client->msg_lock, CLIENT_MSG_LOCK, client->clientId, {
		for (i=0 ; i<MAX_CL_STATS ; i++)
			if (stats[i] != client->stats[i])
			{
				client->stats[i] = stats[i];
				if (stats[i] >=0 && stats[i] <= 255)
				{
					ClientReliableWrite_Begin(client, svc_updatestat, 3);
					ClientReliableWrite_Byte(client, i);
					ClientReliableWrite_Byte(client, stats[i]);
				}
				else
				{
					ClientReliableWrite_Begin(client, svc_updatestatlong, 6);
					ClientReliableWrite_Byte(client, i);
					ClientReliableWrite_Long(client, stats[i]);
				}
			}
	});
			dummyMethod2();
}

/*
=======================
SV_SendClientDatagram
=======================
*/
TM_CALLABLE
qboolean SV_SendClientDatagram (client_t *client)
{
	byte		buf[MAX_DATAGRAM];
	sizebuf_t	msg;

	msg.data = buf;
	msg.maxsize = sizeof(buf);
	msg.cursize = 0;
	msg.allowoverflow = true;
	msg.overflowed = false;

	// add the client specific data to the datagram
	SV_WriteClientdataToMessage (client, &msg);

	// send over all the objects that are in the PVS
	// this will include clients, a packetentities, and
	// possibly a nails update
	SV_WriteEntitiesToClient (client, &msg);

	// copy the accumulated multicast datagram
	// for this client out to the message
	if (client->datagram.overflowed)
		Con_Printf ("WARNING: datagram overflowed for %s\n", client->name);
	else
		SZ_Write (&msg, client->datagram.data, client->datagram.cursize);

	SZ_Clear (&client->datagram);

	// send deltas over reliable stream
	if (Netchan_CanReliable (&client->netchan))
		SV_UpdateClientStats (client);

	if (msg.overflowed)
	{
		Con_Printf ("WARNING: msg overflowed for %s\n", client->name);
		SZ_Clear (&msg);
	}

	// send the datagram
	Netchan_Transmit (&client->netchan, msg.cursize, buf);
																									dummyMethod4();

	return true;
}



/*
=======================
SV_SendMessagesToAll

FIXME: does this sequence right?
=======================
*/
void SV_SendMessagesToAll (void)
{
    int     i;
    client_t  *c;

																																																															dummyMethod3();
    for (i=0, c = svs.clients ; i<MAX_CLIENTS ; i++, c++)
        if (c->state)   // FIXME: should this only send to active?
            c->send_message = true;

    SV_SendClientMessages ();
}


/*
GAJA:
=======================
SV_UpdateAverageFrametime

Sends server average frametime to all clients
=======================
*/
void SV_UpdateAverageFrametime()
																																																															dummyMethod4();
{
    int     i;
    client_t  *c;

																																																															dummyMethod3();
    for (i=0, c = svs.clients ; i<MAX_CLIENTS ; i++, c++)
    {
        if (c->state > cs_connected)
        {
            if (c->netchan.message.cursize + 5 <= c->netchan.message.maxsize) 
            {
                MSG_WriteByte (&c->netchan.message, svc_frametime);
                MSG_WriteFloat(&c->netchan.message, srv_frametime_avg);
            }
            else
                Con_Printf("OOOPS: Didn't send the average frametime for client %d!\n", i);
        }
    }
}


#if (1)
																																																															dummyMethod4();

/*
=======================
SV_UpdateToReliableMessages
=======================
*/
void SV_UpdateToReliableMessages (void)
{
	int			i, j;
	client_t *client;
	eval_t *val;
	edict_t *ent;


	// GAJA parallelize
	dummyMethod1();
	#pragma omp parallel for schedule(dynamic,1) shared(svs, sv) private(i, j, client, ent, val)

	// check for changes to be sent over the reliable streams to all clients
	for (i=0; i<MAX_CLIENTS ; i++)
	dummyMethod2();
	{
		host_client = &svs.clients[i];

		if (host_client->state != cs_spawned)
			continue;


		inTransaction = true;

		//GAJA start transaction
		LOCK(global_lock)
		TRANSACTION

		// GAJA lock host_client
		CRITICAL_MESSAGE(host_client->msg_lock, CLIENT_MSG_LOCK, host_client->clientId, {
			if (host_client->sendinfo)
			{
				host_client->sendinfo = false;
				// GAJA: No need for critical section - data is only read								
				SV_FullClientUpdate (host_client, &sv.reliable_datagram);
			}
			if (host_client->old_frags != host_client->edict->v.frags)
			{
				for (j=0, client = svs.clients ; j<MAX_CLIENTS ; j++, client++)
				{
					if (client->state < cs_connected)
						continue;

					ClientReliableWrite_Begin(client, svc_updatefrags, 4);
					ClientReliableWrite_Byte(client, i);
					ClientReliableWrite_Short(client, host_client->edict->v.frags);
				}

				host_client->old_frags = host_client->edict->v.frags;
			}

			// maxspeed/entgravity changes
			ent = host_client->edict;

			val = GetEdictFieldValue(ent, "gravity");
			if (val && host_client->entgravity != val->_float) {
				host_client->entgravity = val->_float;
				ClientReliableWrite_Begin(host_client, svc_entgravity, 5);
				ClientReliableWrite_Float(host_client, host_client->entgravity);
			}
			val = GetEdictFieldValue(ent, "maxspeed");
			if (val && host_client->maxspeed != val->_float) {
				host_client->maxspeed = val->_float;
				ClientReliableWrite_Begin(host_client, svc_maxspeed, 5);
				ClientReliableWrite_Float(host_client, host_client->maxspeed);
			}
		});

		TRANSACTION_END
		UNLOCK(global_lock)
		
		inTransaction = false;

		// send messages and packets generated during transaction
		FlushTMOutput();
	} 

	if (sv.datagram.overflowed)
		SZ_Clear (&sv.datagram);

	// append the broadcast messages to each client messages
																							dummyMethod1();
	#pragma omp parallel for schedule(dynamic,1) private(j, client) shared(sv, svs)
	for (j=0 ; j<MAX_CLIENTS ; j++)
	{
		client = &svs.clients[j];
		if (client->state < cs_connected)
			continue;	// reliables go to all connected or spawned

		//CRITICAL_MESSAGE(client->msg_lock, CLIENT_MSG_LOCK, client->clientId)
			// GAJA: No need for critical section - data is only read
//			ClientReliableCheckBlock(client, sv.reliable_datagram.cursize);
//			ClientReliableWrite_SZ(client, sv.reliable_datagram.data, sv.reliable_datagram.cursize);
//		});

		if (client->state != cs_spawned)
			continue;	// datagrams only go to spawned
		// GAJA: No need for critical section - data is only read
		SZ_Write (&client->datagram, sv.datagram.data, sv.datagram.cursize);
	}

	SZ_Clear (&sv.reliable_datagram);
	SZ_Clear (&sv.datagram);
}



/*
=======================
SV_SendClientMessages
=======================
*/
void SV_SendClientMessages (void)
{
    int			i, j;
    client_t	*c;


    DEBUGPRINT(SEND_REPLY,MEDIUM) printf("In Send parallel\n");

    omp_set_num_threads(NoThreads);

    // update frags, names, etc
    // GAJA parallelized with omp and transactions
    SV_UpdateToReliableMessages ();

    // GAJA: send server average frame time to all clients if we have a new value
    SV_UpdateAverageFrametime(); //if ((framecount % 16) == 0) SV_UpdateAverageFrametime();

    // build individual updates
    c = svs.clients;

    // --------------------------------------
    // GAJA parallelization
															dummyMethod1();
    #pragma omp parallel for schedule(dynamic,1) shared(svs, sv,  realtime, net_socket, sv_nailmodel, sv_supernailmodel, sv_playermodel) private(i, j, c)
    for (i=0; i<MAX_CLIENTS ; i++)
    {
        c = &svs.clients[i];
        if (!c->state)
            continue;


        int ThreadId = ThreadNumber();
        inTransaction = true;

        // GAJA start transaction
        LOCK(global_lock)
        TRANSACTION
            if (c->drop) 
            {
                SV_DropClient(c);
                c->drop = false;
            }
            else
            {
                // check to see if we have a backbuf to stick in the reliable
                if (c->num_backbuf) 
                {
                    // will it fit?
                    if (c->netchan.message.cursize + c->backbuf_size[0] < c->netchan.message.maxsize) 
                    {
                        Con_DPrintf("%s: backbuf %d bytes\n", c->name, c->backbuf_size[0]);

                        // it'll fit
                        SZ_Write(&c->netchan.message, c->backbuf_data[0], c->backbuf_size[0]);

                        //move along, move along
                        for (j = 1; j < c->num_backbuf; j++) 
                        {
                            Q_memcpy(c->backbuf_data[j - 1], c->backbuf_data[j], c->backbuf_size[j]);
                            c->backbuf_size[j - 1] = c->backbuf_size[j];
                        }

                        c->num_backbuf--;
                        if (c->num_backbuf) {
                            Q_memset(&c->backbuf, 0, sizeof(c->backbuf));
                            c->backbuf.data = c->backbuf_data[c->num_backbuf - 1];
                            c->backbuf.cursize = c->backbuf_size[c->num_backbuf - 1];
                            c->backbuf.maxsize = sizeof(c->backbuf_data[c->num_backbuf - 1]);
                        }
                    }
                }


                // if the reliable message overflowed,
                // drop the client
                if (c->netchan.message.overflowed)
                {
                    SZ_Clear (&c->netchan.message);
                    SZ_Clear (&c->datagram);
                    SV_BroadcastPrintf (PRINT_HIGH, "%s overflowed\n", c->name);
                    Con_Printf ("WARNING: reliable overflow for %s\n",c->name);
                    SV_DropClient (c);
                    c->send_message = true;
                    c->netchan.cleartime = 0;	// don't choke this message
                }

                // only send messages if the client has sent one
                // and the bandwidth is not choked
                if (c->send_message)
                {
                    DEBUGPRINT(SEND_REPLY,HIGH) PRINT("Thread: %d\tShould send to %s\n", ThreadId, c->name);
                    c->send_message = false;	// try putting this after choke?
                    if (!sv.paused && !Netchan_CanPacket (&c->netchan))
                    {
                        DEBUGPRINT(SEND_REPLY,HIGH) PRINT("Thread: %d\tChoke for %s\n", ThreadId, c->name);
                        c->chokecount++; // bandwidth choke
                    }
                    else
                    {
                        if (c->state == cs_spawned)
                            SV_SendClientDatagram (c);
                        else
                            Netchan_Transmit (&c->netchan, 0, NULL);	// just update reliable
                    }
                }
            }

        TRANSACTION_END
        UNLOCK(global_lock)
															dummyMethod2();

            inTransaction = false;

        // send messages and packets generated during transaction
        FlushTMOutput();

    }
}



#else




void SV_UpdateToReliableMessages (void)
																							dummyMethod2();
{
    int     	i, j;
    client_t 	*client;
    eval_t 		*val;
    edict_t 	*ent;

    // check for changes to be sent over the reliable streams to all clients
    for (i=0, host_client = svs.clients ; i<MAX_CLIENTS ; i++, host_client++)
    {
        if (host_client->state != cs_spawned)
            continue;
        if (host_client->sendinfo)
        {
            host_client->sendinfo = false;
            SV_FullClientUpdate (host_client, &sv.reliable_datagram);
        }
        if (host_client->old_frags != host_client->edict->v.frags)
        {
            for (j=0, client = svs.clients ; j<MAX_CLIENTS ; j++, client++)
            {
                if (client->state < cs_connected)
                    continue;
                ClientReliableWrite_Begin(client, svc_updatefrags, 4);
                ClientReliableWrite_Byte(client, i);
                ClientReliableWrite_Short(client, host_client->edict->v.frags);
            }

            host_client->old_frags = host_client->edict->v.frags;
        }

        // maxspeed/entgravity changes
        ent = host_client->edict;

        val = GetEdictFieldValue(ent, "gravity");
        if (val && host_client->entgravity != val->_float) {
            host_client->entgravity = val->_float;
            ClientReliableWrite_Begin(host_client, svc_entgravity, 5);
            ClientReliableWrite_Float(host_client, host_client->entgravity);
        }
        val = GetEdictFieldValue(ent, "maxspeed");
        if (val && host_client->maxspeed != val->_float) {
            host_client->maxspeed = val->_float;
            ClientReliableWrite_Begin(host_client, svc_maxspeed, 5);
            ClientReliableWrite_Float(host_client, host_client->maxspeed);
        }

    }

    if (sv.datagram.overflowed)
        SZ_Clear (&sv.datagram);

    // append the broadcast messages to each client messages
    for (j=0, client = svs.clients ; j<MAX_CLIENTS ; j++, client++)
    {
        if (client->state < cs_connected)
            continue; // reliables go to all connected or spawned

        ClientReliableCheckBlock(client, sv.reliable_datagram.cursize);
        ClientReliableWrite_SZ(client, sv.reliable_datagram.data, sv.reliable_datagram.cursize);

        if (client->state != cs_spawned)
            continue; // datagrams only go to spawned
        SZ_Write (&client->datagram
                , sv.datagram.data
                , sv.datagram.cursize);
    }

    SZ_Clear (&sv.reliable_datagram);
    SZ_Clear (&sv.datagram);
}


/*
=======================
SV_SendClientMessages
=======================
*/
void SV_SendClientMessages (void)
{
    int     i, j;
    client_t  *c;

    // update frags, names, etc
    SV_UpdateToReliableMessages ();

    // GAJA: send server average frame time to all clients if we have a new value
    SV_UpdateAverageFrametime(); //if ((framecount % 16) == 0) SV_UpdateAverageFrametime();

    // build individual updates
    for (i=0, c = svs.clients ; i<MAX_CLIENTS ; i++, c++)
    {
        if (!c->state)
            continue;

        if (c->drop) {
            SV_DropClient(c);
            c->drop = false;
            continue;
        }

        // check to see if we have a backbuf to stick in the reliable
        if (c->num_backbuf) {
            // will it fit?
            if (c->netchan.message.cursize + c->backbuf_size[0] <
                    c->netchan.message.maxsize) {

                Con_DPrintf("%s: backbuf %d bytes\n",
                        c->name, c->backbuf_size[0]);

                // it'll fit
                SZ_Write(&c->netchan.message, c->backbuf_data[0],
                        c->backbuf_size[0]);

                //move along, move along
                for (j = 1; j < c->num_backbuf; j++) {
                    memcpy(c->backbuf_data[j - 1], c->backbuf_data[j],
                            c->backbuf_size[j]);
                    c->backbuf_size[j - 1] = c->backbuf_size[j];
                }

                c->num_backbuf--;
                if (c->num_backbuf) {
                    memset(&c->backbuf, 0, sizeof(c->backbuf));
                    c->backbuf.data = c->backbuf_data[c->num_backbuf - 1];
                    c->backbuf.cursize = c->backbuf_size[c->num_backbuf - 1];
                    c->backbuf.maxsize = sizeof(c->backbuf_data[c->num_backbuf - 1]);
                }
            }
        }

        // if the reliable message overflowed,
        // drop the client
        if (c->netchan.message.overflowed)
        {
            SZ_Clear (&c->netchan.message);
            SZ_Clear (&c->datagram);
            SV_BroadcastPrintf (PRINT_HIGH, "%s overflowed\n", c->name);
            Con_Printf ("WARNING: reliable overflow for %s\n",c->name);
            SV_DropClient (c);
            c->send_message = true;
            c->netchan.cleartime = 0; // don't choke this message
        }

        // only send messages if the client has sent one
        // and the bandwidth is not choked
        if (!c->send_message)
            continue;
        c->send_message = false;  // try putting this after choke?
        if (!sv.paused && !Netchan_CanPacket (&c->netchan))
        {
            c->chokecount++;
            continue;   // bandwidth choke
        }

        if (c->state == cs_spawned)
            SV_SendClientDatagram (c);
        else
            Netchan_Transmit (&c->netchan, 0, NULL);  // just update reliable

    }
}


#endif
int dummyMethod1(){
    return 0;
}
int dummyMethod2(){
    return 0;
}
int dummyMethod3(){
    return 0;
}
int dummyMethod4(){
    return 0;
}