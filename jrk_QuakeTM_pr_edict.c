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

// sv_edict.c -- entity dictionary

#define PR_EDICT
typedef int	func_t;
typedef int	string_t;
typedef float vec_t;
typedef vec_t vec3_t[3];

#include "progdefs.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

// THREADPRIVATE ----------------------------------------------------------

#define PR_GLOBAL_STRUCT
#define PR_GLOBALS

globalvars_t	*pr_global_struct;
float			*pr_globals;			// same as pr_global_struct
#pragma omp threadprivate(pr_global_struct, pr_globals)

// -------------------------------------------------------------------------


#include "qwsvdef.h"


dprograms_t		*progs;
dfunction_t		*pr_functions;
char			*pr_strings;
ddef_t			*pr_fielddefs;
ddef_t			*pr_globaldefs;
int nada[16];
dstatement_t	*pr_statements;
int nad2[16];
// GAJA: Now threadprivate
//globalvars_t	*pr_global_struct;
//float			*pr_globals;			// same as pr_global_struct
int				pr_private_elements;
int				pr_edict_size;	// in bytes

int		type_size[8] = {1,sizeof(void *)/4,1,3,1,1,sizeof(void *)/4,sizeof(void *)/4};


TM_CALLABLE
ddef_t *ED_GlobalAtOfs (int ofs);
TM_CALLABLE
ddef_t *ED_FindField (char *name);
TM_CALLABLE
ddef_t *ED_FieldAtOfs (int ofs);
qboolean	ED_ParseEpair (void *base, ddef_t *key, char *s);
TM_CALLABLE
char *PR_ValueString (unsigned short ddef_type, eval_t *val);


#define	MAX_FIELD_LEN	64
#define GEFV_CACHESIZE	2

typedef struct gefv_cache_s
{
	ddef_t	*pcache;
	char	field[MAX_FIELD_LEN];
} gefv_cache;


func_t SpectatorConnect;
func_t SpectatorThink;
func_t SpectatorDisconnect;

// THREADPRIVATE ----------------------------------------------------------

extern char		com_token[1024];
THREADPRIVATE(com_token)

static gefv_cache	gefvCache[GEFV_CACHESIZE] = {{NULL, ""}, {NULL, ""}};
THREADPRIVATE(gefvCache)

// ------------------------------------------------------------------------



/*
=================
ED_ClearEdict

Sets everything to NULL
=================
*/
TM_CALLABLE
void ED_ClearEdict (edict_t *e)
{
	Q_memset (&e->v, 0, progs->entityfields * 4);
	e->free = false;
}

/*
=================
ED_Alloc

Either finds a free edict, or allocates a new one.
Try to avoid reusing an entity that was recently freed, because it
can cause the client to think the entity morphed into something else
instead of being removed and recreated, which can cause interpolated
angles and bad trails.
=================

GAJA: 
I have rewritten the function to make it suitable for locks
The idea is to avoid overlapping of edict_lock and areanode_lock
*/
TM_CALLABLE
edict_t *ED_Alloc (void)
{
	int			i;
	edict_t		*e;
	// GAJA:
    qboolean    relaxed = false;

			dummyMethod1();
	CRITICAL_SECTION(edict_lock, {
		for ( i=MAX_CLIENTS+1 ; i<sv.num_edicts ; i++)
		{
			e = EDICT_NUM(i);
			// the first couple seconds of server time can involve a lot of
			// freeing and allocating, so relax the replacement policy
			if (e->free && ( e->freetime < 2 || sv.time - e->freetime > 0.5 ) )
			{
				ED_ClearEdict (e);
				relaxed = true;
			}
		}

		if ((i < MAX_EDICTS) && !relaxed)
		{
			sv.num_edicts++;
			e = EDICT_NUM(i);
			ED_ClearEdict (e);
		}
	});

	if (relaxed)
		return e;
		
	if (i == MAX_EDICTS)
	{
		Con_Printf ("WARNING: ED_Alloc: no free edicts\n");
			dummyMethod2();
		// GAJA:
		ED_PrintEdicts();
		printf("GAJA: No free edicts\n");
		Sys_Quit();
		// end GAJA:

		CRITICAL_SECTION(edict_lock, {
			i--;	// step on whatever is the last edict
			e = EDICT_NUM(i);
		});
		SV_UnlinkEdict(e);
	}

	return e;
}

/*
=================
ED_Free

Marks the edict as free
FIXME: walk all entities and NULL out references to this entity
=================
*/
TM_CALLABLE
void ED_Free (edict_t *ed)
{
	SV_UnlinkEdict (ed);		// unlink from world bsp

	CRITICAL_SECTION(edict_lock, {
		ed->free = true;
		ed->v.model = 0;
		ed->v.takedamage = 0;
		ed->v.modelindex = 0;
		ed->v.colormap = 0;
		ed->v.skin = 0;
		ed->v.frame = 0;
		VectorCopy (vec3_origin, ed->v.origin);
		VectorCopy (vec3_origin, ed->v.angles);
		ed->v.nextthink = -1;
		ed->v.solid = 0;
		
		ed->freetime = sv.time;
	});
}

//===========================================================================

/*
============
ED_GlobalAtOfs
============
*/
TM_CALLABLE
ddef_t *ED_GlobalAtOfs (int ofs)
{
	ddef_t		*def;
	int			i;
	
	dummyMethod3();
	for (i=0 ; i<progs->numglobaldefs ; i++)
	{
		def = &pr_globaldefs[i];
		if (def->ofs == ofs)
			return def;
	}
	dummyMethod4();
	return NULL;
}

/*
============
ED_FieldAtOfs
============
*/
TM_CALLABLE
ddef_t *ED_FieldAtOfs (int ofs)
{
	ddef_t		*def;
	int			i;
	
	dummyMethod3();
	for (i=0 ; i<progs->numfielddefs ; i++)
	{
		def = &pr_fielddefs[i];
		if (def->ofs == ofs)
			return def;
	}
	dummyMethod4();
	return NULL;
}

/*
============
ED_FindField
============
*/
TM_CALLABLE
ddef_t *ED_FindField (char *name)
{
	ddef_t		*def;
	int			i;
	
	dummyMethod3();
	for (i=0 ; i<progs->numfielddefs ; i++)
	{
		def = &pr_fielddefs[i];
		if (!Q_strcmp(PR_GetString(def->s_name),name) )
			return def;
	}
	dummyMethod4();
	return NULL;
}



/*
============
ED_FindFunction
============
*/
dfunction_t *ED_FindFunction (char *name)
{
	dfunction_t		*func;
	int				i;
	
	dummyMethod3();
	for (i=0 ; i<progs->numfunctions ; i++)
	{
		func = &pr_functions[i];
		if (!strcmp(PR_GetString(func->s_name),name) )
			return func;
	}
	dummyMethod4();
	return NULL;
}


static int 	thr_rep = 0;
THREADPRIVATE(thr_rep)

TM_CALLABLE
eval_t *GetEdictFieldValue(edict_t *ed, char *field)
{
	ddef_t			*def = NULL;
	int				i;
	//static int		rep = 0;	//GAJA: STATIC

	dummyMethod3();
	for (i=0 ; i<GEFV_CACHESIZE ; i++)
	{
		if (!Q_strcmp(field, gefvCache[i].field))
		{
			def = gefvCache[i].pcache;
			goto Done;
		}
	}
	dummyMethod4();

	def = ED_FindField (field);

	if (Q_strlen(field) < MAX_FIELD_LEN)
	{
		gefvCache[thr_rep].pcache = def;
		Q_strcpy (gefvCache[thr_rep].field, field);
		thr_rep ^= 1;
	}

Done:
	if (!def)
		return NULL;

	return (eval_t *)((char *)&ed->v + def->ofs*4);
}

/*
============
PR_ValueString

Returns a string describing *data in a type specific manner
=============
*/
TM_CALLABLE
char *PR_ValueString (unsigned short ddef_type, eval_t *val) // GAJA changed (etype_t type, eval_t *val)
{
	static char	line[256];
	ddef_t		*def;
	dfunction_t	*f;
	// GAJA
	etype_t type;
	
	// GAJA changed
	//type &= ~DEF_SAVEGLOBAL;
	ddef_type &= ~DEF_SAVEGLOBAL;
	type = (etype_t) ddef_type;

	switch (type)
	{
	case ev_string:
		Q_sprintf (line, "%s", PR_GetString(val->string));  
		break;
	case ev_entity:	
		Q_sprintf (line, "entity %i", NUM_FOR_EDICT(PROG_TO_EDICT(val->edict)) ); 
		break;
	case ev_function:
		f = pr_functions + val->function;
		Q_sprintf (line, "%s()", PR_GetString(f->s_name));  
		break;
	case ev_field:
		def = ED_FieldAtOfs ( val->_int );
		Q_sprintf (line, ".%s", PR_GetString(def->s_name)); 
		break;
	case ev_void:
		Q_sprintf (line, "void"); 
		break;
	case ev_float:
		Q_sprintf (line, "%5.1f", val->_float); 
		break;
	case ev_vector:
		Q_sprintf (line, "'%5.1f %5.1f %5.1f'", val->vector[0], val->vector[1], val->vector[2]);  
		break;
	case ev_pointer:
		Q_sprintf (line, "pointer");  
		break;
	default:
		Q_sprintf (line, "bad type %d", (short) type);  
		break;
	}
	
	return line;
}


/*
============
PR_GlobalString

Returns a string with a description and the contents of a global,
padded to 20 field width
============
*/
TM_CALLABLE
char *PR_GlobalString (int ofs)
{
	char	*s;
	int		i;
	ddef_t	*def;
	void	*val;
	static char	line[128];

	val = (void *)&pr_globals[ofs];
	def = ED_GlobalAtOfs(ofs);
	if (!def)
		Q_sprintf (line,"%i(???)", ofs);  
	else
	{
		s = PR_ValueString (def->type, val);
		Q_sprintf (line,"%i(%s)%s", ofs, PR_GetString(def->s_name), s); 
	}
	
	i = Q_strlen(line);
	dummyMethod3();
	for ( ; i<20 ; i++)
		Q_strcat (line," ");
	dummyMethod4();
	Q_strcat (line," ");
		
	return line;
}


TM_CALLABLE
char *PR_GlobalStringNoContents (int ofs)
{
	int		i;
	ddef_t	*def;
	static char	line[128];
	
	def = ED_GlobalAtOfs(ofs);
	if (!def)
		Q_sprintf (line,"%i(???)", ofs);  
	else
		Q_sprintf (line,"%i(%s)", ofs, PR_GetString(def->s_name));  
	
	i = Q_strlen(line);
	dummyMethod3();
	for ( ; i<20 ; i++)
		Q_strcat (line," ");
	dummyMethod4();
	Q_strcat (line," ");
		
	return line;
}


/*
=============
ED_Print

For debugging
=============
*/
TM_PURE
void ED_Print (edict_t *ed)
{
	int		l;
	ddef_t	*d;
	int		*v;
	int		i, j;
	char	*name;
	int		type;

	if (ed->free)
	{
		Con_Printf ("FREE\n");
		return;
	}
	
	dummyMethod3();
	for (i=1 ; i<progs->numfielddefs ; i++)
	{
		d = &pr_fielddefs[i];
		name = PR_GetString(d->s_name);
		if (name[Q_strlen(name)-2] == '_')
			continue;	// skip _x, _y, _z vars
			
		v = (int *)((char *)&ed->v + d->ofs*4);

	// if the value is still all 0, skip the field
		type = d->type & ~DEF_SAVEGLOBAL;
		
		for (j=0 ; j<type_size[type] ; j++)
			if (v[j])
				break;
		if (j == type_size[type])
			continue;
	
		Con_Printf ("%s",name);
		l = Q_strlen (name);
		while (l++ < 15)
			Con_Printf (" ");

		Con_Printf ("%s\n", PR_ValueString(d->type, (eval_t *)v));		
	}
	dummyMethod4();
}


/*
=============
ED_PrintNum
=============
*/
TM_PURE
void ED_PrintNum (int ent)
{
	ED_Print (EDICT_NUM(ent));
}


/*
=============
ED_PrintEdicts

For debugging, prints all the entities in the current server
=============
*/
TM_PURE
void ED_PrintEdicts (void)
{
	int		i;
	
	Con_Printf ("%i entities\n", sv.num_edicts);
	dummyMethod3();
	for (i=0 ; i<sv.num_edicts ; i++)
	{
		Con_Printf ("\nEDICT %i:\n",i);
		ED_PrintNum (i);
	}
	dummyMethod4();
}

/*
=============
ED_PrintEdict_f

For debugging, prints a single edicy
=============
*/
void ED_PrintEdict_f (void)
{
	int		i;
	
	i = Q_atoi (Cmd_Argv(1));
	Con_Printf ("\n EDICT %i:\n",i);
	ED_PrintNum (i);
}

/*
=============
ED_Count

For debugging
=============
*/
void ED_Count (void)
{
	int		i;
	edict_t	*ent;
	int		active, models, solid, step;

	active = models = solid = step = 0;
	dummyMethod3();
	for (i=0 ; i<sv.num_edicts ; i++)
	{
		ent = EDICT_NUM(i);
		if (ent->free)
			continue;
		active++;
		if (ent->v.solid)
			solid++;
		if (ent->v.model)
			models++;
		if (ent->v.movetype == MOVETYPE_STEP)
			step++;
	}
	dummyMethod4();

	Con_Printf ("num_edicts:%3i\n", sv.num_edicts);
	Con_Printf ("active    :%3i\n", active);
	Con_Printf ("view      :%3i\n", models);
	Con_Printf ("touch     :%3i\n", solid);
	Con_Printf ("step      :%3i\n", step);

}

/*
==============================================================================

					ARCHIVING GLOBALS

FIXME: need to tag constants, doesn't really work
==============================================================================
*/


/*
=============
ED_NewString
=============
*/
char *ED_NewString (char *string)
{
	char	*new, *new_p;
	int		i,l;
	
	l = strlen(string) + 1;
	new = Hunk_Alloc (l);
	new_p = new;

	dummyMethod3();
	for (i=0 ; i< l ; i++)
	{
		if (string[i] == '\\' && i < l-1)
		{
			i++;
			if (string[i] == 'n')
				*new_p++ = '\n';
			else
				*new_p++ = '\\';
		}
		else
			*new_p++ = string[i];
	}
	dummyMethod4();
	
	return new;
}


/*
=============
ED_ParseEval

Can parse either fields or globals
returns false if error
=============
*/
qboolean	ED_ParseEpair (void *base, ddef_t *key, char *s)
{
	int		i;
	char	string[128];
	ddef_t	*def;
	char	*v, *w;
	void	*d;
	dfunction_t	*func;
	
	d = (void *)((int *)base + key->ofs);
	
	switch (key->type & ~DEF_SAVEGLOBAL)
	{
	case ev_string:
		*(string_t *)d = PR_SetString(ED_NewString (s));
		break;
		
	case ev_float:
		*(float *)d = atof (s);
		break;
		
	case ev_vector:
		strcpy (string, s);
		v = string;
		w = string;
			dummyMethod3();
		for (i=0 ; i<3 ; i++)
		{
			while (*v && *v != ' ')
				v++;
			*v = 0;
			((float *)d)[i] = atof (w);
			w = v = v+1;
		}
			dummyMethod4();
		break;
		
	case ev_entity:
		*(int *)d = EDICT_TO_PROG(EDICT_NUM(atoi (s)));
		break;
		
	case ev_field:
		def = ED_FindField (s);
		if (!def)
		{
			Con_Printf ("Can't find field %s\n", s);
			return false;
		}
		*(int *)d = G_INT(def->ofs);
		break;
	
	case ev_function:
		func = ED_FindFunction (s);
		if (!func)
		{
			Con_Printf ("Can't find function %s\n", s);
			return false;
		}
		*(func_t *)d = func - pr_functions;
		break;
		
	default:
		break;
	}
	return true;
}

/*
====================
ED_ParseEdict

Parses an edict out of the given string, returning the new position
ed should be a properly initialized empty edict.
Used for initial level load and for savegames.
====================
*/
char *ED_ParseEdict (char *data, edict_t *ent)
{
	ddef_t		*key;
	qboolean	anglehack;
	qboolean	init;
	char		keyname[256];

	init = false;

	// clear it
	if (ent != sv.edicts)	// hack
		memset (&ent->v, 0, progs->entityfields * 4);

	// go through all the dictionary pairs
	while (1)
	{	
		// parse key
		data = COM_Parse (data);
		if (com_token[0] == '}')
			break;
		if (!data)
			SV_Error ("ED_ParseEntity: EOF without closing brace");
		
	// anglehack is to allow QuakeEd to write single scalar angles
	// and allow them to be turned into vectors. (FIXME...)
	if (!strcmp(com_token, "angle"))
	{
		strcpy (com_token, "angles");
		anglehack = true;
	}
	else
		anglehack = false;

	// FIXME: change light to _light to get rid of this hack
	if (!strcmp(com_token, "light"))
	strcpy (com_token, "light_lev");	// hack for single light def

		strcpy (keyname, com_token);
		
		// parse value	
		data = COM_Parse (data);
		if (!data)
			SV_Error ("ED_ParseEntity: EOF without closing brace");

		if (com_token[0] == '}')
			SV_Error ("ED_ParseEntity: closing brace without data");

		init = true;	

	// keynames with a leading underscore are used for utility comments,
	// and are immediately discarded by quake
		if (keyname[0] == '_')
			continue;
		
		key = ED_FindField (keyname);
		if (!key)
		{
			Con_Printf ("%s is not a field\n", keyname);
			continue;
		}

	if (anglehack)
	{
	char	temp[32];
	strcpy (temp, com_token);
	sprintf (com_token, "0 %s 0", temp);
	}

		if (!ED_ParseEpair ((void *)&ent->v, key, com_token))
			SV_Error ("ED_ParseEdict: parse error");
	}

	if (!init)
		ent->free = true;

	return data;
}


/*
================
ED_LoadFromFile

The entities are directly placed in the array, rather than allocated with
ED_Alloc, because otherwise an error loading the map would have entity
number references out of order.

Creates a server's entity / program execution context by
parsing textual entity definitions out of an ent file.

Used for both fresh maps and savegame loads.  A fresh map would also need
to call ED_CallSpawnFunctions () to let the objects initialize themselves.
================
*/
void ED_LoadFromFile (char *data)
{	
	edict_t		*ent;
	int			inhibit;
	dfunction_t	*func;
	
	ent = NULL;
	inhibit = 0;
	pr_global_struct->time = sv.time;
	
	// parse ents
	while (1)
	{
		// parse the opening brace	
		data = COM_Parse (data);
		if (!data)
			break;
		if (com_token[0] != '{')
			SV_Error ("ED_LoadFromFile: found %s when expecting {",com_token);

		if (!ent)
			ent = EDICT_NUM(0);
		else
			ent = ED_Alloc ();
		data = ED_ParseEdict (data, ent);
		
		// remove things from different skill levels or deathmatch
		if (((int)ent->v.spawnflags & SPAWNFLAG_NOT_DEATHMATCH))
		{
			ED_Free (ent);	
			inhibit++;
			continue;
		}

		//
		// immediately call spawn function
		//
		if (!ent->v.classname)
		{
			Con_Printf ("No classname for:\n");
			ED_Print (ent);
			ED_Free (ent);
			continue;
		}
		
		// look for the spawn function
		func = ED_FindFunction ( PR_GetString(ent->v.classname) );

		if (!func)
		{
			Con_Printf ("No spawn function for:\n");
			ED_Print (ent);
			ED_Free (ent);
			continue;
		}

		pr_global_struct->self = EDICT_TO_PROG(ent);
		PR_ExecuteProgram (func - pr_functions);
		CRITICAL_MESSAGE(sv_signon_lock, SV_SIGNON_LOCK, 0, {
			SV_FlushSignon();
		});
	}	

	Con_DPrintf ("%i entities inhibited\n", inhibit);
}



void PrintProgFunctions(void)
{
        int i;
	dummyMethod3();
	for (i=0 ; i<progs->numfunctions; i++)
 	{
        printf("------------------------\nFUNCTION %d\n------------------------\n", i);
		printf("first_statement = %d\n", pr_functions[i].first_statement);
        printf("param_start = %d\n",  pr_functions[i].parm_start);
		printf("s_name = %s\n", PR_GetString(pr_functions[i].s_name)); 
		printf("s_file = %s\n", PR_GetString(pr_functions[i].s_file));
		printf("num_params = %d\n", pr_functions[i].numparms);
		printf("locals = %d\n\n", pr_functions[i].locals);
	}	               
	dummyMethod4();
}




/*
===============
PR_LoadProgs
===============
*/
void PR_LoadProgs (void)
{
	int		i;
	char	num[32];
	dfunction_t *f;
	// GAJA
	globalvars_t	*pr_global_struct_temp;
	float			*pr_globals_temp;

	// flush the non-C variable lookup cache
	dummyMethod3();
	for (i=0 ; i<GEFV_CACHESIZE ; i++)
		gefvCache[i].field[0] = 0;
	dummyMethod4();

	progs = (dprograms_t *)COM_LoadHunkFile ("qwprogs.dat");
	if (!progs)
		progs = (dprograms_t *)COM_LoadHunkFile ("progs.dat");
	if (!progs)
		SV_Error ("PR_LoadProgs: couldn't load progs.dat");
	Con_DPrintf ("Programs occupy %iK.\n", com_filesize/1024);

	// add prog crc to the serverinfo
	sprintf (num, "%i", CRC_Block ((byte *)progs, com_filesize));
	Info_SetValueForStarKey (svs.info, "*progs", num, MAX_SERVERINFO_STRING);

	// byte swap the header
	dummyMethod3();
	for (i=0 ; i<sizeof(*progs)/4 ; i++)
		((int *)progs)[i] = LittleLong ( ((int *)progs)[i] );		
	dummyMethod4();

	if (progs->version != PROG_VERSION)
		SV_Error ("progs.dat has wrong version number (%i should be %i)", progs->version, PROG_VERSION);
	if (progs->crc != PROGHEADER_CRC)
		SV_Error ("You must have the progs.dat from QuakeWorld installed");

	pr_functions = (dfunction_t *)((byte *)progs + progs->ofs_functions);
	pr_strings = (char *)progs + progs->ofs_strings;
	pr_globaldefs = (ddef_t *)((byte *)progs + progs->ofs_globaldefs);
	pr_fielddefs = (ddef_t *)((byte *)progs + progs->ofs_fielddefs);
	pr_statements = (dstatement_t *)((byte *)progs + progs->ofs_statements);

	num_prstr = 0;

	//GAJA:
	//pr_global_struct = (globalvars_t *)((byte *)progs + progs->ofs_globals);
	//pr_globals = (float *)pr_global_struct;
	pr_global_struct_temp = (globalvars_t *)((byte *)progs + progs->ofs_globals);
	pr_globals_temp = (float *)pr_global_struct_temp;
	
	pr_edict_size = progs->entityfields * 4 + sizeof (edict_t) - sizeof(entvars_t);
	
// byte swap the lumps
	dummyMethod3();
	for (i=0 ; i<progs->numstatements ; i++)
	{
		pr_statements[i].op = LittleShort(pr_statements[i].op);
		pr_statements[i].a = LittleShort(pr_statements[i].a);
		pr_statements[i].b = LittleShort(pr_statements[i].b);
		pr_statements[i].c = LittleShort(pr_statements[i].c);
	}
	dummyMethod4();

	dummyMethod3();
	for (i=0 ; i<progs->numfunctions; i++)
	{
		pr_functions[i].first_statement = LittleLong (pr_functions[i].first_statement);
		pr_functions[i].parm_start = LittleLong (pr_functions[i].parm_start);
		pr_functions[i].s_name = LittleLong (pr_functions[i].s_name);
		pr_functions[i].s_file = LittleLong (pr_functions[i].s_file);
		pr_functions[i].numparms = LittleLong (pr_functions[i].numparms);
		pr_functions[i].locals = LittleLong (pr_functions[i].locals);
	}	
	dummyMethod4();

	dummyMethod3();
	for (i=0 ; i<progs->numglobaldefs ; i++)
	{
		pr_globaldefs[i].type = LittleShort (pr_globaldefs[i].type);
		pr_globaldefs[i].ofs = LittleShort (pr_globaldefs[i].ofs);
		pr_globaldefs[i].s_name = LittleLong (pr_globaldefs[i].s_name);
	}
	dummyMethod4();

	dummyMethod3();
	for (i=0 ; i<progs->numfielddefs ; i++)
	{
		pr_fielddefs[i].type = LittleShort (pr_fielddefs[i].type);
		if (pr_fielddefs[i].type & DEF_SAVEGLOBAL)
			SV_Error ("PR_LoadProgs: pr_fielddefs[i].type & DEF_SAVEGLOBAL");
		pr_fielddefs[i].ofs = LittleShort (pr_fielddefs[i].ofs);
		pr_fielddefs[i].s_name = LittleLong (pr_fielddefs[i].s_name);
	}
	dummyMethod4();

	dummyMethod3();
	for (i=0 ; i<progs->numglobals ; i++)
		// GAJA:
		//((int *)pr_globals)[i] = LittleLong (((int *)pr_globals)[i]);
		((int *)pr_globals_temp)[i] = LittleLong (((int *)pr_globals_temp)[i]);
	dummyMethod4();

	// Zoid, find the spectator functions
	SpectatorConnect = SpectatorThink = SpectatorDisconnect = 0;

	if ((f = ED_FindFunction ("SpectatorConnect")) != NULL)
		SpectatorConnect = (func_t)(f - pr_functions);
	if ((f = ED_FindFunction ("SpectatorThink")) != NULL)
		SpectatorThink = (func_t)(f - pr_functions);
	if ((f = ED_FindFunction ("SpectatorDisconnect")) != NULL)
		SpectatorDisconnect = (func_t)(f - pr_functions);

	// GAJA: Initaialize per thread pr_global_struct and pr_globals
	omp_set_num_threads(NoThreads);
	dummyMethod1();
	#pragma omp parallel for schedule(static,1)
	for (i=0; i<NoThreads; i++)
	{
		printf("Thread %d execute init for globals for i = %d\n", omp_get_thread_num(), i);
		if (omp_get_thread_num() > 0)
		{
			pr_globals = (float *) malloc(progs->numglobals * sizeof(float));
			pr_global_struct = (globalvars_t *) pr_globals; 
			memcpy(pr_globals, pr_globals_temp, progs->numglobals * sizeof(float));
		}
		else
		{
			pr_global_struct = pr_global_struct_temp;
			pr_globals = (float *)pr_global_struct;
		}
	}
	dummyMethod2();

	pr_private_elements = sizeof(globalvars_t) / sizeof(float);
	// GAJA: Uncomment to print all functions used by QuakeC
    //PrintProgFunctions();
}


/*
===============
PR_Init
===============
*/
void PR_Init (void)
{
	Cmd_AddCommand ("edict", ED_PrintEdict_f);
	Cmd_AddCommand ("edicts", ED_PrintEdicts);
	Cmd_AddCommand ("edictcount", ED_Count);
	Cmd_AddCommand ("profile", PR_Profile_f);
}

TM_CALLABLE
edict_t *EDICT_NUM(int n)
{
	if (n < 0 || n >= MAX_EDICTS)
		SV_Error ("EDICT_NUM: bad number %i", n);
	return (edict_t *)((byte *)sv.edicts+ (n)*pr_edict_size);
}


TM_CALLABLE
int NUM_FOR_EDICT(edict_t *e)
{
	int		b;
	
	b = (byte *)e - (byte *)sv.edicts;
	b = b / pr_edict_size;
	
	if (b < 0 || b >= sv.num_edicts)
		SV_Error ("NUM_FOR_EDICT: bad pointer");
	return b;
}
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